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
        return total;
    }
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
        return jumlah;
    }
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


/* Prosedur ShowLaporanTransaksi
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
        printf("|________|______________|______________|______________|______________|______________________|\n");
    }
}

/* Prosedur ShowLaporanKeuangan
	I.S.	: Laporan Pos Anggaran belum muncul ke layar
	F.S.	: Laporan Pos Anggaran sudah muncul ke layar
*/

void ShowLaporanKeuangan(PosAnggaran pos[], int jumlahPos, Transaksi transaksi[], int jumlahTransaksi) 
{
    printf("============================ LAPORAN KEUANGAN BULANAN ============================\n");
    printf("Total Pemasukan (%d Transaksi)     : %d\n", 
            JumlahTransPemasukan(transaksi, jumlahTransaksi), TotalPemasukan(transaksi,jumlahTransaksi));
    printf("Total Pengeluaran (%d Transaksi)   : %d\n",
            JumlahTransPengeluaran(transaksi, jumlahTransaksi), TotalPengeluaran(transaksi,jumlahTransaksi));
    printf("Saldo Akhir                       : %d\n", Saldo(transaksi, jumlahTransaksi));
    printf("Rata-rata Pengeluaran             : %d\n", RataRata(transaksi, jumlahTransaksi));
    printf("----------------------------------------------------------------------------------\n");

    printf("POS ANGGARAN\n");
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

    printf("\n----------------------------------------------------------------------------------\n");
    printf("Kondisi Keuangan  : nanti di isi\n");
    printf("Kesimpulan        : nanti di isi\n");
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