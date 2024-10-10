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
        cout << "<-- DATA TAMBANG KOSONG -->\n";
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
        nama = dataTambang[tambang].nama;
        jumlah = dataTambang[tambang].jumlah;
        tambang++;
    } else {
        cout << "<-- DATA TAMBANG INVALID/PENUH -->\n";        
    }

    HasilTambang* baru = Linked(nama, jumlah);

    if (head == nullptr) {
        head = baru;
    } else {
        HasilTambang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

void Ubah() {
    Tampil();
    cout << "Ubah Data Tambang Ke: ";
    int index;
    cin >> index;

    if (head == nullptr) {
        cout << "<-- DATA TAMBANG KOSONG -->\n";
        return;
    }

    HasilTambang* temp = head;
    for (int i = 0; i < index; i++) {
        if (temp->next == nullptr) {
            cout << "<-- DATA TAMBANG INVALID --> " << endl;
            return;
            }
            temp = temp->next;
        }
        
        cin.ignore();
        cout << "Ubah Nama Hasil Tambang Menjadi: ";
        getline(cin, dataTambang[index - 1].nama);
        cout << "Ubah Jumlah Hasil Tambang Menjadi: ";
        cin >> dataTambang[index - 1].jumlah;
}

void Hapus() {
    Tampil();
    cout << "Hapus Data Tambang ke: ";
    int index;
    cin >> index;

    if (head == nullptr) {
        cout << "<-- DATA TAMBANG KOSONG -->\n";
        return;
    }

    if (index == 1) {
        head = head->next;
    } else {
        HasilTambang* temp = head;
        for (int i = 1; i < index - 1; i++) {
            if (temp->next == nullptr) {
            cout << "<-- DATA TAMBANG INVALID -->" << endl;
            return;
            }
            temp = temp->next;
        } 
        HasilTambang* LinkedHapus = temp->next;
        if (LinkedHapus == nullptr) {
            cout << "<-- DATA TAMBANG INVALID -->" << endl;
            return;
            } 
            temp->next = LinkedHapus->next;
            delete LinkedHapus;
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

int main() {
    HasilTambang hasil;    

    int pilihan;
    do {
        cout << "\n=== GUDANG PENDATAAN HASIL TAMBANG DARI PERTAMBANGAN ===\n"
             << "1. Tambah Data Hasil Tambang\n"
             << "2. Ubah Data Hasil Tambang\n"
             << "3. Hapus Data Hasil Tambang\n"
             << "4. Tampilkan Data Hasil Tambang\n"
             << "5. Hasil Tambang Linked List\n"
             << "6. Hitung Hasil Tambang Dalam Linked List\n"
             << "7. Keluar\n"
             << "Pilih menu yang tertera diatas (1/2/3/4/5/6/7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                Tambah(); 
                break;
            case 2: 
                Ubah(); 
                break;
            case 3: 
                Hapus(); 
                break;
            case 4: 
                Tampil(); 
                break;
            case 5: 
                HasilLinked(); 
                break;
            case 6: 
                HitungNode(); 
                break;
            case 7:
                cout << "Terima kasih telah mendata Hasil Tambang dari pertambangan\n"; 
                return 0;
            default: 
                cout << "Pilihan Invalid\n";
        }
    } while (true);

    return 0;
}
