#include <iostream>
#include <iomanip>
#include <string>

#define kapasitas 20

using namespace std;

struct tokoSerba {
    string namaProduk,kodeProduk;
    int hargaProduk;
};

struct hashNode {
    tokoSerba hashProduk;
    hashNode *next;
};
struct BinaryTree {
    tokoSerba produk;         
    BinaryTree *left;         
    BinaryTree *right;      
};
struct History{
 
};

BinaryTree *root = NULL; 
hashNode *hashTable[kapasitas] = {NULL};
hashNode *temp, *newNode, *bantu; 
// History* historyTree = NULL;

bool isEmptyHash();
int hashFunction(int kodeProduk);
hashNode *cariKode(string kodeProduk);
BinaryTree *tambahProdukTree(BinaryTree *node, const tokoSerba &produk);
void tambahProdukKeHash(const tokoSerba &produk);
string formatHarga(int harga);
void TampilHash();
void HapusDariHash(string kodeProduk);
// Hash* CariProdukHash(int kodeProduk);
// void TambahProdukTree(const &produk);





int main () {
    char pil,Pilihan;
    int pilih, jumlahProduk;
    bool cek = false;
    do {
        system("cls");
        cout << "+=========================================+\n";
        cout << "|         TOKO KELONTONG SERBA ADA        |\n";
        cout << "+=========================================+\n";
        cout << "| [1] Input Produk                        |\n";
        cout << "| [2] Tampilkan Data Produk               |\n";
        cout << "| [3] Hapus Produk                        |\n";
        cout << "| [4] Pencarian Produk                    |\n";
        cout << "| [5] Pengurutan Produk Berdasarkan Nama  |\n";
        cout << "| [6] Riwayat Produk                      |\n";
        cout << "| [7] Keluar                              |\n";
        cout << "+=========================================+\n";
        cout << "Pilih Menu (1-7): ";
        cin >> pilih;
        switch (pilih){
        case 1:
            system("cls");
                cout << "=============================================================\n";
                cout << "|                     Input Produk Ke Hash                  |\n";
                cout << "=============================================================\n\n";
                cout << "Jumlah Produk yang di Input: ";
                cin >> jumlahProduk;
                cin.ignore();
                    for (int i = 0; i < jumlahProduk; i++) {
                        tokoSerba produk;
                        cout << "\nProduk ke-[" << i+1 << ']' << endl;
                        cout << "Nama Produk\t\t: "; getline(cin, produk.namaProduk);
                        cout << "Harga Produk\t\t: Rp "; cin >> produk.hargaProduk;
                        cin.ignore();
                        do {
                            cek = false;                           
                            cout << "Kode Produk\t\t: "; getline(cin, produk.kodeProduk);
                            
                            // Cek apakah kode produk sudah ada
                            if (cariKode(produk.kodeProduk) != NULL) {
                                cek = true;
                                cout << "Kode Produk " << produk.kodeProduk << " telah digunakan, silakan coba lagi.\n";
                            }
                        } while (cek);
                        tambahProdukKeHash(produk);
                        cout << endl;
                    }
                    
        break;
        case 2:
            system("cls");
            cout << "=============================================================\n";
            cout << "|                       Data Produk                         |\n";
            cout << "=============================================================\n\n";
            TampilHash();
            break;
        case 3:
            system("cls");
            cout << "=============================================================\n";
            cout << "|                       Hapus Produk                        |\n";
            cout << "=============================================================\n\n";
            if (isEmptyHash()) {
                cout << "\nProduk masih kosong, tidak ada yang bisa dihapus\n\n";
            } else {
                string kodeHapus;
                cout << "Data Produk yang tersedia:\n\n";
                TampilHash();
                
                cin.ignore();
                cout << "\nMasukkan Kode Produk yang ingin dihapus: ";
                getline(cin, kodeHapus);
                
                HapusDariHash(kodeHapus);
            }

        break;
            case 4:
        /* code */
        break;
            case 5:
        /* code */
        break;
            case 6:
        /* code */
        break;
            case 7:
        /* code */
        break;
    default:
        cout << "Input tidak valid!" << endl;
        break;
    }

            do {
                cout << "\nIngin mencoba menu lain? (y/n) : ";
                cin >> pil; 
                if (pil != 'y' && pil != 'Y' && pil != 'n' && pil != 'N') {
                    cout << "Input tidak valid.\n";
                }
            } while (pil != 'y' && pil != 'Y' && pil != 'n' && pil != 'N');
            cout << "\nTerima Kasih telah menggunakan program ini\n";
        
    } while (pil == 'y' || pil == 'Y');
    
    return 0;
}

bool isEmptyHash() {
    for (int i = 0; i < kapasitas; i++) {
        if (hashTable[i] != NULL) return false;
    }
    return true;
}
int hashFunction(string kodeProduk) {
    int nilaiHash = 0;
    for (char karakter : kodeProduk) {
        nilaiHash += karakter;  // setiap karakter diubah ke ASCII
    }
    return nilaiHash % kapasitas;
}


hashNode* cariKode(string kodeProduk) {
    int index = hashFunction(kodeProduk);
    temp = hashTable[index];
    while (temp != NULL) {
        if (temp->hashProduk.kodeProduk == kodeProduk) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}




void tambahProdukKeHash(const tokoSerba& produk){
    int index = hashFunction(produk.kodeProduk);
    newNode = new hashNode{produk, NULL};
    
    if (hashTable[index] == NULL){
        hashTable[index] = newNode;
        cout <<"\nProduk " << produk.namaProduk << " Berhasil ditambahkan ke hash table pada indeks ke-[" << index << ']';
    }else{
        bantu = hashTable[index];
        while (bantu->next != NULL){
            bantu = bantu->next;
        }
        bantu->next = newNode;
        cout <<"\nProduk " << produk.namaProduk << " Berhasil ditambahkan ke hash table pada indeks ke-[" << index << ']';
    }
    //menyalin data table hash ke binary search tree
    root = tambahProdukTree(root, produk);
    
}
string formatHarga(int harga) {
    string hasil = to_string(harga); // Mengubah angka menjadi string
    int len = hasil.size();
    int count = 0;
    string formatted;

    for (int i = len - 1; i >= 0; i--) {
        formatted = hasil[i] + formatted;
        count++;
        if (count == 3 && i != 0) {
            formatted = '.' + formatted;
            count = 0;
        }
    }

    return formatted;
}


void TampilHash() {
    if (isEmptyHash()) {
        cout << "\nProduk masih kosong, silahkan input produk terlebih dahulu\n\n";
    } else {
        int n = 1;
        cout << "==============================================================================================" << endl;
        cout << setfill(' ') << setiosflags(std::ios::left);
        cout << "| No. |" << setw(31) << "Nama Produk" << '|' << setw(20) << "Harga Produk" << '|' << setw(17) << "Kode Produk" << '|' << setw(6) << "Index" << '|' << setw(8) << "Element" << '|' << endl;
        cout << "==============================================================================================" << endl;

        for (int i = 0; i < kapasitas; i++) {
            if (hashTable[i] != NULL) {
                bantu = hashTable[i];
                int element = 1; // Penomoran elemen pada indeks ini dimulai dari 1
                while (bantu != NULL) {
                    cout << "| " << setw(3) << n
                         << " | " << setw(29) << bantu->hashProduk.namaProduk
                         << " | Rp " << setw(15) << formatHarga(bantu->hashProduk.hargaProduk)
                         << " | " << setw(15) << bantu->hashProduk.kodeProduk
                         << " | " << setw(4) << i
                         << " | " << setw(6) << element << " |" << endl;
                    bantu = bantu->next; 
                    n++; 
                    element++;
                }
                cout << "==============================================================================================\n";
            }
        }
    }
}
    
BinaryTree* tambahProdukTree(BinaryTree* node, const tokoSerba& produk) {
    if (node == NULL) {
        node = new BinaryTree{produk, NULL, NULL};

        return node;
    }

    if (produk.kodeProduk < node->produk.kodeProduk) {
        node->left = tambahProdukTree(node->left, produk); // Rekursif ke kiri
    } else if (produk.kodeProduk > node->produk.kodeProduk) {
        node->right = tambahProdukTree(node->right, produk); // Rekursif ke kanan
    }
    return node;
}

void HapusDariHash(string kodeProduk) {
    int index = hashFunction(kodeProduk);
    hashNode *current = hashTable[index];
    hashNode *sebelum = NULL;

    //mencari produk memakai kode yg sesuai
    while (current != NULL && current->hashProduk.kodeProduk != kodeProduk) {
        sebelum = current;
        current = current->next;
    }

    // klo produk ditemuin
    if (current != NULL) {
        //klp node yg mau diapus ni yang pertama
        if (sebelum == NULL) {
            hashTable[index] = current->next;
        } else {
            sebelum->next = current->next;
        }
        
        string namaProduk = current->hashProduk.namaProduk;
        delete current;
        cout << "\nProduk " << namaProduk << " dengan kode " << kodeProduk << " berhasil dihapus dari tabel hash\n";
    } else {
        cout << "\nProduk dengan kode " << kodeProduk << " tidak ditemukan\n";
    }
}   