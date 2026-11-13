#include <iostream>
#include <string>
using namespace std;

// Single Linked List untuk menyimpan data mahasiswa 
struct Node {
    string nim;
    string nama;
    int nilai;
    Node* next;
};

// Insertion Sort : mengurutkan dari terkecil ke terbesar
void insertionSort(int data[], int n) {
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Linear Search berdasarkan NIM pada linked list 
Node* linearSearch(Node* head, string nimCari) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->nim == nimCari) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Binary Search iterative pada array nilai yang sudah terurut 
int binarySearch(int data[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (data[mid] == target) {
            return mid;
        } else if (target < data[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

// Menampilkan data mahasiswa dari linked list
void tampilMahasiswa(Node* head) {
    Node* temp = head;
    int no = 1;

    cout << "\nData Mahasiswa :" << endl;
    while (temp != nullptr) {
        cout << no << ". NIM : " << temp->nim
             << " | Nama : " << temp->nama
             << " | Nilai : " << temp->nilai << endl;
        temp = temp->next;
        no++;
    }
}

// Menampilkan isi array nilai
void tampilNilai(int data[], int n) {
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main() {
    system("cls");
    int n;

    cout << "Berapa jumlah data mahasiswanya : ";
    cin >> n;
    cin.ignore();

    cout << endl;

    // Dynamic Array untuk menyimpan kumpulan nilai 
    int* nilai = new int[n];

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; i++) {
        string nim, nama;
        int nilaiMhs;

        cout << "Data mahasiswa ke-" << i + 1 << endl;
        cout << "NIM   : ";
        getline(cin, nim);
        cout << "Nama  : ";
        getline(cin, nama);
        cout << "Nilai : ";
        cin >> nilaiMhs;
        cin.ignore();
        cout << endl;

        // Tambah node di belakang linked list
        Node* nodeBaru = new Node();
        nodeBaru->nim = nim;
        nodeBaru->nama = nama;
        nodeBaru->nilai = nilaiMhs;
        nodeBaru->next = nullptr;

        if (head == nullptr) {
            head = nodeBaru;
            tail = nodeBaru;
        } else {
            tail->next = nodeBaru;
            tail = nodeBaru;
        }

        // Simpan nilai ke dynamic array
        nilai[i] = nilaiMhs;
    }

    bool sudahUrut = false;
    int pilihan;

    do {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Tampilkan data mahasiswa" << endl;
        cout << "2. Urutkan nilai (Insertion Sort)" << endl;
        cout << "3. Cari mahasiswa berdasarkan NIM (Linear Search)" << endl;
        cout << "4. Cari nilai tertentu (Binary Search)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tampilMahasiswa(head);

            cout << "\nNilai (array) : ";
            tampilNilai(nilai, n);
        }
        else if (pilihan == 2) {
            cout << "\nNilai sebelum diurutkan : ";
            tampilNilai(nilai, n);

            insertionSort(nilai, n);
            sudahUrut = true;

            cout << "Nilai setelah diurutkan : ";
            tampilNilai(nilai, n);
        }
        else if (pilihan == 3) {
            string nimCari;
            cout << "\nMasukkan NIM yang dicari : ";
            getline(cin, nimCari);

            Node* hasil = linearSearch(head, nimCari);

            if (hasil != nullptr) {
                cout << "Data ditemukan" << endl;
                cout << "NIM   : " << hasil->nim << endl;
                cout << "Nama  : " << hasil->nama << endl;
                cout << "Nilai : " << hasil->nilai << endl;
            } else {
                cout << "Data tidak ditemukan" << endl;
            }
        }
        else if (pilihan == 4) {
            if (!sudahUrut) {
                cout << "\nUrutkan nilai terlebih dahulu (menu 2) sebelum Binary Search !" << endl;
            } else {
                int target;
                cout << "\nMasukkan nilai yang dicari : ";
                cin >> target;
                cin.ignore();

                int hasil = binarySearch(nilai, n, target);

                if (hasil != -1) {
                    cout << "Nilai ditemukan pada indeks : " << hasil << endl;
                } else {
                    cout << "Nilai tidak ditemukan" << endl;
                }
            }
        }
        else if (pilihan != 0) {
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 0);

    // Hapus memori
    while (head != nullptr) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
    }
    delete[] nilai;

    return 0;
}