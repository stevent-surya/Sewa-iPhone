// Menyertakan file header untuk kelas RentalSystem.
// Ini seperti mengimpor "cetak biru" dari seluruh aplikasi
// agar bisa digunakan di dalam file main ini.
#include "RentalSystem.h"

// 'int main()' adalah fungsi utama yang akan dieksekusi pertama kali
// saat program Anda dijalankan oleh sistem operasi.
int main() {
    // Baris ini adalah inti dari segalanya.
    // 'RentalSystem app;' mendeklarasikan sebuah variabel bernama 'app'
    // dan membuatnya sebagai sebuah objek nyata dari kelas 'RentalSystem'.
    // Saat baris ini dieksekusi, Constructor dari RentalSystem akan dipanggil,
    // yang selanjutnya akan memanggil initializeData() untuk mengisi data awal.
    RentalSystem app;

    // Setelah objek 'app' berhasil dibuat dan diinisialisasi,
    // kita memanggil method 'run()' miliknya.
    // Method inilah yang berisi loop utama program: menampilkan menu,
    // menunggu input pengguna, dan seterusnya, hingga pengguna memilih untuk keluar.
    app.run();

    // Ketika loop di dalam app.run() berakhir (karena pengguna memilih keluar),
    // program akan melanjutkan ke baris ini.
    // 'return 0;' adalah cara standar untuk memberitahu sistem operasi
    // bahwa program telah selesai berjalan dengan sukses tanpa ada error.
    return 0;
}