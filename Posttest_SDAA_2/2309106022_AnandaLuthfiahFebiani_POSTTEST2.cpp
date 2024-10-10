#include <iostream>
#include <string>
using namespace std;

#define MAX 100

struct HasilTambang {
    string nama;
    int jumlah;
};

HasilTambang dataTambang[MAX];
int tambang = 0;

void Tampil() {
    if (tambang > 0) {
        cout << "Data Hasil Tambang Ditampilkan\n";
        for (int i = 0; i < tambang; i++) {
            cout << i + 1 << ". " << dataTambang[i].nama << " (Jumlah : " << dataTambang[i].jumlah << ")" << endl;
        }
    } else {
        cout << "=== Data Tambang Kosong ===\n";
    }
}
void Tambah() {
    if (tambang < MAX) {
        cin.ignore();
        cout << "Tambah Data Hasil Tambang: ";
        getline (cin, dataTambang[tambang].nama);
        cout << "Dengan Jumlah Hasil Tambang: ";
        cin >> dataTambang[tambang].jumlah;
        tambang++;
    } else {
        cout << "<-- GUDANG PERTAMBANGAN TELAH PENUH -->\n";
    }
    Tampil();
}

void Ubah() {
    Tampil();
    cout << "Ubah Data Tambang Ke: ";
    int y;
    cin >> y;
    if (y > 0 && y <= tambang) {
        cin.ignore();
        cout << "Ubah Nama Hasil Tambang Menjadi: ";
        getline(cin, dataTambang[y - 1].nama);
        cout << "Ubah Jumlah Hasil Tambang Menjadi: ";
        cin >> dataTambang[y - 1].jumlah;
    }
    Tampil();
}

void Hapus() {
    Tampil();
    cout << "Hapus Data Tambang ke: ";
    int x;
    cin >> x;
    if (x > 0 && x <= tambang) {
        for (int i = x; i < tambang; i++) {
            dataTambang[i - 1] = dataTambang[i];
        }
        tambang--;
    }
    Tampil();
}

bool Login() {
    string Username, Password;
    cout << "=== Login ===\n";
    cout << "Username: ";
    getline(cin, Username);
    cout << "Password: ";
    getline(cin, Password);
    return Username == "admin" && Password == "1234";
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
             << "5. Keluar\n"
             << "Pilih menu yang tertera diatas (1/2/3/4/5): ";
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
                cout << "Terima kasih telah mendata Hasil Tambang dari pertambangan\n"; 
                return 0;
            default: 
                cout << "Pilihan Invalid\n";
        }
    } while (true);

    return 0;
}
