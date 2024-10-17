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

Obat* merge(Obat* left, Obat* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->stok <= right->stok) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

void split(Obat* head, Obat*& left, Obat*& right) {
    if (!head || !head->next) {
        left = head;
        right = nullptr;
        return;
    }

    Obat* slow = head;
    Obat* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = head;
    right = slow->next;
    slow->next = nullptr;
}

void mergeSort(Obat*& head) {
    if (!head || !head->next) return;

    Obat* left;
    Obat* right;
    split(head, left, right);

    mergeSort(left);
    mergeSort(right);

    head = merge(left, right);
}

Obat* partition(Obat* low, Obat* high) {
    int pivot = high->stok;
    Obat* i = low->next; 

    for (Obat* j = low; j != high; j = j->next) {
        if (j->stok >= pivot) { 
            if (!i) {
                i = low;
            }
            swap(i->stok, j->stok);
            i = i->next;
        }
    }
    if (i) {
        swap(i->stok, high->stok);
    }
    return i ? i : low;
}

void quickSort(Obat* low, Obat* high) {
    if (high != nullptr && low != high && low != high->next) {
        Obat* p = partition(low, high);
        quickSort(low, p);
        quickSort(p->next, high);
    }
}

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
    cout << "5. Urutkan daftar obat" << endl; 
    cout << "6. Keluar dari program" << endl;
    cout << "=================================================" << endl;
    cout << "Masukkan pilihan (1/2/3/4/5/6) : ";
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
    return (pilihan >= 1 && pilihan <= 6);
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
            case 5: {
                if (head == nullptr) {
                    cout << "\nDaftar masih kosong, tidak ada yang diurutkan." << endl;
                    break;
                }
                mergeSort(head);
                cout << "\nDaftar obat berhasil diurutkan secara ascending berdasarkan stok." << endl;

                Obat* tail = head;
                while (tail->next != nullptr) {
                    tail = tail->next;
                }
                quickSort(head, tail);
                cout << "Daftar obat berhasil diurutkan secara descending berdasarkan stok." << endl;
                break;
            }
            case 6:
                cout << "Baibaiii" << endl;
                break;
            default:
                cout << "\nPilihan tidak valid. Silakan pilih kembali." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    } while (pilihan != 6);

    return 0;
}
