#pragma once

#include <string>

struct Supplier;
struct Product;
struct CategoryNode;

// --- Cross-links (multi linked list) ---
struct SupplierRef {
    Supplier* supplier{};
    SupplierRef* next{};
};

struct ProductRef {
    Product* product{};
    ProductRef* next{};
};

// --- Core entities ---
struct Product {
    int id{};
    std::string name;
    double price{};

    CategoryNode* category{};      // back-pointer
    SupplierRef* suppliers{};      // suppliers for this product

    Product* nextInCategory{};     // singly linked list under a category

    Product* nextGlobal{};         // global singly linked list (owned by StoreSystem)
};

struct Supplier {
    int id{};
    std::string name;

    ProductRef* products{};        // products supplied by this supplier
    Supplier* next{};              // global singly linked list
};

// Tree node using child-sibling representation
struct CategoryNode {
    std::string name;

    CategoryNode* parent{};
    CategoryNode* firstChild{};
    CategoryNode* nextSibling{};

    Product* products{};           // head of product list in this category
};
