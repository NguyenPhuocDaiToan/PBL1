#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<math.h>
#include<ctime>
#include<string>
#include<sstream>

using namespace std;

const int account_staff     = 123456789;
const string password_staff = "999999";
// ma de exit atm, luu giao dich.

struct UserAccount
{
    int account_number;
    string password_number;
    string money;
    int lock;
    int number_of_transactions;
};

void menu();
void importFile(UserAccount useraccount[],int &size);
void login_password(string &password);
int  login(int &account ,string &password,int index);

bool checkUserAccount(UserAccount useraccount[],int account,string password,int & index,int size);

int  getUserOption();
int  transaction(UserAccount useraccount[],int size,int index,int option); 
int  otherTransaction(); 
long long getMoney(string money);
void formatMoney(UserAccount useraccount[],int index,long long money);
void withdrawCash(UserAccount useraccount[],int index,string &withdraw);
void makeDeposit(UserAccount useraccount[],int index,string &deposit); 
void viewBalance(string money); 

void getTime(int &year,string &month,string &day,string &hour,string &minite);
void formatTime(int time, string &s);
void updateFile(UserAccount useraccount[], int size); 
void storeData(UserAccount useraccount[],int option,int index,string money_transactions); 

int main(){
	
	UserAccount useraccount[100];
	
	int account;
	string password;
	int size,index=0,option,maxInput=3,check,lo_gin;
	int number_of_logins=0;
	
	menu();	
	importFile(useraccount,size);
	
	while(login(account,password,index))
	{	
		// Kiem tra dang nhap
		check = checkUserAccount(useraccount,account,password,index,size);
		if(index==0)	cout<<"Tai Khoan Khong Ton Tai !!!"<<endl;
		else if(useraccount[index].lock)
		{
			cout<<"Tai Khoan Cua Ban Da Bi Khoa !!!\n";
			index=0;
		}
		else if(!check)
		{
			
			number_of_logins++;
			while (number_of_logins<3)
			{
				cout<<"\nMat Khau Cua Ban Khong Dung !!!"<<endl;
				cout<<"Ban Con "<<3-number_of_logins<<" Lan Nhap "<<endl;
				lo_gin = login(account,password,index);
				number_of_logins++;
				check = checkUserAccount(useraccount,account,password,index,size);
				if(check == 1)	break;
			}
			if(!check)
			{
				cout<<"\nTai Khoan Cua Ban Da Bi Khoa"<<endl;
				useraccount[index].lock=1;
				updateFile(useraccount,size);
				index=0;
			}	
		}
		number_of_logins=0;
		
		// Kiem tra giao dich
		if( index != 0 )
		{
			while( useraccount[index].number_of_transactions < 5)
			{
				option=getUserOption();
				if (transaction(useraccount,size,index,option)){
					useraccount[index].number_of_transactions++;
				}
				else break;
				if(! otherTransaction())		break;
			}
			updateFile(useraccount,size);
			if(useraccount[index].number_of_transactions == 5){
					cout<<"\nQuy Khach Da Dat So Giao Dich Toi Da Trong Mot Ngay !!!"<<endl;
					cout<<"Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!"<<endl;
					cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			}
		}
		index=0;
	}
	for(int i=1;i<=size;i++)
	{
		useraccount[i].number_of_transactions = 0;
	}
	updateFile(useraccount,size);

	return 0;
}

void menu(){
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"'                                             DE TAI DO AN PBL1                                            '"<<endl;
	cout<<"'                          DE TAI 701: XAY DUNG UNG DUNG THUC HIEN GIAO DICH TREN ATM                      '"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"'                                     WELCOME TO ATM DT VERSION 0.5.7.8                                    '"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"'                      Sinh Vien Thuc Hien:   Nguyen Tran My Duyen                                         '"<<endl;
	cout<<"'                                             Nguyen Phuoc Dai Toan                                        '"<<endl;
	cout<<"'                     Giang Vien Huong Dan:   Tran Ho Thuy Tien                                            '"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<endl;
}
void importFile(UserAccount	useraccount[],int &size){
	ifstream FileIn;
	FileIn.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin1.TXT",ios_base::in);
	int i=0;
	while(!FileIn.eof())
	{
		i++;
		FileIn>>useraccount[i].account_number;
		FileIn>>useraccount[i].password_number;
		FileIn>>useraccount[i].money;
		FileIn>>useraccount[i].lock;
		FileIn>>useraccount[i].number_of_transactions;
	}
	size=i-1;
	FileIn.close();
}

void login_password(string &password){
	password = "";
	int i = 0 ;
	char pass_word[6];
	for(int i=0;i<7;i++){
			if(i==6){
				pass_word[6]=getch();
				if(pass_word[6] == 8){
					cout<<"\b \b";
					i = i - 2;
				}
				else{
					cout<<"\b";
					break;
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
		for(int i=0;i<6;i++){
			password += pass_word[i] ;
		}
}
int login(int &account,string &password,int index){
	if(index==0)
	{
		cout<<"\nTai Khoan		: ";
		cin>>account;
		cout<<"Mat Khau		: ";
		login_password(password);
		if(account == account_staff && password == password_staff) 	return 0;
	}
	else {
		cout<<"Mat Khau		: ";
		login_password(password);
		if(account == account_staff && password == password_staff) 	return 0;
	}
	return 1;
}
bool checkUserAccount(UserAccount useraccount[],int account,string password,int & index,int size){
	for(int i=1;i<=size;i++)
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
	cout<<"+--------------------------------------------------MENU----------------------------------------------------+"<<endl;
	cout<<"'                                           1. Rut Tien.                                                   '"<<endl;
	cout<<"'                                           2. Nap Tien.                                                   '"<<endl;
	cout<<"'                                           3. Xem Tai Khoan.                                              '"<<endl;
	cout<<"'                                           4. Thoat.                                                      '"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"Vui Long Nhap Lua Chon Cua Ban	: ";
	cin>>option;
	while (option > 4)
	{
		cout<<"Lua Chon Cua Ban Khong Hop Le !!!"<<endl<<endl;
		cout<<"Vui Long Nhap Lai Lua Chon Cua Ban : ";
		cin>>option;
	}
	return option;
}
int  transaction(UserAccount useraccount[],int size,int index,int option){
	switch (option)
	{
		case 1:{
			string withdraw;
			withdrawCash(useraccount,index,withdraw); 
			storeData(useraccount,option,index,withdraw);
			break;
		}
		case 2:{                      
			string deposit ;
			makeDeposit(useraccount,index,deposit); 
			storeData(useraccount,option,index,deposit); 
			break;
		}
		case 3:{
			viewBalance(useraccount[index].money);
			storeData(useraccount,option,index,"0"); 
			break;
		}
		case 4:
		{
			cout<<"\nCam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			return 0;	
		}
	}
	return 1;
}
int  otherTransaction(){
	int option;
	cout<<"Ban Co Muon Giao Dich Tiep Khong ?"<<endl;
	cout<<"1. Co"<<endl;
	cout<<"2. Khong"<<endl;
	cout<<"Vui Long Nhap Lua Chon Cua Ban : ";
	cin>>option;
	while(option>2)
	{
		cout<<"Lua Chon Cua Ban Khong Hop Le !!!"<<endl<<endl;
		cout<<"Vui Long Nhap Lai Lua Chon Cua Ban : ";
		cin>>option;
	}
	if(option==1) return 1;
	return 0;
}

long long getMoney(string money){
	long long tien = 0;
	int length = money.size();
  	for(int i= 0;i < length;i++)
 	{
  		if(money[i] != '.')	
  		{
  			tien += (money[i]-'0') * pow(10,length -1-i);
		}
		else tien = tien / 10;
	}
	return tien; 
}
void formatMoney(UserAccount useraccount[],int index,long long money){
	string s;
	string Result;         
	ostringstream convert;   
	convert << money;      
	Result = convert.str(); 

    int length = Result.size();
	int dem=0;
    for(int i = length-1 ; i >= 0 ; i--)
    {
    	dem++;
    	if(i==0) s = Result[i]+s;	
    	else if(dem%3==0)
    	{
    		s = Result[i]+s;
    		s = '.' +s;
		}
		else s = Result[i]+s;
	}
	useraccount[index].money = s;
}
void withdrawCash(UserAccount useraccount[],int index,string &withdraw){
	cout<<"Nhap So Tien Ban Muon Rut 	: ";
	cin>>withdraw;
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(withdraw);
	if(money_transactions > money) cout<<"So Tien Cua Ban Khong Du De Thuc Hien Giao Dich Nay !!!"<<endl;
	else
	{
		cout<<"Giao Dich Thanh Cong !!!"<<endl;
		money = money - money_transactions;
	}
	formatMoney(useraccount,index,money);
	updateFile(useraccount,index);
}
void makeDeposit(UserAccount useraccount[],int index,string &deposit){

	cout<<"Nhap So Tien Ban Muon Nap 	: ";
	cin>>deposit;
	cout<<"Giao Dich Thanh Cong !!!"<<endl;
	long long money = getMoney(useraccount[index].money);
	long long money_transactions = getMoney(deposit);
	money = money + money_transactions;
	formatMoney(useraccount,index,money);
	updateFile(useraccount,index);
}
void viewBalance(string money){
	cout<<"So Tien Hien Tai Cua Ban 	: "<<money<<endl;
}

void formatTime(int time, string &s){
	s += (time/10) + '0';
	s += (time % 10) + '0';
}
void getTime(int &years,string &month,string &day,string &hour,string &minite){

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
	FileOut.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin1.TXT", ios_base::out);
	while(i <= size)
	{
		FileOut << useraccount[i].account_number << setw(15) << useraccount[i].password_number << setw(20) << useraccount[i].money;
		FileOut << setw(10)<<useraccount[i].lock << setw(10) << useraccount[i].number_of_transactions<<"	"<< endl;
		i ++;
	}
	FileOut.close();
}
void storeData(UserAccount useraccount[],int option,int index,string money_transactions){
	int year;
	string minite,hour,day,month;
	getTime(year,month,day,hour,minite);
	ofstream FileGD;
	FileGD.open("C:\\Users\\DELL\\OneDrive\\Desktop\\GiaoDich.TXT",ios_base::app);
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


