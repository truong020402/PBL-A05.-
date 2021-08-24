

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


int kl[100], gt[100], n, klmax;

FILE *fp;

//hàm menu
void menu()
{

  printf("\n");
  printf("\n    ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
  printf("\n    º                  BAI TOAN CAI TUI                   º");
  printf("\n    ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
  printf("\t\t            \n");
  printf("\n    ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
  printf("\n    º                                                     º ");
  printf("\n    º                 Cach thuc hoat dong                 º");
  printf("\n    º                                                     º ");
  printf("\n    º                                                     º");
  printf("\n    º        Buoc 1:Nhap du lieu                          º");
  printf("\n    º          Chon 1: de nhap tu ban phim                º");
  printf("\n    º          Chon 2: de lay du lieu tu file             º");
  printf("\n    º        Buoc 2: Chon cach lay                        º");
  printf("\n    º          Chon 3: de lay moi vat nhieu lan           º");
  printf("\n    º          Chon 4: de lay moi vat 1 lan               º");
  printf("\n    º                                                     º");
  printf("\n    ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
  	
		printf("\n");

  printf("\t\t\t  #Nhan enter de bat dau!\n");
  getch();
}

//hàm kiểm tra so âm trong file
void kiemtra1(int a)
{
  if (a <= 0)
  {
    printf("Error: Du lieu trong file khong phu hop, nhan enter de quay lai \n");
    getch();
    printf("\033[A\33[2K\r ");
  }
}
//hàm kiểm tra số âm khi nhập
void kiemtra(int *a)
{
  while (*a <= 0)
  {
    printf("\033[A\33[2KT\r ");
    printf("Error: gia tri nhap vao khong hop le moi nhap lai:  ");
    scanf("%d", &*a);
  }
}
//hàm nhập
int Nhap(int *key)
{
  printf("\n Nhap so luong do vat: ");
  scanf("%d", &n);
  kiemtra(&n);

  printf("\n Nhap khoi luong toi da tui mang duoc: ");
  scanf("%d", &klmax);
  kiemtra(&klmax);

  int i;
  for (i = 1; i <= n; i++)
  {
    printf("\n Nhap khoi luong vat %d: ", i);
    scanf("%d", &kl[i]);
    kiemtra(&kl[i]);

    printf("\n Nhap gia tri vat %d: ", i);
    scanf("%d", &gt[i]);
    kiemtra(&gt[i]);
  }
  *key = 0;
}
//hàm báo lỗi thiếu phần tử hoặc có phần tử âm
void error1()
{
  printf("Error du lieu trong file khong chinh xac. Nhan enter de nhap lai \n");
  getch();
  printf("\033[A\33[2K\r ");
  printf("\033[A\33[2K\r ");
}

//hàm nhận giá trị từ file
void Input(int *key)
{
  fp = fopen("bag.txt", "r+");
  if (fp == NULL)
  {
    printf("Error File khong ton tai. Nhan enter de nhap lai \n");
    getch();
    printf("\033[A\33[2K\r ");
    printf("\033[A\33[2K\r ");
  }
  else
  {
    int i;
    n = 0;
    klmax = 0;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &klmax);
    for (i = 1; i <= n; i++)
    {
      kl[i] = 0;
      fscanf(fp, "%d", &kl[i]);
      gt[i] = 0;
      fscanf(fp, "%d", &gt[i]);
    }

    if (n <= 0 || klmax <= 0)
    {
      error1();
    }

    else
    {
      for (i = 1; i <= n; i++)
      {
        if (kl[i] <= 0 || gt[i] <= 0)
        {
          error1();
          return;
        }
      }
      printf("\n");
      printf("#Du lieu doc tu file\n");
      printf("Co tat ca %d do vat\n", n);
      printf("Khoi luong toi da tui mang duoc: %d\n", klmax);

      for (i = 1; i <= n; i++)
      {
        printf("Khoi luong vat %d la: %d\n", i, kl[i]);
        printf("Gia tri vat %d la:    %d\n", i, gt[i]);
      }
      *key = 0;
    }
  }
}

//hàm tinhs tổng dãy
int S(int a[])
{
  int i, s;
  s = 0;
  for (i = 1; i <= n; i++)
    s = s + a[i];
  return s;
}
//hamf khởi tạo giá trị ban đầu
int KTao(int dp[][100])
{
  int i, j;
  for (i = 0; i <= klmax; i++)
    dp[i][0] = 0;
  for (j = 0; j <= n; j++)
    dp[0][j] = 0;
}

// trường hợp một vật được chọn nhiều lần
int TH1(int n, int klmax, int kl[], int gt[])
{ 
  FILE *fp1;
 
  fp1 = fopen("truonghop1.txt", "w+");
  int i, j, z, du, dp[100][100], v1[100];
  v1[1] = 0;
  KTao(dp);
  for (i = 1; i <= klmax; i++)
  {
    printf("\n");
    for (j = 1; j <= n; j++)
    {
      du = i - (i / kl[j]) * kl[j];
      dp[i][j] = i / kl[j] * gt[j] + dp[du][n];

      if (dp[i][j] > dp[i][j - 1])
        v1[i] = j;

      else
        dp[i][j] = dp[i][j - 1];
      printf("%5d", dp[i][j]);
    }
    if (v1[i - 1] == 0)
      v1[1] = v1[i];
  }
  j = v1[1];
  i = klmax;

  printf("\n");
  printf("\n");
  printf("Khoi luong toi da tui mang duoc la %d", dp[klmax][n]);
  fprintf(fp1,"Khoi luong toi da tui mang duoc la %d", dp[klmax][n] );
  printf("\nNhung vat duoc lay la: ");
  fprintf(fp1,"\nNhung vat duoc lay la: ");
  while (i >= kl[j])
  {
    z = v1[i];

    printf(" vat %d lay %d lan,", z, i / kl[z]);
    fprintf(fp1," vat %d lay %d lan,", z,i/kl[z]);
    i = i - i / kl[z] * kl[z];
  }
  printf("\b.");
  fclose(fp1);
}

//   trường hợp 1 vật chỉ được chọn 1 lần
int TH2(int n, int klmax, int kl[], int gt[])
{
  FILE *fp2;
  int dp[100][100], v2[100][100], i, j;
  fp2 = fopen("truonghop2.txt", "w+");
  if (klmax >= S(kl))
  {
    printf("\n Gia tri toi da co the lay la: %d", S(gt));
    fprintf(fp2, "\nGia tri toi da co the lay la: %d", S(gt));
    printf("\n Nhung vat duoc lay la: ");
    for (i = 1; i <= n; i++)
      printf(" vat %d,", i);
    printf("\b.");
    fprintf(fp2, "\nCo the lay tat ca do vat.");
  }
  else
  {
    KTao(dp);
    for (i = 1; i <= klmax; i++)
    {
      printf("\n");
      for (j = 1; j <= n; j++)
      {
        if (i >= kl[j])
        {
          dp[i][j] = gt[j] + dp[i - kl[j]][j - 1];
          if (dp[i][j] > dp[i][j - 1])
            v2[i][j] = j;
          else
          {
            dp[i][j] = dp[i][j - 1];
            v2[i][j] = v2[i][j - 1];
          }
        }
        else
        {
          dp[i][j] = dp[i][j - 1];
          v2[i][j] = v2[i][j - 1];
        }
        printf("%6d", dp[i][j]);
        printf("(%d)", v2[i][j]);
      }
    }
    printf("\nGia tri toi da co the lay la: %d", dp[klmax][n]);

    int z;
    j = v2[1][n];
    i = klmax;

    fprintf(fp2, "\nGia tri toi da co the lay la: %d", dp[klmax][n]);
    printf("\nNhung vat duoc lay la: ");
    fprintf(fp2, "\nNhung vat duoc lay la:");
    while (n > 0)
    {
      if (z != v2[i][n])
      {
        z = v2[i][n];
        if (z != 0)

          {printf(" vat %d,", z);
        fprintf(fp2, " vat %d,", z);}

        i = i - kl[z];
        n--;
      }
      else
        n--;
    }
    printf("\b.");
  }
  fclose(fp2);
}
//ham clrscr
void clrscr()
{
    system("@cls||clear");
}
//ham thoát
void exit0()
{    
    char sl; 
	printf("\nBan co muon thoat khoi chuong trinh (y/n)? ");
	fflush(stdin);
  scanf("%c", &sl);
  if (sl == 'y') 
  { 
   clrscr();
   printf("\n\t\t Cam on ban da su dung chuong trinh!");
   printf("\n\t\t Hen gap lai lan sau!");
   exit(0); 
  }
	 
 } 
// hàm main()
int main()
{
  //C:\Users\HONG TRUONG\Desktop
  printf("\n    ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
  printf("\n    º                                                      º ");
  printf("\n    º              KHOA CONG NGHE THONG TIN                º");
  printf("\n    º            ____________________________              º ");
  printf("\n    º                                                      º ");
  printf("\n    º             DO AN LAP TRINH TINH TOAN                º");
  printf("\n    º              DE TAI BAI TOAN CAI TUI                 º");
  printf("\n    º                                                      º ");
  printf("\n    º          GIANG VIEN HUONG DAN                        º");
  printf("\n    º              TS  Vo Duc Hoang                        º");
  printf("\n    º          Sinh vien thuc hien                         º");
  printf("\n    º              Nguyen Hong Truong -20TCLC-DT2          º");
  printf("\n    º              Duong Minh Duc -20TCLC-DT2              º");
  printf("\n    º                                                      º");
  printf("\n    ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
  getch();
  clrscr();
  
 do
  
  {
    
  menu();
  int ch, key;
  key = 1;
  do
  {
    printf("\nMoi chon cach nhap (1or2): ");
    scanf("%d", &ch);
    if (ch == 1)
      Nhap(&key);
    else if (ch == 2)
      Input(&key);
    else
    {
      printf("Nhap sai nhan enter de nhap lai!\n");
      getch();
      printf("\033[A\33[2K\r ");
      printf("\033[A\33[2K\r ");
    }

  } while (key == 1);
  do
  {
    printf("\n Chon cach lay do vat (3or4): ");
    scanf("%d", &ch);
    if (ch == 3)
    {
      TH1(n, klmax, kl, gt);

      key = 1;
    }
    else if (ch == 4)
    {
      TH2(n, klmax, kl, gt);
      key = 1;
    }
    else
    {
      printf("Nhap sai nhan enter de nhap lai!\n");
      getch();
      printf("\033[A\33[2K\r ");
      printf("\033[A\33[2K\r ");
    }

  } while (key == 0);
  char sl;
  printf("\nBan co muon thu truong hop con lai (y/n): ");
  fflush(stdin);
  scanf("%c", &sl);
  if (sl == 'y')
  {
    if (ch == 3)
      TH2(n, klmax, kl, gt);
    else
      TH1(n, klmax, kl, gt);
  }
  exit0();
  clrscr(); 
} while (1) ;
  fclose(fp);
  getch();
  
}
