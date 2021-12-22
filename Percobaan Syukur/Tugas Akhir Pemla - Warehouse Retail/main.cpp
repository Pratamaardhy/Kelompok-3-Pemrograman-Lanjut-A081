#include <string.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <sstream>
#include <cmath>
#include <windows.h>

using namespace std;

struct Data_Barang{
	int id_barang;
	char Nama_Barang[50], kategori_barang[50], jumlah_barang[50], data_sementara[50], Tgl[50], Waktu[50];
	char tempNama_Barang[50], tempKategori_Barang[50], tempJumlah_Barang[50], tempTgl[50], tempWaktu[50];
} Data_Now[50];

//Fungsi Menu
void lihat_data(int i, char kondisi[], int n), buat_data(int i), hapus_data(int index, int n, char kondisi[50]);
void barang_keluarMasuk(char kondisi[50], char data_utama[50]);
int InsertionSort(char kondisi[50]), InterpolationSearch(int key, char kondisi[]);

//Fungsi Pendukung Menu
void ubah_data(int index, int n, char kondisi[50], int position), ambil_data(int i, char kondisi[50]), Tampilkan_Data(int i), masukkan_data(char data[], char File_name[]);
void copy_dataFile(char Data_File[], char Data_Folder[], char kondisi[], char data[]);
int set_data(char kondisi[50]);

//Fungsi Tambahan
void set_time(char kondisi[]), garis(int x), gotoxy(int x, int y);
int konversi_char(char data[]), membuka_data(char File_name[]), linear_search(char kondisi[], int key, int n, int position), ArrowKey(int x, int pilih);
string copy_dataFileString(char Data_File[], char Data_Folder[], char Type_Data[], int i);

main(){
	system("color 9F");
	HWND hwnd = GetConsoleWindow();
	if( hwnd != NULL){
		SetConsoleTitle("Program Manajemen Gudang Perusahaan Ritel");
		MoveWindow(hwnd, 120, 50, 1080, 720, TRUE);
	}
	int awal = 12;
	int pilih = 1, key, index, position, x = awal;
	char again='y', Data_Dicari[50], Masuk[50] = "/Masuk", Keluar[50] = "/Keluar", lihat_semua[50] = "/", pilih_1[50];
	do{
		int n = set_data(lihat_semua);
		gotoxy(12,x); cout << "->";
		gotoxy(30, 10); 
		printf("<----------------:MANAJEMEN GUDANG PERUSAHAAN RITEL:---------------->\n\n");
		gotoxy(15, 12);
		printf("1. Barang Masuk\n");
		gotoxy(15, 13);
		printf("2. Barang Keluar\n");
		gotoxy(15, 14);
		printf("3. Tampilkan Data Barang\n");
		gotoxy(15, 15);
		printf("4. Cari Data Barang\n");
		gotoxy(15, 16);
		printf("5. Hapus Data Barang\n");
		gotoxy(15, 17);
		printf("6. Ubah Data Barang\n");
		gotoxy(15, 18);
		printf("7. Keluar\n");
		system("pause>nul"); 
		
		int arrow = ArrowKey(x, pilih);
		if (arrow != -1){
			if ( x < arrow){
				pilih++;
			}else{
				pilih--;
			}
			x = arrow;
			continue;
		}if(GetAsyncKeyState(VK_RETURN)){ 
			switch(pilih){
				case 1:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Barang Baru-----\n");
					gotoxy(15, 21);
					garis(40);
					printf("\t\t 1. Barang Baru \n\t\t 2. Barang Digudang \n\t\t Pilihan anda ?");
					scanf("%d", &pilih);
					
					if( pilih == 1 ){
						printf("\t\t Masukkan Jumlah Barang Yang DiInputkan: ");
						scanf("%d", &index);
						
						buat_data(index);
						printf("\t\t Data Berhasil Ditambahkan\n");
					}else if(pilih == 2){
						barang_keluarMasuk(Masuk, lihat_semua);
					}
					
					pilih=1;
					x=awal;
					printf("\t\t Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 2:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Barang Keluar-----\n");
					gotoxy(15, 21);
					garis(40);
					barang_keluarMasuk(Keluar, lihat_semua);
					
					pilih=1;
					x=awal;
					printf("\t\t Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 3:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Tampilkan Barang-----\n");
					gotoxy(15, 21);
					garis(40);
					printf("\t\t 1. Riwayat Barang Masuk \n");
					printf("\t\t 2. Riwayat Barang Keluar \n");
					printf("\t\t 3. Tampilkan Data Barang Digudang \n");
				
					printf("\t\t Pilihan anda ?");
					scanf("%d", &pilih);
					
					if( pilih == 1 ){
						system("cls");
						gotoxy(25, 1);
						printf("<----------------:Data Barang Masuk:---------------->\n\n");
						printf("Berikut Data Berdasarkan Id Barang: \n");
						n = InsertionSort(Masuk);
						printf("No\t Tanggal Input \t\t IdBarang\t NamaBarang\t\t   Kategori\t\t Jumlah\t\t Status\n");
						for (int i = 1; i < n; i++){
							lihat_data(i, Masuk, n);
						}
					}else if(pilih == 2){
						system("cls");
						gotoxy(25, 1);
						printf("<----------------:Data Barang Keluar:---------------->\n\n");
						printf("Berikut Data Berdasarkan Id Barang: \n");
						n = InsertionSort(Keluar);
						printf("No\t Terakhir Diperbarui \t IdBarang\t NamaBarang\t\t   Kategori\t\t Jumlah\t\t Status\n");
						for (int i = 1; i < n; i++){
							lihat_data(i, Keluar, n);
						}
					}else if(pilih == 3){
						system("cls");
						gotoxy(25, 1);
						printf("<----------------:Data Barang:---------------->\n\n");
						printf("Berikut Data Berdasarkan Id Barang: \n");
						n = InsertionSort(lihat_semua);
						printf("No\t Terakhir Diperbarui \t IdBarang\t NamaBarang\t\t   Kategori\t\t Jumlah\t\t Status\n");
						for (int i = 1; i < n; i++){
							lihat_data(i, lihat_semua, n);
						}
					}
					
					pilih=1;
					x=awal;
					printf("Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 4:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Cari Barang-----\n");
					gotoxy(15, 21);
					garis(40);
					printf("\t\t Masukkan Nama Barang: ");
					scanf(" %[^\n]s ", Data_Dicari);
					
					n = strlen(Data_Dicari);
					key = konversi_char(Data_Dicari);
					position = 1;
					
					index = InterpolationSearch(key, lihat_semua);
					
					if(index != -1){
						printf("\t\t Data Ditemukan\n");
						Tampilkan_Data(index);
					}else{
						printf("\t\t Berikut Hasil Pencarian Yang Berhubungan Dengan - %s - :\n", Data_Dicari);
						index = linear_search(lihat_semua, key, n, position);
						if(index != 1){
							printf("\t\t Data Tidak ada\n");
						}
					}
					
					pilih=1;
					x=awal;
					printf("\t\t Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 5:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Hapus Barang-----\n");
					gotoxy(15, 21);
					garis(40);
					printf("\t\t Masukkan Nama Barang: ");
					scanf(" %[^\n]s ", Data_Dicari);
					
					key = konversi_char(Data_Dicari);
					
					n = InsertionSort(lihat_semua);
					index = InterpolationSearch(key, lihat_semua);
					
					if(index != -1){
						printf("\t\t Proses..");
						hapus_data(index, n, lihat_semua);
						
						n = InsertionSort(Masuk);
						for(int i=0; i < n; i++){
							index = InterpolationSearch(key, Masuk);
							if(index != -1){
								hapus_data(index, n, Masuk);
								n = InsertionSort(Masuk);
								printf(".");
							}
						}
						
						n = InsertionSort(Keluar);
						printf("%d", n);
						for(int i=1; i < n; i++){
							printf("%d", n);
							index = InterpolationSearch(key, Keluar);
							if(index != -1){
								hapus_data(index, n, Keluar);
								n = InsertionSort(Keluar);
								printf(".");
							}
						}
						
						printf("\n\t\t Hapus Data Berhasil\n");
					}else{
						printf("\n\t\t Data Tidak ada\n");
					}
					
					
					pilih=1;
					x=awal;
					printf("\t\t Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 6:
					gotoxy(15, 19);
					garis(40);
					gotoxy(25, 20);
					printf("----Ubah Barang-----\n");
					gotoxy(15, 21);
					garis(40);
					
					printf("\t\t Masukkan Nama Barang: ");
					scanf(" %[^\n]s ", Data_Dicari);
					
					key = konversi_char(Data_Dicari);
					
					n = InsertionSort(lihat_semua);
					index = InterpolationSearch(key, lihat_semua);
					position = 0;
					
					if(index != -1){
						Tampilkan_Data(index);
						ubah_data(index, n, lihat_semua, position);
						
						n = InsertionSort(Masuk);
						for(int i=0; i < n; i++){
							index = InterpolationSearch(key, Masuk);
							if(index != -1){
								ubah_data(index, n, Masuk, position);
							}
						}
						
						n = InsertionSort(Keluar);
						for(int i=0; i < n; i++){
							index = InterpolationSearch(key, Keluar);
							if(index != -1){
								ubah_data(index, n, Keluar, position);
							}
						}
						
						printf("\n\t\t Hapus Data Berhasil\n");
					}else{
						printf("\n\t\t Data Tidak ada\n");
					}
					
					pilih=1;
					x=awal;
					printf("\t\t Kembali ke menu [y/t] ?");
					again=getch();
					system("cls");
					break;
				case 7:
					exit(0);
					break;
			}
		}
		
	} while(again=='y');
}
int ArrowKey(int x, int pilih){
	if(GetAsyncKeyState(VK_DOWN) && x != 18){
		gotoxy(12,x); cout << "  ";
		x++;
		gotoxy(12,x); cout << "->";
		pilih++;	
		return x;
	}
			
	if(GetAsyncKeyState(VK_UP) && x != 12){
		gotoxy(12,x); cout << "  ";
		x--;
		gotoxy(12,x); cout << "->";
		pilih--;
		return x;
	}
	
	return -1;
}
void buat_data(int n){
	char Data_Nama[50] = "Data/Data_Nama.txt", Data_Jumlah[50] = "Data/Data_Jumlah.txt", Data_Kategori[50] = "Data/Data_Kategori.txt", Data_Tgl[50] = "Data/Data_Tgl.txt", Data_Waktu[50] = "Data/Data_Waktu.txt";
	char Data_NamaM[50] = "Data/Masuk/Data_Nama.txt", Data_JumlahM[50] = "Data/Masuk/Data_Jumlah.txt", Data_KategoriM[50] = "Data/Masuk/Data_Kategori.txt", Data_TglM[50] = "Data/Masuk/Data_Tgl.txt", Data_WaktuM[50] = "Data/Masuk/Data_Waktu.txt";
	char Masuk[50] = "/Masuk", lihat_semua[50] = "/";
	
	for(int i=0; i < n; i++)
	{
		printf("\t\t Nama Barang\t: ");
		scanf(" %[^\n]s ", &Data_Now[i].Nama_Barang);
		masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
		masukkan_data(Data_Now[i].Nama_Barang, Data_NamaM);
		
		
		printf("\t\t Jumlah Barang\t: ");
		scanf("%s", &Data_Now[i].jumlah_barang);
		masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
		masukkan_data(Data_Now[i].jumlah_barang, Data_JumlahM);
		
		printf("\t\t KategoriBarang\t: ");
		scanf(" %[^\n]s ", &Data_Now[i].kategori_barang);
		masukkan_data(Data_Now[i].kategori_barang, Data_Kategori);
		masukkan_data(Data_Now[i].kategori_barang, Data_KategoriM);
		
		set_time(lihat_semua);
		set_time(Masuk);
	}
}
void masukkan_data(char data[], char File_name[]){
	FILE *DN;
	DN = fopen(File_name, "a");
	fflush(stdin);
	char Data_s[50];
	strcpy(Data_s, data);
	
	strcat(Data_s, "\n");
	fputs(Data_s, DN);
	fclose(DN);
}
int membuka_data(char File_name[]){
	fstream File;
	File.open(File_name, ios::in);
	int i = 0;
	
	while(!File.eof()){
		i++;
		string Data_Sementara;
		getline(File, Data_Sementara);
		strcpy(Data_Now[i].data_sementara, Data_Sementara.c_str());
	}
	File.close();
	return i;
}
void lihat_data(int i, char kondisi[], int n){
	char status[50];
	int jumlah = atoi(Data_Now[i].jumlah_barang);
	if (jumlah < 1){
		strcpy(status, "Tidak Tersedia");
	}else{
		if (strcmp(kondisi, "/Masuk") == 0){
			strcpy(status, "Barang Masuk");
		}else if(strcmp(kondisi, "/Keluar") == 0){
			strcpy(status, "Barang Keluar");
		}else{
			strcpy(status, "Tersedia");
		}
	}
	
	int T_Text = 25;
	int I_Text = strlen(Data_Now[i].Nama_Barang);
	
	int x = 50 + T_Text;
	int y = i+4;
	
	printf("%d\t %s  %s\t %d\t\t ",  i, Data_Now[i].Tgl, Data_Now[i].Waktu, Data_Now[i].id_barang);
	if(I_Text > T_Text-4){
		for(int s = 0; s <= T_Text-5; s++){
			printf("%c", Data_Now[i].Nama_Barang[s]);
		}
		printf("... ");
	}else{
		printf("%s ", Data_Now[i].Nama_Barang);
	}
	
	gotoxy(x, y);
	printf("%s \t\t %s \t\t %s\n", Data_Now[i].kategori_barang, Data_Now[i].jumlah_barang , status);
	
}
void Tampilkan_Data(int i){
	char status[50];
	int jumlah = atoi(Data_Now[i].jumlah_barang);
	if (jumlah < 1){
		strcpy(status, "Tidak Tersedia");
	}else{
		strcpy(status, "Tersedia");
	}
	
	printf("\t\t ---------------------------------------\n");
	printf("\t\t Id Barang\t: %d\n", Data_Now[i].id_barang);
	printf("\t\t Last Update\t: %s - %s\n", Data_Now[i].Tgl, Data_Now[i].Waktu);
	printf("\t\t Nama Barang\t: %s \n\t\t Jumlah Barang\t: %s\n", Data_Now[i].Nama_Barang, Data_Now[i].jumlah_barang);
	printf("\t\t Kategori\t: %s\n", Data_Now[i].kategori_barang);
	printf("\t\t Status Barang\t: %s\n" , status);
	printf("\t\t ---------------------------------------\n");
}
int set_data(char kondisi[50]){
	char Data_Nama[50] = "/Data_Nama.txt", Data_File[50] = "Data";
	strcat(Data_File, kondisi);
	strcat(Data_File, Data_Nama);
	
	int n = membuka_data(Data_File);
	
	for (int i = 1; i < n; i++){
		ambil_data(i, kondisi);
	}
	return n;
}
int InsertionSort(char kondisi[50]){
	char Data_Nama[50] = "/Data_Nama.txt", Data_File[50] = "Data";
	strcat(Data_File, kondisi);
	strcat(Data_File, Data_Nama);
	
	int n = set_data(kondisi);
	

	for (int i = 1; i < n; i++){
		int temp_idBarang = Data_Now[i].id_barang;
		string temp_namaBarang = Data_Now[i].Nama_Barang, temp_jumlahBarang = Data_Now[i].jumlah_barang, temp_kategoriBarang = Data_Now[i].kategori_barang, temp_tgl = Data_Now[i].Tgl, temp_waktu = Data_Now[i].Waktu;
		
		int j = i - 1;
		while(j >= 1 && Data_Now[j].id_barang > temp_idBarang){
			Data_Now[j+1].id_barang = Data_Now[j].id_barang;
			strcpy(Data_Now[j+1].Tgl, Data_Now[j].Tgl);
			strcpy(Data_Now[j+1].Waktu, Data_Now[j].Waktu);
			
			strcpy(Data_Now[j+1].Nama_Barang, Data_Now[j].Nama_Barang);
			strcpy(Data_Now[j+1].jumlah_barang, Data_Now[j].jumlah_barang);
			strcpy(Data_Now[j+1].kategori_barang, Data_Now[j].kategori_barang);
			j--;
		}
		Data_Now[j+1].id_barang = temp_idBarang;
		strcpy(Data_Now[j+1].Tgl, temp_tgl.c_str());
		strcpy(Data_Now[j+1].Waktu, temp_waktu.c_str());
		
		strcpy(Data_Now[j+1].Nama_Barang, temp_namaBarang.c_str());
		strcpy(Data_Now[j+1].jumlah_barang, temp_jumlahBarang.c_str());
		strcpy(Data_Now[j+1].kategori_barang, temp_kategoriBarang.c_str());
	}
	return n;
}
int InterpolationSearch(int key, char kondisi[50]){
	int n = InsertionSort(kondisi);
	int tengah = 1;
    int bawah = 1;
    int atas = n - 1;
    
    while (bawah <= atas) {
    	int data_low = Data_Now[bawah].id_barang;
    	int data_High = Data_Now[atas].id_barang;
    	
        float tengah1 = (float)(key - data_low) / (data_High - data_low);
        float tengahS = (float)tengah1 * (atas - bawah) +  bawah;
        tengah = round(tengahS);
        if(tengahS > tengah){
        	tengah = tengah + 1;
		}
		
		if(atas == bawah){
			if (key == Data_Now[bawah].id_barang){
				return bawah;
			}else{
				return -1;
			}
		}else if(tengah <= 0){
        	return -1;
		}else if (key == Data_Now[tengah].id_barang) {
        	return tengah;
		}else if (key < Data_Now[tengah].id_barang){
        	atas = tengah - 1;
		}else{
			if (bawah == tengah + 1){
				return -1;
			}else{
				bawah = tengah + 1;
			}
        }
    }
	return -1;
}
void ubah_data(int index, int n, char kondisi[50], int position){
	char Masuk[50] = "/Masuk", Keluar[50] = "/Keluar", lihat_semua[50] = "/";
	char Data_Folder[50] = "Data", Data_Nama[50] = "/Data_Nama.txt", Data_Jumlah[50] = "/Data_Jumlah.txt", Data_File[50];
	char Data_Kategori[50] = "/Data_Kategori.txt", Data_Tgl[50] = "/Data_Tgl.txt", Data_Waktu[50] = "/Data_Waktu.txt";
	strcat(Data_Folder, kondisi);
	
	FILE *DN;
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Nama);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Kategori);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Jumlah);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Tgl);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Waktu);
	DN = fopen(Data_File, "w");
	
	if (strcmp(kondisi, Keluar) == 0 && position == 1){
		for(int i = 1; i < n; i++){
			copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
			copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
			copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
		}
		
		n = InsertionSort(lihat_semua);
	}
	for(int i = 1; i < n; i++){
		if(i == index){
			if(strcmp(kondisi, lihat_semua) == 0 && position == 0){
				printf("\t\t Nama Barang: ");
				scanf(" %[^\n]s ", &Data_Now[i].Nama_Barang);
				copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
				
				printf("\t\t Jumlah Barang: ");
				scanf("%s", &Data_Now[i].jumlah_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
				
				printf("\t\t KategoriBarang\t: ");
				scanf(" %[^\n]s ", &Data_Now[i].kategori_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
				
				set_time(kondisi);
				
				strcpy(Data_Now[0].tempNama_Barang, Data_Now[i].Nama_Barang);
				strcpy(Data_Now[0].tempKategori_Barang, Data_Now[i].kategori_barang);
				strcpy(Data_Now[0].tempJumlah_Barang, Data_Now[i].jumlah_barang);
			}else if(strcmp(kondisi, Masuk) == 0){
				if(position == 1){
					strcpy(Data_Now[n].jumlah_barang, Data_Now[i].jumlah_barang);
					strcpy(Data_Now[n].Nama_Barang, Data_Now[i].Nama_Barang);
					strcpy(Data_Now[n].kategori_barang, Data_Now[i].kategori_barang);
					strcpy(Data_Now[n].Tgl, Data_Now[i].Tgl);
					strcpy(Data_Now[n].Waktu, Data_Now[i].Waktu);
					n++;
					
					//Data Baru
					printf("\t\t <----Barang Masuk--->\n");
					printf("\t\t Jumlah Barang: ");
					scanf("%s", &Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
					
					copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
					copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
					set_time(Masuk);
				}else{
					printf("\t\t <----Barang Masuk--->\n");
					printf("\t\t Data Jumlah Masuk Sebelumnya: %s\n", Data_Now[i].jumlah_barang);
					printf("\t\t Jumlah Barang: ");
					scanf("%s", &Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
					copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
					
					copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[0].tempNama_Barang);
					copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[0].tempKategori_Barang);
				}
			}else if(strcmp(kondisi, Keluar) == 0){
				if(position == 1){
					printf("\t\t <----Barang Keluar--->\n");
					printf("\t\t Jumlah Barang: ");
					scanf("%s", &Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
						
					copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
					copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
					set_time(Keluar);
				}else{
					printf("\t\t <----Barang Keluar--->\n");
					printf("\t\t Data Jumlah Keluar Sebelumnya: %s\n", Data_Now[i].jumlah_barang);
					printf("\t\t Jumlah Barang: ");
					scanf("%s", &Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
					copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
					
					copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
					copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[0].tempNama_Barang);
					copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[0].tempKategori_Barang);
				}
				
			}else{
				copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
				copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
				copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
			}
		}else if(strcmp(kondisi, Masuk) == 0 || strcmp(kondisi, lihat_semua) == 0 ){
			copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
			copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
			copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
		}else if(strcmp(kondisi, Keluar) == 0 && position == 0){
			copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
			copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
			copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
		}
	}
	fclose(DN);
}
void copy_dataFile(char Data_File[], char Data_Folder[], char Type_Data[], char Data[]){
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Type_Data);
	masukkan_data(Data, Data_File);
}
string copy_dataFileString(char Data_File[], char Data_Folder[], char Type_Data[], int i){
	string data;
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Type_Data);
	membuka_data(Data_File);
	return data = Data_Now[i].data_sementara;
}
void hapus_data(int index, int n, char kondisi[50]){
	char Data_Folder[50] = "Data", Data_Nama[50] = "/Data_Nama.txt", Data_Jumlah[50] = "/Data_Jumlah.txt", Data_File[50];
	char Data_Kategori[50] = "/Data_Kategori.txt", Data_Tgl[50] = "/Data_Tgl.txt", Data_Waktu[50] = "/Data_Waktu.txt";
	strcat(Data_Folder, kondisi);
	
	FILE *DN;
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Nama);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Kategori);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Jumlah);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Tgl);
	DN = fopen(Data_File, "w");
		
	strcpy(Data_File, Data_Folder);
	strcat(Data_File, Data_Waktu);
	DN = fopen(Data_File, "w");
	
	for(int i = 1; i < n; i++){
		if(i != index){
			copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
			copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
			copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
			copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
		}
	}
	fclose(DN);
}
void ambil_data(int i, char kondisi[50]){
	char Masuk[50] = "/Masuk", Keluar[50] = "/Keluar", lihat_semua[50] = "/";
	char Data_Folder[50] = "Data", Data_Dicari[50], Data_Nama[50] = "/Data_Nama.txt", Data_Jumlah[50] = "/Data_Jumlah.txt", Data_File[50];
	char Data_Kategori[50] = "/Data_Kategori.txt", Data_Tgl[50] = "/Data_Tgl.txt", Data_Waktu[50] = "/Data_Waktu.txt";
	strcat(Data_Folder, kondisi);
	string data_s;
	
	data_s = copy_dataFileString(Data_File, Data_Folder, Data_Tgl, i);
	strcpy(Data_Now[i].Tgl, data_s.c_str());
	
	data_s = copy_dataFileString(Data_File, Data_Folder, Data_Waktu, i);;
	strcpy(Data_Now[i].Waktu, data_s.c_str());
	
	data_s = copy_dataFileString(Data_File, Data_Folder, Data_Nama, i);;
	strcpy(Data_Now[i].Nama_Barang, data_s.c_str());
	Data_Now[i].id_barang = konversi_char(Data_Now[i].Nama_Barang);
		
	data_s = copy_dataFileString(Data_File, Data_Folder, Data_Jumlah, i);
	strcpy(Data_Now[i].jumlah_barang, data_s.c_str());
	
	data_s = copy_dataFileString(Data_File, Data_Folder, Data_Kategori, i);
	strcpy(Data_Now[i].kategori_barang, data_s.c_str());
}
int konversi_char(char data[]){
	int i_data, Hasil = 0;
	int data_n = strlen(data);
	for(int i = 0; i < data_n; i++){
		i_data = data[i];
		Hasil = Hasil + i_data;
	}
	return Hasil;
}
void barang_keluarMasuk(char kondisi[50], char data_utama[50]){
	int key, index, n;
	char Masuk[50] = "/Masuk", Keluar[50] = "/Keluar", lihat_semua[50] = "/";
	char Data_Folder[50] = "Data", Data_Dicari[50], Data_Nama[50] = "/Data_Nama.txt", Data_Jumlah[50] = "/Data_Jumlah.txt", Data_File[50];
	char Data_Kategori[50] = "/Data_Kategori.txt", Data_Tgl[50] = "/Data_Tgl.txt", Data_Waktu[50] = "/Data_Waktu.txt";
	strcat(Data_Folder, kondisi);
	
	printf("\t\t Masukkan Nama Barang: ");
	scanf(" %[^\n]s ", &Data_Dicari);
			
	key = konversi_char(Data_Dicari);
	index = InterpolationSearch(key, data_utama);
				
	if(index != -1){
		printf("\t\t Data Ditemukan\n");
		Tampilkan_Data(index);
		int jumlah = atoi(Data_Now[index].jumlah_barang);
		int position = 1;
		
		n = InsertionSort(kondisi);
		ubah_data(index, n, kondisi, position);
		int jumlah_N = atoi(Data_Now[index].jumlah_barang);
		
		n = InsertionSort(data_utama);
		if(strcmp(kondisi, Masuk) == 0){
			printf("\t\t Barang telah Masuk\n");
			jumlah = jumlah + jumlah_N;
			stringstream ss;
			ss << jumlah;
			ss >> Data_Now[index].jumlah_barang;
			
			Data_Now[index].id_barang = konversi_char(Data_Now[index].Nama_Barang);
		}else if (strcmp(kondisi, Keluar) == 0){
			jumlah = jumlah - jumlah_N;
			printf("\t\t Barang telah Keluar\n");
			
			if(jumlah < 1){
				jumlah = 0;
			}
			
			stringstream ss;
			ss << jumlah;
			ss >> Data_Now[index].jumlah_barang;
			
			Data_Now[index].id_barang = konversi_char(Data_Now[index].Nama_Barang);
		}else{
			printf("\t\t gagal");
		}
		
		ubah_data(index, n, data_utama, position);
	}else{
		printf("\t\t Data Tidak ada\n");
	}
	
}
void set_time(char kondisi[]){
	struct tm *tgl_barang;
	char Data_Folder[50] = "Data", Data_Nama[50] = "/Data_Nama.txt", Data_Jumlah[50] = "/Data_Jumlah.txt", Data_File[50];
	char Data_Kategori[50] = "/Data_Kategori.txt", Data_Tgl[50] = "/Data_Tgl.txt", Data_Waktu[50] = "/Data_Waktu.txt", Tgl[50], waktu[50];
	strcat(Data_Folder, kondisi);
	
	time_t Tval;
	Tval = time(0);
	tgl_barang = localtime(&Tval);
	
	strftime(Tgl, 50, "%d/%m/%y", tgl_barang);
	strftime(waktu, 50, "%H:%M:%S", tgl_barang);
	
	copy_dataFile(Data_File, Data_Folder, Data_Tgl, Tgl);
	copy_dataFile(Data_File, Data_Folder, Data_Waktu, waktu);
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void garis(int x) {
	int z;
	for(z = 0; z < x; z++) {
		printf("=");
	}
	printf("\n");
}
int linear_search(char kondisi[], int key, int n, int position){
	int legth = InsertionSort(kondisi);
	int prev = 1;
	
	int i_data, hasil, flag = 0;
	while(prev <= legth-1){
		for(int i=0; i < n; i++){
			i_data = Data_Now[prev].Nama_Barang[i];
			hasil = hasil + i_data;
		}
		if(hasil == key){
			if(position == 0){
				ubah_data(prev, legth, kondisi, position);
			}else if( position == 1){
				Tampilkan_Data(prev);
			}else if (position == 2){
				hapus_data(prev, legth, kondisi);
			}
			
			hasil = 0;
			flag = 1;
		}else{
			hasil = 0;
		}
		prev++;
	}
	return flag;
}
