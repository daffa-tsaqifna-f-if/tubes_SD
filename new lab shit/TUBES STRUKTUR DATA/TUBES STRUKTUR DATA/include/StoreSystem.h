#pragma once

#include "CategoryTree.h"
#include "SupplierGraph.h"

#include <string>
#include <vector>

class StoreSystem {
public:
    StoreSystem();
    ~StoreSystem();

    StoreSystem(const StoreSystem&) = delete;
    StoreSystem& operator=(const StoreSystem&) = delete;

    // Category
    CategoryNode* ensureCategoryPath(const std::vector<std::string>& path);
    CategoryNode* findCategoryPath(const std::vector<std::string>& path) const;
    void printCategories() const;

    // Product
    Product* addProductToCategory(const std::vector<std::string>& categoryPath, int productId, const std::string& name, double price);
    Product* findProduct(int productId) const;
    void printProductsInCategorySubtree(const std::vector<std::string>& categoryPath) const;
    void printAllProducts() const;
    bool deleteProduct(int productId);

    // Supplier
    Supplier* addSupplier(int supplierId, const std::string& name);
    Supplier* findSupplier(int supplierId) const;
    void printAllSuppliers() const;
    bool deleteSupplier(int supplierId);

    // Relations
    bool linkSupplierToProduct(int supplierId, int productId);
    bool unlinkSupplierFromProduct(int supplierId, int productId);

    void printSuppliersOfProduct(int productId) const;
    void printProductsOfSupplier(int supplierId) const;

    // Demo
    void seedDemoData();

private:
    CategoryTree m_tree;
    SupplierGraph m_suppliers;

    // Product ownership: StoreSystem owns all products (so CategoryTree doesn't delete them)
    Product* m_allProducts{}; // global singly list

    Product* createProduct(int id, const std::string& name, double price);
    Product* findProductInGlobalList(int id) const;
    void deleteAllProducts();

    bool detachProductFromCategory(Product* product);
    bool detachProductFromGlobalList(Product* product);

    static std::vector<std::string> splitPath(const std::string& path, char delim = '>');
};
