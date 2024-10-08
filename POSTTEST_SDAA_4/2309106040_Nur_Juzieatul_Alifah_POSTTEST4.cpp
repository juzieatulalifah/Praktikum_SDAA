#include <iostream>
#include <string>
#include <limits>
#include <queue>
#include <stack>

using namespace std;

int maxPercobaan = 3;

struct Obat {
    string nama;
    string deskripsi;
    int stok;
    Obat* next;
};

stack<string> undoStack;
queue<string> recentlyAdded;

Obat* buatObat(string nama, string deskripsi, int stok) {
    Obat* newObat = new Obat;
    newObat->nama = nama;
    newObat->deskripsi = deskripsi;
    newObat->stok = stok;
    newObat->next = nullptr;
    return newObat;
}

void tambahObat(Obat*& head) {
    string nama, deskripsi;
    int stok;
    
    cout << "\nMasukkan nama obat: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan deskripsi obat: ";
    getline(cin, deskripsi);
    cout << "Masukkan jumlah stok: ";
    cin >> stok;
    
    Obat* newObat = buatObat(nama, deskripsi, stok);
    
    if (head == nullptr) {
        head = newObat;
    } else {
        Obat* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newObat;
    }

    recentlyAdded.push(nama);
    if (recentlyAdded.size() > 100) {  \
        recentlyAdded.pop();
    }

    cout << "\nObat berhasil ditambahkan." << endl;
}

void lihatListObat(Obat* head) {
    if (head == nullptr) {
        cout << "\nBelum ada obat yang disimpan." << endl;
        return;
    }

    Obat* temp = head;
    int nomor = 1;
    cout << "\nDaftar Stok Obat:" << endl;
    while (temp != nullptr) {
        cout << nomor << ". " << temp->nama << " - " << temp->deskripsi << " | Stok: " << temp->stok << endl;
        temp = temp->next;
        nomor++;
    }
    cout << "\nObat yang baru ditambahkan :" << endl;
    queue<string> tempQueue = recentlyAdded;
    while (!tempQueue.empty()) {
        cout << "- " << tempQueue.front() << endl;
        tempQueue.pop();
    }
}

bool ubahObat(Obat* head) {
    if (head == nullptr) {
        cout << "\nDaftar masih kosong" << endl;
        return false;
    }

    lihatListObat(head);

    cout << "Masukkan nomor obat yang ingin diperbarui: ";
    int index;
    cin >> index;
    cin.ignore();

    Obat* temp = head;
    for (int i = 1; i < index && temp != nullptr; ++i) {
        temp = temp->next;
    }

    if (temp != nullptr) {
        undoStack.push(temp->nama);

        cout << "\nMasukkan nama obat baru: ";
        getline(cin, temp->nama);
        cout << "Masukkan deskripsi obat baru: ";
        getline(cin, temp->deskripsi);
        cout << "Masukkan jumlah stok baru: ";
        cin >> temp->stok;
        cout << "\nData obat berhasil diperbarui." << endl;
        return true;
    } else {
        cout << "\nNomor obat tidak valid." << endl;
        return false;
    }
}

bool hapusObat(Obat*& head) {
    if (head == nullptr) {
        cout << "\nTidak ada data untuk dihapus." << endl;
        return false;
    }

    lihatListObat(head);

    cout << "\nMasukkan nomor obat yang ingin dihapus: ";
    int index;
    cin >> index;

    if (index == 1) {
        Obat* temp = head;
        undoStack.push(temp->nama);

        head = head->next;
        delete temp;
        cout << "\nObat berhasil dihapus." << endl;
        return true;
    }

    Obat* temp = head;
    Obat* prev = nullptr;
    for (int i = 1; i < index && temp != nullptr; ++i) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr) {
        undoStack.push(temp->nama);

        prev->next = temp->next;
        delete temp;
        cout << "\nObat berhasil dihapus." << endl;
        return true;
    } else {
        cout << "\nNomor obat tidak valid." << endl;
        return false;
    }
}

void menu() {
    cout << "=================================================" << endl;
    cout << "Menu Manajemen Stok Obat" << endl;
    cout << "=================================================" << endl;
    cout << "1. Lihat daftar stok obat" << endl;
    cout << "2. Tambahkan stok obat baru" << endl;
    cout << "3. Ubah data obat" << endl;
    cout << "4. Hapus obat dari daftar" << endl;
    cout << "5. Keluar dari program" << endl;
    cout << "=================================================" << endl;
    cout << "Masukkan pilihan (1/2/3/4/5) : ";
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

bool pilihanBenar(int pilihan) {
    return (pilihan >= 1 && pilihan <= 5);
}

int main() {
    Obat* head = nullptr;
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
                lihatListObat(head);
                break;
            case 2:
                tambahObat(head);
                break;
            case 3:
                ubahObat(head);
                break;
            case 4:
                hapusObat(head);
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
