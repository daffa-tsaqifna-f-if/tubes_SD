# Mini E-Commerce Toko Elektronik (C++)

Aplikasi CLI sederhana untuk tugas Struktur Data dengan konsep:

- **Tree kategori** (contoh: `Elektronik > Laptop > Gaming`) menggunakan representasi **child-sibling**.
- **Relasi produk–supplier** menggunakan **multi linked list**:
  - Satu produk bisa punya banyak supplier.
  - Satu supplier bisa memasok banyak produk.
  - Operasi **unlink supplier dari produk** tanpa menghapus data produk.

## Fitur Menu

1. Lihat tree kategori
2. Tambah kategori
3. Tampilkan produk dalam satu kategori
4. Lihat semua produk
5. Tambah produk ke kategori
6. Hapus produk
7. Lihat semua supplier
8. Tambah supplier
9. Hapus supplier
10. Hubungkan supplier <-> produk
11. Unlink supplier dari produk
12. Cari supplier dari suatu produk
13. Lihat produk yang dipasok supplier

Saat program dijalankan, sistem otomatis mengisi **data awal** (kategori, produk, supplier) supaya bisa langsung dicoba.

## Struktur File

- `include/Models.h` — struct data (CategoryNode, Product, Supplier + cross-links)
- `include/CategoryTree.h`, `src/CategoryTree.cpp` — tree kategori + traversal
- `include/SupplierGraph.h`, `src/SupplierGraph.cpp` — relasi multi linked list
- `include/StoreSystem.h`, `src/StoreSystem.cpp` — orkestrasi operasi
- `include/Input.h`, `src/Input.cpp` — helper input
- `src/main.cpp` — menu CLI

## Build & Run (tanpa CMake)

Kalau kamu sudah punya `g++` (MinGW-w64/MinGW), kamu bisa build langsung:

- Build menghasilkan `mini_ecommerce_elektronik.exe` di root project.

Atau pakai script yang sudah disediakan:

- `build.ps1` (PowerShell) — otomatis compile semua file.

Perintah (jalankan di PowerShell / CMD):

- `g++ -std=c++17 -I".\include" .\src\main.cpp .\src\CategoryTree.cpp .\src\SupplierGraph.cpp .\src\StoreSystem.cpp .\src\Input.cpp -o .\mini_ecommerce_elektronik.exe`

Run:

- `./mini_ecommerce_elektronik.exe`

## Catatan

- `StoreSystem` memiliki ownership semua `Product`.
- `CategoryTree` hanya menyimpan pointer ke produk (tidak menghapus produk).
- `SupplierGraph` menyimpan list supplier dan list referensi produk per supplier.
