#include <stdio.h>
#include <windows.h> // gotoxy, SetColor
#include <conio.h>	 //rand
#include <string.h>
#include <time.h>
int ran[1000];
int ran2[1000];
int doDaiRan;
int doDaiRan2;
int traiAcQuy;
int traiAcQuyDoc;
int traiAcQuyToiThuong;
int chuongNgaiVat;
int chiSoSucManh;	 // diem cua ran1 va ran co dien
int chiSoSucManhKho; // diem cua ran thach thuc
char ngthang[5];
clock_t t;
int triHoan;
int tocDo = 50;		// binh thuong
int sieuTocDo = 82; // thach thuc
int hoanhToc;
int tungToc;
int hoanhTocDoiThu;
int tungTocDoiThu;

enum state // trang thai
{
	INTRO = 0,
	SANH_CHINH,
	CO_DIEN,
	LUA_CHON,
	THACH_THUC,
	HAI_NGUOI_CHOI,
	THONG_TIN,
	KET_THUC_NHE_NHANG, // mode co dien
	KET_THUC_KHOC_LIET, // mode thach thuc
	KET_THUC_2NGUOI		// mode 2 nguoi
} state;

int layDiemCao()
{
	FILE *fp;

	fp = fopen("./highscore.txt", "r");
	int score;

	if (fscanf(fp, "%d", &score) == -1)
		return 0;

	fclose(fp);
	return score;
}

void luuDiemCao(int x)
{
	FILE *fp;

	fp = fopen("./highscore.txt", "w");
	char highscore[1000];
	sprintf(highscore, "%d", x);
	fprintf(fp, highscore);
	fclose(fp);
}

int layDiemCaoThachThuc()
{
	FILE *fp;

	fp = fopen("./highscorehard.txt", "r");
	int score1;

	if (fscanf(fp, "%d", &score1) == -1)
		return 0;

	fclose(fp);
	return score1;
}

void luuDiemCaoThachThuc(int x)
{
	FILE *fp;

	fp = fopen("./highscorehard.txt", "w");
	char highscore1[1000];
	sprintf(highscore1, "%d", x);
	fprintf(fp, highscore1);
	fclose(fp);
}

int soNgauNhien(int a, int b) // stdlib.h
{
	return a + rand() % (b - a + 1);
}

void gotoxy(short int x, short int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = {x, y};
	SetConsoleCursorPosition(h, c);
}

void setColor(WORD mau)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	mau &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= mau;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void ketThuc()
{
	system("cls");
	setColor(5);
	gotoxy(39, 9);
	printf("....Thua mat roi huhu....");
	gotoxy(41, 11);
	printf("Ban dat duoc %d diem", chiSoSucManh);
	gotoxy(38, 16);
	printf("--An Enter de tro ve Sanh--");
	if (layDiemCao() < chiSoSucManh)
	{
		luuDiemCao(chiSoSucManh);
	}
	gotoxy(44, 12);
	printf("Highscore: %d", layDiemCao());
	getchar();
	state = SANH_CHINH;
}

void ketThucThachThuc()
{
	system("cls");
	setColor(5);
	gotoxy(39, 9);
	printf("....Thua mat roi huhu....");
	gotoxy(41, 11);
	printf("Ban dat duoc %d diem", chiSoSucManhKho);
	gotoxy(38, 16);
	printf("--An Enter de tro ve Sanh--");
	if (layDiemCaoThachThuc() < chiSoSucManhKho)
	{
		luuDiemCaoThachThuc(chiSoSucManhKho);
	}
	gotoxy(44, 12);
	printf("Highscore: %d", layDiemCaoThachThuc());
	getchar();
	state = SANH_CHINH;
}

void ketThuc2Nguoi()
{
	system("cls");
	setColor(5);
	gotoxy(39, 9);
	printf("....Nguoi ben %s thang! ....", ngthang);
	gotoxy(38, 16);
	printf("--An Enter de tro ve Sanh--");
	getchar();
	state = SANH_CHINH;
}

void trangTriKhung()
{
	setColor(2);
	gotoxy(75, 10);
	int i = 75;
	for (i; i < 95; i++)
	{
		printf("O");
	}
	setColor(12);
	gotoxy(74, 10);
	printf("3");
	setColor(2);
	gotoxy(21, 14);
	int j = 21;
	for (j; j < 41; j++)
	{
		printf("O");
	}
	setColor(12);
	gotoxy(41, 14);
	printf("3");
}

void intro()
{
	system("cls");
	int i = 1;
	int x = 45, y = 12;
	while (true)
	{
		system("cls");
		gotoxy(x, y);
		/*CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;  // Width of each character in the font
		cfi.dwFontSize.Y = 24; // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); */
		printf("RAN SAN MOI");
		setColor(i);
		i++;
		if (i > 15)
		{
			i = 1;
		}
		Sleep(200);
		if (x == 57)
		{
			system("cls");
			state = SANH_CHINH;
			break;
		}
		x++;
	}
	
}

void loadCoDien()
{
	system("cls");
	// luat choi che do Co Dien
	gotoxy(51, 14);
	printf("LUAT CHOI");
	gotoxy(17, 15);
	printf("Nhiem vu cua ban la` dieu` khien con ran bang` thanh dieu` huong de an cang` nhieu` hoa qua cang` tot");
	gotoxy(36, 16);
	printf("Danh sach nhung~ loai hoa qua :");
	gotoxy(38, 17);
	printf(" 'O' : +10 diem ");
	gotoxy(38, 18);
	printf(" '!' : -10 diem ");
	gotoxy(38, 19);
	printf(" '0' : +20 diem ");
	gotoxy(25, 20);
	printf("Luu y: ran co the di xuyen tuong` va nen ne nhung~ chuong ngai vat '#' ");
	// khung load
	setColor(15);
	gotoxy(54, 6);
	printf("Loading...\n");
	setColor(9);
	int i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	int j = 0;
	for (j; j < 1; j++)
	{
		printf("\n");
		int i = 0;
		for (i; i < 119; i++)
		{
			printf((i == 0 || i == 118) ? "#" : " ");
		}
	}
	printf("\n");
	i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	gotoxy(1, 8);
	int k = 1;
	int key = 0;
	for (k; k < 118; k++)
	{
		printf("/");
		Sleep(20);
		if (k == 117)
		{
			printf("\n");
			gotoxy(48, 22);
			printf("An Enter de bat dau` choi");
			getchar();
			system("cls");
		}
		state = CO_DIEN;
	}
}

void loadThachThuc()
{
	system("cls");
	// luat choi che do Thach Thuc
	gotoxy(51, 14);
	printf("LUAT CHOI");
	gotoxy(15, 15);
	printf("Nhiem vu cua ban la` dieu` khien con ran bang` thanh dieu` huong de an cang` nhieu` hoa qua cang` tot");
	gotoxy(15, 17);
	printf("Luu y: ran khong the di xuyen tuong` va` toc do se~ rat nhanh, hay su dung trinh` do cua ban :3 ");
	// khung load
	setColor(15);
	gotoxy(54, 6);
	printf("Loading...\n");
	setColor(9);
	int i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	int j = 0;
	for (j; j < 1; j++)
	{
		printf("\n");
		int i = 0;
		for (i; i < 119; i++)
		{
			printf((i == 0 || i == 118) ? "#" : " ");
		}
	}
	printf("\n");
	i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	gotoxy(1, 8);
	int k = 1;
	int key = 0;
	for (k; k < 118; k++)
	{
		printf("/");
		Sleep(20);
		if (k == 117)
		{
			printf("\n");
			gotoxy(48, 22);
			printf("An Enter de bat dau` choi");
			getchar();
			system("cls");
		}
		state = THACH_THUC;
	}
}

void loadHaiNguoiChoi()
{
	system("cls");
	// luat choi che do Co Dien
	gotoxy(53, 14);
	printf("LUAT CHOI");
	gotoxy(15, 15);
	printf("Nhiem vu cua ban la` tieu diet doi thu bang` cach thu thap that nhieu` hoa qua de bao vay doi thu");
	gotoxy(15, 16);
	printf("Dieu khien: nguoi choi ben trai su dung AWSD ; nguoi choi ben phai su dung thanh dieu` huong");
	gotoxy(36, 17);
	printf("Danh sach nhung~ loai hoa qua :");
	gotoxy(38, 18);
	printf(" 'O' : +1 dot ");
	gotoxy(38, 19);
	printf(" '0' : +2 dot");
	gotoxy(19, 20);
	printf("Luu y: ran co the di xuyen tuong` va DAC BIET dau` ran khong duoc cham than ran ke ca ban than ");
	// khung load
	setColor(15);
	gotoxy(54, 6);
	printf("Loading...\n");
	setColor(9);
	int i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	int j = 0;
	for (j; j < 1; j++)
	{
		printf("\n");
		int i = 0;
		for (i; i < 119; i++)
		{
			printf((i == 0 || i == 118) ? "#" : " ");
		}
	}
	printf("\n");
	i = 0;
	for (i; i < 119; i++)
	{
		printf("#");
	}
	gotoxy(1, 8);
	int k = 1;
	int key = 0;
	for (k; k < 118; k++)
	{
		printf("/");
		Sleep(20);
		if (k == 117)
		{
			printf("\n");
			gotoxy(48, 22);
			printf("An Enter de bat dau` choi");
			getchar();
			system("cls");
		}
		state = HAI_NGUOI_CHOI;
	}
}

void trangTriSanhChinh()
{
	// Chu S
	setColor(1);
	gotoxy(40, 5);
	printf("*");
	printf(" *");
	printf("  *");
	gotoxy(40, 6);
	printf("*");
	gotoxy(40, 7);
	printf("*");
	gotoxy(40, 8);
	printf("*");
	printf(" *");
	printf("  *");
	gotoxy(45, 9);
	printf("*");
	gotoxy(45, 10);
	printf("*");
	gotoxy(40, 11);
	printf("  *");
	printf(" *");
	printf("*");
	gotoxy(40, 11);
	printf("*");
	// Chu n
	setColor(2);
	gotoxy(48, 8);
	printf("*");
	gotoxy(48, 9);
	printf("*");
	gotoxy(48, 10);
	printf("*");
	gotoxy(48, 11);
	printf("*");
	gotoxy(49, 9);
	printf("*");
	gotoxy(50, 9);
	printf("*");
	gotoxy(51, 9);
	printf("*");
	gotoxy(52, 9);
	printf("*");
	gotoxy(52, 10);
	printf("*");
	gotoxy(52, 11);
	printf("*");
	// Chu a
	setColor(3);
	gotoxy(55, 9);
	printf("*");
	gotoxy(56, 9);
	printf("*");
	gotoxy(57, 9);
	printf("*");
	gotoxy(58, 9);
	printf("*");
	gotoxy(59, 9);
	printf("*");
	gotoxy(55, 10);
	printf("*");
	gotoxy(55, 11);
	printf("*");
	gotoxy(59, 10);
	printf("*");
	gotoxy(59, 11);
	printf("*");
	gotoxy(56, 11);
	printf("*");
	gotoxy(57, 11);
	printf("*");
	gotoxy(58, 11);
	printf("*");
	gotoxy(60, 11);
	printf("*");
	// Chu k
	setColor(4);
	gotoxy(63, 7);
	printf("*");
	gotoxy(63, 8);
	printf("*");
	gotoxy(63, 9);
	printf("*");
	gotoxy(63, 10);
	printf("*");
	gotoxy(63, 11);
	printf("*");
	gotoxy(67, 8);
	printf("*");
	gotoxy(67, 10);
	printf("*");
	gotoxy(68, 7);
	printf("*");
	gotoxy(68, 11);
	printf("*");
	gotoxy(65, 9);
	printf("*");
	// Chu e
	setColor(5);
	gotoxy(71, 10);
	printf("*");
	gotoxy(72, 10);
	printf("*");
	gotoxy(73, 10);
	printf("*");
	gotoxy(74, 10);
	printf("*");
	gotoxy(75, 10);
	printf("*");
	gotoxy(76, 10);
	printf("*");
	gotoxy(76, 9);
	printf("*");
	gotoxy(75, 8);
	printf("*");
	gotoxy(74, 8);
	printf("*");
	gotoxy(73, 8);
	printf("*");
	gotoxy(73, 9);
	printf("*");
	gotoxy(73, 10);
	printf("*");
	gotoxy(73, 11);
	printf("*");
	gotoxy(74, 11);
	printf("*");
	gotoxy(75, 11);
	printf("*");
	gotoxy(76, 11);
	printf("*");
}

void sanhChinh()
{
	// mo nhac thong qua duong` dan~ toi file chua nhac
	//system("start /min powershell -c (New-Object Media.SoundPlayer 'C:\\Users\\tminh\\OneDrive\\Documents\\snakee\\retrofunk.wav').PlaySync();");//
	system("cls");
	trangTriSanhChinh();
	gotoxy(53, 16);
	setColor(15);
	printf(" CHON CHE DO");
	gotoxy(54, 17);
	printf(" THONG TIN");
	int luaChon = 1;
	int luaChonCu = 1;
	int key;
	setColor(14);
	gotoxy(52, 16);
	printf("%c", 16);
	while (state == SANH_CHINH)
	{
		if (kbhit())
		{
			key = getch();
			if (key == 80)
			{
				luaChon++;
				if (luaChon == 3)
					luaChon = 1;
			}
			if (key == 72)
			{
				luaChon--;
				if (luaChon == 0)
					luaChon = 2;
			}
			switch (luaChon)
			{
			case 1:
				if (luaChonCu = luaChon)
				{
					gotoxy(52, 16);
					printf(" ");
					gotoxy(52, 17);
					printf(" ");
					luaChonCu = 1;
					gotoxy(52, 16);
					setColor(14);
					printf("%c", 16);
				}
				break;
			case 2:
				if (luaChonCu != luaChon)
				{
					gotoxy(52, 16);
					printf(" ");
					gotoxy(52, 17);
					setColor(14);
					printf("%c", 16);
					luaChonCu = 2;
				}
				break;
			}
			if (key == 13)
			{
				switch (luaChon)
				{
				case 1:
					state = LUA_CHON;
					break;
				case 2:
					state = THONG_TIN;
					break;
				}
			}
		}
	}
}

void thongTin()
{
	system("cls");
	setColor(15);
	gotoxy(32, 9);
	printf("-Day la` san pham bai` tap lon cua Nhom 8 ~ eight yo");
	gotoxy(10, 12);
	printf("-Thanh tuu :\n");
	gotoxy(15, 14);
	printf("* Ki luc che do Co Dien la : %d", layDiemCao());
	gotoxy(15, 15);
	printf("* Ki luc che do Thu Thach la: %d", layDiemCaoThachThuc());
	gotoxy(44, 18);
	printf("--An Enter de tro ve Sanh--");
	gotoxy(27, 15);
	setColor(15);
	getchar();
	state = SANH_CHINH;
}

void luaChon()
{
	system("cls");
	trangTriKhung();
	gotoxy(52, 10);
	setColor(2);
	printf("CO DIEN");
	gotoxy(51, 11);
	setColor(4);
	printf("THU THACH");
	gotoxy(49, 12);
	setColor(9);
	printf("HAI NGUOI CHOI");
	int luaChon1 = 1;
	int luaChonCu1 = 1;
	int key;
	setColor(14);
	gotoxy(51, 10);
	printf("%c", 16);
	while (state == LUA_CHON)
	{
		if (kbhit())
		{
			key = getch();
			if (key == 80) // xuong
			{
				luaChon1++;
				if (luaChon1 == 4)
					luaChon1 = 1;
			}
			if (key == 72) // len
			{
				luaChon1--;
				if (luaChon1 == 0)
					luaChon1 = 3;
			}
			// tro chuot toi lua chon
			switch (luaChon1)
			{
			case 1:
				if (luaChonCu1 != luaChon1)
				{
					gotoxy(51, 10);
					printf(" ");
					gotoxy(50, 11);
					printf(" ");
					luaChonCu1 = 1;
					gotoxy(48, 12);
					printf(" ");
					gotoxy(51, 10);
					setColor(14);
					printf("%c", 16);
				}
				break;
			case 2:
				if (luaChonCu1 != luaChon1)
				{
					gotoxy(51, 10);
					printf(" ");
					gotoxy(48, 12);
					printf(" ");
					gotoxy(50, 11);
					setColor(14);
					printf("%c", 16);
					luaChonCu1 = 2;
				}
				break;
			case 3:
				if (luaChonCu1 != luaChon1)
				{
					gotoxy(50, 11);
					printf(" ");
					gotoxy(51, 10);
					printf(" ");
					gotoxy(48, 12);
					setColor(14);
					printf("%c", 16);

					luaChonCu1 = 3;
				}
				break;
				// di toi lua chon
			}
			if (key == 13)
			{
				switch (luaChon1)
				{
				case 1:
					system("cls");
					loadCoDien();
					state = CO_DIEN;
					break;
				case 2:
					system("cls");
					loadThachThuc();
					state = THACH_THUC;
					break;
				case 3:
					system("cls");
					loadHaiNguoiChoi();
					state = HAI_NGUOI_CHOI;
					break;
				}
			}
		}
	}
}

void veKhung()
{
	int i = 0;
	int j = 0;
	setColor(3);
	for (i; i < 79; i++)
	{
		printf("=");
	}
	printf("\n");
	for (i = 0; i < 24; i++)
	{
		for (j; j < 79; j++)
		{
			if (j == 0)
				printf("|");
			else if (j == 78)
				printf("|\n");
			else
				printf(" ");
		}
		j = 0;
	}
	for (i = 0; i < 79; i++)
	{
		printf("=");
	}
}

void veKhungTo()
{
	int i = 0;
	int j = 0;
	setColor(3);
	for (i; i < 100; i++)
	{
		printf("=");
	}
	printf("\n");
	for (i = 0; i < 33; i++)
	{
		for (j; j < 100; j++)
		{
			if (j == 0)
				printf("|");
			else if (j == 99)
				printf("|\n");
			else
				printf(" ");
		}
		j = 0;
	}
	for (i = 0; i < 100; i++)
	{
		printf("=");
	}
}

void khoiNguyen()
{
	system("cls");
	triHoan = 120 - tocDo;
	t = 0;
	hoanhToc = 1;
	tungToc = 0;
	chiSoSucManh = 0;
	doDaiRan = 10;
	ran[0] = 11510; // con ran
	ran[1] = 11410;
	ran[2] = 11310;
	ran[3] = 11210;
	ran[4] = 11110;
	ran[5] = 11010;
	ran[6] = 10910;
	ran[7] = 10810;
	ran[8] = 10710;
	ran[9] = 10610;
	traiAcQuy = 15010;
	traiAcQuyDoc = 15015;
	chuongNgaiVat = 11012;
	traiAcQuyToiThuong = 15016;
}

void khoiNguyenChetChoc() // thach thuc
{
	system("cls");
	triHoan = 120 - sieuTocDo;
	t = 0;
	hoanhToc = 1;
	tungToc = 0;
	chiSoSucManhKho = 0;
	doDaiRan = 10;
	ran[0] = 11510;
	ran[1] = 11410;
	ran[2] = 11310;
	ran[3] = 11210;
	ran[4] = 11110;
	ran[5] = 11010;
	ran[6] = 10910;
	ran[7] = 10810;
	ran[8] = 10710;
	ran[9] = 10610;
	traiAcQuy = 15010;
}

void khoiNguyenDoiThu()
{
	system("cls");
	hoanhTocDoiThu = 1;
	tungTocDoiThu = 0;
	chiSoSucManhKho = 0;
	doDaiRan2 = 10;
	ran2[0] = 11517;
	ran2[1] = 11417;
	ran2[2] = 11317;
	ran2[3] = 11217;
	ran2[4] = 11117;
	ran2[5] = 11017;
	ran2[6] = 10917;
	ran2[7] = 10817;
	ran2[8] = 10717;
	ran2[9] = 10617;
}

void truyTimTraiAcQuy() // truy tim = tao cho~
{
	int trigg = 1;
	while (trigg)
	{
		trigg = 0;
		traiAcQuy = 10000 + soNgauNhien(1, 77) * 100 + soNgauNhien(1, 23);
		int i = 0;
		for (i; i < doDaiRan; i++)
		{
			if (ran[i] == traiAcQuy)
			{
				trigg = 1;
			}
		}
	}
}

void truyTimTraiAcQuy2() // che do 2 nguoi choi
{
	int trigg = 1;
	while (trigg)
	{
		trigg = 0;
		traiAcQuy = 10000 + soNgauNhien(1, 99) * 100 + soNgauNhien(1, 32);
		int i = 0;
		for (i; i < doDaiRan; i++)
		{
			if (ran[i] == traiAcQuy)
			{
				trigg = 1;
			}
		}
	}
}

void truyTimTraiDoc() //-1
{
	int trigg = 1;
	while (trigg)
	{
		trigg = 0;
		traiAcQuyDoc = 10000 + soNgauNhien(1, 77) * 100 + soNgauNhien(1, 23);
		int i = 0;
		for (i; i < doDaiRan; i++)
		{
			if (ran[i] == traiAcQuyDoc)
			{
				trigg = 1;
			}
		}
	}
}

void truyTimTraiToiThuong() //+2
{
	int trigg = 1;
	while (trigg)
	{
		trigg = 0;
		traiAcQuyToiThuong = 10000 + soNgauNhien(1, 77) * 100 + soNgauNhien(1, 23);
		int i = 0;
		for (i; i < doDaiRan; i++)
		{
			if (ran[i] == traiAcQuyToiThuong)
			{
				trigg = 1;
			}
		}
	}
}

void taoChuongNgaiVat()
{
	int trigg = 1;
	while (trigg)
	{
		trigg = 0;
		chuongNgaiVat = 10000 + soNgauNhien(1, 77) * 100 + soNgauNhien(1, 23);
	}
}

int getX(int a)
{
	return (a - 10000) / 100;
}

int getY(int a)
{
	return a % 100;
}

void inChiSoSucManh() // hien thi diem
{

	gotoxy(111, 4);
	printf("d");
	gotoxy(111, 5);
	printf("i");
	gotoxy(111, 6);
	printf("e");
	gotoxy(111, 7);
	printf("m");

	gotoxy(111, 9);
	printf("0");
	gotoxy(111, 10);
	printf("0");
	gotoxy(111, 11);
	printf("0");
	gotoxy(111, 12);
	printf("0");
	gotoxy(111, 13);
	printf("0");
	// cham ngon song
	gotoxy(90, 16);
	printf("CO LAM` THI MOI CO AN - CHAM NGON LOAI` RAN");
}

void inChiSoSucManhThachThuc() // hien thi diem thach thuc
{
	gotoxy(111, 4);
	printf("d");
	gotoxy(111, 5);
	printf("i");
	gotoxy(111, 6);
	printf("e");
	gotoxy(111, 7);
	printf("m");

	gotoxy(111, 9);
	printf("0");
	gotoxy(111, 10);
	printf("0");
	gotoxy(111, 11);
	printf("0");
	gotoxy(111, 12);
	printf("0");
	gotoxy(111, 13);
	printf("0");
	// cham ngon song
	gotoxy(90, 16);
	printf("CO LAM` THI MOI CO AN - CHAM NGON LOAI` RAN");
}

void capNhatChiSo() // score cua nguoi choi co dien va ran1
{
	setColor(14);
	gotoxy(111, 9);
	printf("%d", (chiSoSucManh % 100000) / 10000);
	gotoxy(111, 10);
	printf("%d", (chiSoSucManh % 10000) / 1000);
	gotoxy(111, 11);
	printf("%d", (chiSoSucManh % 1000) / 100);
	gotoxy(111, 12);
	printf("%d", (chiSoSucManh % 100) / 10);
	gotoxy(111, 13);
	printf("%d", chiSoSucManh % 10);
}

void capNhatChiSoThachThuc() // score cua ran thach thuc
{
	setColor(14);
	gotoxy(111, 9);
	printf("%d", (chiSoSucManhKho % 100000) / 10000);
	gotoxy(111, 10);
	printf("%d", (chiSoSucManhKho % 10000) / 1000);
	gotoxy(111, 11);
	printf("%d", (chiSoSucManhKho % 1000) / 100);
	gotoxy(111, 12);
	printf("%d", (chiSoSucManhKho % 100) / 10);
	gotoxy(111, 13);
	printf("%d", chiSoSucManhKho % 10);
}

void coDien()
{
	int key;
	int i;
	khoiNguyen();
	taoChuongNgaiVat();
	truyTimTraiAcQuy();
	truyTimTraiDoc();
	truyTimTraiToiThuong();
	veKhung();
	inChiSoSucManh();
	setColor(13);
	gotoxy(getX(traiAcQuy), getY(traiAcQuy));
	printf("O");
	setColor(9);
	gotoxy(getX(traiAcQuyDoc), getY(traiAcQuyDoc));
	printf("!");
	setColor(5);
	gotoxy(getX(traiAcQuyToiThuong), getY(traiAcQuyToiThuong)); //
	printf("0");
	setColor(14);
	gotoxy(getX(chuongNgaiVat), getY(chuongNgaiVat));
	printf("#");
	setColor(12);
	gotoxy(getX(ran[0]), getY(ran[0]));
	printf("%c", 4);
	i = 1;
	setColor(2);
	for (i; i < doDaiRan; i++)
	{
		gotoxy(getX(ran[i]), getY(ran[i]));
		printf("O");
	}
	while (state == CO_DIEN)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			// nut len
			case 72:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = -1;
				}
				break;
				// nut xuong
			case 80:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = 1;
				}
				break;
				// nut trai
			case 75:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = -1;
				}
				break;
				// nut phai
			case 77:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = 1;
				}
				break;
			}
		}

		if ((clock() - t) >= triHoan)
		{
			if (ran[doDaiRan - 1] != 0)
			{
				gotoxy(getX(ran[doDaiRan - 1]), getY(ran[doDaiRan - 1]));
				printf(" ");
			}
			i = doDaiRan - 1;
			for (i; i > 0; i--)
			{
				ran[i] = ran[i - 1];
			}
			setColor(2);
			gotoxy(getX(ran[0]), getY(ran[0]));
			printf("o");
			ran[0] += hoanhToc * 100;
			ran[0] += tungToc;
			if (ran[0] == traiAcQuy)
			{

				Beep(5000, 109);
				doDaiRan += 1;
				chiSoSucManh += 10;
				capNhatChiSo();
				truyTimTraiAcQuy();
				setColor(13);
				gotoxy(getX(traiAcQuy), getY(traiAcQuy));
				printf("O");
			}
			if (ran[0] == traiAcQuyDoc)
			{
				Beep(15000, 109);
				doDaiRan -= 1;
				chiSoSucManh -= 10;
				capNhatChiSo();
				truyTimTraiDoc();
				setColor(9);
				gotoxy(getX(traiAcQuyDoc), getY(traiAcQuyDoc));
				printf("!");
			}
			if (ran[0] == traiAcQuyToiThuong)
			{
				Beep(4000, 109);
				doDaiRan += 2;
				chiSoSucManh += 20;
				capNhatChiSo();
				truyTimTraiToiThuong();
				setColor(5);
				gotoxy(getX(traiAcQuyToiThuong), getY(traiAcQuyToiThuong));
				printf("0");
			}
			// xuyen tuong
			if ((hoanhToc > 0) && (getX(ran[0]) == 78))
			{
				ran[0] -= 7700;
			}
			if ((hoanhToc < 0) && (getX(ran[0]) == 0))
			{
				ran[0] += 7700;
			}
			if ((tungToc > 0) && (getY(ran[0]) == 25))
			{
				ran[0] -= 24;
			}
			if ((tungToc < 0) && (getY(ran[0]) == 0))
			{
				ran[0] += 24;
			}
			setColor(12);
			gotoxy(getX(ran[0]), getY(ran[0]));
			printf("3");
			if (ran[0] == chuongNgaiVat)
			{
				system("cls");
				state = KET_THUC_NHE_NHANG;
			}
			i = 1;
			for (i; i < doDaiRan; i++)
			{
				if (ran[i] == ran[0])
				{
					system("cls");
					state = KET_THUC_NHE_NHANG;
				}
			}
			t = clock();
		}
	}
}

void thachThuc()
{
	int key;
	int i;
	khoiNguyenChetChoc();
	veKhung();
	inChiSoSucManhThachThuc();
	setColor(13);
	gotoxy(getX(traiAcQuy), getY(traiAcQuy));
	printf("O");
	setColor(12);
	gotoxy(getX(ran[0]), getY(ran[0]));
	printf("%c", 4);
	i = 1;
	setColor(2);
	for (i; i < doDaiRan; i++)
	{
		gotoxy(getX(ran[i]), getY(ran[i]));
		printf("O");
	}
	while (state == THACH_THUC)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			// nut len
			case 72:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = -1;
				}
				break;
				// nut xuong
			case 80:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = 1;
				}
				break;
				// nut trai
			case 75:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = -1;
				}
				break;
				// nut phai
			case 77:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = 1;
				}
				break;
			}
		}

		if ((clock() - t) >= triHoan)
		{
			if (ran[doDaiRan - 1] != 0)
			{
				gotoxy(getX(ran[doDaiRan - 1]), getY(ran[doDaiRan - 1]));
				printf(" ");
			}
			i = doDaiRan - 1;
			for (i; i > 0; i--)
			{
				ran[i] = ran[i - 1];
			}
			setColor(2);
			gotoxy(getX(ran[0]), getY(ran[0]));
			printf("o");
			ran[0] += hoanhToc * 100;
			ran[0] += tungToc;
			if (ran[0] == traiAcQuy)
			{
				doDaiRan += 1;
				chiSoSucManhKho += 10;
				capNhatChiSoThachThuc();
				truyTimTraiAcQuy();
				setColor(13);
				gotoxy(getX(traiAcQuy), getY(traiAcQuy));
				printf("O");
			}
			// dung tuong chet
			if ((hoanhToc > 0) && (getX(ran[0]) == 78))
			{
				system("cls");
				state = KET_THUC_KHOC_LIET;
			}
			if ((hoanhToc < 0) && (getX(ran[0]) == 0))
			{
				system("cls");
				state = KET_THUC_KHOC_LIET;
			}
			if ((tungToc > 0) && (getY(ran[0]) == 25))
			{
				system("cls");
				state = KET_THUC_KHOC_LIET;
			}
			if ((tungToc < 0) && (getY(ran[0]) == 0))
			{
				system("cls");
				state = KET_THUC_KHOC_LIET;
			}
			setColor(12);
			gotoxy(getX(ran[0]), getY(ran[0]));
			printf("#");
			i = 1;
			for (i; i < doDaiRan; i++)
			{
				if (ran[i] == ran[0])
				{
					system("cls");
					state = KET_THUC_KHOC_LIET;
				}
			}
			t = clock();
		}
	}
}

void haiNguoiChoi()
{
	// nguoi choi thanh dieu` huong
	int key;
	int i;
	khoiNguyen();
	khoiNguyenDoiThu();
	veKhungTo();
	setColor(13);
	gotoxy(getX(traiAcQuy), getY(traiAcQuy));
	printf("O");
	setColor(5);
	gotoxy(getX(traiAcQuyToiThuong), getY(traiAcQuyToiThuong)); //
	printf("0");
	setColor(12);
	gotoxy(getX(ran[0]), getY(ran[0]));
	printf("%c", 2);
	setColor(8);
	gotoxy(getX(ran2[0]), getY(ran2[0]));
	printf("%c", 2);
	i = 1;
	setColor(2);
	for (i; i < doDaiRan; i++)
	{
		gotoxy(getX(ran[i]), getY(ran[i]));
		printf("o");
	}
	setColor(6);
	for (i = 1; i < doDaiRan2; i++)
	{
		gotoxy(getX(ran2[i]), getY(ran2[i]));
		printf("o");
	}
	while (state == HAI_NGUOI_CHOI)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			// nut len
			case 72:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = -1;
				}
				break;
				// nut xuong
			case 80:
				if (tungToc == 0)
				{
					hoanhToc = 0;
					tungToc = 1;
				}
				break;
				// nut trai
			case 75:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = -1;
				}
				break;
				// nut phai
			case 77:
				if (hoanhToc == 0)
				{
					tungToc = 0;
					hoanhToc = 1;
				}
				break;

				// w
			case 119:
				if (tungTocDoiThu == 0)
				{
					hoanhTocDoiThu = 0;
					tungTocDoiThu = -1;
				}
				break;
				// s
			case 115:
				if (tungTocDoiThu == 0)
				{
					hoanhTocDoiThu = 0;
					tungTocDoiThu = 1;
				}
				break;
				// a
			case 97:
				if (hoanhTocDoiThu == 0)
				{
					tungTocDoiThu = 0;
					hoanhTocDoiThu = -1;
				}
				break;
				// d
			case 100:
				if (hoanhTocDoiThu == 0)
				{
					tungTocDoiThu = 0;
					hoanhTocDoiThu = 1;
				}
				break;
			}
		}

		if ((clock() - t) >= triHoan)
		{

			if (doDaiRan > 0)
			{
				if (ran[doDaiRan - 1] != 0)
				{
					gotoxy(getX(ran[doDaiRan - 1]), getY(ran[doDaiRan - 1]));
					printf(" ");
				}
				i = doDaiRan - 1;
				for (i; i > 0; i--)
				{
					ran[i] = ran[i - 1];
				}
				setColor(2);
				gotoxy(getX(ran[0]), getY(ran[0]));
				printf("o");
				ran[0] += hoanhToc * 100;
				ran[0] += tungToc;
				if (ran[0] == traiAcQuy)
				{

					Beep(5000, 109);
					doDaiRan += 1;
					truyTimTraiAcQuy2();
					setColor(13);
					gotoxy(getX(traiAcQuy), getY(traiAcQuy));
					printf("O");
				}
				if (ran[0] == traiAcQuyToiThuong)
				{
					Beep(4000, 109);
					doDaiRan += 2;
					truyTimTraiToiThuong();
					setColor(5);
					gotoxy(getX(traiAcQuyToiThuong), getY(traiAcQuyToiThuong));
					printf("0");
				}
				// xuyen tuong
				if ((hoanhToc > 0) && (getX(ran[0]) == 99))
				{
					ran[0] -= 9800;
				}
				if ((hoanhToc < 0) && (getX(ran[0]) == 0))
				{
					ran[0] += 9800;
				}
				if ((tungToc > 0) && (getY(ran[0]) == 34))
				{
					ran[0] -= 32;
				}
				if ((tungToc < 0) && (getY(ran[0]) == 0))
				{
					ran[0] += 32;
				}
				setColor(12);
				gotoxy(getX(ran[0]), getY(ran[0]));
				printf("3");
				for (i = 1; i < doDaiRan; i++)
				{
					if (ran[i] == ran[0]) //ran1 thua
					{

						system("cls");
						state = KET_THUC_2NGUOI;
						ngthang[0] = 't';
						ngthang[1] = 'r';
						ngthang[2] = 'a';
						ngthang[3] = 'i';
					}
					if (doDaiRan2 != 0 && ran[i] == ran2[0]) //ran2 thua 
					{
						system("cls");
						state = KET_THUC_2NGUOI;
						ngthang[0] = 'p';
						ngthang[1] = 'h';
						ngthang[2] = 'a';
						ngthang[3] = 'i';
					}
				}
			}
			if (ran2[0] == ran[0]) // hoa`
			{
				system("cls");
				gotoxy(50, 15);
				setColor(5);
				printf("HOA !");
				gotoxy(38, 16);
				printf("--An Enter de tro ve Sanh--");
				getchar();
				system("cls");
				state = SANH_CHINH;
				break;
			}
			////////////////////////////////////////////////////////////
			// nguoi choi 1 awsd
			if (doDaiRan2 > 0)
			{
				if (ran2[doDaiRan2 - 1] != 0)
				{
					gotoxy(getX(ran2[doDaiRan2 - 1]), getY(ran2[doDaiRan2 - 1]));
					printf(" ");
				}
				i = doDaiRan2 - 1;
				for (i; i > 0; i--)
				{
					ran2[i] = ran2[i - 1];
				}
				setColor(6);
				gotoxy(getX(ran2[0]), getY(ran2[0]));
				printf("o");
				ran2[0] += hoanhTocDoiThu * 100;
				ran2[0] += tungTocDoiThu;
				if (ran2[0] == traiAcQuy)
				{

					Beep(5000, 109);
					doDaiRan2 += 1;
					truyTimTraiAcQuy2();
					setColor(13);
					gotoxy(getX(traiAcQuy), getY(traiAcQuy));
					printf("O");
				}
				if (ran2[0] == traiAcQuyToiThuong)
				{
					Beep(4000, 109);
					doDaiRan2 += 2;
					chiSoSucManh += 20;
					truyTimTraiToiThuong();
					setColor(5);
					gotoxy(getX(traiAcQuyToiThuong), getY(traiAcQuyToiThuong));
					printf("0");
				}
				// xuyen tuong
				if ((hoanhTocDoiThu > 0) && (getX(ran2[0]) == 99))
				{
					ran2[0] -= 9800;
				}
				if ((hoanhTocDoiThu < 0) && (getX(ran2[0]) == 0))
				{
					ran2[0] += 9800;
				}
				if ((tungTocDoiThu > 0) && (getY(ran2[0]) == 33))
				{
					ran2[0] -= 32;
				}
				if ((tungTocDoiThu < 0) && (getY(ran2[0]) == 0))
				{
					ran2[0] += 32;
				}
				setColor(12);
				gotoxy(getX(ran2[0]), getY(ran2[0]));
				printf("3");
				for (i = 1; i < doDaiRan2; i++)
				{
					if (ran2[i] == ran2[0]) //ran2 thua
					{
						system("cls");
						state = KET_THUC_2NGUOI;
						ngthang[0] = 'p';
						ngthang[1] = 'h';
						ngthang[2] = 'a';
						ngthang[3] = 'i';
					}
					if (doDaiRan != 0 && ran2[i] == ran[0]) //ran1 thua
					{
						system("cls");
						state = KET_THUC_2NGUOI;
						ngthang[0] = 't';
						ngthang[1] = 'r';
						ngthang[2] = 'a';
						ngthang[3] = 'i';
					}
				}
			}
			t = clock();
		}
	}
}

int main()
{
	printf("\e[?25l"); // lam con tro khong nhap nhay nua~
	while (1)
	{
		switch (state)
		{
		case INTRO:
			intro();
			break;
		case SANH_CHINH:
			sanhChinh();
			break;
		case CO_DIEN:
			coDien();
			break;
		case THACH_THUC:
			thachThuc();
			break;
		case HAI_NGUOI_CHOI:
			haiNguoiChoi();
			break;
		case KET_THUC_NHE_NHANG:
			ketThuc();
			break;
		case KET_THUC_KHOC_LIET:
			ketThucThachThuc();
			break;
		case KET_THUC_2NGUOI:
			ketThuc2Nguoi();
			break;
		case THONG_TIN:
			thongTin();
			break;
		case LUA_CHON:
			luaChon();
			break;
		}
	}
}