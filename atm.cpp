#include <iostream>
#include <string>
#include <conio.h>
// #include <stdlib.h>
using namespace std;

struct Akun
{
	int id;
	string pin;
	string nama;
	double saldo;
	string status;
	int percobaanPin;
};

void main ()
{
	const int percobaanPin = 3;
	const int minSaldo = 100000;
	int tempID;
	string tempPIN;
	bool check = false;
	struct Akun arrayAkun[10];

	struct Akun akun1;
	akun1.id = 1;
	akun1.pin = "000111";
	akun1.nama = "iqbal";
	akun1.saldo = 1000000;
	akun1.status = "active";
	akun1.percobaanPin = percobaanPin;

	struct Akun akun2;
	akun2.id = 2;
	akun2.pin = "010101";
	akun2.nama = "ansor";
	akun2.saldo = 2000000;
	akun2.status = "active";
	akun2.percobaanPin = percobaanPin;

	arrayAkun[0] = akun1;
	arrayAkun[1] = akun2;
	
START :

	tempID = 0;
	system("CLS");
	cout <<"Masukkan ID Anda\n";
	cin >> tempID;
	if(tempID > 0) {
		int index;
		// Check ID
		for(int i=0;i<10;i++) {
			if(arrayAkun[i].id == tempID) {
				check = true;
				break;
			}
		}
		if(check) {
PINCHECK :
			system("CLS");
			tempPIN = "";
			check = false;
			cout << "Masukkan PIN Anda\n";
			cin >> tempPIN;
			// Check PIN
			for(int i=0;i<10;i++) {
				if(arrayAkun[i].id == tempID && arrayAkun[i].pin == tempPIN) {
					if(arrayAkun[i].status == "active") {
						check = true;
						index = i;
						break;
					} else 
					{
						cout << "Kartu ATM anda telah diblokir, mohon hubungi customer service\n\n(Tekan sembarang tombol)";
						getch();
						goto START;
					}
				} else if (arrayAkun[i].id == tempID && arrayAkun[i].pin != tempPIN) {
					// Password salah
					if(arrayAkun[i].percobaanPin <= 1) {
						// Freeze akun
						arrayAkun[i].status = "inactive";
						cout << "Mohon maaf anda telah salah menginput PIN sebanyak " << percobaanPin << " kali, kartu ATM anda telah diblokir\nSilahkan hubungi customer service\n\n(Tekan sembarang tombol)";
						getch();
						goto START;
					} else {
						arrayAkun[i].percobaanPin -= 1;
						cout << "PIN anda salah, masukkan PIN lagi? (y/t)";
						string kembali;
						cin >> kembali;
						system("CLS");
						if (kembali == "y") {
							goto PINCHECK;
						} else {
							goto START;
						}
					}
				}
			}
			if(check) {
MENU :
			system("CLS");
				cout <<"MENU\n(Pecahan 50.000)\n\n";
				cout <<"1) 100.000\n";
				cout <<"2) 300.000\n";
				cout <<"3) Transfer\n";
				cout <<"4) Penarikan Jumlah Lain\n";
				cout <<"5) Cek Saldo\n";
				cout <<"6) Selesai\n";
				cout << "Pilih Salah Satu Menu\n";
				string kembaliKeMenu = "";
				int menu;
				cin >> menu;
				system("CLS");
				switch(menu) {
					case 1 :
						if (arrayAkun[index].saldo < 100000 + minSaldo) {
							cout << "Mohon maaf, saldo anda tidak mencukupi\n\n(Tekan tombol sembarang untuk kembali ke menu)";
							getch();
							system("CLS");
							goto MENU;
						} else {
							arrayAkun[index].saldo -= 100000;
							cout << "Silahkan ambil uang anda\n\n";
							cout << "Kembali ke menu ? (y/t)\n";
							cin >> kembaliKeMenu;
							system("CLS");
							if (kembaliKeMenu == "y") {
								goto MENU;
							} else {
								goto START;
							}
						}

					case 2 :
						if (arrayAkun[index].saldo < 300000 + minSaldo) {
							cout << "Mohon maaf, saldo anda tidak mencukupi\n\n(Tekan tombol sembarang untuk kembali ke menu)";
							getch();
							system("CLS");
							goto MENU;
						} else {
							arrayAkun[index].saldo -= 300000;
							cout << "Silahkan ambil uang anda\n\n";
							cout << "Kembali ke menu ? (y/t)\n";
							cin >> kembaliKeMenu;
							system("CLS");
							if (kembaliKeMenu == "y") {
								goto MENU;
							} else {
								goto START;
							} 
						}

					case 3 :
						int jumlahTransfer;
						cout << "Masukkan ID yang ingin ditransfer\n";
						int tempIDTransfer;
						cin >> tempIDTransfer;
						if (tempIDTransfer == arrayAkun[index].id) {
							// Jika yang diinput adalah miliknya
							cout << "Mohon maaf, anda tidak bisa mentransfer ke rekening anda sendiri\n\n(Tekan tombol sembarang untuk kembali ke menu)";
							getch();
							goto MENU;
						} else {
							check = false;
							int indexTujuan;
							for(int i=0;i<10;i++) {
								if(arrayAkun[i].id == tempIDTransfer) {
									check = true;
									indexTujuan = i;
									break;
								}
							}
							if(check) {
								system("CLS");
								cout << "Masukkan jumlah saldo yang ingin anda transfer\n";
								cin >> jumlahTransfer;
								if(arrayAkun[index].saldo < jumlahTransfer + minSaldo) {
									system("CLS");
									cout << "Mohon maaf saldo anda tidak mencukupi\n\nKembali ke menu ? (y/t)\n";
									cin >> kembaliKeMenu;
									if (kembaliKeMenu == "y") {
										goto MENU;
									} else {
										goto START;
									}
								} else {
									system("CLS");
									cout << "Nomor rekening tujuan : " << arrayAkun[indexTujuan].id << "\n";
									cout << "Nama rekening tujuan : " << arrayAkun[indexTujuan].nama << "\n";
									cout << "Jumlah uang transfer : " << jumlahTransfer << "\n\n";
									cout << "Lanjut ? (y/t)";
									cin >> kembaliKeMenu;
									if(kembaliKeMenu == "t") {
										goto MENU;
									} else {
										system("CLS");
										arrayAkun[index].saldo -= jumlahTransfer;
										arrayAkun[indexTujuan].saldo += jumlahTransfer;
										cout << "Transaksi selesai\n\nKembali ke menu ? (y/t)\n";
										cin >> kembaliKeMenu;
										if (kembaliKeMenu == "y") {
											goto MENU;
										} else {
											goto START;
										}
									}
								}
							}
						}
					
					case 4 :
						system("CLS");
						cout << "Masukkan jumlah yang ingin anda ambil :\n";
						int jumlahPenarikan;
						cin >> jumlahPenarikan;
						if (jumlahPenarikan % 50000 == 0) {
							if (arrayAkun[index].saldo < jumlahPenarikan + minSaldo) {
								system("CLS");
								cout << "Mohon maaf, saldo anda tidak mencukupi\n\n(Tekan tombol sembarang untuk kembali ke menu)";
								getch();
								goto MENU;
							} else {
								system("CLS");
								arrayAkun[index].saldo -= jumlahPenarikan;
								cout << "Silahkan ambil uang anda\n";
								cout << "Kembali ke menu ? (y/t)\n";
								cin >> kembaliKeMenu;
								if (kembaliKeMenu == "y") {
									goto MENU;
								} else {
									goto START;
								} 
							}
						} else {
							system("CLS");
							cout << "Mohon maaf nominal anda tidak termasuk dalam kelipatan 50000\n\n(Tekan tombol sembarang untuk kembali ke menu)";
							getch();
							goto MENU;
						}
						

					case 5 :
						system("CLS");
						cout << "Saldo anda sekarang senilai : \n";
						// Mengeprint angka besar tanpa ruwet
						printf("%.0f", arrayAkun[index].saldo);
						cout << "Kembali ke menu ? (y/t)\n";
						cin >> kembaliKeMenu;
						if (kembaliKeMenu == "y") {
							goto MENU;
						} else {
							goto START;
						}

					case 6 :
						goto START; 
						
				}
			}
		} else {
			cout <<"ID Tidak Dapat Ditemukan!\n\n(Tekan Sembarang Tombol)";
			getch();
			system("CLS");
			goto START;			
		}
	} else {
		cout << "Inputan salah, ID harus berupa angka\n\n(Tekan tombol sembarang untuk kembali ke menu)";
		getch();
		goto START;
	}
}
