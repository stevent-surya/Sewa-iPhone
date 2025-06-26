// memeriksa apakah 'DATEUTILS_H' belum pernah didefinisikan sebelumnya. Jika belum, maka kode
// di antara '#ifndef' dan '#endif' akan diproses.
#ifndef DATEUTILS_H

// menandai bahwa file ini sudah pernah disertakan (included).
// Jika file ini di-include lagi di tempat lain dalam proyek yang sama,
// '#ifndef' di atas akan gagal, dan seluruh isi file ini akan dilewati,
// sehingga mencegah error akibat deklarasi ganda.
#define DATEUTILS_H

// Menyertakan pustaka standar C++ untuk menggunakan tipe data string.
// 'std::string' digunakan untuk menyimpan dan memanipulasi teks, seperti "18-06-2025".
#include <string>

// Menyertakan pustaka standar C++ untuk menangani waktu dan durasi.
// 'std::chrono' menyediakan alat modern untuk mengelola data tanggal dan waktu,
// seperti 'std::chrono::system_clock::time_point' yang merepresentasikan
// satu titik waktu spesifik.
#include <chrono>

// ---------------------------------------------------------------------------------
// DEKLARASI FUNGSI (PROTOTIPE)
// ---------------------------------------------------------------------------------
// Bagian ini adalah "daftar isi" atau "kontrak" dari file ini.
// Ia memberitahu seluruh program fungsi apa saja yang tersedia untuk digunakan,
// tanpa perlu menunjukkan detail implementasinya (logikanya ada di DateUtils.cpp).


/**
 * @brief Mengubah objek waktu internal komputer (time_point) menjadi string yang mudah dibaca.
 * @param timePoint Objek waktu yang akan diubah formatnya. Ini adalah input fungsi.
 * @return String tanggal dalam format "DD-MM-YYYY". Ini adalah output fungsi.
 */
std::string formatDate(const std::chrono::system_clock::time_point& timePoint);


/**
 * @brief Mengubah string tanggal (misal: "18-06-2025") menjadi objek waktu internal komputer.
 * @param dateStr String tanggal yang akan diuraikan (parsed). Ini adalah input fungsi.
 * @return Objek time_point yang sesuai dengan string input. Jika format string salah,
 * fungsi akan mengembalikan time_point yang merepresentasikan "epoch" (waktu nol).
 */
std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

// ---------------------------------------------------------------------------------
// HEADER GUARD (Penjaga Header) - Bagian 3
// ---------------------------------------------------------------------------------
// Menandai akhir dari blok #ifndef.
#endif // DATEUTILS_H