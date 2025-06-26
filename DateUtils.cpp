// Menyertakan file header-nya sendiri memastikan
// implementasi (.cpp) cocok dengan deklarasinya (.h).
#include "DateUtils.h"
// Menyertakan pustaka untuk memanipulasi output, seperti mengatur format tanggal.
#include <iomanip>
// Menyertakan pustaka untuk membaca string sebagai seolah-olah itu adalah sebuah file (stream),
// sangat berguna untuk mengurai (parsing) input tanggal.
#include <sstream>
// Menyertakan pustaka C-style untuk fungsi-fungsi waktu dasar seperti `std::time_t` dan `std::tm`.
#include <ctime>

// Di sini kita mendefinisikan logika sebenarnya dari fungsi formatDate.
std::string formatDate(const std::chrono::system_clock::time_point& timePoint) {
    // Langkah 1: Pemeriksaan Awal.
    // Jika time_point belum pernah diinisialisasi (masih pada waktu "epoch" atau nol),
    // kita tidak perlu memformatnya. Cukup kembalikan tanda strip.
    if (timePoint.time_since_epoch().count() == 0) {
        return "-";
    }

    // Langkah 2: Konversi Tipe Data Waktu.
    // Mengubah tipe data C++ modern (`time_point`) menjadi tipe data C yang lebih dasar (`time_t`).
    // Ini diperlukan karena fungsi pemformatan C-style (`strftime`) bekerja dengan `time_t`.
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);

    // Langkah 3: Siapkan Tempat Penyimpanan Hasil.
    // Membuat sebuah array karakter (buffer) untuk menampung string hasil format,
    // contohnya "18-06-2025". Ukuran 11 cukup untuk "DD-MM-YYYY" plus karakter null di akhir.
    char buffer[11];

    // Langkah 4: Dapatkan Tanggal (Hari, Bulan, Tahun).
    // Membuat struct `tm` untuk menampung komponen tanggal yang sudah dipecah.
    std::tm tm_info;

    // Ini adalah blok kondisional untuk kompatibilitas lintas platform.
#ifdef _MSC_VER // Jika dikompilasi dengan Microsoft Visual C++ (di Windows)...
    // Gunakan `localtime_s`, versi yang lebih aman dan direkomendasikan oleh Microsoft
    // untuk menghindari potensi masalah pada aplikasi multi-threaded.
    localtime_s(&tm_info, &time);
#else // Jika dikompilasi dengan compiler lain (misal: GCC di Linux, Clang di macOS)...
    // Gunakan `localtime` standar. Hasilnya adalah pointer, jadi kita perlu menyalin
    // nilainya ke dalam `tm_info` kita menggunakan operator dereference (*).
    tm_info = *std::localtime(&time);
#endif

    // Langkah 5: Format String.
    // `strftime` (string format time) mengambil komponen tanggal dari `tm_info`,
    // memformatnya sesuai pola "%d-%m-%Y" (hari-bulan-tahun),
    // dan menyimpan hasilnya ke dalam `buffer`.
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tm_info);

    // Langkah 6: Kembalikan Hasil.
    // Mengembalikan buffer yang kini berisi string tanggal yang sudah jadi.
    return buffer;
}


// Mendefinisikan logika untuk mengubah string menjadi objek waktu.
std::chrono::system_clock::time_point parseDate(const std::string& dateStr) {
    // Langkah 1: Siapkan Struktur untuk Hasil Parsing.
    // Membuat sebuah struct `tm` kosong yang akan diisi dengan hasil pengurai tanggal.
    std::tm tm = {};

    // Langkah 2: Ubah String menjadi Stream.
    // `stringstream` memungkinkan kita untuk "membaca" string `dateStr` seolah-olah itu adalah input dari keyboard atau file.
    std::stringstream ss(dateStr);

    // Langkah 3: Lakukan Parsing.
    // `std::get_time` mencoba membaca dari stream (`ss`) dan mengisi `tm` sesuai format "%d-%m-%Y".
    ss >> std::get_time(&tm, "%d-%m-%Y");

    // Langkah 4: Periksa Kegagalan.
    // Jika format input pengguna tidak cocok dengan pola (misal: "18/06/2025" atau "hello"),
    // proses akan gagal. `ss.fail()` akan menjadi `true`.
    if (ss.fail()) {
        // Jika gagal, kembalikan objek `time_point` kosong (epoch) untuk menandakan error.
        return std::chrono::system_clock::time_point{};
    }

    // Langkah 5: Konversi Kembali ke time_point.
    // Jika berhasil, `std::mktime` mengubah struct `tm` yang sudah terisi menjadi tipe `time_t`,
    // lalu `std::chrono::system_clock::from_time_t` mengubah `time_t` menjadi `time_point` C++.
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}