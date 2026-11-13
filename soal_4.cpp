#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

class HashTable {
private:
    vector<pair<int, string>> table;
    vector<int> status; // 0 = kosong, 1 = terisi, 2 = dihapus

    // Hash1(key) = key % 20
    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    // Hash2(key) = 19 - (key % 19)
    int hash2(int key) {
        return 19 - (key % 19);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        status.resize(TABLE_SIZE, 0);
    }

    void insert(int key, string value) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        int deletedIndex = -1;

        while (true) {
            if (status[index] == 1 && table[index].first == key) {
                table[index].second = value;
                cout << "Key " << key << " sudah ada, nama diperbarui" << endl;
                return;
            }

            if (status[index] == 2 && deletedIndex == -1) {
                deletedIndex = index;
            }

            if (status[index] == 0) {
                if (deletedIndex != -1) {
                    index = deletedIndex;
                }

                table[index] = make_pair(key, value);
                status[index] = 1;
                cout << "Insert " << key << " (" << value << ") ke index " << index << endl;
                return;
            }

            // collision 
            if (status[index] == 1) {
                cout << "  Collision pada index " << index << " (key " << table[index].first << ")" << endl;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        if (deletedIndex != -1) {
            table[deletedIndex] = make_pair(key, value);
            status[deletedIndex] = 1;
            cout << "Insert " << key << " (" << value << ") ke index " << deletedIndex << endl;
        } else {
            cout << "Tabel penuh" << endl;
        }
    }

    void search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                cout << "Data ditemukan pada index " << index << " : " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                status[index] = 2;
                cout << "Data berhasil dihapus" << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";

            if (status[i] == 1) {
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == 2) {
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }

            cout << endl;
        }
    }
};

int main() {
    system("cls");
    HashTable ht;

    cout << "=== INSERT 15 DATA MAHASISWA ===" << endl;
    ht.insert(251401001, "Daniel");
    ht.insert(251401011, "Aditya");
    ht.insert(251401021, "Aksa");
    ht.insert(251401005, "Febrian");
    ht.insert(251401015, "Rafly");
    ht.insert(251401025, "Hafifudin");
    ht.insert(251401002, "Wira");
    ht.insert(251401012, "Wahyudi");
    ht.insert(251401022, "Patrick");
    ht.insert(251401007, "Milan");
    ht.insert(251401016, "Axel");
    ht.insert(251401027, "Malvin");
    ht.insert(251401009, "Poltack");
    ht.insert(251401019, "Boy");
    ht.insert(251401029, "Ferdinand");

    cout << "\n=== ISI HASH TABLE ===" << endl;
    ht.display();

    cout << "\n=== SEARCH ===" << endl;
    cout << "Mencari key 251401011 : " << endl;
    ht.search(251401011);
    cout << "Mencari key 251401099 : " << endl;
    ht.search(251401099);

    cout << "\n=== REMOVE ===" << endl;
    cout << "Menghapus key 251401011 : " << endl;
    ht.remove(251401011);
    cout << "Menghapus key 251401005 : " << endl;
    ht.remove(251401005);
    cout << "Menghapus key 251401099 : " << endl;
    ht.remove(251401099);

    cout << "\n=== ISI HASH TABLE SETELAH PENGHAPUSAN ===" << endl;
    ht.display();

    cout << "\n=== SEARCH SETELAH PENGHAPUSAN ===" << endl;
    cout << "Mencari key 251401011 : " << endl;
    ht.search(251401011);
    cout << "Mencari key 251401021 : " << endl;
    ht.search(251401021);

    cout << "\n=== INSERT ULANG (memakai slot DELETED) ===" << endl;
    ht.insert(251401031, "Putra");

    cout << "\n=== ISI HASH TABLE AKHIR ===" << endl;
    ht.display();

    return 0;
}