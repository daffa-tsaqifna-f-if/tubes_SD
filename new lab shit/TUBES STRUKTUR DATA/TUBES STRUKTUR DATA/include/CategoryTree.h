#pragma once

#include "Models.h"

#include <string>
#include <vector>

class CategoryTree {
public:
    CategoryTree();
    ~CategoryTree();

    CategoryTree(const CategoryTree&) = delete;
    CategoryTree& operator=(const CategoryTree&) = delete;

    CategoryNode* root() const { return m_root; }

    // Create (if missing) a path like: ["Elektronik","Laptop","Gaming"]
    CategoryNode* ensurePath(const std::vector<std::string>& path);

    // Find exact node for a path; nullptr if missing.
    CategoryNode* findPath(const std::vector<std::string>& path) const;

    // Find category by simple DFS name match (first hit).
    CategoryNode* findByName(const std::string& name) const;

    // Print the tree.
    void print() const;

    // Product list ops under a category
    void addProduct(CategoryNode* category, Product* product);
    Product* findProductInSubtree(CategoryNode* start, int productId) const;

    // Print all products in a category subtree
    void printProductsInSubtree(CategoryNode* start) const;

private:
    CategoryNode* m_root{};

    static CategoryNode* createNode(const std::string& name, CategoryNode* parent);
    static void deleteSubtree(CategoryNode* node);

    static CategoryNode* findChild(CategoryNode* parent, const std::string& childName);
    static CategoryNode* dfsFindByName(CategoryNode* node, const std::string& name);

    static void printSubtree(const CategoryNode* node, int depth);
    static void printProducts(const CategoryNode* node);

    static Product* dfsFindProduct(CategoryNode* node, int productId);
};
