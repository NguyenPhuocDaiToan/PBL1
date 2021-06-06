// De tai 701 : Xay dung ung dung giao dich ATM
// Giang vien huong dan : Tran Ho Thuy Tien
// Sinh vien thuc hien  : Nguyen Tran My Duyen
//					    : Nguyen Phuoc Dai Toan

#include<iostream>
#include<fstream>     // doc - ghi file
#include<conio.h>	  // su dung ham getch() de chuyen mat khau ve *
#include<iomanip>	  // su dung ham setw() de canh do rong luu vao file
#include<math.h>	  // su dung ham pow(), dùng trong ham getmoney chuyen tien tu string ve int
#include<ctime>	 	  // su dung de lay thoi gian luu lich su giao dich
#include<string>	  // su dung chuoi de dinh dang tien va mat khau
#include<sstream>	  // su dung ostringstream, de chuyen tien dang int ve string de dinh dang tien

using namespace std;

const int account_staff     = 123456789;
const string password_staff = "999999";
// tai khoan cua nhan vien de bat dau va ket thuc chuong trinh

struct UserAccount
{
    int account_number;
    string password_number;
    string money;
    int lock;
    int number_of_transactions;
};

void menu();
void importFile(UserAccount useraccount[], int &size);
void login_password(string &password);
int  login(int &account, string &password, int index);

bool checkUserAccount(UserAccount useraccount[], int account, string password, int &index, int size);

int  getUserOption();
int  transaction(UserAccount useraccount[], int size, int index, int option); 
int  otherTransaction(); 
long long getMoney(string money);
void formatMoney(UserAccount useraccount[], int index, long long money);
void withdrawCash(UserAccount useraccount[], int index, string &withdraw);
void makeDeposit(UserAccount useraccount[], int index, string &deposit); 
void viewBalance(string money); 

void getTime(int &year, string &month, string &day, string &hour, string &minite);
void formatTime(int time, string &s);
void updateFile(UserAccount useraccount[], int size); 
void storeData(UserAccount useraccount[], int option, int index, string money_transactions); 

int main(){
	
	UserAccount useraccount[100];
	
	int number_login[100];
	int account;
	string password;
	int size, index = 0, option, maxInput=3, check, lo_gin;
	int number_of_logins = 0;
	
	menu();	
	
	while(login(account,password,index))
	{	
		cout<<"\n\n Dang nhap cua ban khong hop le !!!\n";
		cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
	}
	cout<<"\n\n Cap nhat du lieu thanh cong !!!\n";
	cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
	importFile(useraccount, size);
	
	for(int i=1;i<=size;i++)
	{
		number_login[i]=0;
	}
	
	z:
	while(login(account, password, index))
	{	
		// Kiem tra dang nhap
		check = checkUserAccount(useraccount, account, password, index, size);
		if(index==0)
		{
			cout<<"\n Tai Khoan Khong Ton Tai !!!\n";
			cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
		}	
		else if(useraccount[index].lock)
		{
			cout<<"\n Tai Khoan Cua Ban Da Bi Khoa !!!\n";
			cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
			goto z;
		}
		else if(!check)
		{
			number_login[index]++;
			if(number_login[index]==3)
			{
				useraccount[index].lock = 1;
				updateFile(useraccount, size);
				cout<<"\n Tai Khoan Cua Ban Da Bi Khoa !!!\n";
				cout<<" ------------------------------------------------------------------------------------------------------------\n";
			}
			else
			{
				cout<<"\n Mat khau cua ban khong dung !!!\n";
				cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
				index = 0;
			}
			goto z; // z dong 77
		}
		
		// Kiem tra giao dich
		
		while( useraccount[index].number_of_transactions < 5)
		{
				option=getUserOption();
				if (transaction(useraccount, size, index, option)){
					useraccount[index].number_of_transactions++;
				}
				else break;
				if(! otherTransaction())		break;
		}
			updateFile(useraccount, size);
			if(useraccount[index].number_of_transactions == 5){
					cout<<"\n\n Quy Khach Da Dat So Giao Dich Toi Da Trong Mot Ngay !!!";
					cout<<"\n Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
					cout<<"\n Chuc Quy Khach Co Mot Ngay Tot Lanh!!!\n\n";
					cout<<"\n ------------------------------------------------------------------------------------------------------------\n";
			}
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
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '                                             DE TAI DO AN PBL1                                            '"<<endl;
	cout<<" '                          DE TAI 701: XAY DUNG UNG DUNG THUC HIEN GIAO DICH TREN ATM                      '"<<endl;
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '                                     WELCOME TO ATM DT VERSION 0.5.7.8                                    '"<<endl;
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" '                     Giang Vien Huong Dan:   Tran Ho Thuy Tien                                            '"<<endl;
	cout<<" '                      Sinh Vien Thuc Hien:   Nguyen Tran My Duyen                                         '"<<endl;
	cout<<" '                                             Nguyen Phuoc Dai Toan                                        '"<<endl;
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
}
void importFile(UserAccount	useraccount[],int &size){
	ifstream FileIn;
	FileIn.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.txt",ios_base::in);
	int i = 0;
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
}

void login_password(string &password){
	password = "";
	int i = 0 ;
	char pass_word[6];
	for(int i = 0; i < 7; i++){
			if(i == 6){
				pass_word[6] = getch();
				if(pass_word[6] == 8){
					cout << "\b \b";
					i = i - 2;
				}
				else if(pass_word[6] ==13) break;
				else{
					i--;
				}
			}
			else {
				pass_word[i] = getch() ;
				if( pass_word[i] !=8 )	cout<<"*";
				else {
					if( i > 0 )	{
						cout<<"\b \b";
						i = i - 2;
					}
					else i = i - 1;
				}
			}
		}
		for(int i=0; i<6; i++){
			password += pass_word[i] ;
		}
}
int login(int &account,string &password,int index){
	
	cout<<"\n Tai Khoan			: ";
	cin>>account;
	cout<<" Mat Khau			: ";
	login_password(password);
	if(account == account_staff && password == password_staff) 	return 0;
	
	return 1;
}
bool checkUserAccount(UserAccount useraccount[], int account, string password, int &index, int size){
	for(int i=1; i<=size; i++)
		if(useraccount[i].account_number == account)
		{
			index=i;
			if(useraccount[i].password_number == password)	return true;
			break;
		}
	return false;
}

int  getUserOption(){
	int option;
	cout<<endl;
	cout<<" +--------------------------------------------------MENU----------------------------------------------------+"<<endl;
	cout<<" '                                           1. Rut Tien.                                                   '"<<endl;
	cout<<" '                                           2. Nap Tien.                                                   '"<<endl;
	cout<<" '                                           3. Xem Tai Khoan.                                              '"<<endl;
	cout<<" '                                           4. Thoat.                                                      '"<<endl;
	cout<<" +----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<" Vui Long Nhap Lua Chon Cua Ban	: ";
	cin>>option;
	while (option > 4)
	{
		cout<<" Lua Chon Cua Ban Khong Hop Le !!!"<<endl<<endl;
		cout<<" Vui Long Nhap Lai Lua Chon Cua Ban : ";
		cin>>option;
	}
	return option;
}
int  transaction(UserAccount useraccount[], int size, int index, int option){
	switch (option)
	{
		case 1:{
			string withdraw;
			withdrawCash(useraccount, index, withdraw); 
			storeData(useraccount, option, index, withdraw);
			break;
		}
		case 2:{                      
			string deposit ;
			makeDeposit(useraccount, index, deposit); 
			storeData(useraccount, option, index, deposit); 
			break;
		}
		case 3:{
			viewBalance(useraccount[index].money);
			storeData(useraccount, option, index, "0"); 
			break;
		}
		case 4:
		{
			cout<<"\n Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
			cout<<"\n Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			cout<<" ------------------------------------------------------------------------------------------------------------"<<endl;
			return 0;	
		}
	}
	return 1;
}
int  otherTransaction(){
	int option;
	cout<<"\n\n Ban Co Muon Giao Dich Tiep Khong ?";
	cout<<"\n 1. Co";
	cout<<"\n 2. Khong";
	cout<<"\n Vui Long Nhap Lua Chon Cua Ban : ";
	cin>>option;
	while(option>2)
	{
		cout<<"\n Lua Chon Cua Ban Khong Hop Le !!!";
		cout<<"\n Vui Long Nhap Lai Lua Chon Cua Ban : ";
		cin>>option;
	}
	if(option==1) return 1;
	else 
	{
		cout<<"\n Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!";
		cout<<"\n Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
		cout<<" ------------------------------------------------------------------------------------------------------------"<<endl;
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
void withdrawCash(UserAccount useraccount[], int index, string &withdraw){
	cout<<"\n Nhap So Tien Ban Muon Rut 	: ";
	cin>>withdraw;
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(withdraw);
	if(money_transactions > money) cout<<"\n So Tien Cua Ban Khong Du De Thuc Hien Giao Dich Nay !!!";
	else
	{
		cout<<"\n Giao Dich Thanh Cong !!!";
		money = money - money_transactions;
	}
	formatMoney(useraccount,index,money);
	updateFile(useraccount,index);
}
void makeDeposit(UserAccount useraccount[], int index, string &deposit){

	cout<<"\n Nhap So Tien Ban Muon Nap 	: ";
	cin>>deposit;
	cout<<"\n Giao Dich Thanh Cong !!!";
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(deposit);
	money = money + money_transactions;
	formatMoney(useraccount,index,money);
	updateFile(useraccount,index);
}
void viewBalance(string money){
	cout<<"\n So Tien Hien Tai Cua Ban 	: "<< money;
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
	FileOut.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.txt", ios_base::out);
	while(i <= size)
	{
		FileOut << useraccount[i].account_number << setw(15) << useraccount[i].password_number << setw(20) << useraccount[i].money;
		FileOut << setw(10)<<useraccount[i].lock << setw(10) << useraccount[i].number_of_transactions<<"	"<< endl;
		i ++;
	}
	FileOut.close();
}
void storeData(UserAccount useraccount[], int option, int index, string money_transactions){
	int year;
	string minite, hour, day, month;
	getTime(year, month, day, hour, minite);
	ofstream FileGD;
	FileGD.open("C:\\Users\\DELL\\OneDrive\\Desktop\\GiaoDich.txt",ios_base::app);
	int length = money_transactions.size();
	if(option==1)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|"<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|"<<setw(19-length)<<"-"<<money_transactions<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	} 
	else if(option==2)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|"<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|"<<setw(19-length)<<"+"<<money_transactions<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	}
	else if(option==3)
	{
		FileGD<<"|"<<setw(20)<<useraccount[index].account_number<<setw(10)<<"|"<<setw(10)<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<setw(8)<<"|"<<setw(19)<<"ViewBalance"<<setw(9)<<"|"<<endl;
		FileGD<<"|-----------------------------|-------------------------------|---------------------------|"<<endl;
	}
}


