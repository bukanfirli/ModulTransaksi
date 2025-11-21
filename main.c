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
int jumlahInputTransaksi;
int jumlahPos;

//Deklarasi Modul Pos Anggaran
void InputPosAnggaran(PosAnggaran pos[], int jumlahPos);
void ShowPosAnggaran(PosAnggaran pos[], int jumlahPos);
void PrintPosAnggaran(PosAnggaran pos[], int jumlahPos);

//Deklarasi Modul Transaksi
void InputTransaksi (Transaksi transaksi[], int jumlahInputTransaksi);
int HitungTransaksi (Transaksi transaksi[]);
bool ValidasiTanggal (char tanggal[]);
bool ValidasiJenis (char jenis[]);
bool ValidasiPos (PosAnggaran pos[], int jumlahPos, char namaPos[]);
bool ValidasiNominal (int nominal);
void ShowTransaksi (Transaksi transaksi[], int jumlahTransaksi);
void PrintTransaksi (Transaksi transaksi[], int jumlahTransaksi);

//Program Utama
int main()
{
	//Pos Anggaran
    printf("Masukkan jumlah pos anggaran: ");
    scanf("%d", &jumlahPos);
    getchar();

    printf("\n============= INPUT DATA POS ANGGARAN =============\n");
    InputPosAnggaran(pos, jumlahPos);

    printf("\n============= DAFTAR POS ANGGARAN =============\n");
    ShowPosAnggaran(pos, jumlahPos);

    PrintPosAnggaran(pos, jumlahPos);

    //Transaksi
	printf("Masukkan jumlah transaksi: ");
    scanf("%d", &jumlahInputTransaksi);
    getchar(); 

    printf("\n============= INPUT DATA TRANSAKSI =============\n");
    InputTransaksi(transaksi, jumlahInputTransaksi);
    jumlahTransaksi = HitungTransaksi(transaksi);

    printf("\n============= DAFTAR TRANSAKSI =============\n");
    ShowTransaksi(transaksi, jumlahTransaksi);

    PrintTransaksi(transaksi, jumlahTransaksi);
    
    return 0;
}

void InputPosAnggaran(PosAnggaran pos[], int jumlahPos)
{
    for (int i = 0; i < jumlahPos; i++)
    {
        printf("Masukan nama anggaran : ");
        scanf("%s", pos[i].namaAnggaran);
		getchar();

        do
        {
            printf("Masukan batas nominal : ");
            scanf("%d", &pos[i].batasNominal);

            if (pos[i].batasNominal <= 0)
            {
                printf("Batas nominal tidak boleh negatif dan 0! ulangin input batas nominal!\n");
            } 

        } while (pos[i].batasNominal <= 0);
    }
}

void ShowPosAnggaran(PosAnggaran pos[], int jumlahPos)
{
    printf("____________________________________________________________\n");
    printf("| No |  %-15s |  %-14s |\n", 
            "Nama Anggaran", "Batas Nominal");
    printf("|____|__________________|_________________|\n");

    for (int i = 0; i < jumlahPos; i++)
    {
        printf("| %-3d|  %-15s |  %-14d |\n", 
                i + 1, 
                pos[i].namaAnggaran, 
                pos[i].batasNominal);
    }
    printf("|____|__________________|_________________|\n");
}

void PrintPosAnggaran(PosAnggaran pos[], int jumlahPos)
{
    FILE *file;

    file = fopen("DataPosAnggaran.txt", "a");

    for (int i = 0; i < jumlahPos; i++)
    {
        fprintf(file, "|  %-15s |  %-14d |\n", pos[i].namaAnggaran, pos[i].batasNominal);
    }
    fclose(file);
}

/*	Prosedur InputTransaksi
	I.S.	: Data transaksi dari user belum diketahui
	F.S.	: Data transaksi dari user sudah tersimpan ke array record
*/

void InputTransaksi(Transaksi transaksi[], int jumlahInputTransaksi) 
{	
	for (int i=0; i<jumlahInputTransaksi; i++) 
	{
		printf("Input Transaksi ke-%d\n", i+1);

		//ID otomatis
		sprintf(transaksi[i].id, "T%03d", i + 1);
	
    	//Tanggal
        do {
            printf("Tanggal (dd/mm/yyyy): ");
            scanf("%s", transaksi[i].tanggal);

            if (!ValidasiTanggal(transaksi[i].tanggal))
            {
                printf("Tanggal tidak boleh kosong!\n");
            }

        } while (!ValidasiTanggal(transaksi[i].tanggal));
    
    	//Jenis transaksi
        do {
            printf("Jenis (Pemasukan/Pengeluaran): ");
    	    scanf("%s", transaksi[i].jenis);

            if (!ValidasiJenis(transaksi[i].jenis))
            {
                printf("Jenis transaksi harus 'Pemasukan' atau 'Pengeluaran'\n");
            }
        } while (!ValidasiJenis(transaksi[i].jenis));

    	//Pos Anggaran
        do {
            printf("Pos Anggaran: ");
    	    scanf("%s", transaksi[i].namaPos);
            
            if (!ValidasiPos(pos, jumlahPos, transaksi[i].namaPos))
            {
                printf("Pos anggaran '%s' tidak ditemukan\n", transaksi[i].namaPos);
            }

        } while (!ValidasiPos(pos, jumlahPos, transaksi[i].namaPos));
    
    	//Nominal
        do {
            printf("Nominal (Rp): ");
            scanf("%d", &transaksi[i].nominal);

            if (!ValidasiNominal(transaksi[i].nominal))
            {
                printf("Nominal harus lebih dari 0\n");
            }

        } while (!ValidasiNominal(transaksi[i].nominal));
    	getchar();
        
        //Deskripsi
        printf("Deskripsi: ");
        scanf(" %[^\n]", transaksi[i].deskripsi);
	}
}

//Fungsi HitungTransaksi
/*	Menghitung jumlah transaksi baik yang tersimpan dalam file dan yang akan ditambahkan user
	Input	: Data yang tersimpan di dalam array transaksi
	Output	: Jumlah array transaksi yang terisi
*/

int HitungTransaksi(Transaksi transaksi[])
{
    int jumlah = 0;

    for (int i = 0; i < 100; i++)
    {
        if (strlen(transaksi[i].jenis) > 0)
        {
            jumlah++;
        }
    }
    return jumlah;
}

//Fungsi ValidasiTanggal
/*	Memeriksa keabsahan data tanggal
	Input	: Data tanggal dari user
	Output	: True  -> valid
              False -> tidak valid
*/

bool ValidasiTanggal (char tanggal[])
{
	return strlen(tanggal)>0;
}

//Fungsi ValidasiJenis
/*	Memeriksa keabsahan data jenis transaksi
	Input	: Data jenis transaksi dari user
	Output	: True  -> valid
              False -> tidak valid
*/

bool ValidasiJenis (char jenis[])
{
	return (strcasecmp(jenis, "Pemasukan") == 0 ||
            strcasecmp(jenis, "Pengeluaran") == 0);
}

//Fungsi ValidasiPos
/*	Memeriksa keabsahan jenis pos anggaran
	Input	: Data jenis pos anggaran dari user
	Output	: True  -> valid
              False -> tidak valid
*/

bool ValidasiPos (PosAnggaran pos[], int jumlahPos, char namaPos[])
{
	for (int i = 0; i < jumlahPos; i++)
    {
        if (strcasecmp(namaPos, pos[i].namaAnggaran) == 0)
        {
            return true;
        }
    }
    return false;
}

//Fungsi ValidasiNominal
/*	Memeriksa keabsahan nominal transaksi
	Input	: Data nominal transaksi dari user
	Output	: True  -> valid
              False -> tidak valid
*/

bool ValidasiNominal (int nominal)
{ 
	return nominal>0;
}

/*	Prosedur ShowTransaksi
	I.S.	: Data transaksi dari user tersimpan di array record Transaksi
	F.S.	: Data transaksi dari user muncul di layar
*/

void ShowTransaksi(Transaksi transaksi[], int jumlahInputTransaksi)
{
    printf("_____________________________________________________________________________________________\n");
    printf("| %-6s | %-12s | %-12s | %-12s | %-12s | %-20s |\n",
           "ID", "Tanggal", "Jenis", "Pos", "Nominal", "Deskripsi");
    printf("|________|______________|______________|______________|______________|______________________|\n");

    for (int i = 0; i < jumlahInputTransaksi; i++)
    {
        printf("| %-6s | %-12s | %-12s | %-12s | %-12d | %-20s |\n",
               transaksi[i].id,
               transaksi[i].tanggal,
               transaksi[i].jenis,
               transaksi[i].namaPos,
               transaksi[i].nominal,
               transaksi[i].deskripsi);
    }

    printf("|________|______________|______________|______________|______________|______________________|\n");

}

/*	Prosedur PrintTransaksi
	I.S.	: Data transaksi dari user belum tersimpan di file eksternal
	F.S.	: Data transaksi dari user sudah tersimpan di file eksternal
*/

void PrintTransaksi (Transaksi transaksi[], int jumlahTransaksi)
{
    FILE *file = fopen("DataTransaksi.txt", "a");

    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        fprintf(file, "%s | %s | %s | %s | %d | %s\n",
                transaksi[i].id,
                transaksi[i].tanggal,
                transaksi[i].jenis,
                transaksi[i].namaPos,
                transaksi[i].nominal,
                transaksi[i].deskripsi);
    }

    fclose(file);
}
