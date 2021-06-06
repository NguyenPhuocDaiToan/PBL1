#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
using namespace std;

const int account_staff     = 123456789;
const int password_staff    = 990578;
// ma de exit atm, luu giao dich.

typedef struct UserAccount
{
    int account_number;
    int password;
};

void menu();
void importFile(int account[],int password[],long long money[],int lock[],int &size);
void login(UserAccount & account,int index);

bool checkUserAccount(int account[], int password[],UserAccount userAccount,int & index,int size);
bool validateAccountNumber(const int account_number); 
bool validatePassword(const int password);

int  getUserOption();
int  transaction(int account[],int password[],long long money[],int lock[],int size,int index,int option); 
int  otherTransaction(); 
int  withdrawCash(long long money[],int index); 
int  makeDeposit(long long money[],int index); 
void viewBalance(long long money[],int index); 
void changePassword(int password[],int index,int size); 

void formatTime(int time, string &s);
void getTime(int &year,string &month,string &day,string &hour,string &minite);
void updateFile(int account[], int password[], long long money[], int lock[], int size); 
void storeData(int account[],int option,int index,int x); 

int main(){
	long long money[100];
	int account[100],password[100],lock[100],size,index=0;
	int number_of_logins=0,number_of_transactions=0,maxInput=3,option;
	UserAccount userAccount;
	
	menu();
	importFile(account,password,money,lock,size);
	
	do
	{
		login(userAccount,index);
		int check=checkUserAccount(account,password,userAccount,index,size);
		
		if(!index){
			if(!validateAccountNumber(userAccount.account_number))
			{
				cout<<"Tai Khoan Khong Hop Le!!!"<<endl;
				cout<<"Vui Long Nhap Lai Tai Khoan !!!"<<endl<<endl;
			}
			else
			{
				cout<<"Tai Khoan Khong Ton Tai !!!"<<endl;
				cout<<"Vui Long Nhap Lai Tai Khoan Va Mat Khau !!!"<<endl;
			}
		}
		else if(lock[index])
		{
			cout<<"Tai Khoan Cua Quy Khach Da Bi Khoa !"<<endl;
			return 0;
		}
		else if(check)	break;
		else{
				number_of_logins++;
				cout<<"Mat Khau Cua Quy Khach Khong Dung !!!"<<endl;
				if(number_of_logins==3){
					lock[index]=1;
					cout<<"Tai Khoan Cua Quy Khach Da Bi Khoa !"<<endl;
				}
				cout<<"Quy Khach Con "<<maxInput-number_of_logins<<" Lan Nhap"<<endl<<endl;
		}
	}
	while(number_of_logins<3);
	
	if(lock[index]){
		updateFile(account,password,money,lock,size);
		return 0;
	}
	do  
	{
		number_of_transactions++;
		option=getUserOption();
		if (!transaction(account,password,money,lock,size,index,option))
		{
			cout<<"Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			return 0;
		}
		if(otherTransaction())
		if(number_of_transactions == 5)
		{
			cout<<"\nQuy Khach Da Dat So Lan Giao Dich Trong Mot Ngay !!!"<<endl;
			cout<<"Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi!!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh!!!"<<endl;
			return 0;
		}
	}	while(number_of_transactions<5);
	
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

void importFile(int account[],int password[],long long money[],int lock[],int &size){
	ifstream FileIn;
	FileIn.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.TXT",ios_base::in);
	int i=1;
	while(!FileIn.eof())
	{
		FileIn>>lock[i];
		FileIn>>account[i];
		FileIn>>password[i];
		FileIn>>money[i];
		i++;
	}
	size=i-2;
	FileIn.close();
}
void login(UserAccount & userAccount,int index){
	char pass_word[6];
	int value_password=0;
	if(index==0)
	{
		cout<<"Tai Khoan		: ";
		cin>>userAccount.account_number;
		cout<<"Mat Khau		: ";
		for(int i=0;i<6;i++)
		{
			pass_word[i] = getch() ;
			cout<<"*";
			value_password += (pass_word[i] - '0') * pow(10,5-i);
		}
		cout<<endl;
		userAccount.password = value_password;
	}
	else 
	{
		cout<<"Mat Khau		: ";
		for(int i=0;i<6;i++)
		{
			pass_word[i] = getch() ;
			cout<<"*";
			value_password += (pass_word[i] - '0') * pow(10,5-i);
		}
		cout<<endl;
		cout<<value_password;
		userAccount.password = value_password;	
	}
}

bool checkUserAccount(int account[], int password[],UserAccount userAccount,int & index,int size){
	for(int i=1;i<=size;i++)
		if(userAccount.account_number == account[i])
		{
			index=i;
			if(userAccount.password == password[i])	return true;
			break;
		}
	return false;
}
bool validateAccountNumber(const int account_number){
    int number_account_of_digits = 9;
    int temp = account_number/pow(10,number_account_of_digits-1);
    return temp>0 && temp<10;
}
bool validatePassword(const int password){
    int password_of_digits = 6;
    int temp = password/pow(10,password_of_digits-1);
    return temp>0 && temp<10;
}

int  getUserOption(){
	int option;
	cout<<endl;
	cout<<"+--------------------------------------------------MENU----------------------------------------------------+"<<endl;
	cout<<"'                                           1. Rut Tien.                                                   '"<<endl;
	cout<<"'                                           2. Nap Tien.                                                   '"<<endl;
	cout<<"'                                           3. Xem Tai Khoan.                                              '"<<endl;
	cout<<"'                                           4. Doi Mat Khau.                                               '"<<endl;
	cout<<"'                                           5. Thoat.                                                      '"<<endl;
	cout<<"+----------------------------------------------------------------------------------------------------------+"<<endl;
	cout<<"Vui Long Nhap Lua Chon Cua Ban	: ";
	cin>>option;
	while (option > 5)
	{
		cout<<"Lua Chon Cua Ban Khong Hop Le !!!"<<endl<<endl;
		cout<<"Vui Long Nhap Lai Lua Chon Cua Ban : ";
		cin>>option;
	}
	return option;
}
int  transaction(int account[],int password[],long long money[],int lock[],int size,int index,int option){
	switch (option)
	{
		case 1:{
			int withdraw = withdrawCash(money,index);
			updateFile(account,password,money,lock,size);
			storeData(account,option,index,withdraw); 
			break;
		}
		case 2:{
			int deposit = makeDeposit(money,index);
			updateFile(account,password,money,lock,size);
			storeData(account,option,index,deposit); 
			break;
		}
		case 3:{
			viewBalance(money,index);
			storeData(account,option,index,0); 
			break;
		}
		case 4:{
			changePassword(password,index,size);
			updateFile(account,password,money,lock,size);
			storeData(account,option,index,0); 
			break;
		}
		case 5:
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
int  withdrawCash(long long money[],int index){
	long long withdraw;
	cout<<"Nhap So Tien Ban Muon Rut 	: ";
	cin>>withdraw;
	if(withdraw > money[index]) cout<<"So Tien Cua Ban Khong Du De Thuc Hien Giao Dich Nay !!!"<<endl;
	else
	{
		cout<<"Giao Dich Thanh Cong !!!"<<endl;
		money[index]-=withdraw;
	}
	otherTransaction();
	return withdraw;
}
int  makeDeposit(long long money[],int index){
	long long deposit;
	cout<<"Nhap So Tien Ban Muon Nap 	: ";
	cin>>deposit;
	cout<<"Giao Dich Thanh Cong !!!"<<endl;
	money[index]+=deposit;
	otherTransaction();
	return deposit;
}
void viewBalance(long long money[],int index){
	cout<<"So Tien Hien Tai Cua Ban 	: "<<money[index]<<endl;
	otherTransaction();
}
void changePassword(int password[],int index,int size){
	int old_password,new_password;
	cout<<"Vui Long Nhap Mat Khau Cu Cua Ban : ";
	cin>>old_password;
	bool status = false;
	while(!status)
	{
		if(validatePassword(old_password))
		{

			for(int i=1;i<=size;i++)
				if(old_password == password[i])
				{
						status = true;
						break;
				}
			if(status ==  false)
			{
				cout<<"Mat Khau Cua Ban Khong Dung !!!"<<endl;
				cout<<"Vui Long Nhap Lai Mat Khau Cua Ban : ";
				cin>>old_password;
				cout<<endl;
			}
		}
		else
		{
			cout<<"Mat Khau Cua Ban Khong Hop Le !!!"<<endl;
			cout<<"Vui Long Nhap Lai Mat Khau Cua Ban : ";
			cin>>old_password;
			cout<<endl;
		}
	}
	status = false;
	cout<<"Nhap Mat Khau Moi Ban Can Doi	  : ";
	cin>>new_password;
	while(!status)
	{
		if(validatePassword(new_password))
		{
			password[index] = new_password;
			status = true;
		}
		else
		{
			cout<<"Mat Khau Khong Hop Le !!!"<<endl;
			cout<<"Vui Long Nhap Lai Mat Khau Moi Cua Ban  : ";
			cin>>new_password;
			cout<<endl;
		} 
	}
	otherTransaction();
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
void updateFile(int account[], int password[], long long money[], int lock[], int size){
	int count = 1;
	ofstream FileOut;
	FileOut.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.TXT", ios_base::out);
	while(count <= size)
	{
		FileOut << lock[count]<<"	"<<account[count] <<"			"<< password[count]<<"			"<< money[count]<<endl;
		count ++;
	}
	FileOut.close();
}
void storeData(int account[],int option,int index,int x){
	int year;
	string minite,hour,day,month;
	getTime(year,month,day,hour,minite);
	ofstream FileGD;
	FileGD.open("C:\\Users\\DELL\\OneDrive\\Desktop\\GiaoDich.TXT",ios_base::app);
	if(option==1)
	{
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"-"<<x<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(option==2)
	{
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"+"<<x<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(option==3)
	{
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"View Balance"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(option==4)
	{
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"Change Password"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
}

