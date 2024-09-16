#include <iostream>
using namespace std;

int fact(int angka) {
    if (angka == 0 || angka == 1) {
        return 1;
    } else {
        return angka * fact(angka - 1);
    }
}

int pascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    } else {
        return pascal(baris - 1, kolom - 1) + pascal(baris - 1, kolom);
    }
}

int main() {
    int tingkat = 3;
    for (int baris = 0; baris < tingkat; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
            cout << pascal(baris, kolom) << " ";
        }
        cout << endl;
    }

    return 0;
}