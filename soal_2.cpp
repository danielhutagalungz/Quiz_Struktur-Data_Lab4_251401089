#include <iostream>
#include <string>
using namespace std;

// Queue (Linked List) : antrean mahasiswa peminjam buku, FIFO 
struct NodeQueue {
    string nama;
    NodeQueue* next;
};

NodeQueue* front = nullptr;
NodeQueue* rear = nullptr;

void enqueue(string nama) {
    NodeQueue* nodeBaru = new NodeQueue();
    nodeBaru->nama = nama;
    nodeBaru->next = nullptr;

    if (front == nullptr) {
        front = nodeBaru;
        rear = nodeBaru;
    } else {
        rear->next = nodeBaru;
        rear = nodeBaru;
    }
    cout << nama << " masuk antrean" << endl;
}

void dequeue() {
    if (front == nullptr) {
        cout << "Antrean kosong" << endl;
        return;
    }

    NodeQueue* hapus = front;
    cout << hapus->nama << " dilayani (keluar dari antrean)" << endl;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }
    delete hapus;
}

void tampilQueue() {
    NodeQueue* temp = front;
    cout << "Isi antrean (depan -> belakang) : ";

    if (temp == nullptr) {
        cout << "Kosong";
    }
    while (temp != nullptr) {
        cout << temp->nama << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Stack (Linked List) : riwayat pengembalian buku, LIFO 
struct NodeStack {
    int idBuku;
    NodeStack* next;    
};

NodeStack* top = nullptr;

void push(int idBuku) {
    NodeStack* nodeBaru = new NodeStack();
    nodeBaru->idBuku = idBuku;
    nodeBaru->next = top;
    top = nodeBaru;
    cout << "Buku ID " << idBuku << " dicatat dalam riwayat pengembalian" << endl;
}

void pop() {
    if (top == nullptr) {
        cout << "Riwayat pengembalian kosong" << endl;
        return;
    }

    NodeStack* hapus = top;
    cout << "Riwayat terakhir dihapus (Pop) : Buku ID " << top->idBuku << endl;
    top = top->next;
    delete hapus;
}

void tampilStack() {
    NodeStack* temp = top;
    cout << "Riwayat pengembalian (terbaru -> terlama) : ";

    if (temp == nullptr) {
        cout << "Kosong";
    }
    while (temp != nullptr) {
        cout << temp->idBuku << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Binary Search Tree : ID buku 
struct Node {
    int data;
    Node* kiri;
    Node* kanan;
};

void tambah(Node*& root, int angka) {
    if (root == NULL) {
        root = new Node();
        root->data = angka;
        root->kiri = NULL;
        root->kanan = NULL;

        return;
    }

    // ID lebih kecil dari data root -> ke kiri
    else if (angka < root->data) {
        tambah(root->kiri, angka);

    // ID lebih besar dari data root -> ke kanan
    } else {
        tambah(root->kanan, angka);
    }

    return;
}

// Pencarian ID buku pada BST
bool cari(Node* root, int angka) {
    if (root == NULL) {
        return false;
    }

    if (angka == root->data) {
        return true;
    } else if (angka < root->data) {
        return cari(root->kiri, angka);
    } else {
        return cari(root->kanan, angka);
    }
}

// Pre order
void preOrder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

// In order
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->kiri);
        cout << root->data << " ";
        inOrder(root->kanan);
    }
}

// Post order
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->kiri);
        postOrder(root->kanan);
        cout << root->data << " ";
    }
}

int main() {
    system("cls");
    Node* root = NULL;
    int pilihan;

    do {
        cout << "\n===== SISTEM PERPUSTAKAAN =====" << endl;
        cout << "1. Tambah antrean peminjam (Enqueue)" << endl;
        cout << "2. Layani antrean (Dequeue)" << endl;
        cout << "3. Tampilkan antrean" << endl;
        cout << "4. Catat pengembalian buku (Push)" << endl;
        cout << "5. Hapus riwayat terakhir (Pop)" << endl;
        cout << "6. Tampilkan riwayat pengembalian" << endl;
        cout << "7. Tambah ID buku ke BST" << endl;
        cout << "8. Cari ID buku" << endl;
        cout << "9. Tampilkan isi BST (Pre-Order, In-Order, Post-Order)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;
        cout << endl;

        if (pilihan == 1) {
            string nama;
            cout << "Nama mahasiswa : ";
            cin.ignore();
            getline(cin, nama);
            enqueue(nama);
        }
        else if (pilihan == 2) {
            dequeue();
        }
        else if (pilihan == 3) {
            tampilQueue();
        }
        else if (pilihan == 4) {
            int id;
            cout << "ID buku yang dikembalikan : ";
            cin >> id;
            push(id);
        }
        else if (pilihan == 5) {
            pop();
        }
        else if (pilihan == 6) {
            tampilStack();
        }
        else if (pilihan == 7) {
            int id;
            cout << "Masukkan ID buku : ";
            cin >> id;
            tambah(root, id);
            cout << "ID buku " << id << " ditambahkan ke BST" << endl;
        }
        else if (pilihan == 8) {
            int id;
            cout << "Masukkan ID buku yang dicari : ";
            cin >> id;

            if (cari(root, id)) {
                cout << "ID buku " << id << " ditemukan" << endl;
            } else {
                cout << "ID buku " << id << " tidak ditemukan" << endl;
            }
        }
        else if (pilihan == 9) {
            cout << "Pre Order : ";
            preOrder(root);

            cout << endl;

            cout << "In Order : ";
            inOrder(root);

            cout << endl;

            cout << "Post Order : ";
            postOrder(root);

            cout << endl;
        }
        else if (pilihan != 0) {
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 0);

    return 0;
}