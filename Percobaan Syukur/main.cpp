#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <time.h>

using namespace std;

struct Data_Barang{
	int id_barang;
	char Nama_Barang[50], kategori_barang[50], tgl_barang[50], jumlah_barang[50], data_sementara[50];
} Data_Now[50];

void buat_data(), lihat_data(int i), InsertionSort(), ubah_data(int index, int n), hapus_data(int index, int n), ambil_data(int i), masukkan_data(char data[], char File_name[]);
int konversi_char(char data[]), InterpolationSearch(int key, int n), konversi_String(string data), membuka_data(char File_name[]), set_data();

main(){
	int pilih, key, index;
	char again='y',Data_Dicari[50];;
	
	do
	{
		int n = set_data();
		system("cls");
		printf("===Menu Utama===\n");
		printf("1. Tambahkan barang\n");
		printf("2. Hapus Barang\n");
		printf("3. Tampilkan Barang\n");
		printf("4. Cari Barang\n");
		printf("5. Perbarui Barang\n");
		
		printf("Pilihan anda ?");
		scanf("%d", &pilih);
		
		if(pilih>5){
			system("cls");
			printf("INPUT SALAH, COBA LAGI!!\n");
			printf("Kembali ke menu [y/t] ?");
			again=getch();
		}
		
		switch(pilih)
		{
			case 1:
				buat_data();
				printf("Data Berhasil Ditambahkan\n");
				
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 2:
				InsertionSort();
				printf("Masukkan Nama Barang: ");
				gets(Data_Dicari);
				scanf("%[^\n]s", Data_Dicari);
				
				key = konversi_char(Data_Dicari);
				index = InterpolationSearch(key, n);
				if(index != -1){
					hapus_data(index, n);
					printf("Hapus Data Berhasil\n");
				}else{
					printf("Data Tidak ada\n");
				}
				
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 3:
				printf("Berikut Data Berdasarkan Id Barang: \n");
				printf("---------------------------------------\n");
				InsertionSort();
				for (int i = 1; i < n; i++){
					lihat_data(i);
				}
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 4:
				InsertionSort();	
				printf("Masukkan Nama Barang: ");
				gets(Data_Dicari);
				scanf("%[^\n]s", Data_Dicari);
				
				key = konversi_char(Data_Dicari);
				printf("%d\n", key);
				index = InterpolationSearch(key, n);
				
				if(index != -1){
					printf("Data Ditemukan\n");
					lihat_data(index);
				}else{
					printf("Data Tidak ada\n");
				}
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
			case 5:
				InsertionSort();
				printf("Masukkan Nama Barang: ");
				gets(Data_Dicari);
				scanf("%[^\n]s", Data_Dicari);
				
				key = konversi_char(Data_Dicari);
				index = InterpolationSearch(key, n);
				if(index != -1){
					ubah_data(index, n);
					printf("Data Telah Diperbarui\n");
				}else{
					printf("Data Tidak ada\n");
				}
				
				printf("Kembali ke menu [y/t] ?");
				again=getch();
				break;
		}
	}
	while(again=='y');
}

void buat_data(){
	char Data_Nama[50] = "Data_Nama.txt", Data_Jumlah[50] = "Data_Jumlah.txt";
	int Banyak_Barang;
	
	printf("Masukkan Jumlah Barang Yang DiInputkan: ");
	scanf("%d", &Banyak_Barang);
	for(int i=0; i < Banyak_Barang; i++)
	{
		printf("Nama Barang: ");
		gets(Data_Now[i].Nama_Barang);
		scanf("%[^\n]s", &Data_Now[i].Nama_Barang);
		masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
		
		printf("Jumlah Barang: ");
		scanf("%s", &Data_Now[i].jumlah_barang);
		masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
	}
}
void masukkan_data(char data[], char File_name[]){
	FILE *DN;
	DN = fopen(File_name, "a");
	fflush(stdin);
	strcat(data, "\n");
	fputs(data, DN);
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
void lihat_data(int i){
	printf("Id Barang\t: %d\n", Data_Now[i].id_barang);
	printf("Nama Barang\t: %s \nJumlah Barang\t: %s\n", Data_Now[i].Nama_Barang, Data_Now[i].jumlah_barang);
	printf("---------------------------------------\n");
}
int set_data(){
	char Data_Nama[50] = "Data_Nama.txt";
	int n = membuka_data(Data_Nama);
	
	for (int i = 1; i < n; i++){
		ambil_data(i);
	}
	return n;
}
void InsertionSort(){
	char Data_Nama[50] = "Data_Nama.txt";
	int n = membuka_data(Data_Nama);
	set_data();

	for (int i = 1; i < n; i++){
		int temp_idBarang = Data_Now[i].id_barang;
		string temp_namaBarang = Data_Now[i].Nama_Barang, temp_jumlahBarang = Data_Now[i].jumlah_barang;
		
		int j = i - 1;
		while(j >= 1 && Data_Now[j].id_barang > temp_idBarang){
			Data_Now[j+1].id_barang = Data_Now[j].id_barang;
			strcpy(Data_Now[j+1].Nama_Barang, Data_Now[j].Nama_Barang);
			strcpy(Data_Now[j+1].jumlah_barang, Data_Now[j].jumlah_barang);
			j--;
		}
		Data_Now[j+1].id_barang = temp_idBarang;
		strcpy(Data_Now[j+1].Nama_Barang, temp_namaBarang.c_str());
		strcpy(Data_Now[j+1].jumlah_barang, temp_jumlahBarang.c_str());
	}
}
int InterpolationSearch(int key, int n){
	int tengah = 1;
    int bawah = 1;
    int atas = 4;
    
    for(int i = 1; i < n; i++){
    	lihat_data(i);
	}
    while (bawah <= atas) {
    	int data_low = Data_Now[bawah].id_barang;
    	int data_High = Data_Now[atas].id_barang;
    	
        float tengah1 = (float)(key - data_low) / (data_High - data_low);
        tengah = (float)tengah1 * (atas - bawah) +  bawah;
		
        if(tengah < 0){
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
void ubah_data(int index, int n){
	char Data_Nama[50] = "Data_Nama.txt", Data_Jumlah[50] = "Data_Jumlah.txt";
	
	FILE *DN;
	DN = fopen(Data_Nama, "w");
	DN = fopen(Data_Jumlah, "w");
	for(int i = 1; i < n; i++){
		if(i == index){
			printf("Nama Barang: ");
			gets(Data_Now[i].Nama_Barang);
			scanf("%[^\n]s", &Data_Now[i].Nama_Barang);
			masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
			
			printf("Jumlah Barang: ");
			scanf("%s", &Data_Now[i].jumlah_barang);
			masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
		}else{
			masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
			masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
		}
		
	}
	fclose(DN);
}
void hapus_data(int index, int n){
	char Data_Nama[50] = "Data_Nama.txt", Data_Jumlah[50] = "Data_Jumlah.txt";
	
	FILE *DN;
	DN = fopen(Data_Nama, "w");
	DN = fopen(Data_Jumlah, "w");
	for(int i = 1; i < n; i++){
		if(i != index){
			masukkan_data(Data_Now[i].Nama_Barang, Data_Nama);
			masukkan_data(Data_Now[i].jumlah_barang, Data_Jumlah);
		}
		
	}
	fclose(DN);
}
void ambil_data(int i){
	char Data_Nama[50] = "Data_Nama.txt", Data_Jumlah[50] = "Data_Jumlah.txt";
	string data_s;
	
	membuka_data(Data_Nama);
	data_s = Data_Now[i].data_sementara;
	strcpy(Data_Now[i].Nama_Barang, data_s.c_str());
	Data_Now[i].id_barang = konversi_char(Data_Now[i].Nama_Barang);
		
	membuka_data(Data_Jumlah);
	data_s = Data_Now[i].data_sementara;
	strcpy(Data_Now[i].jumlah_barang, data_s.c_str());
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
int konversi_String(string data){
	int i_data, Hasil = 0;
	int data_n = data.length();
	for(int i = 0; i < data_n; i++){
		i_data = data[i];
		Hasil = Hasil + i_data;
	}
	return Hasil;
}
