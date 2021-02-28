// Nama Anggota Kelompok : Rychie C Manik(11318032)
//						   Nancy Aprelia Sibarani (11318034)
//						 : Anjelin Hutauruk(11318038)
//Kelas					 : 31 TI 1
//Topik 				 : Sistem Pendataan Pasien Rumah Sakit Balige .



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tambahpasien(char * pathData, char * namapasien,  char * alamat ,char * tanggallahir, char * umur, char * berat, char * tinggi, char *golda, char * keluhan);
void lihatdaftarpasien(char * data);
char * bacaDataDanSimpanKeDynamicArray(char * pathData);



int main(){
	int opsi;
	char namapasien[1024], tanggallahir[1024], alamat[1024] , umur[1024], berat[1024] ,tinggi[1024],golda [1025],keluhan[1024];
	char *pathData = "Database Pasien RS Balige.txt";

	

	while(1){
	puts("--------------------------------------------");
	puts("SELAMAT DATANG DI RUMAH SAKIT HKBP BALIGE");
	puts("--------------------------------------------\n");
	puts("\t\tMenu	: ");
	puts("1. Tambah Data Pasien baru");
	puts("2. Lihat Daftar Pasien");
	puts("3. Keluar Dari Aplikasi");
	puts("--------------------------------------------");
		printf("Menu Pilihan Anda: ");
		scanf("%d", &opsi);
		
		
		if(opsi == 3){
			system("cls");
			printf("\n\n\n\n\n\t\t\tTerima Kasih Telah Berkunjung.");
			getch();
			break;
		}

		if(opsi == 1){
			system("cls");
			
			puts("============================================");
			puts("\t\tTambah Pasien");
			puts("--------------------------------------------");	
			printf("\nNama Pasien\t\t: ");
			scanf(" %[^\t\n]s", namapasien);

			printf("Alamat\t\t\t: ");
			scanf(" %[^\t\n]s", alamat);
			
			printf("Tempat, Tanggal Lahir\t: ");
			scanf(" %[^\t\n]s", tanggallahir);
			
			printf("Umur\t\t\t: ");
			scanf(" %[^\t\n]s", umur);
			
			printf("Berat Badan \t\t: ");
			scanf(" %[^\t\n]s", berat);
			

			printf("Tinggi Badan \t\t: ");
			scanf(" %[^\t\n]s", tinggi);
			
			printf("Golongan Darah \t\t: ");
			scanf(" %[^\t\n]s", golda);
			
			printf("Keluhan Anda \t\t: ");
			scanf(" %[^\t\n]s", keluhan);
			
			// memanggil prosedur tambah pasien
			tambahpasien(pathData, namapasien, alamat, tanggallahir , umur , berat , tinggi ,golda,  keluhan);
			
			getch();
		}

		if(opsi == 2){
			system("cls");
			puts("\tDaftar Nama Pasien");
			puts("--------------------------------------------");
		
			char * data = bacaDataDanSimpanKeDynamicArray(pathData);
			lihatdaftarpasien(data); // memanggil prosedur lihat daftar pasien 
			free(data); //free memory yang digunakan
			puts("");
			getch();
		}
	}
	return 0;
}





// Merupakan fungsi yang akan membaca file,kemudian menyimpannya ke dalam sebuah dynamic memory satu dimensi.
//Fungsi ini membutuhkan sebuah parameter yang berisikan 'path' atau lokasi dimana file data berada.
char * bacaDataDanSimpanKeDynamicArray(char* pathData){
	int first_size = 1; // pemisalan dengan kata first_size untuk alokasi pertama dengan nilai 1
	char * arrData = (char *) malloc (first_size * sizeof(char)); //mengalokasikan memori 
	int c;
	FILE *f; // pemanggilan file

	if((f = fopen(pathData, "r")) == NULL){
		puts("Gagal Membuka Data Base , Silahkan Coba Lagi ");
		exit(1); // apabila file tidak ada atau path salah maka akan keluar.
	}else{
			// Looping selama tidak akhir dari file (EOF)
		do{
			c = fgetc(f);
			if(feof(f)) break;  // kondisi yang akan memeriksa akhir file
			else{
				arrData[first_size - 1] = c; // Masukan satu-per-satu karakter ke dalam blok memori
				first_size += 1; // Update size memori yang dibutuhkan, dengan cara menambah 1 blok saja 
				arrData = (char *) realloc (arrData, first_size); // Realokasi blok memori
			}
		}while(1);
	}

	fclose(f); // menutup file data sehabis memakainya.
	return arrData;
}




void tambahpasien(char * pathData, char *namapasien, char * alamat , char * tanggallahir, char * umur, char * berat, char * tinggi, char * golda, char * keluhan){
	FILE *f;
	if((f = fopen(pathData, "a")) == NULL){ // a itu buka dan melihat
												// a+ itu buka lihat tambah
		puts("Gagal Membuka Data Base , Silahkan Coba Lagi");
		exit(1);
	}else{
		// strcat merupakan fungsi yang dapat digunakan untuk menggabungkan dua buah string.
		strcat(namapasien, "|");
		strcat(namapasien, alamat);
	
		strcat(namapasien, "|");
		strcat(namapasien, tanggallahir);
		
		strcat(namapasien, "|");
		strcat(namapasien, umur);
		
		strcat(namapasien, "|");
		strcat(namapasien, berat);
		
		strcat(namapasien, "|");
		strcat(namapasien, tinggi);
		
		strcat(namapasien, "|");
		strcat(namapasien, golda);		
		
		strcat(namapasien, "|");
		strcat(namapasien, keluhan);
		
		strcat(namapasien, "\n");
		fprintf(f, "%s", namapasien);
		
		puts("Data Anda Telah Tersimpan . Terima Kasih :) ");
		puts("--------------------------------------------\n");
	}
	fclose(f); //menutup file data sehabis memakainya.
}

void lihatdaftarpasien(char * data){
	char * token_sharp = "\n";
	char * temp_per_pasien;
	char * rest = data;

	// Untuk loop pertama (while) bertujuan untuk 'memotong' data yang dibatasi dengan
	// delimiter '|'. 

	// 'strtok_r merupakan versi reentrant dari 'strtok'.
	// Penggunaan 'strtok' kurang aman dibandingkan dengan 'strtok_r',
	// hal ini dikarenakan masalah static context yang terdapat pada 'strtok'.	
	
	while((temp_per_pasien = strtok_r(rest, token_sharp, &rest))){ //loop pertama
		char * token_pipe = "|";
		char * temp_per_token;
		char * last = temp_per_pasien;

		char * _namapasien = NULL;
		char * _alamat = NULL;
		char * _tanggallahir = NULL;
		char * _umur= NULL;
		char * _berat = NULL;
		char * _tinggi = NULL;
		char * _golda = NULL;
		char * _keluhan = NULL;
		while((temp_per_token = strtok_r(last, token_pipe, &last))){ //loop 2
			if(_namapasien == NULL){
				int len = strlen(temp_per_token); // Fungsi ini bertujuan untuk menghitung berapa banyak
												// jumlah karakter yang ada di dalam sebuah string.
				_namapasien = (char *) malloc (len * sizeof(char)); // mengalokasikan memory sepanjang strlen yang  di tentukan
				strcpy(_namapasien, temp_per_token);// Fungsi 'strcpy' berada di dalam pustaka string.h
													// Fungsi ini bertujuan untuk meng-copy data dari sebuah
													// variable yang bertipe char *.
			}
			else if(_alamat == NULL){
				int len = strlen(temp_per_token);
				_alamat = (char *) malloc (len * sizeof(char));
				strcpy(_alamat, temp_per_token);
			}
			else if(_tanggallahir == NULL){
				int len = strlen(temp_per_token);
				_tanggallahir = (char *) malloc (len * sizeof(char));
				strcpy(_tanggallahir, temp_per_token);
			}
				else if(_umur == NULL){
				int len = strlen(temp_per_token);
				_umur = (char *) malloc (len * sizeof(char));
				strcpy(_umur, temp_per_token);
			}
				else if(_berat == NULL){
				int len = strlen(temp_per_token);
				_berat = (char *) malloc (len * sizeof(char));
				strcpy(_berat, temp_per_token);
			}
				else if(_tinggi == NULL){
				int len = strlen(temp_per_token);
				_tinggi = (char *) malloc (len * sizeof(char));
				strcpy(_tinggi, temp_per_token);
			}
			
				else if(_golda == NULL){
				int len = strlen(temp_per_token);
				_golda = (char *) malloc (len * sizeof(char));
				strcpy(_golda, temp_per_token);
			}			
			
			else{
				int len = strlen(temp_per_token);
				_keluhan = (char *) malloc (len * sizeof(char));
				strcpy(_keluhan, temp_per_token);
				
			}
			
		}

		printf("Nama Pasien\t\t : %s \n", _namapasien);
		printf("Alamat \t\t\t : %s\n",_alamat );
		printf("Tempat, tanggal lahir\t : %s\n", _tanggallahir);
		printf("Umur \t\t\t : %s\n", _umur);
		printf("Berat Badan \t\t : %s\n", _berat);
		printf("Tinggi Badan \t\t : %s\n", _tinggi);
		printf("Golongan Darah \t\t : %s\n", _golda);
		printf("Keluhan Pasien \t\t : %s\n", _keluhan);		
		puts("--------------------------------------------");
		
		free(_namapasien);
		free(_alamat);
		free(_tanggallahir);
		free(_umur);
		free(_berat);
		free(_tinggi);
		free(_golda);
		free(_keluhan);
	}
}
