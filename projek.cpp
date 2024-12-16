#include <iostream>
#include <iomanip>
#include <string>

#define kapasitas 20
#define RESET   "\033[0m"
#define RED     "\033[38;2;255;0;0m"
#define GREEN   "\033[38;2;0;255;0m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

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
    tokoSerba historyProduk; 
    History *left;
    History *right;
};

BinaryTree *root = NULL, *hapusNode; 
hashNode *hashTable[kapasitas] = {NULL};
hashNode *temp, *newNode, *bantu, *bantu2, *hapus; 
History *historyRoot = NULL;

bool isEmptyHash();
void tampilanBST();
void tampilanHash();
void anggota();
void penutup();
int hashFunction(string kodeProduk);
hashNode *cariKode(string kodeProduk);
BinaryTree *tambahProdukTree(BinaryTree *node, const tokoSerba &produk);
void tambahProdukKeHash(const tokoSerba &produk);
string formatHarga(int harga);
void TampilHash();
void HapusDariHash(string kodeProduk);
BinaryTree *hapusDariBST(BinaryTree *node, string namaProduk);
void pencarianHash();
void pencarianBST(BinaryTree *node, string startName, string endName,int &i, bool &found);
void urutkanProdukDescending(BinaryTree *node, int &index);
void tampilkanProdukDescending(BinaryTree *root);
History *tambahKeHistory(History *node, const tokoSerba &produk);
void riwayatInOrder(History *node, int &i);
void riwayatPostOrder(History *node, int &i);
void preOrderTraversal(History *node, int &i); 


int main () {
    char pil,Pilihan;
    int pilih,pilih2,pilih3, jumlahProduk;
    bool cek = false;
    anggota();
    do {
        system("cls");
        cout << "+==========================================+\n";
        cout << "|         TOKO KELONTONG SERBA ADA         |\n";
        cout << "+==========================================+\n";
        cout << "| [1] Input Produk                         |\n";
        cout << "| [2] Tampilkan Data Produk                |\n";
        cout << "| [3] Hapus Produk                         |\n";
        cout << "| [4] Pencarian Produk                     |\n";
        cout << "| [5] Pengurutan Produk Berdasarkan Nama   |\n";
        cout << "| [6] History Produk                       |\n";
        cout << "| [7] Keluar                               |\n";
        cout << "+==========================================+\n";
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
                                cout << RED << "Kode Produk " << produk.kodeProduk << " telah digunakan, silakan coba lagi.\n" << RESET;
                            }
                        } while (cek);
                        tambahProdukKeHash(produk);
                    }
                    
        break;
        case 2:
            system("cls");
            cout << "=============================================================\n";
            cout << "|                    Tampilan Data Produk                   |\n";
            cout << "=============================================================\n\n";
            TampilHash();
            break;
        case 3:
            system("cls");
            cout << "=============================================================\n";
            cout << "|                       Hapus Produk                        |\n";
            cout << "=============================================================\n\n";
            if (isEmptyHash()) {
                cout << CYAN <<"Produk masih kosong, silahkan input produk terlebih dahulu!\n\n" << RESET;
            } else {
                string kodeHapus;
                // cout << "Data produk yang tersedia:\n";
                TampilHash();
                
                cin.ignore();
                cout << "\nMasukkan Kode Produk yang ingin dihapus: ";
                getline(cin, kodeHapus);
                
                HapusDariHash(kodeHapus);
            }
            break;
        case 4: 
                system("cls");
                cout << "+=========================================+\n";
                cout << "|            PENCARIAN PRODUK             |\n";
                cout << "+=========================================+\n";
                cout << "| [1] Berdasarkan Kode Produk             |\n";
                cout << "| [2] Berdasarkan Nama Produk             |\n";
                cout << "| [3] Kembali ke Menu Utama               |\n";
                cout << "+=========================================+\n";
                cout << "Pilih Sub-Menu (1-3): ";
                cin >> pilih2;
                switch (pilih2) {
                case 1:
                    pencarianHash(); // Pencarian berdasarkan kode
                    break;
                case 2:
                    system("cls");
                    cout << "=============================================================\n";
                    cout << "|     Pencarian Produk Berdasarkan Rentang Nama [BST]       |\n";
                    cout << "=============================================================\n\n";
                    if (root == NULL) {
                        cout << CYAN << "Produk masih kosong, silahkan input produk terlebih dahulu!\n\n" << RESET;
                    } else {
                        string startName, endName;
                        cout << "Masukkan rentang awal nama produk: ";
                        cin.ignore();
                        getline(cin, startName);
                        cout << "Masukkan rentang akhir nama produk: ";
                        getline(cin, endName);
                        int i = 1;
                        bool found = false;
                        pencarianBST(root, startName, endName, i, found);  
                        if (!found) {
                            cout << CYAN << "\nProduk dengan nama \"" << startName << "\" hingga \"" << endName << "\" tidak ditemukan.\n" << RESET;
                        }
                    }
                    break;
                case 3:
                    // Kembali ke menu utama
                    break;
                default:
                    cout << "Input tidak valid! Silakan coba lagi.\n";
                }  
            break;
        case 5:
            system("cls");
            cout << "=============================================================\n";
            cout << "|           Pengurutan Data Secara Descending               |\n";
            cout << "=============================================================\n\n";
            tampilkanProdukDescending(root);
            break;
        case 6: {
            system ("cls");
            int i = 1;
            cout << "+=========================================+\n";
            cout << "|              History Produk             |\n";
            cout << "+=========================================+\n";
            cout << "| [1] History Produk In-Order             |\n";
            cout << "| [2] History Produk Post-Order           |\n";
            cout << "| [3] History Produk Pre-Order            |\n";
            cout << "| [4] Kembali ke Menu Utama               |\n";
            cout << "+=========================================+\n";
            cout << "Pilih Sub-Menu (1-4): ";
            cin>> pilih3;
            switch (pilih3) {
            case 1:
                system("cls");
                cout << "=============================================================\n";
                cout << "|                    History Produk In-Order                |\n";
                cout << "=============================================================\n\n";
                if (historyRoot == NULL) {
                    cout << CYAN << "History produk masih kosong, silahkan hapus produk terlebih dahulu!\n" << RESET;
                }else {
                    cout << "Data Produk yang telah dihapus:\n";
                    tampilanBST();
                    riwayatInOrder(historyRoot,i);
                    cout << "=================================================================================\n";
                }
                break;
            case 2:
                system("cls");
                cout << "=============================================================\n";
                cout << "|                   History Produk Post-Order               |\n";
                cout << "=============================================================\n\n";
                if (historyRoot == NULL) {
                    cout << CYAN << "History produk masih kosong, silahkan hapus produk terlebih dahulu!\n" << RESET;
                }else {
                    cout << "Data Produk yang telah dihapus:\n";
                    tampilanBST();
                    riwayatPostOrder(historyRoot,i);
                    cout << "=================================================================================\n";
                }
                break;
            case 3:
                system("cls");
                cout << "=============================================================\n";
                cout << "|                   History Produk Pre-Order                |\n";
                cout << "=============================================================\n\n";
                if (historyRoot == NULL) {
                    cout << CYAN << "History produk masih kosong, silahkan hapus produk terlebih dahulu!\n" << RESET;
                }else {
                    cout << "Data Produk yang telah dihapus:\n";
                    tampilanBST();
                    preOrderTraversal(historyRoot,i);
                    cout << "=================================================================================\n";
                }
                break;
            case 4:
                // Kembali ke menu utama
                break;
            default:
                cout << "Input tidak valid! Silakan coba lagi.\n";
            }
            break;
        break;
        }case 7:
            system("cls");
            penutup();
            exit(0);
            break;
        default:
        cout << "Input tidak valid!" << endl;
        break;
    }
            if(pilih2 == 3 || pilih3 == 4){ 
                pil = 'y';
                pilih2 = 0; pilih3 = 0;
            }else {
                do {
                    cout << YELLOW << "\nIngin mencoba menu lain? (y/n) : " << RESET;
                    cin >> pil; 
                    if (pil != 'y' && pil != 'Y' && pil != 'n' && pil != 'N') {
                        cout << RED << "Input tidak valid.\n" << RESET;
                    }
                } while (pil != 'y' && pil != 'Y' && pil != 'n' && pil != 'N');
                penutup();
            }
        
    } while (pil == 'y' || pil == 'Y');
    
    return 0;
}

void anggota() {
    system("cls");
    cout << "+================================================+\n";
    cout << "|                KELOMPOK KAMI                   |\n";
    cout << "=================================================+\n";
    cout << "| Ayudya Prameswari                  (123230016) |\n";
    cout << "| Zulfa Perwitasari                  (123230017) |\n";
    cout << "| Salman Faris                       (123230024) |\n";
    cout << "| Irfan Fitra Pratama                (123230028) |\n";
    cout << "| Reza Rasendriya Adi Putra          (123220030) |\n";
    cout << "==================================================\n";
    system("pause");
}
void penutup () {
    system("cls");
    cout << "+==========================================+\n";
    cout << "|               TERIMA KASIH               |\n";
    cout << "|         TELAH MENGUNAKAN PROGRAM         |\n";
    cout << "|         TOKO KELONTONG SERBA ADA         |\n";
    cout << "+==========================================+\n";
    cout << "|          Sampai Jumpa di Lain Waktu      |\n";
    cout << "+==========================================+\n";
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




void tambahProdukKeHash(const tokoSerba &produk){
    int index = hashFunction(produk.kodeProduk);
    newNode = new hashNode{produk, NULL};
    
    int element = 1; // Elemen ke-1 jika bucket kosong
    bantu = hashTable[index];
    while (bantu != NULL) {
        bantu = bantu->next;
        element++;
    }
    
    if (hashTable[index] == NULL){
        hashTable[index] = newNode;
    }else{
        bantu = hashTable[index];
        while (bantu->next != NULL){
            bantu = bantu->next;
        }
        bantu->next = newNode;
    }
    cout << GREEN <<"\nProduk " << produk.namaProduk << " Berhasil ditambahkan ke hash table pada indeks ke-[" << index << "] dengan elemen ke-[" << element << ']' << RESET << endl;
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
void tampilanHash() {
    cout << "==============================================================================================" << endl;
    cout << setfill(' ') << setiosflags(std::ios::left);
    cout << "| No. |" << setw(31) << "Nama Produk" << '|' << setw(20) << "Harga Produk" << '|' << setw(17) << "Kode Produk" << '|' << setw(6) << "Index" << '|' << setw(8) << "Element" << '|' << endl;
    cout << "==============================================================================================" << endl;
}

void TampilHash() {
    if (isEmptyHash()) {
        cout << CYAN << "Produk masih kosong, silahkan input produk terlebih dahulu!\n\n" << RESET;
    } else {
        int n = 1;
        cout << "Data produk yang tersedia:\n";
        tampilanHash();
        for (int i = 0; i < kapasitas; i++) {
            if (hashTable[i] != NULL) {
                bantu = hashTable[i];
                int element = 1;
                while (bantu != NULL) {
                    cout << "| " << setw(3) << n << " | " << setw(29) << bantu->hashProduk.namaProduk << " | Rp " << setw(15) << formatHarga(bantu->hashProduk.hargaProduk) << " | " << setw(15) << bantu->hashProduk.kodeProduk << " | " << setw(4) << i << " | " << setw(6) << element << " |" << endl;
                    bantu = bantu->next; 
                    n++; 
                    element++;
                }
                cout << "==============================================================================================\n";
            }
        }
    }
}
    
BinaryTree *tambahProdukTree(BinaryTree *node, const tokoSerba &produk) {
    if (node == NULL) {
        node = new BinaryTree{produk, NULL, NULL};
        return node;
    }

    if (produk.namaProduk < node->produk.namaProduk) {
        node->left = tambahProdukTree(node->left, produk); //Rekurrsif ke kiri
    } else if (produk.namaProduk > node->produk.namaProduk) {
        node->right = tambahProdukTree(node->right, produk); //Rekursif ke kanan
    }

    return node;
}

void HapusDariHash(string kodeProduk) {
    int index = hashFunction(kodeProduk);
    hapus = hashTable[index];
    hashNode *sebelum = NULL;

    //mencari produk memakai kode yg sesuai
    while (hapus != NULL && hapus->hashProduk.kodeProduk != kodeProduk) {
        sebelum = hapus;
        hapus = hapus->next;
    }

    if (hapus != NULL) {
        if (sebelum == NULL) {
            hashTable[index] = hapus->next;
        } else {
            sebelum->next = hapus->next;
        }
        
        historyRoot = tambahKeHistory(historyRoot, hapus->hashProduk);
        string namaProduk = hapus->hashProduk.namaProduk;
        root = hapusDariBST(root, hapus->hashProduk.namaProduk);
        delete hapus;
        cout << RED << "\nProduk \"" << namaProduk << "\" dengan kode \"" << kodeProduk << "\" berhasil dihapus dari tabel hash\n" << RESET;
    } else {
        cout << CYAN << "\nProduk dengan kode " << kodeProduk << " tidak ditemukan.\n" << RESET;
    }
}  

BinaryTree *hapusDariBST(BinaryTree *node, string namaProduk) {
    if (node == NULL) {
        return NULL;
    }
    if (namaProduk < node->produk.namaProduk) {
        node->left = hapusDariBST(node->left, namaProduk);
    } else if (namaProduk > node->produk.namaProduk) {
        node->right = hapusDariBST(node->right, namaProduk);
    } else {
        if (node->left == NULL) {
            // Node hanya memiliki child kanan atau tidak memiliki child
            hapusNode = node->right;
            delete node;
            return hapusNode;
        } else if (node->right == NULL) {
            // Node hanya memiliki child kiri
            hapusNode = node->left;
            delete node;
            return hapusNode;
        } else {
            // Node memiliki kedua child
            BinaryTree *pengganti = node->right;
            while (pengganti->left != NULL) {
                pengganti = pengganti->left;
            }
            node->produk = pengganti->produk;
            node->right = hapusDariBST(node->right, pengganti->produk.namaProduk); // Hapus pengganti dari tree
        }
    }
    return node;
}

void tampilanBST() {
    cout << "=================================================================================\n";
    cout << setfill(' ') << setiosflags(std::ios::left);
    cout << "| No. | " << setw(30) << "Nama Produk" << " | " << setw(20) << "Harga Produk" << "| " << setw(16) << "Kode Produk" << " |\n";
    cout << "=================================================================================\n";
}
void pencarianHash() {
    system("cls");
    cout << "=============================================================\n";
    cout << "|      Pencarian Produk Berdasarkan Kode Produk [Hash]      |\n";
    cout << "=============================================================\n\n";
    if (isEmptyHash()) {
        cout << CYAN << "Produk masih kosong, silahkan input produk terlebih dahulu!\n\n" << RESET;
    } else {
        string cariKodeProduk;
        cin.ignore();
        cout << "Masukkan Kode Produk yang ingin dicari: "; getline(cin, cariKodeProduk);
        int index = hashFunction(cariKodeProduk);
        bantu2 = hashTable[index];
        int element = 1;
        while (bantu2 != NULL) {
            if (bantu2->hashProduk.kodeProduk == cariKodeProduk) {
                cout << "\nData Produk dengan Kode Produk \"" << cariKodeProduk << "\" ditemukan:\n";
                cout << "==============================================================================================" << endl;
                cout << setfill(' ') << setiosflags(std::ios::left);
                cout << "| " <<setw(31) << "Nama Produk" << '|' << setw(20) << "Harga Produk" << " | " << setw(17) << "Kode Produk" << '|' << setw(7) << "Index" << '|' << setw(10) << "Element" << '|' << endl;
                cout << "==============================================================================================" << endl;
                cout << "| " << setw(30) << bantu2->hashProduk.namaProduk
                     << " | Rp " << setw(16) << formatHarga(bantu2->hashProduk.hargaProduk)
                     << " | " << setw(16) << bantu2->hashProduk.kodeProduk
                     << " | " << setw(5) << index
                     << " | " << setw(8) << element << " |" << endl;
                cout << "==============================================================================================\n";
                return;
            }
            bantu2 = bantu2->next;
            element++; 
        }
        cout << CYAN << "\nProduk dengan kode \"" << cariKodeProduk << "\" tidak ditemukan.\n" << RESET;
    }
}

void pencarianBST(BinaryTree *node, string startName, string endName, int &i, bool &found) {
    if (node == NULL) {
        return;
    }
    if (startName < node->produk.namaProduk) {
        pencarianBST(node->left, startName, endName, i, found);
    }
    // Cetak produk jika berada dalam rentang
    if (node->produk.namaProduk >= startName && node->produk.namaProduk <= endName) {
        if (!found) {
            found = true; 
            cout << "\nProduk dengan nama \"" << startName << "\" hingga \"" << endName << "\" ditemukan:\n";
            tampilanBST();
        }
        cout << "| " << setw(4) << i << "| " << setw(30) << node->produk.namaProduk << " | Rp " << setw(16) << formatHarga(node->produk.hargaProduk) << " | " << setw(16) << node->produk.kodeProduk << " |\n";
        i++;
        cout << "=================================================================================\n";
    }
    if (endName > node->produk.namaProduk) {
        pencarianBST(node->right, startName, endName, i, found);
    }
}
void urutkanProdukDescending(BinaryTree *node, int &index) {
    if (node == NULL) {
        return;
    }
    urutkanProdukDescending(node->right, index);
    cout << "| " << setw(3) << index << " | " << setw(30) << node->produk.namaProduk << " | Rp " << setw(16) << formatHarga(node->produk.hargaProduk) << " | " << setw(16) << node->produk.kodeProduk << " |\n";
    cout << "=================================================================================\n";
    index++;
    urutkanProdukDescending(node->left, index);
}

void tampilkanProdukDescending(BinaryTree *root) {
    if (root == NULL) {
        cout << CYAN << "Produk masih kosong, silahkan input produk terlebih dahulu!\n\n" << RESET;
        return;
    }
    int index = 1;
    cout << "Data produk yang diurutkan secara descending:\n";
    tampilanBST();
    urutkanProdukDescending(root, index);
}



History *tambahKeHistory(History *node, const tokoSerba &produk) {
    if (node == NULL) {
        node = new History{produk, NULL, NULL};
        return node;
    }

    if (produk.namaProduk < node->historyProduk.namaProduk) {
        node->left = tambahKeHistory(node->left, produk); // Rekursif ke kiri
    } else if (produk.namaProduk > node->historyProduk.namaProduk) {
        node->right = tambahKeHistory(node->right, produk); // Rekursif ke kanan
    }
    return node;
}

void riwayatInOrder(History *node, int &i) {
    if (node == NULL) {
        return;
    }
    riwayatInOrder(node->left, i);
    cout << "| " << setw(3) << i++ << " | " << setw(30) << node->historyProduk.namaProduk << " | Rp " << setw(16) << formatHarga(node->historyProduk.hargaProduk) << " | " << setw(16) << node->historyProduk.kodeProduk << " |\n";
    riwayatInOrder(node->right, i);
}

void preOrderTraversal(History *node, int &i) {
    if (node == NULL) {
        return;
    }
    cout << "| " << setw(3) << i++ << " | " << setw(30) << node->historyProduk.namaProduk << " | Rp " << setw(16) << formatHarga(node->historyProduk.hargaProduk) << " | " << setw(16) << node->historyProduk.kodeProduk << " |\n";
    preOrderTraversal(node->left, i);
    preOrderTraversal(node->right, i);
}

void riwayatPostOrder(History *node, int &i) {
    if (node == NULL) {
        return;
    }
    riwayatPostOrder(node->left, i);
    riwayatPostOrder(node->right, i);
    cout << "| " << setw(3) << i++ << " | " << setw(30) << node->historyProduk.namaProduk << " | Rp " << setw(16) << formatHarga(node->historyProduk.hargaProduk) << " | " << setw(16) << node->historyProduk.kodeProduk << " |\n";
}
