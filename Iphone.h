// Memeriksa apakah 'IPHONE_H' belum pernah didefinisikan.
// Ini adalah pengaman untuk mencegah isi file ini di-include berkali-kali.
#ifndef IPHONE_H

// Mendefinisikan 'IPHONE_H' file ini sudah disertakan.
#define IPHONE_H

// Diperlukan untuk menggunakan tipe data 'std::string' untuk nama tipe dan nama penyewa.
#include <string>
// Diperlukan untuk menggunakan tipe data 'std::chrono::system_clock::time_point'
// untuk menyimpan tanggal sewa dan tanggal tenggat.
#include <chrono>

// 'class Iphone' mendefinisikan sebuah "cetak biru" atau tipe data baru bernama Iphone.
// Setiap objek yang dibuat dari kelas ini akan memiliki data dan fungsi yang sama.
// Ini adalah inti dari Object-Oriented Programming (OOP).
class Iphone {
    // 'private:' berarti semua variabel (data) yang dideklarasikan di bawah ini
    // hanya dapat diakses dan diubah oleh fungsi-fungsi dari dalam kelas Iphone itu sendiri.
    // Ini adalah prinsip enkapsulasi, yang melindungi data agar tidak diubah secara sembarangan dari luar.
private:
    int id;                                 // Nomor identifikasi unik untuk setiap unit iPhone.
    std::string type;                       // Model iPhone (misal: "iPhone 15 Pro Max").
    int dailyRate;                          // Tarif sewa per hari dalam Rupiah.
    bool isRented;                          // Status, true jika sedang disewa, false jika tersedia.
    std::string renterName;                 // Nama orang yang sedang menyewa iPhone ini.
    std::chrono::system_clock::time_point rentDate; // Tanggal kapan iPhone ini mulai disewa.
    std::chrono::system_clock::time_point dueDate;  // Tanggal tenggat pengembalian iPhone.

    // 'public:' berarti semua fungsi (method) yang dideklarasikan di bawah ini
    // dapat dipanggil dari bagian mana pun di program yang memiliki akses ke objek Iphone.
    // Ini adalah "antarmuka" atau cara program luar berinteraksi dengan objek Iphone.
public:
    // CONSTRUCTOR: Fungsi khusus yang otomatis dipanggil saat sebuah objek Iphone baru dibuat.
    // Tugasnya adalah untuk menginisialisasi nilai awal dari variabel-variabel di atas.
    Iphone(int id, const std::string& type, int rate);

    // METHODS (Perilaku): Fungsi-fungsi yang mendefinisikan apa yang bisa dilakukan oleh objek Iphone.

    // Method untuk mengubah status iPhone menjadi "disewa".
    void rent(const std::string& renter, std::chrono::system_clock::time_point startDate, int duration);

    // Method untuk mengembalikan status iPhone menjadi "tersedia" setelah disewa.
    void returnDevice();

    // Method untuk menampilkan semua detail iPhone ke layar.
    // Kata kunci 'const' di akhir berarti fungsi ini berjanji untuk tidak mengubah data apa pun di dalam objek.
    void displayDetails() const;

    // Ini adalah serangkaian fungsi publik yang bertujuan untuk memberikan akses "hanya-baca" (read-only)
    // ke data privat di atas. Ini adalah cara yang aman untuk membiarkan kode luar "melihat"
    // nilai data tanpa bisa mengubahnya secara langsung.

    int getId() const;                             // Mengembalikan ID iPhone.
    int getDailyRate() const;                      // Mengembalikan tarif sewa harian.
    std::chrono::system_clock::time_point getDueDate() const; // Mengembalikan tanggal tenggat.
    bool isAvailable() const;                      // Mengembalikan true jika TIDAK sedang disewa.
    std::string getType() const;                   // Mengembalikan tipe/model iPhone.
    std::string getRenterName() const;             // Mengembalikan nama penyewa saat ini.
};

// Menandai akhir dari blok header guard #ifndef.
#endif // IPHONE_H