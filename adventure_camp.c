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

// ===== RIWAYAT =====
char nama_penyewa[10][50];
char rincian_transaksi[10][400];
int total_bayar[10];
int jumlah_transaksi = 0;

// ===== FUNGSI =====
void tampilkanDaftar() {
    printf("\n===== DAFTAR PERALATAN =====\n");
    printf("No  Nama                    Harga/Hari\n");
    for(int i=0; i<5; i++){
        printf("%d.  %-24s Rp%d\n", i+1, nama_alat[i], harga_alat[i]);
    }
}

int hitungDiskon(int subtotal, int hari) {
    if(hari >= 5) return subtotal * 15 / 100;
    if(hari >= 3) return subtotal * 10 / 100;
    return 0;
}

void sewaPeralatan() {
    if(jumlah_transaksi >= 10){
        printf("Riwayat penuh!\n"); return;
    }

    char nama[50];
    int lama_hari;
    int subtotal = 0;
    char rincian[400] = "";
    char lanjut;

    printf("\nNama Penyewa: ");
    scanf(" %[^\n]s", nama);

    do {
        printf("Lama sewa (hari): ");
        scanf("%d", &lama_hari);
        if(lama_hari < 1) printf("Minimal 1 hari!\n");
    } while(lama_hari < 1);

    do {
        tampilkanDaftar();
        int pilih, jumlah;

        do {
            printf("\nPilih nomor peralatan [1-5]: ");
            scanf("%d", &pilih);
            if(pilih < 1 || pilih > 5) printf("Tidak ada, pilih ulang!\n");
        } while(pilih < 1 || pilih > 5);

        do {
            printf("Jumlah unit: ");
            scanf("%d", &jumlah);
            if(jumlah < 1) printf("Minimal 1 unit!\n");
        } while(jumlah < 1);

        int idx = pilih - 1;
        int biaya = harga_alat[idx] * jumlah * lama_hari;
        subtotal += biaya;

        char baris[120];
        sprintf(baris, "- %s: %d unit\n", nama_alat[idx], jumlah);
        strcat(rincian, baris);

        printf("Ditambahkan!\n");

        // === INI BAGIAN PENTING ===
        printf("\nMasih tambah peralatan lain? (Y/T): ");
        scanf(" %c", &lanjut);

    } while(lanjut == 'Y' || lanjut == 'y');

    int diskon = hitungDiskon(subtotal, lama_hari);
    int total = subtotal - diskon;
    int persen = (lama_hari>=5)?15:(lama_hari>=3)?10:0;

    // Simpan ke riwayat
    strcpy(nama_penyewa[jumlah_transaksi], nama);
    strcpy(rincian_transaksi[jumlah_transaksi], rincian);
    total_bayar[jumlah_transaksi] = total;
    jumlah_transaksi++;

    // Struk
    printf("\n========== STRUK PENYEWAAN ==========\n");
    printf("Nama Penyewa : %s\n", nama);
    printf("Lama Sewa    : %d hari\n", lama_hari);
    printf("\nPeralatan:\n%s", rincian);
    printf("-------------------------------------\n");
    printf("Subtotal     : Rp%d\n", subtotal);
    if(diskon > 0) printf("Diskon %d%%    : Rp%d\n", persen, diskon);
    printf("TOTAL BAYAR  : Rp%d\n", total);
    printf("=====================================\n");
}

void lihatRiwayat() {
    printf("\n===== RIWAYAT TRANSAKSI =====\n");
    if(jumlah_transaksi == 0){
        printf("Belum ada transaksi.\n"); return;
    }
    int total_pendapatan = 0;
    for(int i=0; i<jumlah_transaksi; i++){
        printf("%d. %-15s Rp%d\n", i+1, nama_penyewa[i], total_bayar[i]);
        total_pendapatan += total_bayar[i];
    }
    printf("------------------------------\n");
    printf("Jumlah Transaksi: %d\n", jumlah_transaksi);
    printf("Total Pendapatan: Rp%d\n", total_pendapatan);
}

int main() {
    int menu;
    do {
        printf("\n===== ADVENTURE CAMP =====\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat\n");
        printf("4. Keluar\n");
        printf("Pilih menu [1-4]: ");
        scanf("%d", &menu);

        switch(menu){
            case 1: tampilkanDaftar(); break;
            case 2: sewaPeralatan(); break;
            case 3: lihatRiwayat(); break;
            case 4: printf("Terima kasih!\n"); break;
            default: printf("Pilihan salah!\n");
        }
    } while(menu != 4);
    return 0;
}
