#pragma once

#include "Models.h"

#include <string>

class SupplierGraph {
public:
    SupplierGraph() = default;
    ~SupplierGraph();

    SupplierGraph(const SupplierGraph&) = delete;
    SupplierGraph& operator=(const SupplierGraph&) = delete;

    Supplier* addSupplier(int id, const std::string& name);
    Supplier* findSupplier(int id) const;

    // Delete supplier entity (will detach from all products first)
    bool deleteSupplier(int id);

    // Link/unlink supplier <-> product (multi linked list)
    bool link(Supplier* supplier, Product* product);
    bool unlink(Supplier* supplier, Product* product);

    void printSuppliersOfProduct(const Product* product) const;
    void printProductsOfSupplier(const Supplier* supplier) const;

    void printAllSuppliers() const;

    Supplier* head() const { return m_head; }

private:
    Supplier* m_head{};

    static bool hasSupplier(const Product* product, const Supplier* supplier);
    static bool hasProduct(const Supplier* supplier, const Product* product);

    static void removeSupplierRef(Product* product, const Supplier* supplier);
    static void removeProductRef(Supplier* supplier, const Product* product);
};
