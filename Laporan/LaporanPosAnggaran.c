#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_STRING 100

//Kamus data variabel global
typedef struct
{
    char namaAnggaran[MAX_STRING];
    int batasNominal;
} PosAnggaran;
PosAnggaran pos[100];

int jumlahPos;

typedef struct
{
    char id[10];
	char tanggal[20];
    char jenis[20];
    char namaPos[20];
    int nominal;
    char deskripsi[100];
} Transaksi ;
Transaksi transaksi[100];

int jumlahTransaksi;

//Deklarasi Modul Analisis Keuangan
int JumlahTransPemasukan(Transaksi transaksi[], int jumlahTransaksi);
int JumlahTransPengeluaran(Transaksi transaksi[], int jumlahTransaksi);
int TotalPemasukan(Transaksi transaksi[],int jumlahTransaksi);
int TotalPengeluaran(Transaksi transaksi[],int jumlahTransaksi);
int Saldo(Transaksi transaksi[], int jumlahTransaksi);
int RataRata(Transaksi transaksi[], int jumlahTransaksi);
void ShowRekapitulasi(Transaksi transaksi[], int jumlahTransaksi);

//Deklarasi Modul Laporan Keuangan
int RealisasiPos(Transaksi transaksi[], int jumlahTransaksi, char namaPos[]);
int JumlahTransPerPos(Transaksi transaksi[], int jumlahTransaksi, char namaPos[]);
char* StatusPos(int sisa);
void ShowTransaksi(Transaksi transaksi[], int jumlahTransaksi, int pilihanUser);
void ShowLaporanKeuangan(PosAnggaran pos[], int jumlahPos, Transaksi transaksi[], int jumlahTransaksi);
void MenuLaporanAkhir(PosAnggaran pos[], int jumlahPos, Transaksi transaksi[], int jumlahTransaksi); 

//Program Utama
int main()
{
    PosAnggaran pos[] = {
        {"Makan", 300000},
        {"Transportasi", 150000},
        {"Lainnya", 100000},
    };

    int jumlahPos = sizeof(pos) / sizeof(pos[0]);

    Transaksi transaksi[] = {
        {"T001","2024-01-01","Pemasukan","Gaji",100000,"Gaji Bulanan"},
        {"T002","2024-01-05","Pemasukan","Asu Kayang",150000,"Proyek Desain"},
        {"T003","2024-01-10","Pengeluaran","Makan",80000,"Makan Siang"},
        {"T004","2024-01-15","Pengeluaran","Transportasi",150000,"Ojek Online"},
        {"T005","2024-01-20","Pemasukan","Bonus",1000000,"Bonus Proyek"}
    };

    int jumlahTransaksi = sizeof(transaksi) / sizeof(transaksi[0]);

    MenuLaporanAkhir(pos, jumlahPos, transaksi, jumlahTransaksi);

    return 0;
}

//Fungsi JumlahTransPemasukan
/*	Menghitung jumlah transaksi berjenis pemasukan
	Input	: Data jumlah transaksi dari user
	Output	: Jumlah transaksi yang berjenis pemasukan saja
*/

int JumlahTransPemasukan(Transaksi transaksi[], int jumlahTransaksi)
{
    int hitung = 0;
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (strcasecmp(transaksi[i].jenis, "Pemasukan") == 0)
        {
            hitung++;
        }
    }
    return hitung;
}

//Fungsi JumlahTransPengeluaran
/*	Menghitung jumlah transaksi berjenis pengeluaran
	Input	: Data jumlah transaksi dari user
	Output	: Jumlah transaksi yang berjenis pengeluaran saja
*/

int JumlahTransPengeluaran(Transaksi transaksi[], int jumlahTransaksi)
{
    int hitung = 0;
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (strcasecmp(transaksi[i].jenis, "Pengeluaran") == 0)
        {
            hitung++;
        }
    }
    return hitung;
}

// Fungsi Total Pemasukan
int TotalPemasukan(Transaksi transaksi[],int jumlahTransaksi)
{
    int total = 0;
    for (int i = 0; i < jumlahTransaksi; i++){
            {
                if(strcasecmp(transaksi[i].jenis,"Pemasukan")==0)
            total += transaksi[i].nominal;
            }
    }
    return total;
}


// Fungsi Total Pengeluaran
int TotalPengeluaran(Transaksi transaksi[],int jumlahTransaksi)
{
    int total = 0;
    for (int i = 0; i < jumlahTransaksi; i++){
            {
                if(strcasecmp(transaksi[i].jenis,"Pengeluaran")==0)
            total += transaksi[i].nominal;
            }
    }
    return total;
}


// Fungsi Saldo 
int Saldo(Transaksi transaksi[], int jumlahTransaksi){
    int saldo = TotalPemasukan(transaksi,jumlahTransaksi) - TotalPengeluaran (transaksi,jumlahTransaksi);
    return saldo;
}

// Fungsi Rata-rata pengeluaran
int RataRata(Transaksi transaksi[],int jumlahTransaksi){
    int ratarata;
    if (jumlahTransaksi == 0) {     // Jika tidak ada transaksi, rata-rata dianggap = 0
        ratarata = 0;
    } else if (jumlahTransaksi > 0){
        ratarata = TotalPengeluaran(transaksi, jumlahTransaksi) / jumlahTransaksi;
    }
    return ratarata;
}

/*	Prosedur ShowRekapitulasi
	I.S.	: Data transaksi dari user tersimpat di array record Transaksi
	F.S.	: Data transaksi dari user muncul di layar
*/

void ShowRekapitulasi(Transaksi transaksi[], int jumlahTransaksi)
{
    int jumlahKeluar = JumlahTransPemasukan(transaksi, jumlahTransaksi);
    int jumlahMasuk = JumlahTransPengeluaran(transaksi, jumlahTransaksi);
    int totalMasuk = TotalPemasukan(transaksi, jumlahTransaksi);
    int totalKeluar = TotalPengeluaran(transaksi, jumlahTransaksi);
    int saldoAkhir = Saldo(transaksi, jumlahTransaksi);
    int rataKeluar = RataRata(transaksi, jumlahTransaksi);

    printf("______________________________________________________________\n");
    printf("| %-20s  | %-17s | %-15s |\n", "Jenis", "Jumlah Transaksi", "Total (Rp)");
    printf("|_______________________|___________________|_________________|\n");
    printf("| %-20s  | %-17d | %-15d |\n", "Pemasukan", jumlahMasuk, totalMasuk);
    printf("|_______________________|___________________|_________________|\n");
    printf("| %-20s  | %-17d | %-15d |\n", "Pengeluaran", jumlahKeluar, totalKeluar);
    printf("|_______________________|___________________|_________________|\n");
    printf("| %-20s  | %-17s | %-15d |\n", "Saldo Akhir", "-", saldoAkhir);
    printf("|_______________________|___________________|_________________|\n");
    printf("| %-20s | %-17s | %-15d |\n", "Rata-rata Pengeluaran", "-", rataKeluar);
    printf("|_______________________|___________________|_________________|\n");
}

//Fungsi RealisasiPos
/*	Menghitung total nominal transaksi pengekuaran per satu pos anggaran
	Input	: Data yang tersimpan di dalam array transaksi
	Output	: Totak nominal transaksi pengeluaran per pos anggaran
*/

int RealisasiPos(Transaksi transaksi[], int jumlahTransaksi, char namaPos[])
{
    int total = 0;
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if(strcasecmp(transaksi[i].namaPos, namaPos) == 0 &&
        strcasecmp(transaksi[i].jenis, "Pengeluaran") == 0)
        {
            total += transaksi[i].nominal;
        }
    }
    return total;
}

//Fungsi JumlahTransPerPos
/*	Menghitung jumlah transaksi per satu pos anggaran
	Input	: Data yang tersimpan di dalam array transaksi
	Output	: Jumlah transaksi per pos anggaran
*/

int JumlahTransPerPos(Transaksi transaksi[], int jumlahTransaksi, char namaPos[])
{
    int jumlah = 0;
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (strcasecmp(transaksi[i].namaPos, namaPos) == 0)
        {
            jumlah++;
        }
    }
    return jumlah;
}

//Fungsi StatusPos
/*	Menentukan status satu pos anggaran berdasarkan sisa anggaran yang tersedia
	Input	: Nilai sisa
	Output	: Aman           -> jika sisa anggaran 0 atau lebih
              Melebihi batas -> jika sisa anggaran negatif alias melebihi batas nominal
*/

char* StatusPos(int sisa)
{
    if(sisa >= 0)
    {
        return "Aman";
    }
    return "Melebihi batas";
}

/* Prosedur ShowTransaksi
	I.S.	: Laporan Transaksi pilihan user belum muncul ke layar
	F.S.	: Laporan Transaksi pilihan user sudah muncul ke layar
*/

void ShowTransaksi(Transaksi transaksi[], int jumlahTransaksi, int pilihanUser)
{
    printf("\n================ DAFTAR TRANSAKSI ================\n");
    printf("_____________________________________________________________________________________________\n");
    printf("| %-6s | %-12s | %-12s | %-12s | %-12s | %-20s |\n",
           "ID", "Tanggal", "Jenis", "Pos", "Nominal", "Deskripsi");
    printf("|________|______________|______________|______________|______________|______________________|\n");

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        bool tampil = false;

        if (pilihanUser == 0) {
            tampil = true;
        } else if (pilihanUser == 1 && strcasecmp(transaksi[i].jenis, "Pemasukan") == 0) {
            tampil = true;
        } else if (pilihanUser == 2 && strcasecmp(transaksi[i].jenis, "Pengeluaran") == 0) {
            tampil = true;
        }

        if (tampil) {
            printf("| %-6s | %-12s | %-12s | %-12s | %-12d | %-20s |\n",
               transaksi[i].id,
               transaksi[i].tanggal,
               transaksi[i].jenis,
               transaksi[i].namaPos,
               transaksi[i].nominal,
               transaksi[i].deskripsi);
        }   
    }
    printf("|________|______________|______________|______________|______________|______________________|\n");
}

/* Prosedur ShowLaporanKeuangan
	I.S.	: Laporan Pos Anggaran belum muncul ke layar
	F.S.	: Laporan Pos Anggaran sudah muncul ke layar
*/

void ShowLaporanKeuangan(PosAnggaran pos[], int jumlahPos, Transaksi transaksi[], int jumlahTransaksi) 
{
    printf("__________________________________________________________________________________________________________\n");
    printf("| %-15s | %-15s | %-15s | %-15s | %-17s | %-10s |\n",
           "Pos", "Batas Nominal", "Realisasi", "Sisa", "Jumlah Transaksi", "Status");
    printf("|_________________|_________________|_________________|_________________|___________________|____________|\n");

    for (int i = 0; i < jumlahPos; i++) {

        int realisasi = RealisasiPos(transaksi, jumlahTransaksi, pos[i].namaAnggaran);
        int sisa = pos[i].batasNominal - realisasi;
        int jumlah = JumlahTransPerPos(transaksi, jumlahTransaksi, pos[i].namaAnggaran);

        printf("| %-15s | %-15d | %-15d | %-15d | %-17d | %-10s |\n",
               pos[i].namaAnggaran,
               pos[i].batasNominal,
               realisasi,
               sisa,
               jumlah,
               StatusPos(sisa));
    }

    printf("|_________________|_________________|_________________|_________________|___________________|____________|\n");
}

/* Prosedur MenuLaporanAkhir
	I.S.	: Laporan Keuanngan pilihan user belum muncul ke layar
	F.S.	: Laporan Keuangan pilihan user sudah muncul ke layar
*/
void MenuLaporanAkhir(PosAnggaran pos[], int jumlahPos, Transaksi transaksi[], int jumlahTransaksi){
    int select;
    do{
        printf("Menu Laporan Keuangan:\n");
        printf("1. Tampilkan Laporan Keuangan\n");
        printf("2. Tampilkan Seluruh Transaksi\n");
        printf("3. Tampilkan Transaksi Pemasukan\n");
        printf("4. Tampilkan Transaksi Pengeluaran\n");
        printf("5. Tampilkan Rekapitulasi\n");  
        printf("0. Keluar\n");
        printf("Pilih opsi (0-5): ");
        scanf("%d", &select);
        switch(select){
            case 1:
                ShowLaporanKeuangan(pos, jumlahPos, transaksi, jumlahTransaksi);
                break;
            case 2:
                ShowTransaksi(transaksi, jumlahTransaksi, 0);
                break;
            case 3:
                ShowTransaksi(transaksi, jumlahTransaksi, 1);
                break;
            case 4:
                ShowTransaksi(transaksi, jumlahTransaksi, 2);
                break;
            case 5:
                ShowRekapitulasi(transaksi, jumlahTransaksi);
                break;
            case 0:
                printf("Keluar...\n"); 
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (select != 0);
}