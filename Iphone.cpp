// ---------------------------------------------------------------------------------
// PENYERTAAN DEPENDENSI (INCLUDE DEPENDENCIES)
// ---------------------------------------------------------------------------------
// File-file header yang dibutuhkan oleh implementasi kelas Iphone ini.

// Menyertakan "Iphone.h". Ini adalah file header untuk kelas ini sendiri.
// Langkah ini penting untuk memastikan bahwa implementasi di file .cpp ini
// konsisten dengan deklarasi (seperti nama fungsi, parameter, dan variabel anggota)
// yang ada di file .h. Tanpa ini, compiler tidak akan tahu bahwa fungsi-fungsi di bawah
// adalah bagian dari kelas Iphone.
#include "Iphone.h"

// Menyertakan "DateUtils.h". Ini adalah header untuk kumpulan fungsi utilitas
// yang berhubungan dengan tanggal. Kita membutuhkannya secara spesifik untuk fungsi `formatDate`,
// yang akan mengubah objek waktu (std::chrono::system_clock::time_point) menjadi
// format string yang mudah dibaca manusia (misal: "19-06-2025").
#include "DateUtils.h"

// Menyertakan pustaka <iostream> (Input/Output Stream). Pustaka standar C++ ini
// menyediakan fungsionalitas untuk melakukan operasi input dan output,
// terutama ke konsol. Kita menggunakannya untuk `std::cout` untuk menampilkan
// detail iPhone ke layar.
#include <iostream>

// ---------------------------------------------------------------------------------
// IMPLEMENTASI METHOD DARI KELAS IPHONE
// ---------------------------------------------------------------------------------
// Di bagian ini, kita menuliskan kode aktual (definisi) dari semua fungsi (method)
// yang telah dideklarasikan di dalam file "Iphone.h".

/**
 * @brief Constructor untuk kelas Iphone.
 * @details Fungsi ini dipanggil setiap kali sebuah objek Iphone baru dibuat.
 * Tugasnya adalah untuk menginisialisasi semua variabel anggota (data)
 * objek dengan nilai awal yang diberikan atau nilai default.
 * @param id ID unik untuk iPhone.
 * @param type Model atau jenis iPhone (misal: "iPhone 15 Pro").
 * @param rate Tarif sewa per hari untuk iPhone ini.
 */
Iphone::Iphone(int id, const std::string& type, int rate)
// Ini adalah "Member Initializer List". Cara ini lebih disukai daripada
// assignment di dalam body constructor `{}` karena lebih efisien. Ia langsung
// mengkonstruksi variabel anggota dengan nilai yang diberikan.
    : id(id),                // Inisialisasi 'id' dengan parameter 'id'.
    type(type),              // Inisialisasi 'type' dengan parameter 'type'.
    dailyRate(rate),         // Inisialisasi 'dailyRate' dengan parameter 'rate'.
    isRented(false),         // Default-kan status sewa menjadi 'false' (Tersedia).
    renterName("-"),         // Default-kan nama penyewa menjadi strip "-".
    rentDate{},              // Inisialisasi 'rentDate' ke nilai default (epoch time).
    dueDate{}                // Inisialisasi 'dueDate' ke nilai default (epoch time).
{
    // Body constructor ini sengaja dikosongkan.
    // Semua pekerjaan inisialisasi yang diperlukan sudah selesai dilakukan
    // di dalam member initializer list di atas, sehingga tidak ada logika
    // tambahan yang perlu dijalankan saat objek dibuat.
}

/**
 * @brief Memproses penyewaan iPhone.
 * @details Fungsi ini mengubah status iPhone menjadi "Disewa" dan mencatat semua
 * informasi relevan terkait penyewaan.
 * @param renter Nama orang yang menyewa iPhone.
 * @param startDate Waktu (tanggal dan jam) saat penyewaan dimulai.
 * @param duration Lama waktu sewa dalam satuan HARI.
 */
void Iphone::rent(const std::string& renter, std::chrono::system_clock::time_point startDate, int duration) {
    // 1. Mengubah status ketersediaan iPhone.
    isRented = true;

    // 2. Menyimpan nama penyewa yang diberikan.
    renterName = renter;

    // 3. Mencatat tanggal dimulainya sewa.
    rentDate = startDate;

    // 4. Menghitung tanggal jatuh tempo (tenggat).
    //    Ini dilakukan dengan menambahkan durasi sewa ke tanggal mulai.
    //    Karena 'duration' dalam hari, kita ubah dulu ke jam (hari * 24).
    //    `std::chrono::hours` adalah tipe data durasi dari pustaka <chrono>
    //    yang memungkinkan operasi aritmatika waktu yang aman dan jelas.
    dueDate = startDate + std::chrono::hours(24 * duration);
}

/**
 * @brief Memproses pengembalian iPhone.
 * @details Fungsi ini mereset status iPhone kembali ke keadaan semula (Tersedia),
 * menghapus data penyewa sebelumnya.
 */
void Iphone::returnDevice() {
    // Mengembalikan status iPhone menjadi "tidak disewa" atau "tersedia".
    isRented = false;

    // Menghapus nama penyewa, kembali ke nilai default.
    renterName = "-";

    // Mereset tanggal mulai sewa. Inisialisasi dengan kurung kurawal kosong `{}`
    // akan mengembalikannya ke nilai default (epoch time, atau 1 Januari 1970).
    rentDate = {};

    // Mereset tanggal tenggat ke nilai default juga.
    dueDate = {};
}

/**
 * @brief Menampilkan semua detail informasi iPhone ke konsol.
 * @details Fungsi ini mencetak atribut dasar iPhone dan, jika sedang disewa,
 * juga menampilkan detail penyewaan. Kata kunci 'const' di akhir
 * menjamin bahwa fungsi ini tidak akan mengubah data apapun di dalam objek.
 * Ini adalah "read-only" function.
 */
void Iphone::displayDetails() const {
    // Mencetak informasi dasar yang selalu ada untuk setiap iPhone.
    std::cout << "ID Handphone  : " << id << std::endl;
    std::cout << "Jenis         : " << type << std::endl;
    std::cout << "Tarif/hari    : Rp " << dailyRate << std::endl;

    // Menggunakan operator ternary ( ? : ) sebagai cara singkat untuk if-else.
    // Jika `isRented` adalah `true`, string "Disewa" akan digunakan.
    // Jika `false`, string "Tersedia" akan digunakan.
    std::cout << "Status        : " << (isRented ? "Disewa" : "Tersedia") << std::endl;

    // Cek apakah iPhone saat ini sedang dalam status disewa.
    if (isRented) {
        // Jika ya, tampilkan informasi tambahan yang hanya relevan saat disewa.
        std::cout << "Disewa oleh   : " << renterName << std::endl;

        // Memanggil fungsi `formatDate` dari DateUtils untuk mengubah objek waktu
        // `rentDate` dan `dueDate` menjadi string "DD-MM-YYYY" yang mudah dibaca
        // sebelum dicetak ke konsol.
        std::cout << "Tgl Sewa      : " << formatDate(rentDate) << std::endl;
        std::cout << "Tgl Tenggat   : " << formatDate(dueDate) << std::endl;
    }
    // Mencetak garis pemisah untuk membuat output lebih rapi dan terstruktur.
    std::cout << "----------------------------------------------------" << std::endl;
}

// ---------------------------------------------------------------------------------
// IMPLEMENTASI GETTERS (FUNGSI AKSESOR)
// ---------------------------------------------------------------------------------
// Getter adalah fungsi publik yang bertujuan untuk memberikan akses "read-only"
// ke variabel anggota (member variables) yang bersifat privat. Ini adalah pilar
// dari enkapsulasi, di mana data internal kelas dilindungi dari perubahan langsung.

// Mengembalikan ID unik iPhone.
int Iphone::getId() const { return id; }

// Mengembalikan tarif sewa harian iPhone.
int Iphone::getDailyRate() const { return dailyRate; }

// Mengembalikan waktu (tanggal dan jam) jatuh tempo sewa.
std::chrono::system_clock::time_point Iphone::getDueDate() const { return dueDate; }

// Mengembalikan status ketersediaan iPhone. `true` jika tersedia, `false` jika disewa.
// Ini adalah kebalikan (`!`) dari `isRented`.
bool Iphone::isAvailable() const { return !isRented; }

// Mengembalikan tipe atau model dari iPhone.
std::string Iphone::getType() const { return type; }

// Mengembalikan nama penyewa saat ini.
std::string Iphone::getRenterName() const { return renterName; }