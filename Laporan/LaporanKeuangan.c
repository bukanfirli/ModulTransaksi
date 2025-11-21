#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_STRING_LENGTH 100

//Struct Data (Sinkron dengann modul yang lain)

typedef struct
{
    char id[10];
	char tanggal[20];
    char namaPos[20];
    int nominal;
    char deskripsi[100];
    char jenis[20];
} Transaksi ;
Transaksi transaksi[100];

// Perhitungan keuangan

// Deklarsi Fungsi dan Procedure
void MenuLaporanKeuangan(Transaksi transaksi[], int jumlahTransaksi);
void ShowLaporanKeuangan(Transaksi transaksi[], int jumlahTransaksi);
void ShowRekapitulasi(Transaksi transaksi[], int jumlahTransaksi);

int JumlahTransPemasukan(Transaksi transaksi[], int jumlahTransaksi);
int JumlahTransPengeluaran(Transaksi transaksi[], int jumlahTransaksi);
int TotalPemasukan(Transaksi transaksi[],int jumlahTransaksi);
int TotalPengeluaran(Transaksi transaksi[],int jumlahTransaksi);
int Saldo(Transaksi transaksi[], int jumlahTransaksi);
int RataRata(Transaksi transaksi[], int jumlahTransaksi);
char* KondisiKeuangan(int saldo);
float PersentaseSisa(int saldo, int totalPemasukan);
float PersentaseSD(int saldo, int totalPemasukan);

// Procedure Input Laporan Keuangan
// Data yang ada disini hanya sebagai contoh untuk menguji fungsi dan prosedur apakah berjalan dengan baik atau tidak,
// untuk data yang sebenarnya, akan diambil dari modul input transaksi

int main(){
    Transaksi transaksi[5] = {
        {"T001","2024-01-01","Gaji",100000,"Gaji Bulanan","Pemasukan"},
        {"T002","2024-01-05","Asu Kayang",150000,"Proyek Desain","Pemasukan"},
        {"T003","2024-01-10","Makan",80000,"Makan Siang","Pengeluaran"},
        {"T004","2024-01-15","Transportasi",150000,"Ojek Online","Pengeluaran"},
        {"T005","2024-01-20","Bonus",1000000,"Bonus Proyek","Pemasukan"}
    };

    int jumlahTransaksi = sizeof(transaksi) / sizeof(transaksi[0]);
    MenuLaporanKeuangan(transaksi, jumlahTransaksi);

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


// Fungsi Kondisi Keuangan
char* KondisiKeuangan(int saldo){
    if (saldo > 0){
        return "Surplus"; //Sehat
    } else if (saldo == 0){
        return "Seimbang"; //Cukup
    } else {
        return "Defisit"; //Buruk
    }
}


// Persentase Sisa
float PersentaseSisa(int saldo, int totalPemasukan){
    if (totalPemasukan == 0){
        return 0.0; // Menghindari pembagian dengan nol
    }
    return ((float)saldo / totalPemasukan) * 100;
}

// Persentase Surplus dan Defisit
float PersentaseSD(int saldo, int totalPemasukan){
    if (saldo >= 200000) {
        return 0.0; // Surplus Besar
    } else if (saldo >= 100000 && saldo < 200000) {
        return 0.0; // Surplus Sedang
    } else if (saldo > 0 && saldo < 100000) {
        return 0.0; // Surplus Kecil
    } else if (saldo == 0) {
        return 0.0; // Seimbang
    } else if (saldo < 0) {
        return 0.0; // Defisit Kecil
    } else if (saldo < -100000) {
        return 0.0; // Defisit Sedang
    } else if (saldo < -200000) {
        return 0.0; // Defisit Besar
    }
    return ((float)saldo/ totalPemasukan) * 100;
    }


// Procedure Menampilkan Laporan Keuangan
void ShowLaporanKeuangan(Transaksi transaksi[], int jumlahTransaksi)
{
    printf("Laporan Keuangan:\n");
    printf("______________________________________________________________________________________________________\n");
    printf("%-8s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "id", "Tanggal", "Nama Pos", "Nominal", "Deskripsi", "Jenis");
    printf("_______________________________________________________________________________________________________\n");
    for (int i = 0; i < jumlahTransaksi; i++){
        printf("%-8s | %-15s | %-15s | %-15d | %-15s | %-15s |\n", 
        transaksi[i].id,
        transaksi[i].tanggal,
        transaksi[i].namaPos,
        transaksi[i].nominal,
        transaksi[i].deskripsi,
        transaksi[i].jenis);
    }
    printf("Laporan Kondisi Keuangan:\n");
    printf("___________________________________________________________________\n");
    printf("| %-35s | %-25s |\n", "Komponen", "Nilai (Rp)");
    printf("|_____________________________________|___________________________|\n");
    printf("| %-35s | %-25d |\n", "Total Pemasukan", TotalPemasukan(transaksi, jumlahTransaksi));
    printf("| %-35s | %-25d |\n", "Total Pengeluaran", TotalPengeluaran(transaksi, jumlahTransaksi));
    printf("| %-35s | %-25d |\n", "Total Pengeluaran Keseluruhan", TotalPengeluaran(transaksi, jumlahTransaksi));
    printf("| %-35s | %-25d |\n", "Saldo Akhir (Sisa Uang)", Saldo(transaksi, jumlahTransaksi));
    printf("| %-35s | %-25d |\n", "Rata-rata Pengeluaran per Transaksi", RataRata(transaksi, jumlahTransaksi));
    printf("| %-35s | %-24.2f%% |\n", "Persentase Sisa terhadap Pemasukan", 
    PersentaseSisa(Saldo(transaksi, jumlahTransaksi), TotalPemasukan(transaksi, jumlahTransaksi)));
    printf("|_____________________________________|___________________________|\n");
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

// Menu Laporan Keuangan
void MenuLaporanKeuangan(Transaksi transaksi[], int jumlahTransaksi){
    int select;
    do{
        printf("Menu Laporan Keuangan:\n");
        printf("1. Tampilkan Laporan Keuangan\n");
        printf("2. Tampilkan Total Pemasukan\n");
        printf("3. Tampilkan Total Pengeluaran\n");
        printf("4. Tampilkan Saldo Akhir\n");
        printf("5. Tampilkan Rata-rata Pengeluaran\n");  
        printf("6. Tampilkan Rekapitulasi\n");
        printf("0. Keluar\n");
        printf("Pilih opsi (0-6): ");
        scanf("%d", &select);
        switch(select){
            case 1:
                ShowLaporanKeuangan(transaksi, jumlahTransaksi);
                break;
            case 2:
                printf("Total Pemasukan: %d\n", TotalPemasukan(transaksi, jumlahTransaksi));
                break;
            case 3:
                printf("Total Pengeluaran: %d\n", TotalPengeluaran(transaksi, jumlahTransaksi));
                break;
            case 4:
                printf("Saldo Akhir: %d\n", Saldo(transaksi, jumlahTransaksi));
                break;
            case 5:
                printf("Rata-rata Pengeluaran: %d\n", RataRata(transaksi, jumlahTransaksi));
                break;
            case 6:
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