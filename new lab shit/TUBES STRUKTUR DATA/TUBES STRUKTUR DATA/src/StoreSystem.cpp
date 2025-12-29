#include "StoreSystem.h"

#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

StoreSystem::StoreSystem() = default;

StoreSystem::~StoreSystem() {
    deleteAllProducts();
}

void StoreSystem::deleteAllProducts() {
    Product* p = m_allProducts;
    while (p) {
        // free supplier refs owned by product
        SupplierRef* sr = p->suppliers;
        while (sr) {
            SupplierRef* next = sr->next;
            delete sr;
            sr = next;
        }
        p->suppliers = nullptr;

        Product* nextP = p->nextGlobal;
        delete p;
        p = nextP;
    }
    m_allProducts = nullptr;
}

Product* StoreSystem::createProduct(int id, const string& name, double price) {
    auto* p = new Product();
    p->id = id;
    p->name = name;
    p->price = price;
    return p;
}

Product* StoreSystem::findProductInGlobalList(int id) const {
    for (Product* p = m_allProducts; p; p = p->nextGlobal) {
        if (p->id == id) return p;
    }
    return nullptr;
}

CategoryNode* StoreSystem::ensureCategoryPath(const vector<string>& path) {
    return m_tree.ensurePath(path);
}

CategoryNode* StoreSystem::findCategoryPath(const vector<string>& path) const {
    return m_tree.findPath(path);
}

void StoreSystem::printCategories() const {
    m_tree.print();
}

vector<string> StoreSystem::splitPath(const string& path, char delim) {
    vector<string> parts;
    stringstream ss(path);
    string item;

    while (getline(ss, item, delim)) {
        // trim spaces
        auto l = item.find_first_not_of(" \t");
        auto r = item.find_last_not_of(" \t");
        if (l == string::npos) continue;
        parts.push_back(item.substr(l, r - l + 1));
    }
    return parts;
}

Product* StoreSystem::addProductToCategory(const vector<string>& categoryPath, int productId, const string& name, double price) {
    if (findProductInGlobalList(productId)) return nullptr;

    CategoryNode* cat = ensureCategoryPath(categoryPath);
    if (!cat) return nullptr;

    Product* p = createProduct(productId, name, price);

    // Insert into category list
    m_tree.addProduct(cat, p);

    // Insert into global list
    p->nextGlobal = m_allProducts;
    m_allProducts = p;

    return p;
}

Product* StoreSystem::findProduct(int productId) const {
    if (auto* p = findProductInGlobalList(productId)) return p;
    // fallback
    return m_tree.findProductInSubtree(m_tree.root(), productId);
}

void StoreSystem::printProductsInCategorySubtree(const vector<string>& categoryPath) const {
    CategoryNode* cat = findCategoryPath(categoryPath);
    if (!cat) {
        cout << "Kategori tidak ditemukan.\n";
        return;
    }
    m_tree.printProductsInSubtree(cat);
}

void StoreSystem::printAllProducts() const {
    cout << "\n=== DAFTAR PRODUK ===\n";
    if (!m_allProducts) {
        cout << "(belum ada produk)\n";
        return;
    }
    for (Product* p = m_allProducts; p; p = p->nextGlobal) {
        cout << "- [" << p->id << "] " << p->name
                  << " | Rp" << p->price;
        if (p->category) {
            cout << " | Kategori: " << p->category->name;
        }
        cout << "\n";
    }
}

bool StoreSystem::detachProductFromCategory(Product* product) {
    if (!product || !product->category) return false;
    CategoryNode* cat = product->category;
    Product* prev = nullptr;
    Product* cur = cat->products;
    while (cur && cur != product) {
        prev = cur;
        cur = cur->nextInCategory;
    }
    if (!cur) return false;
    if (prev) prev->nextInCategory = cur->nextInCategory;
    else cat->products = cur->nextInCategory;
    cur->nextInCategory = nullptr;
    cur->category = nullptr;
    return true;
}

bool StoreSystem::detachProductFromGlobalList(Product* product) {
    if (!product) return false;
    Product* prev = nullptr;
    Product* cur = m_allProducts;
    while (cur && cur != product) {
        prev = cur;
        cur = cur->nextGlobal;
    }
    if (!cur) return false;
    if (prev) prev->nextGlobal = cur->nextGlobal;
    else m_allProducts = cur->nextGlobal;
    cur->nextGlobal = nullptr;
    return true;
}

bool StoreSystem::deleteProduct(int productId) {
    Product* p = findProductInGlobalList(productId);
    if (!p) return false;

    // Unlink from all suppliers safely
    while (p->suppliers) {
        Supplier* s = p->suppliers->supplier;
        // unlink deletes one SupplierRef and one ProductRef
        m_suppliers.unlink(s, p);
    }

    // Detach from category and global list
    detachProductFromCategory(p);
    detachProductFromGlobalList(p);

    // Free remaining supplier refs (should be none, but safe)
    SupplierRef* sr = p->suppliers;
    while (sr) {
        SupplierRef* next = sr->next;
        delete sr;
        sr = next;
    }
    p->suppliers = nullptr;

    delete p;
    return true;
}

Supplier* StoreSystem::addSupplier(int supplierId, const string& name) {
    return m_suppliers.addSupplier(supplierId, name);
}

Supplier* StoreSystem::findSupplier(int supplierId) const {
    return m_suppliers.findSupplier(supplierId);
}

void StoreSystem::printAllSuppliers() const {
    m_suppliers.printAllSuppliers();
}

bool StoreSystem::deleteSupplier(int supplierId) {
    return m_suppliers.deleteSupplier(supplierId);
}

bool StoreSystem::linkSupplierToProduct(int supplierId, int productId) {
    Supplier* s = m_suppliers.findSupplier(supplierId);
    Product* p = findProduct(productId);
    if (!s || !p) return false;
    return m_suppliers.link(s, p);
}

bool StoreSystem::unlinkSupplierFromProduct(int supplierId, int productId) {
    Supplier* s = m_suppliers.findSupplier(supplierId);
    Product* p = findProduct(productId);
    if (!s || !p) return false;
    return m_suppliers.unlink(s, p);
}

void StoreSystem::printSuppliersOfProduct(int productId) const {
    Product* p = findProduct(productId);
    if (!p) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }
    m_suppliers.printSuppliersOfProduct(p);
}

void StoreSystem::printProductsOfSupplier(int supplierId) const {
    Supplier* s = m_suppliers.findSupplier(supplierId);
    if (!s) {
        cout << "Supplier tidak ditemukan.\n";
        return;
    }
    m_suppliers.printProductsOfSupplier(s);
}

void StoreSystem::seedDemoData() {
    // kategori: Elektronik > Laptop > Gaming
    ensureCategoryPath({"Elektronik", "Laptop", "Gaming"});
    ensureCategoryPath({"Elektronik", "Laptop", "Ultrabook"});
    ensureCategoryPath({"Elektronik", "Aksesoris", "Keyboard"});
    ensureCategoryPath({"Elektronik", "Aksesoris", "Mouse"});

    // suppliers
    addSupplier(1, "PT Sumber Jaya Elektronik");
    addSupplier(2, "CV MegaTech Supply");
    addSupplier(3, "UD MurahMeriah Gadget");

    // products
    addProductToCategory({"Elektronik","Laptop","Gaming"}, 101, "Laptop Gaming RTX", 18999000);
    addProductToCategory({"Elektronik","Laptop","Ultrabook"}, 102, "Ultrabook Tipis", 14999000);
    addProductToCategory({"Elektronik","Aksesoris","Keyboard"}, 201, "Mechanical Keyboard", 799000);
    addProductToCategory({"Elektronik","Aksesoris","Mouse"}, 202, "Mouse Wireless", 299000);

    // links
    linkSupplierToProduct(1, 101);
    linkSupplierToProduct(2, 101);
    linkSupplierToProduct(2, 102);
    linkSupplierToProduct(3, 201);
    linkSupplierToProduct(1, 202);
    linkSupplierToProduct(3, 202);
}
