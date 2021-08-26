// De tai 701 : Xay dung ung dung thuc hien giao dich ATM
// Giang vien huong dan : Tran Ho Thuy Tien
// Sinh vien thuc hien  : Nguyen Tran My Duyen
//					    : Nguyen Phuoc Dai Toan

#include<iostream>
#include<fstream>     // doc - ghi file text ThongTin.txt
#include<conio.h>	  // su dung ham getch() de chuyen mat khau ve *
#include<iomanip>	  // su dung ham setw() de canh do rong luu vao file GiaoDich.txt
#include<math.h>	  // su dung ham pow(), dung trong ham getmoney chuyen tien tu string ve int
#include<ctime>	 	  // su dung de lay thoi gian luu lich su giao dich
#include<string>	  // su dung chuoi de dinh dang tien va mat khau
#include<sstream>	  // su dung ostringstream, de chuyen tien dang int ve string de dinh dang tien
#include<windows.h>	  // dinh dang mau chu

using namespace std;

const string account_staff     = "123456789";
const string password_staff = "999999";
// tai khoan cua nhan vien ngan hang de bat dau va ket thuc chuong trinh

// Thong tin account nguoi dung
struct UserAccount
{
    string account_number;
    string password_number;
    string money;
    int lock;
    int number_of_transactions;
};

void menu();// In ten do an, giang vien va sinh vien thuc hien
bool importFile(UserAccount useraccount[], int &size);// Lay thong tin trong file

// Dang nhap giao dich
int  login(string &account, string &password, int index);
void login_account(string &account);
void login_password(string &password);

// Kiem tra tai khoan nhan vien IT va chi so trong mang nguoi giao dich
bool checkUserAccount(UserAccount useraccount[], string account, string password, int &index, int size);

int  getUserOption(); // Nhap lua chon giao dich
int  transaction(UserAccount useraccount[], int index,int size, int option); // Ham giao dich
int  otherTransaction(); // Hoi co muon giao dich tiep khong?

// Cac chuc nang trong giao dich
void formatMoney(UserAccount useraccount[], int index, long long money);
void withdrawCash(UserAccount useraccount[], int index,int size, string &withdraw);
void makeDeposit(UserAccount useraccount[], int index,int size, string &deposit); 
void viewBalance(string money); 

long long getMoney(string money); // Chuyen tien kieu string ve long long de giao dich

// Lay thoi gian de luu thoi gian giao dich
void getTime(int &year, string &month, string &day, string &hour, string &minite);
void formatTime(int time, string &s);
void updateFile(UserAccount useraccount[], int size); // Cap nhat file chua thong tin nguoi dung
void storeData(UserAccount useraccount[], int option, int index, string money_transactions); // Luu lai thong tin giao dich

// Ham dinh dang mau sac
void set_color ( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}

# define aqua   3
# define yellow 6
# define green  10
# define blue   11
# define white  15

int main(){
	
	UserAccount useraccount[100];
	
	int number_login[100];
	string account;
	string password;
	int size, index, option, check, number_of_logins;
	number_of_logins = 0;
	index = 0;
	
	menu();	
	
	while(!login(account,password,index))
	{
		set_color(blue);
		cout<<"\n\n\t\tDu lieu cap nhat khong thanh cong !!!";
		cout<<"\n\t\tNhan vien IT cua ngan hang can khoi dong chuong trinh !!!\n";
		set_color(green);
		cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
	}
	
	if(!importFile(useraccount, size))	return 0;
	set_color(blue);
	cout<<"\n\n\t\tCap nhat du lieu thanh cong !!!\n";
	set_color(green);
	cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
	
	for(int i=1;i<=size;i++)
	{
		number_login[i]=0;
	}
	
	while(!login(account, password, index))
	{	
		// Kiem tra dang nhap
		check = checkUserAccount(useraccount, account, password, index, size);
		if(index==0)
		{
			set_color(blue);
			cout<<"\n\n\t\tTai Khoan Khong Ton Tai !!!\n";
			set_color(green);
			cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
		}	
		else if(useraccount[index].lock)
		{
			set_color(blue);
			cout<<"\n\n\t\tTai Khoan Cua Ban Da Bi Khoa !!!\n";
			set_color(green);
			cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
			index = 0;
		}
		else if(!check)
		{
			number_login[index]++;
			if(number_login[index]==3)
			{
				useraccount[index].lock = 1;
				updateFile(useraccount, size);
				set_color(blue);
				cout<<"\n\n\t\tTai Khoan Cua Ban Da Bi Khoa !!!\n";
				set_color(green);
				cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
			}
			else
			{
				set_color(blue);
				cout<<"\n\n\t\tMat khau cua ban khong dung !!!\n";
				set_color(green);
				cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
			}
			index = 0;
		}
		
		// Kiem tra giao dich
		
		while( useraccount[index].number_of_transactions < 5 && index != 0 )
		{
				option=getUserOption();
				if (transaction(useraccount, index,size, option)){
					useraccount[index].number_of_transactions++;
				}
				else break;
				if(!otherTransaction())		break;
		}
			
		if( useraccount[index].number_of_transactions == 5 && index != 0 )
		{
			set_color(blue);
			cout<<"\n\n\t\tQuy Khach Da Dat So Giao Dich Toi Da Trong Mot Ngay !!!";
			cout<<"\n\t\tCam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
			cout<<"\n\t\tChuc Quy Khach Co Mot Ngay Tot Lanh!!!\n";
			set_color(green);
			cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
		}
		updateFile(useraccount, size);
		index = 0;
	}
	
	for(int i=1; i<=size; i++)
	{
		useraccount[i].number_of_transactions = 0;
	}
	updateFile(useraccount, size);

	return 0;
}
void menu(){
	set_color(green);
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '";
	set_color(aqua);
	cout<<"                                             DE TAI DO AN PBL1                                            ";
	set_color(green);
	cout<<"'"<<endl<<" '";
	set_color(aqua);
	cout<<"                            DE TAI 701: XAY DUNG UNG DUNG THUC HIEN GIAO DICH TREN ATM                    ";
	set_color(green);
	cout<<"'"<<endl<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '";
	set_color(yellow);
	cout<<"                                       WELCOME TO ATM DT VERSION 0.5.7.8                                  ";
	set_color(green);
	cout<<"'"<<endl<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '";
	set_color(white);
	cout<<"                                 Giang Vien Huong Dan:   Tran Ho Thuy Tien                                ";
	set_color(green);
	cout<<"'"<<endl<<" '";
	set_color(white);
	cout<<"                                 Sinh Vien Thuc Hien :   Nguyen Tran My Duyen                             ";
	set_color(green);
	cout<<"'"<<endl<<" '";
	set_color(white);
	cout<<"                                                         Nguyen Phuoc Dai Toan                            ";
	set_color(green);
	cout<<"'"<<endl<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
}
bool importFile(UserAccount	useraccount[],int &size){
	ifstream FileIn;
	FileIn.open("F:\\PBL1\\ThongTin.txt",ios::in);
	int i = 0;
	if(FileIn.fail())
	{
		cout<<"Cap nhat du lieu khong thanh cong !!!";
		return false;
	}
	while(!FileIn.eof())
	{
		i++;
		FileIn>>useraccount[i].account_number;
		FileIn>>useraccount[i].password_number;
		FileIn>>useraccount[i].money;
		FileIn>>useraccount[i].lock;
		FileIn>>useraccount[i].number_of_transactions;
	}
	size = i-1;
	FileIn.close();
	return true;
}
int login(string &account,string &password,int index){
	set_color(yellow);
	cout<<"\n\t\tTai Khoan			: ";
	set_color(white);
	login_account(account);
	set_color(yellow);
	cout<<"\n\t\tMat Khau			: ";
	set_color(white);
	login_password(password);
	if(account==account_staff && password==password_staff) 	return 1;
	set_color(white);
	return 0;
}
void login_account(string &account)
{
	account = "";
	char user_account[10];
	for(int i = 0; i < 10; i++)	{
		user_account[i] = getch();
		if(i == 9){
			if(user_account[9] == 8) // Ki tu co ma askii = 8 la ki tu backspace
			{
				cout << "\b \b";
				i = i - 2;
			}
			else if(user_account[9] ==13) break; // Ki tu co ma askii = 13 la ki tu enter
			else	i--;
		}
		else {
			if( user_account[i] >= '0' &&  user_account[i] <= '9')		cout<<user_account[i];	
			else if(user_account[i] == 8){ // Ki tu co ma askii = 8 la ki tu backspace
				if( i == 0 ) i--;	
				else{
					cout<<"\b \b";// dung de xoa ki tu muon xoa
					i = i - 2;
				}
				
			}
			else i=i-1;
		}
	}	
	for(int i=0;i<9;i++)	account += user_account[i];
}
void login_password(string &password){
	password = "";
	char pass_word[7];
	for(int i = 0; i < 7; i++){
		pass_word[i] = getch();
		if(i == 6){
			if(pass_word[6] == 8) // Ki tu co ma askii = 8 la ki tu backspace
			{
				cout << "\b \b";
				i = i - 2;
			}
			else if(pass_word[6] ==13) break; // Ki tu co ma askii = 13 la ki tu enter
			else	i--;
		}
		else {
			if( pass_word[i] >= '0' &&  pass_word[i] <= '9'){
				cout<<pass_word[i];
				Sleep(150);
				cout<<"\b"<<"*";
			}
			else if(pass_word[i] == 8){
				if( i > 0 )	{
					cout<<"\b \b";// dung de xoa ki tu muon xoa
					i = i - 2;
				}
				else i = i - 1;
			}
			else i=i-1;
		}
	}	
	for(int i=0;i<6;i++)	password += pass_word[i];
}


bool checkUserAccount(UserAccount useraccount[], string account, string password, int &index, int size){
	int left, mid, right;
	left=1;
	right=size;
	while(left<=right)
	{	
		mid = (left+right)/2;
		if(account>useraccount[mid].account_number)	left = mid + 1 ;
		else if(account<useraccount[mid].account_number) right = mid - 1;
		else{
			index=mid;
			if(useraccount[mid].password_number == password)	return true;
			else break;
		}
	}
	return false;
}
int  getUserOption(){
	string option;
	cout<<endl;
	set_color(blue);
	cout<<endl;
	cout<<" +--------------------------------------------------MENU----------------------------------------------------+"<<endl;
	cout<<" '                                           1. Rut Tien.                                                   '"<<endl;
	cout<<" '                                           2. Nap Tien.                                                   '"<<endl;
	cout<<" '                                           3. Xem Tai Khoan.                                              '"<<endl;
	cout<<" '                                           4. Thoat.                                                      '"<<endl;
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	set_color(yellow);
	cout<<"\t\tVui Long Nhap Lua Chon Cua Ban	: ";
	set_color(white);
	getline(cin,option);
	int length = option.size();
	while (length!=1 || option[0]<'1' || option[0]>'4'){
		set_color(blue);
		cout<<"\n\t\tLua Chon Cua Ban Khong Hop Le !!!\n\n";
		set_color(yellow);
		cout<<"\t\tVui Long Nhap Lai Lua Chon Cua Ban  : ";
		set_color(white);
		getline(cin,option);
		length = option.size();
	}
	return option[0]-'0';
}
int  transaction(UserAccount useraccount[], int index,int size, int option){
	switch (option){
		case 1:{
			string withdraw;
			withdrawCash(useraccount, index,size, withdraw); 
			storeData(useraccount, option, index, withdraw);
			return 1;
		}
		case 2:{                      
			string deposit ;
			makeDeposit(useraccount, index,size, deposit); 
			storeData(useraccount, option, index, deposit); 
			return 1;
		}
		case 3:{
			viewBalance(useraccount[index].money);
			storeData(useraccount, option, index, "0"); 
			return 1;
		}
		case 4:	{
			set_color(blue);
			cout<<"\n\t\tCam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
			cout<<"\n\t\tChuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			set_color(green);
			cout<<"\n ------------------------------------------------------------------------------------------------------------"<<endl;
			return 0;	
		}
	}
}
int otherTransaction(){
	string option;
	set_color(yellow);
	cout<<"\n\n\t\tBan Co Muon Giao Dich Tiep Khong ?";
	set_color(white );
	cout<<"\n\t\t 1. Co";
	cout<<"\n\t\t 2. Khong";
	set_color(yellow);
	cout<<"\n\t\tVui Long Nhap Lua Chon Cua Ban  : ";
	set_color(white);
	getline(cin,option);
	int length = option.size();
	while (length!=1 || option[0]<'1' || option[0]>'2'){
		set_color(blue);
		cout<<"\n\t\tLua Chon Cua Ban Khong Hop Le !!!";
		set_color(yellow);
		cout<<"\n\t\tVui Long Nhap Lai Lua Chon Cua Ban : ";
		set_color(white);
		getline(cin,option);
		length = option.size();
	}
	if(option[0]=='1') return 1;
	else {
		set_color(blue);
		cout<<"\n\t\tCam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
		cout<<"\n\t\tChuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
		set_color(green);
		cout<<"\n ------------------------------------------------------------------------------------------------------------"<<endl;
	}
	return 0;
}
long long getMoney(string money){
	long long tien = 0;
	int length = money.size();
  	for(int i= 0;i < length;i++)
 	{
  		if(money[i] != '.')	
  		{
  			tien += (money[i] - '0') * pow(10, length -1-i);
		}
		else tien = tien / 10;
	}
	return tien; 
}
void formatMoney(UserAccount useraccount[], int index, long long money){
	string s;
	string Result;         
	ostringstream convert;   
	convert << money;      
	Result = convert.str(); 

    int length = Result.size();
	int dem = 0;
    for(int i = length-1 ; i >= 0 ; i--)
    {
    	dem++;
    	if(i == 0) s = Result[i]+s;	
    	else if(dem % 3 == 0)
    	{
    		s = Result[i]+s;
    		s = '.' +s;
		}
		else s = Result[i] + s;
	}
	useraccount[index].money = s;
}
void withdrawCash(UserAccount useraccount[], int index,int size, string &withdraw){
	set_color(blue);
	cout<<"\n\t\tNhap So Tien Ban Muon Rut 	: ";
	set_color(white);
	getline(cin,withdraw);
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(withdraw);
	
	if(money_transactions > money) {
		set_color(blue);
		cout<<"\n\t\tSo Tien Cua Ban Khong Du De Thuc Hien Giao Dich Nay !!!";
	}
	else{
		set_color(blue);
		cout<<"\n\t\tGiao Dich Thanh Cong !!!";
		money = money - money_transactions;
	}
	formatMoney(useraccount,index,money);
	updateFile(useraccount,size);
}
void makeDeposit(UserAccount useraccount[], int index,int size, string &deposit){
	set_color(blue);
	cout<<"\n\t\tNhap So Tien Ban Muon Nap 	: ";
	set_color(white );
	getline(cin,deposit);
	set_color(blue);
	cout<<"\n\t\tGiao Dich Thanh Cong !!!";
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(deposit);
	money = money + money_transactions;
	formatMoney(useraccount,index,money);
	updateFile(useraccount,size);
}
void viewBalance(string money){
	set_color(blue);
	cout<<"\n\t\tSo Tien Hien Tai Cua Ban 	: ";
	set_color(white );
	cout<<money;
}
void formatTime(int time, string &s){
	s += (time/10) + '0';
	s += (time % 10) + '0';
}
void getTime(int &years, string &month, string &day, string &hour, string &minite){

	time_t now = time(0);
   	tm *ltm = localtime(&now);

  	int YEAR   = 1900 + ltm->tm_year;
   	int MONTH  = 1    + ltm->tm_mon;
   	int DAY    = ltm->tm_mday ;
   	int HOUR   = ltm->tm_hour;
   	int MINITE = ltm->tm_min ;
 	years = YEAR;
   	formatTime(MINITE,minite);
   	formatTime(HOUR,hour);
   	formatTime(DAY,day);
   	formatTime(MONTH,month);
}
void updateFile(UserAccount useraccount[], int size){
	int i = 1;
	ofstream FileOut;
	FileOut.open("F:\\PBL1\\ThongTin.txt", ios::out);
	while(i <= size)
	{
		FileOut << useraccount[i].account_number;
		FileOut << setw(15) << useraccount[i].password_number;
		FileOut << setw(20) << useraccount[i].money;
		FileOut << setw(10)<<useraccount[i].lock;
		FileOut << setw(10) << useraccount[i].number_of_transactions<<endl;
		i++;
	}
	FileOut.close();
}
void storeData(UserAccount useraccount[], int option, int index, string money_transactions){
	int year;
	string minite, hour, day, month;
	getTime(year, month, day, hour, minite);
	ofstream FileGD;
	FileGD.open("F:\\PBL1\\GiaoDich.txt",ios::app);
	int length = money_transactions.size();
	if(option==1)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|";
		FileGD<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|";
		FileGD<<setw(19-length)<<"-"<<money_transactions<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	} 
	else if(option==2)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|";
		FileGD<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|";
		FileGD<<setw(19-length)<<"+"<<money_transactions<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	}
	else if(option==3)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|";
		FileGD<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|";
		FileGD<<setw(19)<<"ViewBalance"<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	}
}


