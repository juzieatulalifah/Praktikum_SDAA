#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int banyakObat = 10000;
int maxPercobaan = 3;

struct DataObat {
    struct Obat {
        string nama;
        string deskripsi;
        int stok;
    } obat[banyakObat];
    int hitung = 0;
};

void menu() {
    cout <<" "<<endl;
    cout <<"================================================="<<endl;
    cout << "Menu Manajemen Stok Obat" << endl;
    cout <<"================================================="<<endl;
    cout <<"1. Lihat daftar stok obat" << endl;
    cout <<"2. Tambahkan stok obat baru" << endl;
    cout <<"3. Ubah data obat" << endl;
    cout <<"4. Hapus obat dari daftar" << endl;
    cout <<"5. Keluar dari program" << endl;
    cout <<"================================================="<<endl;
    cout <<"Masukkan pilihan (1/2/3/4/5) : ";
}

bool login() {
    string username;
    string password;
    int percobaan = 0;

    do {
        cout << "Masukkan username: ";
        getline(cin, username);

        cout << "Masukkan password: ";
        getline(cin, password);

        if (username == "Nur Juzieatul Alifah" && password == "2309106040") {
            return true;
        } else {
            cout << "Username atau password salah." << endl;
            percobaan++;
        }
    } while (percobaan < maxPercobaan);

    cout << "\nAnda telah salah memasukkan username atau password sebanyak 3 kali. Program akan berhenti" << endl;
    return false;
}

bool ubahObat(DataObat &data){
    if (data.hitung == 0) {
        cout << "\nGak bisa dong, daftar masih kosong" << endl;
        return false;
    }

    cout << "Masukkan nomor obat yang ingin diperbarui: ";
    int index;
    cin >> index;
    cin.ignore();
    if (index >= 1 && index <= data.hitung) {
        cout << "\nMasukkan nama obat baru: ";
        getline(cin, data.obat[index - 1].nama);
        cout << "Masukkan deskripsi obat baru: ";
        getline(cin, data.obat[index - 1].deskripsi);
        cout << "Masukkan jumlah stok baru: ";
        cin >> data.obat[index - 1].stok;
        cin.ignore();
        cout << "\nData obat berhasil diperbarui." << endl;
        return true; 
    } else {
        cout << "\nNomor obat tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
}

bool hapusObat(DataObat &data){
    if (data.hitung == 0) {
        cout << "\nTidak ada data untuk dihapus." << endl;
        return false;
    }
    cout << "\nMasukkan nomor obat yang ingin dihapus: ";
    int index;
    cin >> index;
    if (index >= 1 && index <= data.hitung) {
        for (int i = index - 1; i < data.hitung - 1; ++i) {
            data.obat[i] = data.obat[i + 1];
        }
        data.hitung--;
        cout << "\nObat berhasil dihapus." << endl;
        return true; 
    } else {
        cout << "\nNomor obat tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

void tambahObat(DataObat &data){
    if (data.hitung < banyakObat) {
        cout << "\nMasukkan nama obat: ";
        cin.ignore();
        getline(cin, data.obat[data.hitung].nama);
        cout << "Masukkan deskripsi obat: ";
        getline(cin, data.obat[data.hitung].deskripsi);
        cout << "Masukkan jumlah stok: ";
        cin >> data.obat[data.hitung].stok;
        data.hitung++;
        cout << "\nObat berhasil ditambahkan." << endl;
    } else {
        cout << "\nDaftar obat sudah penuh." << endl;
    }
}

void lihatListObat(const DataObat *data){
    if (data->hitung == 0) {
        cout << "\nBelum ada obat yang disimpan." << endl;
    } else {
        cout << "\nDaftar Stok Obat:" << endl;
        for (int i = 0; i < data->hitung; ++i) {
            cout << i + 1 << ". " << data->obat[i].nama << " - " << data->obat[i].deskripsi << " | Stok: " << data->obat[i].stok << endl;
        }
        cout << "\nJumlah obat dalam daftar: " << data->hitung << endl;
    }
}

bool pilihanBenar(int pilihan) {
    return (pilihan >= 1 && pilihan <= 5);
}

int main() {
    DataObat data;
    int pilihan;

    if (!login()) {
        return 1;
    }

    do {
        menu();
        cin >> pilihan;

        if (!pilihanBenar(pilihan)) {
            cout << "\nPilihan tidak valid. Silakan pilih kembali." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (pilihan) {
            case 1:
                lihatListObat(&data);
                break;
            case 2:
                tambahObat(data);
                break;
            case 3:
                ubahObat(data);
                break;
            case 4:
                hapusObat(data);
                break;
            case 5:
                cout << "Baibaiii" << endl;
                break;
            default:
                cout << "\nPilihan tidak valid. Silakan pilih kembali." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    } while (pilihan != 5);

    return 0;
}
