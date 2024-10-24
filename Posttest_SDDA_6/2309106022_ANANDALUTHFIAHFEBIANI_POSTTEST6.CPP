#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

#define MAX 100

struct HasilTambang {
    int id_HasilTambang;
    string nama_HasilTambang;
    int jumlah_HasilTambang;
    string persebaran_HasilTambang;
    HasilTambang* next;
};

HasilTambang* head = nullptr;
HasilTambang dataTambang[MAX];
int tambang = 0;

vector<int> BoyerMoore(string pattern);

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

HasilTambang* Linked(int id, string nama, int jumlah, string persebaran) {
    HasilTambang* baru = new HasilTambang();
    baru->id_HasilTambang = id;
    baru->nama_HasilTambang = nama;
    baru->jumlah_HasilTambang = jumlah;
    baru->persebaran_HasilTambang = persebaran;
    baru->next = nullptr;
    return baru;
}

void Tampil() {
    if (tambang > 0) {
    cout << "Data Hasil Tambang Ditampilkan\n";
    for (int i = 0; i < tambang; i++) {
        cout << i + 1 << ". ID: " << dataTambang[i].id_HasilTambang
             << ", Nama Hasil Tambang: " << dataTambang[i].nama_HasilTambang
             << ", Jumlah Hasil Tambang: " << dataTambang[i].jumlah_HasilTambang 
             << ", Persebaran HAsil Tambang: " << dataTambang[i].persebaran_HasilTambang << endl;
        }
    } else {
        cout << "<-- DATA HASIL TAMBANG KOSONG -->\n";
    }
}

void Tambah() {
    if (tambang < MAX) {
        int id, jumlah;
        string nama, persebaran;

        cout << "Tambah id Hasil Tambang: ";
        cin >> id;
        cin.ignore();
        cout << "Tambah Nama Hasil Tambang: ";
        getline(cin, nama);
        cout << "Jumlah/Total Hasil Tambang: ";
        cin >> jumlah;
        cin.ignore();
        cout << "Persebaran Hasil Tambang: ";
        getline(cin, persebaran);

        dataTambang[tambang].id_HasilTambang = id;
        dataTambang[tambang].nama_HasilTambang = nama;
        dataTambang[tambang].jumlah_HasilTambang = jumlah;
        dataTambang[tambang].persebaran_HasilTambang = persebaran;
        
        HasilTambang* baru = Linked(id, nama, jumlah, persebaran);
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

int jumpsearch(int arr[], int n, int target) {
    int step = sqrt(n), prev = 0;
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int fibonaccisearch(int arr[], int n, int target) {
    int fib1 = 0;
    int fib2 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib1 = fib2;
        fib2 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;
    while (fib > 1) {
        int i = min(offset + fib1, n - 1);
        if (arr[i] < target) {
            fib = fib2;
            fib2 = fib1;
            fib1 = fib - fib1;
            offset = i;
        } else if (arr[i] > target) {
            fib = fib1;
            fib2 -= fib1;
            fib1 = fib - fib2;
        } else return i;
    }

    if (fib2 && arr[offset + 1] == target) return offset + 1;
    return -1;
}

int BoyerMooresearch(string text, string pattern) {
    vector<int> Char = BoyerMoore(pattern);
    int m = pattern.size();
    int n = text.size();

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            return shift;    
        }
        shift += max(1, j - Char[text[shift + j]]);
    }
    return -1;
}

vector<int> BoyerMoore(string pattern) {
    vector<int> Char(256, -1);
    for (int i = 0; i < pattern.size(); i++)
        Char[pattern[i]] = i;
    return Char;
}

void SearchingMenu() {
    int pil;
    cout << "Pilih metode pencarian: " << endl;
    cout << "1. Berdasarkan Jumlah (Integer)" << endl;
    cout << "2. Berdasarkan Nama/Persebaran (String)" << endl;
    cout << "Pilih Menu: ";
    cin >> pil;

    if (pil == 1) {
        int jumlah;
        cout << "Masukkan jumlah data Hasil Tambang yang ingin dicari: ";
        cin >> jumlah;

        int arr[MAX];
        for (int i = 0; i < tambang; i++) arr[i] = dataTambang[i].jumlah_HasilTambang;

        cout << "Pilih Metode " << endl;
        cout << "1. Jump Search" << endl;
        cout << "2. Fibonacci Search" << endl;
        cout << "Pilih Menu: " << endl;
        int method;
        cin >> method;

        int result = (method == 1) ? jumpsearch(arr, tambang, jumlah)
                                   : fibonaccisearch(arr, tambang, jumlah);

        if (result != -1)
            cout << "Jumlah Pada Data Hasil Tambang Berada di indeks ke-" << result + 1 << ".\n";
        else
            cout << "Jumlah Pada Data Hasil Tambang Tidak Ditemukan";
    } else if (pil == 2) {
        string target;
        cout << "Masukkan text data Hasil Tambang yang ingin dicari: ";
        cin.ignore();
        getline(cin, target);

        cout << "Pilih Data " << endl;
        cout << "1. Nama Hasil Tambang" << endl;
        cout << "2. Persebaran Hasil Tambang" << endl;
        cout << "Pilih Menu" << endl;
        int field;
        cin >> field;
        cin.ignore();

        bool temu = false;
        for (int i = 0; i < tambang; i++) {
            string text = (field == 1) ? dataTambang[i].nama_HasilTambang : dataTambang[i].persebaran_HasilTambang;
            if (BoyerMooresearch(text, target) != -1) {
                cout << "Data Hasil Tambang Berada di indeks ke-" << i + 1 << ".\n";
                temu = true;
                break;
            }
        }
        if (!temu) cout << "Data Hasil Tambang Tidak ditemukan.\n";
    } else {
        cout << "Pilihan Tidak Tersedia.\n";
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
        cout << "id: " << temp->id_HasilTambang
             << ", nama: " << temp->nama_HasilTambang
             << ", jumlah: " << temp->jumlah_HasilTambang
             << ", persebaran: " << temp->persebaran_HasilTambang << " -> ";
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

    if (kiri->id_HasilTambang <= kanan->id_HasilTambang) {
        kiri->next = merge(kiri->next, kanan);
        return kiri;
    } else {
        kanan->next = merge(kiri, kanan->next);
        return kanan;
    }
}

HasilTambang* mergesort(HasilTambang* head) {
    if (!head || !head->next) return head;

    HasilTambang* tengah = split(head);
    HasilTambang* kiri = mergesort(head);
    HasilTambang* kanan = mergesort(tengah);

    return merge(kiri, kanan);
}

HasilTambang* quick(HasilTambang* head, HasilTambang* end, HasilTambang** newHead, HasilTambang** newEnd) {
    HasilTambang* pivot = end;
    HasilTambang* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != nullptr) {
        HasilTambang* next = cur->next;

        if (cur->jumlah_HasilTambang >= pivot->jumlah_HasilTambang) {
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

void SortingMenu() {
    int pil;
    cout << "Pilih Menu Sorting" << endl;
    cout << "1. Merge Sort (Ascending)" << endl;
    cout << "2. Quick Sort (Descending)" << endl;
    cout << "Pilih Metode Sorting: " << endl;
    cin >> pil;

    switch (pil) {
        case 1:
            cout << "Melakukan Merge Sort (Ascending)...\n";
            head = mergesort(head);
            HasilLinked();
            break;
        case 2:
            cout << "Melakukan Quick Sort (Descending)...\n";
            head = quicksort(head, nullptr);
            HasilLinked();
            break;
        default:
            cout << "Pilihan Tidak Tersedia.\n";
    }

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
            int id_HasilTambang;
            string nama_HasilTambang;
            int jumlah_HasilTambang;
            string persebaran_HasilTambang;
            cout << "Masukkan ID Hasil Tambang: ";
            cin >> id_HasilTambang;
            cout << "Masukkan data Hasil Tambang: ";
            getline(cin, nama_HasilTambang);
            cout << "Masukkan jumlah Hasil Tambang: ";
            cin >> jumlah_HasilTambang;
            cout << "Masukkan persebaran Hasil Tambang: ";
            getline(cin, persebaran_HasilTambang);
            stackTambang.data[++stackTambang.top].id_HasilTambang = id_HasilTambang;
            stackTambang.data[++stackTambang.top].nama_HasilTambang = nama_HasilTambang;
            stackTambang.data[++stackTambang.top].jumlah_HasilTambang = jumlah_HasilTambang;
            stackTambang.data[++stackTambang.top].persebaran_HasilTambang = persebaran_HasilTambang;
            cout << "Data hasil tambang berhasil ditambahkan ke dalam stack.\n";
            break;
        }
        case 2: {
            if (isEmpty()) {
                cout << "Stack kosong. Tidak bisa menghapus data hasil tambang.\n";
            } else {
            cout << "Menghapus data hasil tambang " << stackTambang.data[stackTambang.top--].nama_HasilTambang << " dari stack.\n";
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
                cout << i + 1 << "id: " << stackTambang.data[i].id_HasilTambang << ", nama: " << stackTambang.data[i].nama_HasilTambang << ", jumlah: " << stackTambang.data[i].jumlah_HasilTambang << ", persebaran: " << stackTambang.data[i].persebaran_HasilTambang;
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
            int id_HasilTambang;
            string nama_HasilTambang;
            int jumlah_HasilTambang;
            string persebaran_HasilTambang;
            cout << "Masukkan ID Hasil Tambang: ";
            cin >> id_HasilTambang;
            cout << "Masukkan data Hasil Tambang: ";
            getline(cin, nama_HasilTambang);
            cout << "Masukkan jumlah Hasil Tambang: ";
            cin >> jumlah_HasilTambang;
            cout << "Masukkan persebaran Hasil Tambang: ";
            getline(cin, persebaran_HasilTambang);
            queueTambang.data[++queueTambang.rear].id_HasilTambang = id_HasilTambang;
            queueTambang.data[queueTambang.rear].nama_HasilTambang = nama_HasilTambang;
            queueTambang.data[queueTambang.rear].jumlah_HasilTambang = jumlah_HasilTambang;
            queueTambang.data[queueTambang.rear].persebaran_HasilTambang = persebaran_HasilTambang;
            cout << "Data hasil tambang berhasil ditambahkan ke dalam Queue.\n";
            break;

        }
        case 2: 
            if (isQueueEmpty()) {
                cout << "Queue kosong. Tidak ada data hasil tambang untuk dihapus.\n";
            } else {
            cout << "Menghapus Data hasil tambang " << queueTambang.data[queueTambang.front++].nama_HasilTambang << " dari queue.\n";
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
                cout << i + 1 << "id: " << queueTambang.data[i].id_HasilTambang << ", nama: " << queueTambang.data[i].nama_HasilTambang << ", jumlah: " << queueTambang.data[i].jumlah_HasilTambang << ", persebaran: " << queueTambang.data[i].persebaran_HasilTambang;
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
             << "5. Menu Searching\n"
             << "6. Menu Sorting\n"
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
                SearchingMenu(); 
                break;
            case 6: 
                SortingMenu(); 
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
