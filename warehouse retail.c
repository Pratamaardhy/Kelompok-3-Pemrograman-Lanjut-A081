#include <stdio.h>

struct barang
{
	char nama[50];
	char asal[50];
	char tanggal[50];
	int jml;
	int nomor;
	char kategori[50];
} m[100];

int main()
{
	int pilih,temp;
	int i,j,n,rn,k,a,b,c,cari,masuk;
	int mid,low,high;
	menu:
	system("cls");
	printf("\t\t\n\n\n\t\t\t<----------------:MANAJEMEN GUDANG PERUSAHAAN RITEL:---------------->\n\n");
	printf("\t\t1 Tambah Data Barang\n\t\t2 Tampilkan Data Barang\n\t\t3 Hapus Data Barang\n\t\t4 Perbarui Data Barang\n\t\t5 Cari Data Barang\n\t\t6 Keluar");
	do
	{
	 printf("\n\n\t\tMasukan Pilihan: ");
     scanf("%d", &pilih);
     switch (pilih)
	 {
     	case 1:
     		//------------Menambah Data Mahasiswa----------------//
		 	system("cls");
			printf("\t\t\n\n\n\t\t\t<----------------:Tambah Data Barang:---------------->\n\n");
		 	printf("\t\tMasukan Jumlah Data:");
				scanf("%d",&n);
				for(i=0;i<n;i++)
				{
					printf("\n\t\tMasukan Data Barang ke-%d:\n",i+1);
					fflush(stdin);

                    printf("\t\tMasukan Nomor Barang : ");
					gets(m[i].nomor);

                    printf("\t\tMasukan Asal Barang: ");
					scanf("%d", &m[i].asal);

                    printf("\t\tMasukan Tanggal Datang Barang: ");
					scanf("%d", &m[i].tanggal);

					printf("\t\tMasukan Jumlah Barang: ");
					scanf("%d", &m[i].jml);

					printf("\t\tMasukan Nama Barang : ");
					gets(m[i].nama);

					printf("\t\tMasukan Kategori Barang: ");
					scanf("%d", &m[i].kategori);

				}
			goto menu;
     		break;
     	case 2:
     		//------------Tampilkan Data Barang----------------//
     		system("cls");
     		printf("\t\t\n\n\n\t\t\t<----------------:Tampilan Data Barang:---------------->\n\n");
			printf("\t\t\t\t\t      Metode Pencarian\n\n");
			printf("\t\t1.Metode selection Search\n");
			printf("\t\t2.Metode insertion Search\n");
			printf("\n\t\tMasukan pilihan metode:");
			scanf("%d",&masuk);
			switch(masuk)
			{
				case 1:
					lihat:
					system("cls");
		     		printf("\t\t<---------------------------------:Lihat Data Barang:--------------------------------->\n\n");
				    printf("\t\tNo\tNomor\t\tAsal\t\tTanggal\t\tJumlah\t\tNama Barang\t\tKategori\n");
		    		printf("\t\t--------------------------------------------------------------------------------\n");

						for(i = 0; i<n; i++){
							for(j = 0; j<n-1;j++){
								if(m[j].nomor>m[j+1].nomor){
									temp = m[j].nomor;
									m[j].nomor = m[j+1].nomor;
									m[j+1].nomor=temp;
									}
							}
						}
						for(i = 0; i<n; i++)
						{
						printf("\t\t%d\t%s\t\t\t%d\t\t%d\n",i+1,m[i].nomor,m[i].asal,m[i].tanggal,m[i].jml,m[i].nama,m[i].kategori);
						}
						system("pause");
						goto menu;
						break;

				case 2:
					system("cls");
		     		printf("\t\t<---------------------------------:Lihat Data Barang:--------------------------------->\n\n");
				    printf("\t\tNo\tNomor\t\tAsal\t\tTanggal\t\tJumlah\t\tNama Barang\t\tKategori\n");
		    		printf("\t\t--------------------------------------------------------------------------------\n");
					for(i=1;i<n;i++)
					{
						c=m[i].nomor;
						for(j=i-1;j>0 && c<m[j].nomor;j--)
						{
							m[j+1].nomor=m[j].nomor;
							m[j+1].nomor=c;
						}

					}
					for(i = 0; i<n; i++)
						{
						printf("\t\t%d\t%s\t\t\t%d\t\t%d\n",i+1,m[i].nomor,m[i].asal,m[i].tanggal,m[i].jml,m[i].nama,m[i].kategori);
						}
						system("pause");
						goto menu;
						break;
			}


		case 3:
			//------------Pencarian Data Barang----------------//
			system("cls");
			printf("\t\t\n\n\n\t\t\t<----------------:Hapus Data Barang:---------------->\n\n");
			printf("\t\tHapus data ke-");
			scanf("%d",&a);
			b=a-1;
			n--;
			for(i=b;i<n;i++)
			{
				m[i]=m[i+1];

			}
			printf("\n\n\t\tData ke-%d Terhapus\n",a);
			system("pause");
			goto menu;

		case 4:
			//------------Edit Data Barang----------------//
			system("cls");
			printf("\t\t\n\n\n\t\t\t<----------------:Edit Data Barang:---------------->\n\n");
			printf("\t\tMasukan Data Yang akan diperbarui:");
			scanf("%d",&b);
			a=b-1;
                    fflush(stdin);
                    printf("\t\tMasukan Nomor Barang : ");
					gets(m[a].nomor);

                    printf("\t\tMasukan Asal Barang: ");
					scanf("%d", &m[a].asal);

                    printf("\t\tMasukan Tanggal Datang Barang: ");
					scanf("%d", &m[a].tanggal);

					printf("\t\tMasukan Jumlah Barang: ");
					scanf("%d", &m[a].jml);

					printf("\t\tMasukan Nama Barang : ");
					gets(m[a].nama);

					printf("\t\tMasukan Kategori Barang: ");
					scanf("%d", &m[a].kategori);
			goto lihat;
			system("pause");
			goto menu;

		case 5:
			//------------Cari Data Barang----------------//
			system("cls");
			printf("\t\t\n\n\n\t\t\t<----------------:Cari Data Barang:---------------->\n\n");

					printf("\t\tMasukan Nomor Barang :");
					scanf("%d",&rn);
					for(i=0;i<n;i++) //Mencari data Barang//
						{
							if(m[i].nomor==rn)
						{
							printf("\n\n\t\t<---------------------------------:Cari Data:--------------------------------->\n\n");
                            printf("\t\tNo\tNomor\t\tAsal\t\tTanggal\t\tJumlah\t\tNama Barang\t\tKategori\n");
			    			printf("\t\t------------------------------------------------------------------------------\n");
							k=i;
						printf("\t\t%d\t%s\t\t\t%d\t\t%d\n",i+1,m[i].nomor,m[i].asal,m[i].tanggal,m[i].jml,m[i].nama,m[i].kategori);
						}
						else{
							printf("\n\n\t\t<---------------------------------:Data Eror:--------------------------------->\n\n");
                            printf("\t\tNo\tNomor\t\tAsal\t\tTanggal\t\tJumlah\t\tNama Barang\t\tKategori\n");
		    				printf("\t\t------------------------------------------------------------------------------\n");
							}
						}
						system("pause");
						goto menu;
						break;

		case 6:
			exit(0);
			break;
		default:
		printf("\n\t\t-_- -_- -_-  Sorry Input salah silahkan ulangi lagi  -_- -_- -_-\n\n");
		printf("\n\n				    ");
		system("pause");
		goto menu;
	 }

	}while (pilih != 0);
	return 0;
}
