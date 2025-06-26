#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

// Menyertakan definisi kelas Iphone, karena RentalSystem akan mengelola banyak objek Iphone.
#include "Iphone.h"
#include <vector>
#include <string>

// Mendefinisikan sebuah struktur data sederhana untuk menyimpan testimoni.
struct Testimoni {
    std::string nama;
    std::string pesan;
};

/**
 * @brief KELAS RENTALSYSTEM (Otak Aplikasi).
 * @details Kelas ini mengatur semua logika utama aplikasi: menampilkan menu, mengelola data iPhone,
 * memproses transaksi sewa dan kembali, serta menangani otentikasi admin.
 * Ia bertindak sebagai "controller" yang menghubungkan semua bagian lain dari program.
 */
class RentalSystem {

    // Bagian private berisi data dan fungsi yang hanya boleh diakses oleh RentalSystem sendiri.
private:
    // --- Variabel Anggota (Data Inti) ---
    std::vector<Iphone> catalog;       // Daftar dinamis untuk menyimpan semua objek iPhone.
    std::vector<Testimoni> testimonials;  // Daftar dinamis untuk menyimpan semua testimoni.
    bool isAdminLoggedIn;              // Penanda status login admin (true/false).

    // --- Method Bantuan Internal (Fungsi Pembantu) ---
    void initializeData();        // Untuk mengisi data awal saat program mulai.
    void clearScreen();           // Untuk membersihkan layar konsol.
    void pressEnterToContinue();  // Untuk menjeda program.
    Iphone* findIphoneById(int id); // Untuk mencari iPhone di dalam 'catalog'.
    std::string getCurrentTimestamp(bool forFilename = false); // Untuk mendapatkan waktu saat ini.
    void saveReceiptToFile(const std::string& filename, const std::string& content); // Untuk menyimpan nota ke file .txt.

    // --- Method untuk alur kerja spesifik ---
    void login();                 // Untuk proses login.
    void logout();                // Untuk proses logout.
    void displayMainMenu();       // Untuk menampilkan menu.
    void displayCatalog();        // Untuk menampilkan semua iPhone.
    void displayRequirements();   // Untuk menampilkan syarat sewa.
    void handleRentIphone();      // Untuk proses menyewa iPhone.
    void handleAddNewIphone();    // Untuk proses admin menambah jenis iPhone baru.
    void handleAddExistingStock();// [BARU] Untuk menambah jumlah stock jenis yang ada.
    void handleReturnIphone();    // Untuk proses mengembalikan iPhone.
    void handleTestimonials();    // Untuk menu testimoni.

    // Bagian public berisi fungsi yang bisa dipanggil dari luar kelas (dalam kasus ini, dari main.cpp).
public:
    // Constructor: Fungsi yang otomatis dipanggil saat objek RentalSystem dibuat.
    RentalSystem();

    // Method Utama: Titik masuk untuk menjalankan seluruh aplikasi.
    void run();
};

#endif // RENTALSYSTEM_H