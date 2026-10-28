[main.c Camping.c](https://github.com/user-attachments/files/34104094/main.c.Camping.c)# Tugas Pemrograman Bahasa C
## Identitas Mahasiswa
- **Nama Lengkap:** [Dimas Adi Tiara Hayu]
- **NIM:** [C2583207053]
- **Nama Proyek:** []

## Deskripsi Singkat Program
Program ini adalah aplikasi berbasis konsol untuk mengelola penyewaan peralatan camping milik Adventure Camp. Program dibuat menggunakan bahasa C dengan pendekatan terstruktur.

## Source Code
#include <stdio.h>
#include <string.h>

// ===== DATA PERALATAN =====
const char nama_alat[5][30] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};
const int harga_alat[5] = {50000, 15000, 20000, 10000, 12000};

// ===== PENYIMPANAN RIWAYAT =====
char nama_penyewa[10][50];
char alat_sewa[10][50];
int jumlah_unit[10];
int lama_hari[10];
int total_bayar[10];
int jumlah_transaksi = 0;

// ===== DEKLARASI FUNGSI =====
void tampilkanDaftarPeralatan();
void prosesPenyewaan();
void tampilkanRiwayat();
int hitungDiskon(int subtotal, int hari);

// ===== FUNGSI UTAMA =====
int main() {
    int menu;
    do {
        printf("\n========================================\n");
        printf("       ADVENTURE CAMP\n");
        printf("    SISTEM PENYEWAAN PERALATAN\n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("Pilih menu [1-4]: ");

        if (scanf("%d", &menu) != 1) {
            while(getchar() != '\n'); // bersihkan input
            printf("Masukan tidak valid! Pilih angka 1-4.\n");
            continue;
        }

        switch(menu) {
            case 1: tampilkanDaftarPeralatan(); break;
            case 2: prosesPenyewaan(); break;
            case 3: tampilkanRiwayat(); break;
            case 4: printf("Terima kasih telah menggunakan layanan kami!\n"); break;
            default: printf("Pilihan tidak tersedia! Silakan pilih 1-4.\n");
        }
    } while(menu != 4);

    return 0;
}

// ===== FUNGSI 1: DAFTAR PERALATAN =====
void tampilkanDaftarPeralatan() {
    printf("\n========================================\n");
    printf("        DAFTAR PERALATAN CAMPING\n");
    printf("========================================\n");
    printf("No  Peralatan                    Harga/Hari\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < 5; i++) {
        printf("%-3d %-28s Rp%d\n", i+1, nama_alat[i], harga_alat[i]);
    }
    printf("========================================\n");
}

// ===== FUNGSI 2: HITUNG DISKON =====
int hitungDiskon(int subtotal, int hari) {
    if(hari >= 5) return subtotal * 15 / 100;
    if(hari >= 3) return subtotal * 10 / 100;
    return 0;
}

// ===== FUNGSI 3: PROSES PENYEWAAN =====
void prosesPenyewaan() {
    if(jumlah_transaksi >= 10) {
        printf("\n⚠️  Kapasitas riwayat penuh! Tidak dapat menerima pesanan baru.\n");
        return;
    }

    char nama[50];
    int pilih_alat, unit, hari;
    char kembali;

    printf("\n--- FORM PENYEWAAN ---\n");
    printf("Nama Penyewa: ");
    scanf(" %[^\n]s", nama);

    // Pilih peralatan + validasi
    do {
        printf("\nPilih nomor peralatan [1-5]: ");
        scanf("%d", &pilih_alat);
        if(pilih_alat < 1 || pilih_alat > 5)
            printf("Nomor tidak tersedia! Silakan pilih ulang.\n");
    } while(pilih_alat < 1 || pilih_alat > 5);

    // Jumlah unit + validasi
    do {
        printf("Jumlah unit: ");
        scanf("%d", &unit);
        if(unit < 1) printf("Jumlah minimal 1 unit!\n");
    } while(unit < 1);

    // Lama sewa + validasi
    do {
        printf("Lama penyewaan (hari): ");
        scanf("%d", &hari);
        if(hari < 1) printf("Lama sewa minimal 1 hari!\n");
    } while(hari < 1);

    // Perhitungan
    int idx = pilih_alat - 1;
    int subtotal = harga_alat[idx] * unit * hari;
    int diskon = hitungDiskon(subtotal, hari);
    int total = subtotal - diskon;

    // Simpan ke riwayat
    strcpy(nama_penyewa[jumlah_transaksi], nama);
    strcpy(alat_sewa[jumlah_transaksi], nama_alat[idx]);
    jumlah_unit[jumlah_transaksi] = unit;
    lama_hari[jumlah_transaksi] = hari;
    total_bayar[jumlah_transaksi] = total;
    jumlah_transaksi++;

    // Tampilkan Struk
    printf("\n\n========================================\n");
    printf("         ADVENTURE CAMP\n");
    printf("          STRUK PENYEWAAN\n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", nama);
    printf("Peralatan      : %s\n", nama_alat[idx]);
    printf("Harga per Hari : Rp%d\n", harga_alat[idx]);
    printf("Jumlah Unit    : %d\n", unit);
    printf("Lama Sewa      : %d hari\n", hari);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%d\n", subtotal);
    if(diskon > 0)
        printf("Diskon         : Rp%d\n", diskon);
    printf("TOTAL BAYAR    : Rp%d\n", total);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan layanan Adventure Camp!\n");

    printf("\nKembali ke menu utama? (Y/T): ");
    scanf(" %c", &kembali);
    if(kembali == 'T' || kembali == 't') {
        printf("Terima kasih!\n");
        __builtin_exit(0); // keluar program
    }
}

// ===== FUNGSI 4: TAMPILKAN RIWAYAT =====
void tampilkanRiwayat() {
    printf("\n========================================\n");
    printf("         RIWAYAT TRANSAKSI\n");
    printf("========================================\n");

    if(jumlah_transaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        return;
    }

    printf("No  Nama        Peralatan            Total\n");
    printf("----------------------------------------\n");
    int total_pendapatan = 0;
    for(int i = 0; i < jumlah_transaksi; i++) {
        printf("%-3d %-12s %-20s Rp%d\n",
            i+1, nama_penyewa[i], alat_sewa[i], total_bayar[i]);
        total_pendapatan += total_bayar[i];
    }
    printf("----------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlah_transaksi);
    printf("Total Pendapatan : Rp%d\n", total_pendapatan);
    printf("========================================\n");
}
ding main.c Camping.c…]()

## Screenshot Hasil Eksekusi
<img width="410" height="851" alt="Screenshot 2026-10-29 051203" src="https://github.com/user-attachments/assets/995cff0e-b319-478a-8365-0799616c2dd4" />
<img width="412" height="862" alt="Screenshot 2026-10-29 051216" src="https://github.com/user-attachments/assets/99136559-8694-4e63-a73f-3916806b7ec6" />
<img width="362" height="806" alt="Screenshot 2026-10-29 051227" src="https://github.com/user-attachments/assets/1bd8f6cc-ebb6-4df9-b9ba-a5e715e98dee" />
<img width="442" height="862" alt="Screenshot 2026-10-29 051150" src="https://github.com/user-attachments/assets/b6fbb5a6-3567-4387-b869-acc37de9f624" />
