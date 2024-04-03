#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    string title;
    string author;
    int year;
};

struct User {
    string name;
    int nim;
};

struct Library {
    Book books[MAX_BOOKS];
    int numBooks;
};

void displayMenu() {
    cout << "\nMenu Perpustakaan:\n";
    cout << "1. Tambah Data Buku\n";
    cout << "2. Tampilkan Data Buku\n";
    cout << "3. Ubah Data Buku\n";
    cout << "4. Hapus Data Buku\n";
    cout << "5. Keluar\n";
}

// Fungsi untuk mengecek apakah user adalah admin
bool isAdmin(User* user) {
    return (user->name == "gibran" && user->nim == 139);
}

// Fungsi untuk mencari indeks buku berdasarkan judul
int findBookIndex(Library* library, string title) {
    for (int i = 0; i < library->numBooks; ++i) {
        if (library->books[i].title == title) {
            return i;
        }
    }
    return -1; // Buku tidak ditemukan
}

void addBook(Library* library) {
    if (library->numBooks < MAX_BOOKS) {
        cout << "Masukkan judul buku: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, library->books[library->numBooks].title);
        cout << "Masukkan penulis buku: ";
        getline(cin, library->books[library->numBooks].author);
        cout << "Masukkan tahun terbit: ";
        cin >> library->books[library->numBooks].year;
        library->numBooks++;
        cout << "Data buku berhasil ditambahkan.\n";
    } else {
        cout << "Maaf, sudah mencapai batas maksimum data buku.\n";
    }
}

void displayBooks(Library* library) {
    if (library->numBooks > 0) {
        cout << "Daftar Buku:\n";
        for (int i = 0; i < library->numBooks; ++i) {
            cout << i + 1 << ". " << library->books[i].title << " oleh " << library->books[i].author << " (" << library->books[i].year << ")\n";
        }
    } else {
        cout << "Belum ada data buku.\n";
    }
}

void modifyBook(Library* library) {
    if (library->numBooks > 0) {
        string titleToModify;
        cout << "Masukkan judul buku yang ingin diubah: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, titleToModify);
        int bookIndex = findBookIndex(library, titleToModify);
        if (bookIndex != -1) {
            cout << "Masukkan judul baru: ";
            getline(cin, library->books[bookIndex].title);
            cout << "Masukkan penulis baru: ";
            getline(cin, library->books[bookIndex].author);
            cout << "Masukkan tahun terbit baru: ";
            cin >> library->books[bookIndex].year;
            cout << "Data buku berhasil diubah.\n";
        } else {
            cout << "Buku dengan judul tersebut tidak ditemukan.\n";
        }
    } else {
        cout << "Belum ada data buku.\n";
    }
}

void deleteBook(Library* library) {
    if (library->numBooks > 0) {
        string titleToDelete;
        cout << "Masukkan judul buku yang ingin dihapus: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, titleToDelete);
        int bookIndex = findBookIndex(library, titleToDelete);
        if (bookIndex != -1) {
            // Geser semua buku setelah buku yang dihapus
            for (int i = bookIndex; i < library->numBooks - 1; ++i) {
                library->books[i] = library->books[i + 1];
            }
            library->numBooks--;
            cout << "Data buku berhasil dihapus.\n";
        } else {
            cout << "Buku dengan judul tersebut tidak ditemukan.\n";
        }
    } else {
        cout << "Belum ada data buku.\n";
    }
}

int main() {
    User user;
    int loginAttempt = 0;

    // Login
    do {
        cout << "Masukkan Nama: ";
        cin >> user.name;
        cout << "Masukkan NIM: ";
        cin >> user.nim;
        loginAttempt++;
    } while (!isAdmin(&user) && loginAttempt < 3);

    if (loginAttempt >= 3) {
        cout << "Anda telah salah login sebanyak 3 kali. Program berhenti.\n";
        return 0;
    }

    // Data perpustakaan
    Library library;
    library.numBooks = 0;

    int choice;
    do {
        displayMenu();
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                displayBooks(&library);
                break;
            case 3:
                modifyBook(&library);
                break;
            case 4:
                deleteBook(&library);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program perpustakaan.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 5);

    return 0;
}