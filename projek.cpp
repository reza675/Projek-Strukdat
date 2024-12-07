#include <iostream>
#include <iomanip>

#define kapasitas 100

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
void TampilHash();
// void HapusDariHash(int kodeProduk);
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
        /* code */
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

void TampilHash(){
    if(isEmptyHash()){
        cout << "\nProduk masih kosong, silahkan input produk terlebih dahulu\n\n";
    } else {
        int n = 1;
        cout << "=====================================================================================" << endl;
        cout << setfill(' ') << setiosflags(std::ios::left);
        cout << "| No. |" << setw(31) << "Nama Produk" << '|' << setw(20) << "Harga Produk" << '|' << setw(17) << "kode Produk" << '|' << setw(6) << "Index" << '|' << endl;
        cout << "=====================================================================================" << endl;

        
        for (int i = 0; i < kapasitas; ++i) {
            if (hashTable[i] != NULL) {
                bantu = hashTable[i];  
                while (bantu != NULL) {
                    cout << "| " << setw(3) << n
                         << " | " << setw(29) << bantu->hashProduk.namaProduk
                         << " | Rp " << setw(15) << bantu->hashProduk.hargaProduk
                         << " | " << setw(15) << bantu->hashProduk.kodeProduk
                         << " | " << setw(4) << i
                         << " |" << endl;
                    bantu = bantu->next; 
                    n++;
                }
                cout << "=====================================================================================\n";
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



