#include "CategoryTree.h"

#include <iostream>

using namespace std;

CategoryTree::CategoryTree() {
    m_root = createNode("ROOT", nullptr);
}

CategoryTree::~CategoryTree() {
    deleteSubtree(m_root);
    m_root = nullptr;
}

CategoryNode* CategoryTree::createNode(const string& name, CategoryNode* parent) {
    auto* n = new CategoryNode();
    n->name = name;
    n->parent = parent;
    return n;
}

void CategoryTree::deleteSubtree(CategoryNode* node) {
    if (!node) return;

    // delete products list in this category
    Product* p = node->products;
    while (p) {
        // NOTE: Product object is owned by StoreSystem, so don't delete here.
        // We only detach list pointers.
        Product* next = p->nextInCategory;
        p->nextInCategory = nullptr;
        p->category = nullptr;
        p = next;
    }

    // delete children (subtrees)
    CategoryNode* child = node->firstChild;
    while (child) {
        CategoryNode* nextSibling = child->nextSibling;
        deleteSubtree(child);
        child = nextSibling;
    }

    delete node;
}

CategoryNode* CategoryTree::findChild(CategoryNode* parent, const string& childName) {
    if (!parent) return nullptr;
    CategoryNode* c = parent->firstChild;
    while (c) {
        if (c->name == childName) return c;
        c = c->nextSibling;
    }
    return nullptr;
}

CategoryNode* CategoryTree::ensurePath(const vector<string>& path) {
    CategoryNode* cur = m_root;
    for (const auto& part : path) {
        if (part.empty()) continue;
        CategoryNode* child = findChild(cur, part);
        if (!child) {
            child = createNode(part, cur);
            // insert at head for simplicity
            child->nextSibling = cur->firstChild;
            cur->firstChild = child;
        }
        cur = child;
    }
    return cur;
}

CategoryNode* CategoryTree::findPath(const vector<string>& path) const {
    const CategoryNode* cur = m_root;
    for (const auto& part : path) {
        if (!cur) return nullptr;
        if (part.empty()) continue;
        const CategoryNode* child = cur->firstChild;
        while (child && child->name != part) child = child->nextSibling;
        cur = child;
    }
    return const_cast<CategoryNode*>(cur);
}

CategoryNode* CategoryTree::dfsFindByName(CategoryNode* node, const string& name) {
    if (!node) return nullptr;
    if (node->name == name) return node;
    for (CategoryNode* c = node->firstChild; c; c = c->nextSibling) {
        if (auto* hit = dfsFindByName(c, name)) return hit;
    }
    return nullptr;
}

CategoryNode* CategoryTree::findByName(const string& name) const {
    return dfsFindByName(m_root, name);
}

void CategoryTree::printSubtree(const CategoryNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "- " << node->name << "\n";
    for (const CategoryNode* c = node->firstChild; c; c = c->nextSibling) {
        printSubtree(c, depth + 1);
    }
}

void CategoryTree::print() const {
    cout << "\n=== TREE KATEGORI ===\n";
    printSubtree(m_root, 0);
}

void CategoryTree::addProduct(CategoryNode* category, Product* product) {
    if (!category || !product) return;
    product->category = category;
    product->nextInCategory = category->products;
    category->products = product;
}

Product* CategoryTree::dfsFindProduct(CategoryNode* node, int productId) {
    if (!node) return nullptr;

    for (Product* p = node->products; p; p = p->nextInCategory) {
        if (p->id == productId) return p;
    }

    for (CategoryNode* c = node->firstChild; c; c = c->nextSibling) {
        if (auto* hit = dfsFindProduct(c, productId)) return hit;
    }
    return nullptr;
}

Product* CategoryTree::findProductInSubtree(CategoryNode* start, int productId) const {
    return dfsFindProduct(start ? start : m_root, productId);
}

void CategoryTree::printProducts(const CategoryNode* node) {
    for (const Product* p = node->products; p; p = p->nextInCategory) {
        cout << "  [" << p->id << "] " << p->name << " | Rp" << p->price << "\n";
    }
}

void CategoryTree::printProductsInSubtree(CategoryNode* start) const {
    if (!start) start = m_root;
    cout << "\n=== PRODUK DI SUBTREE: " << start->name << " ===\n";

    // DFS traversal
    const CategoryNode* stack[512];
    int top = 0;
    stack[top++] = start;

    while (top > 0) {
        const CategoryNode* node = stack[--top];
        cout << "\nKategori: " << node->name << "\n";
        printProducts(node);

        // push children
        for (const CategoryNode* c = node->firstChild; c; c = c->nextSibling) {
            if (top < 512) stack[top++] = c;
        }
    }
}
