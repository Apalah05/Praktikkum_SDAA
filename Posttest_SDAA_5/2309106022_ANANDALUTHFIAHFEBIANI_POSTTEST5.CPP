#include <iostream>
#include <string>
using namespace std;

#define MAX 100

struct HasilTambang {
    string nama;
    int jumlah;
    HasilTambang* next;
};

HasilTambang* head = nullptr;
HasilTambang dataTambang[MAX];
int tambang = 0;

struct Stack {
    HasilTambang data[MAX];
    int top;
} stackTambang;

struct Queue {
    HasilTambang data[MAX];
    int front, rear;
} queueTambang;

void initStack() {
    stackTambang.top = -1;
}

bool isFull() {
    return stackTambang.top == MAX - 1;
}

bool isEmpty() {
    return stackTambang.top == -1;
}

void initQueue() {
    queueTambang.front = -1;
    queueTambang.rear = -1;
}

bool isQueueFull() {
    return (queueTambang.rear == MAX - 1);
}

bool isQueueEmpty() {
    return (queueTambang.front == -1 || queueTambang.front > queueTambang.rear);
}

HasilTambang* Linked(string nama, int jumlah) {
    HasilTambang* baru = new HasilTambang();
    baru->nama = nama;
    baru->jumlah = jumlah;
    baru->next = nullptr;
    return baru;
}

void Tampil() {
    if (tambang > 0) {
    cout << "Data Hasil Tambang Ditampilkan\n";
    for (int i = 0; i < tambang; i++) {
        cout << i + 1 << ". " << dataTambang[i].nama << " (Jumlah : " << dataTambang[i].jumlah << ")" << endl;
        }
    } else {
        cout << "<-- DATA HASIL TAMBANG KOSONG -->\n";
    }
}

void Tambah() {
    string nama;
    int jumlah;
    if (tambang < MAX) {
        cin.ignore();
        cout << "Tambah Data Hasil Tambang: ";
        getline(cin, dataTambang[tambang].nama);
        cout << "Jumlah Hasil Tambang: ";
        cin >> dataTambang[tambang].jumlah;
        
        HasilTambang* baru = Linked(dataTambang[tambang].nama, dataTambang[tambang].jumlah);
        if (head == nullptr) {
            head = baru;
        } else {
            HasilTambang* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = baru;
        }

        tambang++;
    } else {
        cout << "<-- DATA TAMBANG INVALID/PENUH -->\n";        
    }
}

void HitungNode() {
    int hitung = 0;
    HasilTambang* temp = head;
    while (temp != nullptr) {
        hitung++;
        temp = temp->next;
    }
    cout << "Total Data Hasil Tambang Dalam Linked List: " << hitung << endl;
}

void HasilLinked() {
    HasilTambang* temp = head;
    cout << "Hasil Tambang Dalam Linked List: " << endl;
    while (temp != nullptr) {
        cout << temp->nama << " (Jumlah: " << temp->jumlah << ") -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

HasilTambang* split(HasilTambang* head) {
    HasilTambang* pelan = head;
    HasilTambang* cepat = head->next;

    while (cepat && cepat->next) {
        pelan = pelan->next;
        cepat = cepat->next->next;
    }
    HasilTambang* tengah = pelan->next;
    pelan->next = nullptr;
    return tengah;
}

HasilTambang* merge(HasilTambang* kiri, HasilTambang* kanan) {
    if (!kiri) return kanan;
    if (!kanan) return kiri;

    if (kiri->jumlah <= kanan->jumlah) {
        kiri->next = merge(kiri->next, kanan);
        return kiri;
    } else {
        kanan->next = merge(kiri, kanan->next);
        return kanan;
    }
}

HasilTambang* mergesort(HasilTambang* head) {
    if (!head || !head->next) return head;

    HasilTambang* pelan = head;
    HasilTambang* cepat = head->next;
    while (cepat && cepat->next) {
        pelan = pelan->next;
        cepat = cepat->next->next;
    }

    HasilTambang* tengah = pelan->next;
    pelan->next = nullptr;

    HasilTambang* kiri = mergesort(head);
    HasilTambang* kanan = mergesort(tengah);

    return merge(kiri, kanan);
}

HasilTambang* quick(HasilTambang* head, HasilTambang* end, HasilTambang** newHead, HasilTambang** newEnd) {
    HasilTambang* pivot = end;
    HasilTambang* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != nullptr) {
        HasilTambang* next = cur->next;

        if (cur->jumlah >= pivot->jumlah) {
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
        } else {
            if (prev) prev->next = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
        }
        cur = next;
    }
    if (*newHead == nullptr) *newHead = pivot;
    *newHead = tail;
    
    return pivot;
}

HasilTambang* quicksort(HasilTambang* head, HasilTambang* end) {
    if (!head || head == end) return head;

    HasilTambang *newHead = nullptr, *newEnd = nullptr;
    HasilTambang* pivot = quick(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        HasilTambang* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quicksort(newHead, temp);

        temp = newHead;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = pivot;
    }
    pivot->next = quicksort(pivot->next, newEnd);
    return newHead;
}

void QuickSorting() {
    cout << "Quick Sorting Data Hasil Tambang(descending): " << endl;
    head = quicksort(head, nullptr);
    HasilLinked();
}

void MergeSorting() {
    cout << "Merge Sorting Data Hasil Tambang(ascending): " << endl;
    head = mergesort(head);
    HasilLinked();

}

void StackMenu() {
    int pilihan;
    do {
        cout << "Stack Menu:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Top" << endl;
        cout << "4. Kembali" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            if (isFull()) {
                cout << "Stack penuh. Tidak bisa menambah data hasil tambang.\n";
                break;
            }
            cin.ignore();
            string nama;
            int jumlah;
            cout << "Masukkan data Hasil Tambang: ";
            getline(cin, nama);
            cout << "Masukkan jumlah Hasil Tambang: ";
            cin >> jumlah;
            stackTambang.data[++stackTambang.top].nama = nama;
            stackTambang.data[++stackTambang.top].jumlah = jumlah;
            cout << "Data hasil tambang berhasil ditambahkan ke dalam stack.\n";
            break;
        }
        case 2: {
            if (isEmpty()) {
                cout << "Stack kosong. Tidak bisa menghapus data hasil tambang.\n";
            } else {
            cout << "Menghapus data hasil tambang " << stackTambang.data[stackTambang.top--].nama << " dari stack.\n";
            }
            break;
        }
        case 3: 
            if (isEmpty()) {
                cout << "Stack kosong.\n";
                break;
            } else {
            cout << "Data hasil tambang dalam Stack: \n";
            for (int i = stackTambang.top; i >= 0; i--) {
                cout << i + 1 << ". " << stackTambang.data[i].nama << "(Jumlah: " << stackTambang.data[i].jumlah << ")\n";
                }
            }
            break;
        case 4: 
            return;
        default:
            cout << "Pilihan Tidak Tersedia!\n";
        }
    } while (true);
}

void QueueMenu () {
    int pilihan;
    do {
        cout << "Menu Queue" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Lihat Queue" << endl;
        cout << "4. Kembali" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan; 

        switch (pilihan) {
        case 1: {
            if (isQueueFull()) {
                cout << "Queue penuh. Tidak bisa menambah data hasil tambang.\n";
                break;
            }
            if (isQueueEmpty()) {
                queueTambang.front = 0;
            }
            cin.ignore();
            string nama;
            int jumlah;
            cout << "Masukkan data hasil tambang: ";
            getline(cin, nama);
            cout << "Masukkan jumlah hasil tambang: ";
            cin >> jumlah;
            queueTambang.data[++queueTambang.rear].nama = nama;
            queueTambang.data[++queueTambang.rear].jumlah = jumlah;
            cout << "Data hasil tambang berhasil ditambahkan ke dalam Queue.\n";
            break;

        }
        case 2: 
            if (isQueueEmpty()) {
                cout << "Queue kosong. Tidak ada data hasil tambang untuk dihapus.\n";
            } else {
            cout << "Menghapus Data hasil tambang " << queueTambang.data[queueTambang.front++].nama << " dari queue.\n";
            if (queueTambang.front > queueTambang.rear) {
                initQueue();
                }
            }
            break;
        case 3: 
            if (isQueueEmpty()) {
                cout << "Queue kosong. Tidak ada data hasil tambang untuk dihapus.\n";
            } else {
            cout << "Menghapus data hasil tambang dalam Queue :\n";
            for (int i = queueTambang.front; i <= queueTambang.rear; i++) {
                cout << i + 1 << ". " << queueTambang.data[i].nama << "(Jumlah: " << queueTambang.data[i].jumlah << ")\n";
                }
            }
            break;
        case 4:
            return;
        default:
            cout << "Pilihan Invalid!\n";
        }   
    } while (true);
}

int main() {
    int pilihan;
    initStack();
    initQueue();

    do {
        cout << "\n=== GUDANG PENDATAAN HASIL TAMBANG DARI PERTAMBANGAN ===\n"
             << "1. Tambah Data Hasil Tambang\n"
             << "2. Hasil Tambang Linked List\n"
             << "3. Menu Stack\n"
             << "4. Menu Queue\n"
             << "5. Merge Sorting (Ascending)\n"
             << "6. Quick Sorting (Descending)\n"
             << "7. Hitung Hasil Tambang Dalam Linked List\n"
             << "8. Keluar\n"
             << "Pilih menu yang tertera diatas (1/2/3/4/5/6/7/8): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                Tambah(); 
                break;
            case 2: 
                HasilLinked(); 
                break;
            case 3: 
                StackMenu(); 
                break;
            case 4: 
                QueueMenu(); 
                break;
            case 5: 
                MergeSorting(); 
                break;
            case 6: 
                QuickSorting(); 
                break;
            case 7: 
                HitungNode(); 
                break;
            case 8:
                cout << "Terima kasih telah mendata Hasil Tambang dari pertambangan\n"; 
                return 0;
            default: 
                cout << "Pilihan Invalid\n";
        }
    } while (true);

    return 0;
}
