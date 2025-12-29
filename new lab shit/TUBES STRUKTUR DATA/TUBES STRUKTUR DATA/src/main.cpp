#include "Input.h"
#include "StoreSystem.h"

#include <iostream>

using namespace std;

static void printMenu() {
    cout << "\n==== MINI E-COMMERCE TOKO ELEKTRONIK (CLI) ====\n"
              << "1. Lihat tree kategori\n"
              << "2. Tambah kategori\n"
              << "3. Tampilkan produk dalam satu kategori\n"
              << "4. Lihat semua produk\n"
              << "5. Tambah produk ke kategori\n"
              << "6. Hapus produk\n"
              << "7. Lihat semua supplier\n"
              << "8. Tambah supplier\n"
              << "9. Hapus supplier\n"
              << "10. Hubungkan supplier <-> produk\n"
              << "11. Unlink supplier dari produk\n"
              << "12. Cari supplier dari suatu produk\n"
              << "13. Lihat produk yang dipasok supplier\n"
              << "0. Keluar\n";
}

// Format input path: Elektronik > Laptop > Gaming
static vector<string> readPath() {
    string p = input::line("Masukkan path kategori (contoh: Elektronik > Laptop > Gaming): ");
    // split uses '>'
    // We'll just reuse StoreSystem by a temporary instance? Better: local splitter.
    vector<string> parts;
    string cur;
    for (char ch : p) {
        if (ch == '>') {
            // trim cur
            auto l = cur.find_first_not_of(" \t");
            auto r = cur.find_last_not_of(" \t");
            if (l != string::npos) parts.push_back(cur.substr(l, r - l + 1));
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    auto l = cur.find_first_not_of(" \t");
    auto r = cur.find_last_not_of(" \t");
    if (l != string::npos) parts.push_back(cur.substr(l, r - l + 1));
    return parts;
}

int main() {
    StoreSystem store;

    // isi data awal (kategori, produk, supplier)
    store.seedDemoData();

    cout << "Mini E-Commerce: Manage Kategori, Produk, Supplier\n";
    cout << "Data awal sudah di-load (kategori/produk/supplier contoh).\n";

    while (true) {
        printMenu();
        int choice = input::integer("Pilih menu: ");

        switch (choice) {
        case 1: {
            store.printCategories();
            break;
        }
        case 2: {
            auto path = readPath();
            auto* node = store.ensureCategoryPath(path);
            if (node) cout << "Kategori dibuat/tersedia: " << node->name << "\n";
            else cout << "Gagal membuat kategori.\n";
            break;
        }
        case 3: {
            auto path = readPath();
            store.printProductsInCategorySubtree(path);
            break;
        }
        case 4: {
            store.printAllProducts();
            break;
        }
        case 5: {
            auto path = readPath();
            int id = input::integer("ID Produk: ");
            string name = input::line("Nama Produk: ");
            double price = input::number("Harga (angka): ");

            auto* p = store.addProductToCategory(path, id, name, price);
            if (!p) {
                cout << "Gagal menambah produk (mungkin ID sudah ada).\n";
            } else {
                cout << "Produk ditambahkan: [" << p->id << "] " << p->name << "\n";
            }
            break;
        }
        case 6: {
            int pid = input::integer("ID Produk yang dihapus: ");
            if (store.deleteProduct(pid)) cout << "Produk berhasil dihapus.\n";
            else cout << "Produk tidak ditemukan.\n";
            break;
        }
        case 7: {
            store.printAllSuppliers();
            break;
        }
        case 8: {
            int id = input::integer("ID Supplier: ");
            string name = input::line("Nama Supplier: ");
            auto* s = store.addSupplier(id, name);
            if (!s) cout << "Gagal menambah supplier (mungkin ID sudah ada).\n";
            else cout << "Supplier ditambahkan: [" << s->id << "] " << s->name << "\n";
            break;
        }
        case 9: {
            int sid = input::integer("ID Supplier yang dihapus: ");
            if (store.deleteSupplier(sid)) cout << "Supplier berhasil dihapus (relasi dilepas).\n";
            else cout << "Supplier tidak ditemukan.\n";
            break;
        }
        case 10: {
            int sid = input::integer("ID Supplier: ");
            int pid = input::integer("ID Produk: ");
            if (store.linkSupplierToProduct(sid, pid)) cout << "Berhasil di-link.\n";
            else cout << "Gagal link (cek ID / mungkin sudah terhubung).\n";
            break;
        }
        case 11: {
            int sid = input::integer("ID Supplier: ");
            int pid = input::integer("ID Produk: ");
            if (store.unlinkSupplierFromProduct(sid, pid)) cout << "Berhasil di-unlink.\n";
            else cout << "Gagal unlink (cek ID / mungkin belum terhubung).\n";
            break;
        }
        case 12: {
            int pid = input::integer("ID Produk: ");
            store.printSuppliersOfProduct(pid);
            break;
        }
        case 13: {
            int sid = input::integer("ID Supplier: ");
            store.printProductsOfSupplier(sid);
            break;
        }
        case 0:
            cout << "Bye!\n";
            return 0;
        default:
            cout << "Pilihan tidak dikenal.\n";
            break;
        }
    }
}
