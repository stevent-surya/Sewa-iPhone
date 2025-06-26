// =================================================================================
// NAMA FILE: RentalSystem.cpp
// DESKRIPSI: Implementasi lengkap untuk kelas RentalSystem.
// Versi: 3.1 (dengan perbaikan bug dan fitur lengkap)
// =================================================================================

// ---------------------------------------------------------------------------------
// BAGIAN 1: PENYERTAAN FILE-FILE PENTING
// ---------------------------------------------------------------------------------
#include "RentalSystem.h" // Menyertakan "cetak biru" dari kelas RentalSystem itu sendiri.
#include "DateUtils.h"    // Menyertakan fungsi-fungsi bantuan untuk mengelola tanggal.
#include <iostream>       // Diperlukan untuk menampilkan teks ke layar (std::cout) dan membaca input (std::cin).
#include <limits>         // Digunakan untuk membersihkan input yang salah dari pengguna.
#include <algorithm>      // Pustaka standar C++, meski di sini tidak terlalu digunakan, baik untuk ada.
#include <fstream>        // Diperlukan untuk membuat dan menulis ke file teks (untuk menyimpan nota).
#include <sstream>        // Diperlukan untuk membangun teks/string yang panjang dengan mudah (untuk isi nota).
#include <ctime>          // Diperlukan untuk mendapatkan tanggal dan waktu saat ini dari komputer.
#include <set>            // Diperlukan untuk mendapatkan daftar jenis iPhone yang unik.

// ---------------------------------------------------------------------------------
// PENDEKLARASIAN SHORTCUT/ALIAS
// ---------------------------------------------------------------------------------
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// ---------------------------------------------------------------------------------
// IMPLEMENTASI FUNGSI CONSTRUCTOR
// ---------------------------------------------------------------------------------
RentalSystem::RentalSystem() : isAdminLoggedIn(false) {
    initializeData();
}

// ---------------------------------------------------------------------------------
// IMPLEMENTASI FUNGSI UTAMA PROGRAM (RUN)
// ---------------------------------------------------------------------------------
void RentalSystem::run() {
    int pilihan;
    do {
        displayMainMenu();
        std::cout << "Pilih menu: ";
        while (!(std::cin >> pilihan)) {
            std::cout << "Input tidak valid. Masukkan angka: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (pilihan) {
        case 1: displayCatalog(); break;
        case 2: displayRequirements(); break;
        case 3: handleRentIphone(); break;
        case 4: handleReturnIphone(); break;
        case 5: handleTestimonials(); break;
        case 6:
            if (isAdminLoggedIn) {
                handleAddNewIphone();
            }
            else {
                login();
            }
            break;
        case 7:
            if (isAdminLoggedIn) {
                handleAddExistingStock();
            }
            else {
                std::cout << "Pilihan tidak valid." << std::endl;
                pressEnterToContinue();
            }
            break;
        case 8:
            if (isAdminLoggedIn) {
                logout();
            }
            else {
                std::cout << "Pilihan tidak valid." << std::endl;
                pressEnterToContinue();
            }
            break;
        case 9:
            std::cout << "Terima kasih telah menggunakan program ini." << std::endl;
            break;
        default:
            std::cout << "Pilihan tidak valid." << std::endl;
            pressEnterToContinue();
            break;
        }
    } while (pilihan != 9);
}

// ---------------------------------------------------------------------------------
// IMPLEMENTASI FUNGSI-FUNGSI BANTUAN (PRIVATE)
// ---------------------------------------------------------------------------------

void RentalSystem::initializeData() {
    catalog.emplace_back(101, "iPhone 13 Pro", 150000);
    catalog.emplace_back(102, "iPhone 14", 175000);
    catalog.emplace_back(103, "iPhone 15 Pro Max", 250000);
    catalog.emplace_back(104, "iPhone 12 Mini", 120000);

    Iphone iphone105(105, "iPhone 14 Pro", 200000);
    auto t_start = std::chrono::system_clock::now() - std::chrono::hours(24 * 5);
    iphone105.rent("Budi", t_start, 3);
    catalog.push_back(iphone105);

    testimonials.push_back({ "Andi", "Pelayanannya cepat dan iPhone-nya mulus seperti baru. Mantap!" });
    testimonials.push_back({ "Sari", "Sangat membantu untuk kebutuhan konten. Syaratnya mudah." });
}

void RentalSystem::clearScreen() {
    system(CLEAR_SCREEN);
}

void RentalSystem::pressEnterToContinue() {
    std::cout << "\nTekan Enter untuk melanjutkan...";
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Iphone* RentalSystem::findIphoneById(int id) {
    for (auto& iphone : catalog) {
        if (iphone.getId() == id) {
            return &iphone;
        }
    }
    return nullptr;
}

std::string RentalSystem::getCurrentTimestamp(bool forFilename) {
    auto now = std::time(nullptr);
    std::tm ltm;
#ifdef _WIN32
    localtime_s(&ltm, &now);
#else
    ltm = *std::localtime(&now);
#endif
    char buffer[20];
    if (forFilename) {
        std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &ltm);
    }
    else {
        std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &ltm);
    }
    return buffer;
}

void RentalSystem::saveReceiptToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        std::cout << "\nNota juga telah disimpan ke file: " << filename << std::endl;
    }
    else {
        std::cout << "\nError: Gagal menyimpan nota ke file." << std::endl;
    }
}

void RentalSystem::login() {
    clearScreen();
    std::string username, password;
    std::cout << "================== Login Admin ==================" << std::endl;
    std::cout << "Username : ";
    std::cin >> username;
    std::cout << "Password : ";
    std::cin >> password;
    std::cout << "===============================================" << std::endl;

    if (username == "admin" && password == "admin") {
        isAdminLoggedIn = true;
        std::cout << "Login berhasil! Selamat datang, admin." << std::endl;
    }
    else {
        isAdminLoggedIn = false;
        std::cout << "Username atau password salah." << std::endl;
    }
    pressEnterToContinue();
}

void RentalSystem::logout() {
    isAdminLoggedIn = false;
    std::cout << "Anda telah logout." << std::endl;
    pressEnterToContinue();
}

void RentalSystem::displayMainMenu() {
    clearScreen();
    std::cout << "======== Menu Utama Rental iPhone (OOP) ========" << std::endl;
    std::cout << "1. Lihat Katalog iPhone" << std::endl;
    std::cout << "2. Lihat Persyaratan Sewa" << std::endl;
    std::cout << "3. Sewa iPhone" << std::endl;
    std::cout << "4. Pengembalian iPhone" << std::endl;
    std::cout << "5. Testimoni Pelanggan" << std::endl;

    if (isAdminLoggedIn) {
        std::cout << "6. Tambah Jenis iPhone Baru" << std::endl;
        std::cout << "7. Tambah Jumlah Stock per Jenis" << std::endl;
        std::cout << "8. Logout" << std::endl;
    }
    else {
        std::cout << "6. Login sebagai Admin" << std::endl;
    }
    std::cout << "9. Keluar" << std::endl;
    std::cout << "===============================================" << std::endl;
}

void RentalSystem::displayCatalog() {
    clearScreen();
    std::cout << "==================== Katalog iPhone ====================" << std::endl;
    if (catalog.empty()) {
        std::cout << "Katalog masih kosong." << std::endl;
    }
    else {
        for (const auto& hp : catalog) {
            hp.displayDetails();
        }
    }
    pressEnterToContinue();
}

void RentalSystem::displayRequirements() {
    clearScreen();
    std::cout << "===================== Persyaratan Sewa =====================" << std::endl;
    std::cout << "1. Wajib menitipkan kartu identitas asli (KTP/SIM) yang masih berlaku." << std::endl;
    std::cout << "2. Penyewa bertanggung jawab penuh atas segala kerusakan atau kehilangan unit." << std::endl;
    std::cout << "3. Keterlambatan pengembalian akan dikenakan denda otomatis per hari." << std::endl;
    std::cout << "============================================================" << std::endl;
    pressEnterToContinue();
}

void RentalSystem::handleRentIphone() {
    clearScreen();
    std::cout << "==================== Sewa iPhone ====================" << std::endl;
    if (!isAdminLoggedIn) {
        std::cout << "Akses ditolak. Silakan login sebagai admin terlebih dahulu." << std::endl;
        pressEnterToContinue();
        return;
    }

    int idSewa;
    std::cout << "Masukkan ID iPhone yang ingin disewa: ";
    std::cin >> idSewa;

    Iphone* iphone = findIphoneById(idSewa);

    if (iphone) {
        if (iphone->isAvailable()) {
            std::string namaPenyewa, tglSewaStr;
            int duration;

            std::cout << "iPhone '" << iphone->getType() << "' tersedia." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Atas Nama                 : ";
            std::getline(std::cin, namaPenyewa);

            std::chrono::system_clock::time_point startDate;
            while (true) {
                std::cout << "Tanggal Peminjaman (DD-MM-YYYY): ";
                std::getline(std::cin, tglSewaStr);
                startDate = parseDate(tglSewaStr);
                if (startDate.time_since_epoch().count() != 0) break;
                std::cout << "Format tanggal salah. Harap gunakan format DD-MM-YYYY." << std::endl;
            }

            std::cout << "Lama Sewa (hari)          : ";
            std::cin >> duration;

            long long hargaSewa = (long long)iphone->getDailyRate() * duration;
            iphone->rent(namaPenyewa, startDate, duration);

            clearScreen();

            std::stringstream receiptStream;
            receiptStream << "=================== Nota Penyewaan iPhone ===================" << std::endl;
            receiptStream << "                 *** Untuk Pelanggan ***" << std::endl;
            receiptStream << "Tanggal Cetak: " << getCurrentTimestamp() << std::endl;
            receiptStream << "-----------------------------------------------------------" << std::endl;
            receiptStream << "Penyewaan berhasil dicatat atas nama: " << iphone->getRenterName() << std::endl << std::endl;
            receiptStream << "Detail Transaksi:" << std::endl;
            receiptStream << "  ID Handphone             : " << iphone->getId() << std::endl;
            receiptStream << "  Jenis iPhone             : " << iphone->getType() << std::endl;
            receiptStream << "  Tanggal Sewa             : " << formatDate(startDate) << std::endl;
            receiptStream << "  Lama Sewa                : " << duration << " hari" << std::endl;
            receiptStream << "  Tgl Tenggat Pengembalian : " << formatDate(iphone->getDueDate()) << std::endl << std::endl;
            receiptStream << "Rincian Biaya:" << std::endl;
            receiptStream << "  Tarif per Hari           : Rp " << iphone->getDailyRate() << std::endl;
            receiptStream << "  Total Biaya Sewa         : Rp " << hargaSewa << " ( " << duration << " hari x Rp " << iphone->getDailyRate() << " )" << std::endl;
            receiptStream << "-----------------------------------------------------------" << std::endl;
            receiptStream << "Terima kasih telah menyewa dari kami." << std::endl;
            receiptStream << "Mohon simpan nota ini sebagai bukti transaksi." << std::endl;
            receiptStream << "===========================================================" << std::endl;

            std::cout << receiptStream.str();

            std::string filename = "Sewa-" + std::to_string(iphone->getId()) + "-" + getCurrentTimestamp(true) + ".txt";
            saveReceiptToFile(filename, receiptStream.str());

        }
        else {
            std::cout << "Maaf, iPhone dengan ID " << idSewa << " sedang disewa." << std::endl;
        }
    }
    else {
        std::cout << "iPhone dengan ID " << idSewa << " tidak ditemukan." << std::endl;
    }
    pressEnterToContinue();
}

void RentalSystem::handleReturnIphone() {
    clearScreen();
    std::cout << "================= Pengembalian iPhone =================" << std::endl;
    if (!isAdminLoggedIn) {
        std::cout << "Akses ditolak. Silakan login sebagai admin terlebih dahulu." << std::endl;
        pressEnterToContinue();
        return;
    }

    int idKembali;
    std::cout << "Masukkan ID iPhone yang dikembalikan: ";
    std::cin >> idKembali;

    Iphone* iphone = findIphoneById(idKembali);

    if (iphone) {
        if (!iphone->isAvailable()) {
            std::string tglKembaliStr;

            std::cout << "Konfirmasi Pengembalian: iPhone '" << iphone->getType() << "' atas nama " << iphone->getRenterName() << "." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::chrono::system_clock::time_point actualReturnDate;
            while (true) {
                std::cout << "Masukkan tanggal pengembalian aktual (DD-MM-YYYY): ";
                std::getline(std::cin, tglKembaliStr);
                actualReturnDate = parseDate(tglKembaliStr);
                if (actualReturnDate.time_since_epoch().count() != 0) break;
                std::cout << "Format tanggal salah. Harap gunakan format DD-MM-YYYY." << std::endl;
            }

            long long daysLate = 0;
            if (actualReturnDate > iphone->getDueDate()) {
                auto difference = actualReturnDate - iphone->getDueDate();
                daysLate = std::chrono::duration_cast<std::chrono::hours>(difference + std::chrono::hours(23)).count() / 24;
            }
            if (daysLate < 0) daysLate = 0;

            long long fine = daysLate * iphone->getDailyRate();

            clearScreen();

            std::stringstream receiptStream;
            receiptStream << "================== Nota Pengembalian iPhone ==================" << std::endl;
            receiptStream << "                  *** Untuk Pelanggan ***" << std::endl;
            receiptStream << "Tanggal Cetak: " << getCurrentTimestamp() << std::endl;
            receiptStream << "------------------------------------------------------------" << std::endl;
            receiptStream << "Pengembalian atas nama: " << iphone->getRenterName() << std::endl << std::endl;
            receiptStream << "Detail Pengembalian:" << std::endl;
            receiptStream << "  ID Handphone           : " << iphone->getId() << std::endl;
            receiptStream << "  Jenis iPhone           : " << iphone->getType() << std::endl;
            receiptStream << "  Seharusnya Kembali Pada: " << formatDate(iphone->getDueDate()) << std::endl;
            receiptStream << "  Dikembalikan Pada      : " << formatDate(actualReturnDate) << std::endl << std::endl;
            receiptStream << "Rincian Denda:" << std::endl;
            receiptStream << "  Keterlambatan          : " << daysLate << " hari" << std::endl;
            receiptStream << "  Tarif Denda per Hari   : Rp " << iphone->getDailyRate() << std::endl;
            receiptStream << "  Total Denda            : Rp " << fine << " ( " << daysLate << " hari x Rp " << iphone->getDailyRate() << " )" << std::endl;
            receiptStream << "------------------------------------------------------------" << std::endl;
            if (fine > 0) {
                receiptStream << "Denda sebesar Rp " << fine << " telah dicatat." << std::endl;
            }
            receiptStream << "Terima kasih, iPhone telah berhasil dikembalikan." << std::endl;
            receiptStream << "============================================================" << std::endl;

            std::cout << receiptStream.str();

            std::string filename = "Kembali-" + std::to_string(iphone->getId()) + "-" + getCurrentTimestamp(true) + ".txt";
            saveReceiptToFile(filename, receiptStream.str());

            iphone->returnDevice();

        }
        else {
            std::cout << "iPhone dengan ID " << idKembali << " berstatus tersedia (tidak sedang disewa)." << std::endl;
        }
    }
    else {
        std::cout << "iPhone dengan ID " << idKembali << " tidak ditemukan." << std::endl;
    }
    pressEnterToContinue();
}

void RentalSystem::handleTestimonials() {
    clearScreen();
    int pilihan;
    std::cout << "================== Testimoni Pelanggan ==================" << std::endl;
    std::cout << "1. Lihat Semua Testimoni" << std::endl;
    if (isAdminLoggedIn) {
        std::cout << "2. Tambah Testimoni (Placeholder)" << std::endl;
    }
    std::cout << "Pilih opsi: ";
    std::cin >> pilihan;

    switch (pilihan) {
    case 1:
        clearScreen();
        std::cout << "--- Semua Testimoni ---" << std::endl;
        if (testimonials.empty()) {
            std::cout << "Belum ada testimoni." << std::endl;
        }
        else {
            for (const auto& t : testimonials) {
                std::cout << "Nama: " << t.nama << std::endl;
                std::cout << "Pesan: \"" << t.pesan << "\"" << std::endl;
                std::cout << "-----------------------" << std::endl;
            }
        }
        break;
    case 2:
        if (isAdminLoggedIn) {
            std::cout << "Fitur ini belum diimplementasikan." << std::endl;
        }
        else {
            std::cout << "Pilihan tidak valid." << std::endl;
        }
        break;
    default:
        std::cout << "Pilihan tidak valid." << std::endl;
        break;
    }
    pressEnterToContinue();
}

void RentalSystem::handleAddNewIphone() {
    clearScreen();
    std::cout << "================= Tambah Jenis iPhone Baru =================" << std::endl;

    std::string newType;
    int newRate;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Masukkan Jenis iPhone Baru (contoh: iPhone 16 Pro): ";
    std::getline(std::cin, newType);

    std::cout << "Masukkan Tarif Sewa per Hari (Rp): ";
    while (!(std::cin >> newRate) || newRate <= 0) {
        std::cout << "Input tidak valid. Masukkan angka tarif yang benar: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int maxId = 0;
    for (const auto& iphone : catalog) {
        if (iphone.getId() > maxId) {
            maxId = iphone.getId();
        }
    }
    int newId = maxId + 1;

    catalog.emplace_back(newId, newType, newRate);

    std::cout << "\nSukses! Stock iPhone '" << newType << "' dengan ID " << newId << " berhasil ditambahkan." << std::endl;
    std::cout << "==========================================================" << std::endl;
    pressEnterToContinue();
}

void RentalSystem::handleAddExistingStock() {
    clearScreen();
    std::cout << "============== Tambah Jumlah Stock per Jenis ==============" << std::endl;

    std::set<std::string> unique_types_set;
    for (const auto& iphone : catalog) {
        unique_types_set.insert(iphone.getType());
    }

    if (unique_types_set.empty()) {
        std::cout << "Tidak ada jenis iPhone di katalog untuk ditambah stoknya." << std::endl;
        pressEnterToContinue();
        return;
    }

    std::vector<std::string> unique_types_vec(unique_types_set.begin(), unique_types_set.end());
    std::cout << "Pilih jenis iPhone yang akan ditambah stoknya:" << std::endl;
    for (size_t i = 0; i < unique_types_vec.size(); ++i) {
        std::cout << i + 1 << ". " << unique_types_vec[i] << std::endl;
    }
    std::cout << "---------------------------------------------------------" << std::endl;

    int choice;
    std::cout << "Pilih nomor jenis iPhone: ";
    while (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(unique_types_vec.size())) {
        std::cout << "Input tidak valid. Masukkan nomor dari daftar di atas: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int quantity;
    std::cout << "Masukkan jumlah unit baru yang ingin ditambahkan: ";
    while (!(std::cin >> quantity) || quantity <= 0) {
        std::cout << "Input tidak valid. Masukkan jumlah (angka positif): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string template_type;
    int template_rate = 0;
    int maxId = 0;

    std::string selected_type_str = unique_types_vec[choice - 1];

    for (const auto& iphone : catalog) {
        if (template_rate == 0 && iphone.getType() == selected_type_str) {
            template_type = iphone.getType();
            template_rate = iphone.getDailyRate();
        }
        if (iphone.getId() > maxId) {
            maxId = iphone.getId();
        }
    }

    if (template_rate == 0) {
        std::cout << "Error internal: Gagal menemukan template iPhone." << std::endl;
        pressEnterToContinue();
        return;
    }

    for (int i = 0; i < quantity; ++i) {
        maxId++;
        catalog.emplace_back(maxId, template_type, template_rate);
    }

    std::cout << "\nSukses! " << quantity << " unit iPhone '" << selected_type_str << "' berhasil ditambahkan ke katalog." << std::endl;
    std::cout << "=========================================================" << std::endl;
    pressEnterToContinue();
}