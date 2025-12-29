#include "SupplierGraph.h"

#include <iostream>

using namespace std;

SupplierGraph::~SupplierGraph() {
    // Free supplier list and all ProductRef lists
    Supplier* s = m_head;
    while (s) {
        ProductRef* pr = s->products;
        while (pr) {
            ProductRef* next = pr->next;
            delete pr;
            pr = next;
        }
        s->products = nullptr;

        Supplier* nextS = s->next;
        delete s;
        s = nextS;
    }
    m_head = nullptr;
}

Supplier* SupplierGraph::addSupplier(int id, const string& name) {
    if (findSupplier(id)) return nullptr;
    auto* s = new Supplier();
    s->id = id;
    s->name = name;
    s->next = m_head;
    m_head = s;
    return s;
}

Supplier* SupplierGraph::findSupplier(int id) const {
    for (Supplier* s = m_head; s; s = s->next) {
        if (s->id == id) return s;
    }
    return nullptr;
}

bool SupplierGraph::deleteSupplier(int id) {
    Supplier* prev = nullptr;
    Supplier* cur = m_head;
    while (cur && cur->id != id) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return false;

    // Detach supplier from all products it supplies
    ProductRef* pr = cur->products;
    while (pr) {
        // remove SupplierRef from the product side
        removeSupplierRef(pr->product, cur);
        pr = pr->next;
    }

    // Free ProductRef list
    pr = cur->products;
    while (pr) {
        ProductRef* next = pr->next;
        delete pr;
        pr = next;
    }
    cur->products = nullptr;

    // Remove from supplier list
    if (prev) prev->next = cur->next;
    else m_head = cur->next;

    delete cur;
    return true;
}

bool SupplierGraph::hasSupplier(const Product* product, const Supplier* supplier) {
    for (SupplierRef* sr = product ? product->suppliers : nullptr; sr; sr = sr->next) {
        if (sr->supplier == supplier) return true;
    }
    return false;
}

bool SupplierGraph::hasProduct(const Supplier* supplier, const Product* product) {
    for (ProductRef* pr = supplier ? supplier->products : nullptr; pr; pr = pr->next) {
        if (pr->product == product) return true;
    }
    return false;
}

bool SupplierGraph::link(Supplier* supplier, Product* product) {
    if (!supplier || !product) return false;
    if (hasSupplier(product, supplier) || hasProduct(supplier, product)) return false;

    auto* sr = new SupplierRef();
    sr->supplier = supplier;
    sr->next = product->suppliers;
    product->suppliers = sr;

    auto* pr = new ProductRef();
    pr->product = product;
    pr->next = supplier->products;
    supplier->products = pr;

    return true;
}

void SupplierGraph::removeSupplierRef(Product* product, const Supplier* supplier) {
    if (!product) return;
    SupplierRef* prev = nullptr;
    SupplierRef* cur = product->suppliers;
    while (cur) {
        if (cur->supplier == supplier) {
            if (prev) prev->next = cur->next;
            else product->suppliers = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void SupplierGraph::removeProductRef(Supplier* supplier, const Product* product) {
    if (!supplier) return;
    ProductRef* prev = nullptr;
    ProductRef* cur = supplier->products;
    while (cur) {
        if (cur->product == product) {
            if (prev) prev->next = cur->next;
            else supplier->products = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

bool SupplierGraph::unlink(Supplier* supplier, Product* product) {
    if (!supplier || !product) return false;
    if (!hasSupplier(product, supplier) || !hasProduct(supplier, product)) return false;

    // unlink both sides
    removeSupplierRef(product, supplier);
    removeProductRef(supplier, product);

    return true;
}

void SupplierGraph::printSuppliersOfProduct(const Product* product) const {
    if (!product) return;
    cout << "\nSupplier untuk produk [" << product->id << "] " << product->name << ":\n";
    if (!product->suppliers) {
        cout << "  (belum ada supplier)\n";
        return;
    }
    for (SupplierRef* sr = product->suppliers; sr; sr = sr->next) {
        cout << "  - [" << sr->supplier->id << "] " << sr->supplier->name << "\n";
    }
}

void SupplierGraph::printProductsOfSupplier(const Supplier* supplier) const {
    if (!supplier) return;
    cout << "\nProduk yang dipasok supplier [" << supplier->id << "] " << supplier->name << ":\n";
    if (!supplier->products) {
        cout << "  (belum memasok produk)\n";
        return;
    }
    for (ProductRef* pr = supplier->products; pr; pr = pr->next) {
        cout << "  - [" << pr->product->id << "] " << pr->product->name << " | Rp" << pr->product->price << "\n";
    }
}

void SupplierGraph::printAllSuppliers() const {
    cout << "\n=== DAFTAR SUPPLIER ===\n";
    if (!m_head) {
        cout << "(belum ada supplier)\n";
        return;
    }
    for (Supplier* s = m_head; s; s = s->next) {
        cout << "- [" << s->id << "] " << s->name << "\n";
    }
}
