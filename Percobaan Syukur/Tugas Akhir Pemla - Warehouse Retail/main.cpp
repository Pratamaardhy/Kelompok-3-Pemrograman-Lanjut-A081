#include <string.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

struct Data_Barang{
	int id_barang;
	char Nama_Barang[50], kategori_barang[50], jumlah_barang[50], data_sementara[50], Tgl[50], Waktu[50];
} Data_Now[50];

//Fungsi Menu
void lihat_data(int i, char kondisi[]), buat_data(int i), hapus_data(int index, int n, char kondisi[50]);
void barang_keluarMasuk(char kondisi[50], char data_utama[50]);
int InsertionSort(char kondisi[50]), InterpolationSearch(int key, char kondisi[]);

//Fungsi Pendukung Menu
void ubah_data(int index, int n, char kondisi[50]), ambil_data(int i, char kondisi[50]), Tampilkan_Data(int i), masukkan_data(char data[], char File_name[]);
void copy_dataFile(char Data_File[], char Data_Folder[], char kondisi[], char data[]);
int set_data(char kondisi[50]);

//Fungsi Tambahan
void set_time(char kondisi[]);
int konversi_char(char data[]), membuka_data(char File_name[]);
string copy_dataFileString(char Data_File[], char Data_Folder[], char Type_Data[], int i);

main(){
	int pilih, key, index;
	char again='y', Data_Dicari[50], Masuk[50] = "/Masuk", Keluar[50] = "/Keluar", lihat_semua[50] = "/", pilih_1[50];
	do
	{
		int n = set_data(lihat_semua);
		system("cls");
		printf("\t\t\n\n\n\t\t\t<----------------:MANAJEMEN GUDANG PERUSAHAAN RITEL:---------------->\n\n");
		printf("\t\t 1. Barang Masuk\n\t\t 2. Barang Keluar\n\t\t 3. Tampilkan Data Barang\n\t\t 4. Cari Data Barang\n\t\t 5. Hapus Data Barang\n\t\t 6. Keluar\n\t\t Pilihan anda ? ");
		scanf("%d", &pilih);
		
		if(pilih>6){
			system("cls");
			printf("\t\t INPUT SALAH, COBA LAGI!!\n");
			printf("\t\t Kembali ke menu [y/t] ?");
			again=getch();
		}
		
		switch(pilih)
		{
			case 1:
				system("cls");
				printf("\t\t\n\n\n\t\t\t<----------------:Data Barang Masuk:---------------->\n\n");
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
				
				printf("\t\t Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 2:
				barang_keluarMasuk(Keluar, lihat_semua);
				
				printf("\t\t Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 3:
				printf("1. Riwayat Barang Masuk \n");
				printf("2. Riwayat Barang Keluar \n");
				printf("3. Tampilkan Data Barang Digudang \n");
				
				printf("Pilihan anda ?");
				printf("Pilihan anda ?");
				scanf("%d", &pilih);
				
				if( pilih == 1 ){
					n = set_data(Masuk);
					printf("Berikut Data Berdasarkan Id Barang: \n");
					InsertionSort(Masuk);
					printf("No\t Terakhir Diperbarui \t IdBarang\t NamaBarang\t\t Kategori\t Jumlah\t Status\n");
					for (int i = 1; i < n; i++){
						lihat_data(i, Masuk);
					}
				}else if(pilih == 2){
					n = set_data(Keluar);
					printf("Berikut Data Berdasarkan Id Barang: \n");
					InsertionSort(Keluar);
					printf("No\t Terakhir Diperbarui \t IdBarang\t NamaBarang\t\t Kategori\t Jumlah\t Status\n");
					for (int i = 1; i < n; i++){
						lihat_data(i, Keluar);
					}
				}else if(pilih == 3){
					printf("Berikut Data Berdasarkan Id Barang: \n");
					InsertionSort(lihat_semua);
					printf("No\t Terakhir Diperbarui \t IdBarang\t NamaBarang\t\t Kategori\t Jumlah\t Status\n");
					for (int i = 1; i < n; i++){
						lihat_data(i, lihat_semua);
					}
				}
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 4:
				printf("Masukkan Nama Barang: ");
				scanf(" %[^\n]s ", Data_Dicari);
				
				key = konversi_char(Data_Dicari);
				index = InterpolationSearch(key, lihat_semua);
				
				if(index != -1){
					printf("Data Ditemukan\n");
					Tampilkan_Data(index);
				}else{
					printf("Data Tidak ada\n");
				}
				
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 5:
				printf("Masukkan Nama Barang: ");
				scanf(" %[^\n]s ", Data_Dicari);
				
				key = konversi_char(Data_Dicari);
				if(index != -1){
					index = InterpolationSearch(key, lihat_semua);
					hapus_data(index, n, lihat_semua);
					
					index = InterpolationSearch(key, Masuk);
					hapus_data(index, n, Masuk);
					
					index = InterpolationSearch(key, Keluar);
					hapus_data(index, n, Keluar);
					printf("Hapus Data Berhasil\n");
				}else{
					printf("Data Tidak ada\n");
				}
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 6:
				exit(0);
				break;
		}
	}
	while(again=='y');
}
void buat_data(int n){
	char Data_Nama[50] = "Data/Data_Nama.txt", Data_Jumlah[50] = "Data/Data_Jumlah.txt", Data_Kategori[50] = "Data/Data_Kategori.txt", Data_Tgl[50] = "Data/Data_Tgl.txt", Data_Waktu[50] = "Data/Data_Waktu.txt";
	char Data_NamaM[50] = "Data/Masuk/Data_Nama.txt", Data_JumlahM[50] = "Data/Masuk/Data_Jumlah.txt", Data_KategoriM[50] = "Data/Masuk/Data_Kategori.txt", Data_TglM[50] = "Data/Masuk/Data_Tgl.txt", Data_WaktuM[50] = "Data/Masuk/Data_Waktu.txt";
	char Masuk[50] = "/Masuk", lihat_semua[50] = "/";
	
	for(int i=0; i < n; i++)
	{
		printf("Nama Barang\t: ");
		scanf(" %[^\n]s ", &Data_Now[i].Nama_Barang);
		masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
		masukkan_data(Data_Now[i].Nama_Barang, Data_NamaM);
		
		
		printf("Jumlah Barang\t: ");
		scanf("%s", &Data_Now[i].jumlah_barang);
		masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
		masukkan_data(Data_Now[i].jumlah_barang, Data_JumlahM);
		
		printf("KategoriBarang\t: ");
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
void lihat_data(int i, char kondisi[]){
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
	
	int A = konversi_char(Data_Now[i].Nama_Barang), B = konversi_char(Data_Now[i].kategori_barang);
	if(A<1100){
		printf("%d\t %s  %s\t %d\t\t %s \t\t %s \t  %s  \t %s\n", i, Data_Now[i].Tgl, Data_Now[i].Waktu, Data_Now[i].id_barang, Data_Now[i].Nama_Barang, Data_Now[i].kategori_barang, Data_Now[i].jumlah_barang , status);
	}else if (B<500){
		printf("%d\t %s  %s\t %d\t\t %s \t %s \t\t  %s  \t %s\n", i, Data_Now[i].Tgl, Data_Now[i].Waktu, Data_Now[i].id_barang, Data_Now[i].Nama_Barang, Data_Now[i].kategori_barang, Data_Now[i].jumlah_barang , status);
	}else{
		printf("%d\t %s  %s\t %d\t\t %s \t %s \t  %s  \t %s\n", i, Data_Now[i].Tgl, Data_Now[i].Waktu, Data_Now[i].id_barang, Data_Now[i].Nama_Barang, Data_Now[i].kategori_barang, Data_Now[i].jumlah_barang , status);
	}
}
void Tampilkan_Data(int i){
	char status[50];
	int jumlah = atoi(Data_Now[i].jumlah_barang);
	if (jumlah < 1){
		strcpy(status, "Tidak Tersedia");
	}else{
		strcpy(status, "Tersedia");
	}
	
	printf("---------------------------------------\n");
	printf("Id Barang\t: %d\n", Data_Now[i].id_barang);
	printf("Last Update\t: %s - %s\n", Data_Now[i].Tgl, Data_Now[i].Waktu);
	printf("Nama Barang\t: %s \nJumlah Barang\t: %s\n", Data_Now[i].Nama_Barang, Data_Now[i].jumlah_barang);
	printf("Kategori\t: %s\n", Data_Now[i].kategori_barang);
	printf("Status Barang\t: %s\n" , status);
	printf("---------------------------------------\n");
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
        if(tengah <= 0){
        	return -1;
		}else if (key == Data_Now[tengah].id_barang) {
        	return tengah;
		}else if (key < Data_Now[tengah].id_barang){
        	atas = tengah - 1;
		}else{
        	bawah = tengah + 1;
        }
    }
	return -1;
}
void ubah_data(int index, int n, char kondisi[50]){
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
	
	printf("Kondisi: %s\n", kondisi);
	if (strcmp(kondisi, Keluar) == 0){
		n = InsertionSort(lihat_semua);
	}
	for(int i = 1; i < n; i++){
		if(i == index){
			if(strcmp(kondisi, lihat_semua) == 0 && Data_Now[index].id_barang == 0){
				printf("Nama Barang: ");
				scanf(" %[^\n]s ", &Data_Now[i].Nama_Barang);
				copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
				
				printf("Jumlah Barang: ");
				scanf("%s", &Data_Now[i].jumlah_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
				
				printf("KategoriBarang\t: ");
				scanf(" %[^\n]s ", &Data_Now[i].kategori_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
				
				set_time(kondisi);
			}else if(strcmp(kondisi, Masuk) == 0){
				printf("N a: %d\n", n);
				strcpy(Data_Now[n].jumlah_barang, Data_Now[i].jumlah_barang);
				strcpy(Data_Now[n].Nama_Barang, Data_Now[i].Nama_Barang);
				strcpy(Data_Now[n].kategori_barang, Data_Now[i].kategori_barang);
				strcpy(Data_Now[n].Tgl, Data_Now[i].Tgl);
				strcpy(Data_Now[n].Waktu, Data_Now[i].Waktu);
				n++;
				printf("N r: %d\n", n);
				//Data Baru
				printf("Jumlah Barang: ");
				scanf("%s", &Data_Now[i].jumlah_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
				
				copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
				copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
				copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
			}else if(strcmp(kondisi, Keluar) == 0){
				printf("Jumlah Barang: ");
				scanf("%s", &Data_Now[i].jumlah_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Jumlah, Data_Now[i].jumlah_barang);
					
				copy_dataFile(Data_File, Data_Folder, Data_Nama, Data_Now[i].Nama_Barang);
				copy_dataFile(Data_File, Data_Folder, Data_Kategori, Data_Now[i].kategori_barang);
				copy_dataFile(Data_File, Data_Folder, Data_Tgl, Data_Now[i].Tgl);
				copy_dataFile(Data_File, Data_Folder, Data_Waktu, Data_Now[i].Waktu);
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
	
	if (strcmp(kondisi, "/Keluar") == 0){
		n = InsertionSort(kondisi);
	}
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
	
	printf("Masukkan Nama Barang: ");
	scanf(" %[^\n]s ", &Data_Dicari);
			
	key = konversi_char(Data_Dicari);
	printf("%d\n", key);
	index = InterpolationSearch(key, data_utama);
				
	if(index != -1){
		printf("Data Ditemukan\n");
		Tampilkan_Data(index);
		int jumlah = atoi(Data_Now[index].jumlah_barang);
		
		n = InsertionSort(kondisi);
		ubah_data(index, n, kondisi);
		int jumlah_N = atoi(Data_Now[index].jumlah_barang);
		
		n = InsertionSort(data_utama);
		if(strcmp(kondisi, Masuk) == 0){
			printf("Barang telah Masuk\n");
			jumlah = jumlah + jumlah_N;
			stringstream ss;
			ss << jumlah;
			ss >> Data_Now[index].jumlah_barang;
			
			Data_Now[index].id_barang = konversi_char(Data_Now[index].Nama_Barang);
		}else if (strcmp(kondisi, Keluar) == 0){
			jumlah = jumlah - jumlah_N;
			printf("Barang telah Keluar\n");
			
			if(jumlah < 1){
				jumlah = 0;
			}
			
			stringstream ss;
			ss << jumlah;
			ss >> Data_Now[index].jumlah_barang;
			
			Data_Now[index].id_barang = konversi_char(Data_Now[index].Nama_Barang);
		}else{
			printf("gagal");
		}
		
		ubah_data(index, n, data_utama);
		printf("%s\n", data_utama);
	}else{
		printf("Data Tidak ada\n");
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
