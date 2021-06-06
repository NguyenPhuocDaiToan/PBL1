#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

int  LuaChon();
void menu();
void LayDuLieu(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int &n);
void DangNhap(long long &TK,long long &MK,int VT);
int  KiemTra(long long TaiKhoan[],long long MatKhau[],int Khoa[],long long TK,long long MK,int n,int &VT);
int  GiaoDich(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int LC,int VT,int n);
int  HoiGD();
int  RutTien(long long SoTien[],long long VT);
int  NapTien(long long SoTien[],long long VT);
void XemTaiKhoan(long long SoTien[],long long VT);
int  DoiMatKhau(long long MatKhau[],int VT);
void DinhDangThoiGian(int a,string &s);
void CapNhat(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int n);
void LuuGD(long long TaiKhoan[],long long SoTien[],int LC,int VT,int x);

int main()
{
	long long Rut,Nap;
	long long TaiKhoan[100],MatKhau[100],SoTien[100];
	int Khoa[100];
	long long TK,MK;
	int dem=0,SGD=0,n=0,VT=0,LC=0;
	
	
	menu();
	LayDuLieu(TaiKhoan,MatKhau,SoTien,Khoa,n);
	do
	{
		
		DangNhap(TK,MK,VT);
		dem++;
		// xac dinh trang thai
		if(!KiemTra(TaiKhoan,MatKhau,Khoa,TK,MK,n,VT)){
			if(VT==0)
			{
				cout<<"Tai Khoan Khong Ton Tai"<<endl;
			}
			else{
				cout<<"Mat Khau Cua Ban Khong Dung !!!"<<endl;
			}
		}
		if(KiemTra(TaiKhoan,MatKhau,Khoa,TK,MK,n,VT)==0)
		{
			
			if(Khoa[VT]==1){
				break;
			}		
			 
			if(dem==3)
			{
				Khoa[VT]=1;
				break;
				
			}
			cout<<"Ban con so lan nhap la : "<<3-dem<<endl<<endl;
		}
		else break;
	}	while(dem<3);
	if(VT==0)		return 0;
	if(Khoa[VT]==1)
	{                         
			cout<<"Tai Khoan Cua Ban Da Bi Khoa !!!"<<endl;
			cout<<"Vui Long Den Diem Giao Dich Gan Nhat !!!"<<endl;
			CapNhat(TaiKhoan,MatKhau,SoTien,Khoa,n);
			return 0;
	}
	do  
	{	
		SGD++;
		LC=LuaChon();
		if(GiaoDich(TaiKhoan,MatKhau,SoTien,Khoa,LC,VT,n)==0) return 0;
		if(SGD==5)
		{
			cout<<"Ban Da Giao Dich Du So Lan Trong Mot Ngay !!!";
			return 0;
		}
		if(HoiGD()==0)
		{
			cout<<"Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi !!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh !!!"<<endl;
			return 0;
		}
	}	while(SGD<5);
	
	return 0;
}
void menu()
{
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<"'                             WELCOME TO ATM DT                            '"<<endl;
	cout<<"'                       SV:   Nguyen Tran My Duyen                         '"<<endl;
	cout<<"'                             Nguyen Phuoc Dai Toan                        '"<<endl;
	cout<<"'                     GVHD:   Tran Ho Thuy Tien                            '"<<endl;
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<endl;
}
void LayDuLieu(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int &n)
{
	ifstream FileIn;
	FileIn.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.TXT",ios_base::in);

	int i=1;
	while(!FileIn.eof())
	{
		FileIn>>Khoa[i];
		FileIn>>TaiKhoan[i];
		FileIn>>MatKhau[i];
		FileIn>>SoTien[i];
		i++;
	}
	n=i-2;
	FileIn.close();
}
void DangNhap(long long &TK,long long &MK,int vitri)
{	if(vitri==0)
	{
		cout<<"Nhap Tai Khoan Cua Ban : ";
		cin>>TK;
		cout<<"Nhap Mat Khau Cua Ban  : ";
		cin>>MK;
	}
	else
	{
		cout<<"Nhap Mat Khau Cua Ban  : ";
		cin>>MK;
	}
}

int KiemTra(long long TaiKhoan[],long long MatKhau[],int Khoa[],long long TK,long long MK,int n,int &ViTri)
{
	for(int i=1;i<=n;i++)
	{
		if(TK == TaiKhoan[i])
		{
			ViTri=i;
			if(Khoa[i]==1) return 0;
			if( MK == MatKhau[i] )	return 1;
		}
	}
	return 0;
}
int LuaChon()
{
	int luachon;
	do
	{
		cout<<endl;
		cout<<"+----------------------------------MENU------------------------------------+"<<endl;
		cout<<"'                             1. Rut Tien.                                 '"<<endl;
		cout<<"'                             2. Nap Tien.                                 '"<<endl;
		cout<<"'                             3. Xem Tai Khoan.                            '"<<endl;
		cout<<"'                             4. Doi Mat Khau.                             '"<<endl;
		cout<<"'                             5. Thoat.                                    '"<<endl;
		cout<<"+--------------------------------------------------------------------------+"<<endl;
		cout<<"Vui Long Chon Giao Dich		: ";
		cin>>luachon;
	} 
	while (luachon>5);
	return luachon;
}
int GiaoDich(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int LC,int vitri,int n)
{
	switch (LC)
		{
			case 1:
				{
					int Rut=RutTien(SoTien,vitri);
					CapNhat(TaiKhoan,MatKhau,SoTien,Khoa,n);
					LuuGD(TaiKhoan,SoTien,LC,vitri,Rut);
					break;
				}
			case 2:
				{
					int Nap=NapTien(SoTien,vitri);
					CapNhat(TaiKhoan,MatKhau,SoTien,Khoa,n);
					LuuGD(TaiKhoan,SoTien,LC,vitri,Nap);
					break;
				}
			case 3:
				{
					XemTaiKhoan(SoTien,vitri);
					LuuGD(TaiKhoan,SoTien,LC,vitri,0);
					break;
				}
			case 4:
				{
					if(DoiMatKhau(MatKhau,vitri)==0)
					{
						cout<<"Mat Khau Hien Tai Cua Ban Khong Dung !!!"<<endl;
						cout<<"Tai Khoan Cua Ban Da Bi Khoa !!!"<<endl;
						cout<<"Vui Long Den Diem Giao Dich Gan Nhat !!!"<<endl;
						return 0;
					}
					CapNhat(TaiKhoan,MatKhau,SoTien,Khoa,n);
					LuuGD(TaiKhoan,SoTien,LC,vitri,0);
					break;
				}
			case 5:
				{
						return 0;
				}	
		}
		return 1;
}
int HoiGD()
{
	int chon;
	cout<<"Ban Co Muon Giao Dich Tiep Khong ?"<<endl;
	cout<<"1. CO"<<endl;
	cout<<"2. KHONG"<<endl;
	cout<<"Nhap Vao Lua Chon Cua Ban :";
	cin>>chon;
	if(chon==1) return 1;
	return 0;
}
int RutTien(long long SoTien[],long long vitri)
{
	int Rut;
	cout<<"Nhap so tien ban can rut	: ";
	cin>>Rut;
	if(Rut>SoTien[vitri]) cout<<"So tien cua ban khong du de thuc hien giao dich nay !!!"<<endl;
	else 
	{
		cout<<"Giao dich thanh cong !!!"<<endl;
		SoTien[vitri] -= Rut;
	}
	cout<<"Vui Long Nhap EnTer De Tiep Tuc !!!"<<endl;
	getch();
	system("cls");
	return Rut;
}

int NapTien(long long SoTien[],long long vitri)
{
	int Nap;
	cout<<"Nhap so tien ban can nap	: ";
	cin>>Nap;
	SoTien[vitri]+=Nap;
	cout<<"Giao dich thanh cong !!!"<<endl;
	cout<<"Vui Long Nhap EnTer De Tiep Tuc !!!"<<endl;
	getch();
	system("cls");
	return Nap;
}

void XemTaiKhoan(long long SoTien[],long long vitri)
{
	cout<<"So Tien Cua Ban Hien Tai La	: "<<SoTien[vitri]<<endl;
	cout<<"Vui Long Nhap EnTer De Tiep Tuc !!!"<<endl;
	getch();
	system("cls");
}
int DoiMatKhau(long long MatKhau[],int vitri)
{
	int dem=0;
	int MK1;
	int MK2;
	cout<<"Nhap mat khau hien tai cua ban : ";
	cin>>MK1;
	
	while(MK1!=MatKhau[vitri])
	{
		cout<<"Mat khau cua ban hien tai khong dung !!!"<<endl;
		cout<<"Vui long nhap lai !!!"<<endl<<endl;
		cout<<"Nhap mat khau hien tai cua ban : ";
		cin>>MK1;
		dem++;
		if(dem>1) break;
	}
	if(dem>1)	return 0;
	cout<<"Nhap mat khau moi cua ban : ";
	cin>>MK2;
	MatKhau[vitri]=MK2;
	cout<<"Vui Long Nhap EnTer De Tiep Tuc !!!"<<endl;
	getch();
	system("cls");
	return 1;
}
void DinhDangThoiGian(int a,string &s)
{
	s+=(a/10)+'0';
	s+=(a%10)+'0';
}
void CapNhat(long long TaiKhoan[],long long MatKhau[],long long SoTien[],int Khoa[],int n)
{
	int i=1;
	ofstream FileOut;
	FileOut.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.TXT",ios_base::out);
	while(i<=n)
	{
		FileOut<<Khoa[i]<<"	"<<TaiKhoan[i]<<"			"<<MatKhau[i]<<"			"<<SoTien[i]<<endl;
		i++;
	}
	FileOut.close();
}

void LuuGD(long long TaiKhoan[],long long SoTien[],int LC,int vitri,int x)
{
	string phut,gio,ngay,thang;
	time_t now = time(0);
   	tm *ltm = localtime(&now);

  	int NAM   = 1900 + ltm->tm_year ;
   	int THANG =  1 + ltm->tm_mon;
   	int NGAY  = ltm->tm_mday ;
   	int GIO   = ltm->tm_hour;
   	int PHUT  = ltm->tm_min ;
   	
   	DinhDangThoiGian(PHUT,phut);
   	DinhDangThoiGian(GIO,gio);
   	DinhDangThoiGian(NGAY,ngay);
   	DinhDangThoiGian(THANG,thang);
   	
	ofstream FileGD;
	FileGD.open("C:\\Users\\DELL\\OneDrive\\Desktop\\GiaoDich.TXT",ios_base::app);
	if(LC==1)
	{
		FileGD<<"|	"<<TaiKhoan[vitri]<<"		|	"<<gio<<":"<<phut<<" "<<ngay<<"/"<<thang<<"/"<<NAM<<"	|	"<<"-"<<x<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(LC==2)
	{
		FileGD<<"|	"<<TaiKhoan[vitri]<<"		|	"<<gio<<":"<<phut<<" "<<ngay<<"/"<<thang<<"/"<<NAM<<"	|	"<<"+"<<x<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(LC==3)
	{
		FileGD<<"|	"<<TaiKhoan[vitri]<<"		|	"<<gio<<":"<<phut<<" "<<ngay<<"/"<<thang<<"/"<<NAM<<"	|	"<<"Xem Tai Khoan"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
		else if(LC==4)
	{
		FileGD<<"|	"<<TaiKhoan[vitri]<<"		|	"<<gio<<":"<<phut<<" "<<ngay<<"/"<<thang<<"/"<<NAM<<"	|	"<<"DoiMatKhau"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
}

	
