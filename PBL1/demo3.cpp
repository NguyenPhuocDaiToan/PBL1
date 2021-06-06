#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

using namespace std;

typedef struct UserAccount
{
    long long account_number;
    int password;
};

void Menu();
void Import_File(long long account[],int password[],long long money[],int lock[],int &size);
void Login(UserAccount & useraccount,int index);

bool Valid_Account_Number(const long long account_number);
bool Valid_Password(const int password);
bool Check(long long account[], int password[],UserAccount useraccount,int & index,int size);

int  Option();
int  Deal(long long account[],int password[],long long money[],int lock[],int size,int index,int option);
int  Question();
int  WithDraw(long long money[],int index);
int  Recharge(long long money[],int index);
void ViewAccount(long long money[],int index);
void ChangePassword(int password[],int index,int size);

void DinhDangThoiGian(int a,string &s);
void LayThoiGian(int &years,string &month,string &day,string &hour,string &minite);
void UpDateFile(int lock[],long long account[],int password[],long long money[],int size);
void Transaction_History(long long account[],int option,int index,int x);

int main(){
	long long account[100],money[100];
	int password[100],lock[100],size,index;
	int number_of_logins=0,number_of_transactions=0,MAX_INPUT=3,option;
	UserAccount useraccount;
	
	Menu();
	Import_File(account,password,money,lock,size);
	
	do
	{
		Login(useraccount,index);
		int check=Check(account,password,useraccount,index,size);
		
		if(index==0){
			if(!Valid_Account_Number(useraccount.account_number))		cout<<"This account is invalid !!!"<<endl<<endl;
			else
			{
				cout<<"Account does not exist"<<endl;
				cout<<"Please re-enter your account and password !!!"<<endl;1
			}
		}
		else if(lock[index])
			{
				cout<<"Your account has been locked"<<endl;
				return 0;
			}
		else if(check)	break;
		else{
				number_of_logins++;
				cout<<"Your password is wrong !!!"<<endl;
				cout<<"You still have the number of entries : "<<MAX_INPUT-number_of_logins<<endl<<endl;
		}
		if(number_of_logins==3){
			lock[index]=1;
			cout<<"Your account has been locked"<<endl;
		}
	}
	while(number_of_logins<3);
	if(lock[index]){
		UpDateFile(lock,account,password,money,size);
		return 0;
	}
	do  
	{	
		number_of_transactions++;
		option=Option();
		if(Deal(account,password,money,lock,size,index,option)==0) return 0;
		if(number_of_transactions==5)
		{
			cout<<"You have been max the transaction in a day !!!";
			return 0;
		}
		if(Question()==0)
		{
			cout<<"Thank you for using our service!!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh !!!"<<endl;
			return 0;
		}
	}	while(number_of_transactions<5);
	
	do  
	{	
		number_of_transactions++;
		option=Option();
		if(Deal(account,password,money,lock,size,index,option)) return 0;
		if(number_of_transactions==5)
		{
			cout<<"Ban Da Giao Dich Du So Lan Trong Mot Ngay !!!";
			return 0;
		}
		if(Question()==0)
		{
			cout<<"Cam On Quy Khach Da Su Dung Dich Vu Cua Chung Toi !!!"<<endl;
			cout<<"Chuc Quy Khach Co Mot Ngay Tot Lanh !!!"<<endl;
			return 0;
		}
	}	while(number_of_transactions<5);
	
	return 0;
}

void Menu(){
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<"'                             WELCOME TO ATM DT                            '"<<endl;
	cout<<"'                       SV:   Nguyen Tran My Duyen                         '"<<endl;
	cout<<"'                             Nguyen Phuoc Dai Toan                        '"<<endl;
	cout<<"'                     GVHD:   Tran Ho Thuy Tien                            '"<<endl;
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<endl;
}
void Import_File(long long account[],int password[],long long money[],int lock[],int &size){
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
void Login(UserAccount & useraccount,int index){
	
	if(index==0)
	{
		cout<<"Account		: ";
		cin>>useraccount.account_number;
		cout<<"Password	: ";
		cin>>useraccount.password;
	}
	else 
	{
		cout<<"Password	: ";
		cin>>useraccount.password;
	}
	cout<<endl;
}
bool Valid_Account_Number(const long long account_number){
    int number_account_of_digits = 9;
    int temp = account_number/pow(10,number_account_of_digits-1);
    return temp>0 && temp<10;
}
bool Valid_Password(const int password){
    int password_of_digits = 6;
    int temp = password/pow(10,password_of_digits-1);
    return temp>0 && temp<10;
}
bool Check(long long account[], int password[],UserAccount useraccount,int & index,int size){
	for(int i=1;i<=size;i++)
		if(useraccount.account_number == account[i])
		{
			index=i;
			if(useraccount.password == password[i])	return true;
			break;
		}
	return false;
}
int  Option(){
	int option;
	cout<<endl;
	cout<<"+----------------------------------MENU------------------------------------+"<<endl;
	cout<<"'                             1. Wirhdraw.                                 '"<<endl;
	cout<<"'                             2. Recharge.                                 '"<<endl;
	cout<<"'                             3. View Account.                             '"<<endl;
	cout<<"'                             4. Change Password.                          '"<<endl;
	cout<<"'                             5. Exit.                                     '"<<endl;
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<"Please enter your option: ";
	cin>>option;
	while (option > 5)
	{
		cout<<"Your selection is not valid !!!"<<endl<<endl;
		cout<<"Please re-enter your option: ";
		cin>>option;
	}
	return option;
}
int  Deal(long long account[],int password[],long long money[],int lock[],int size,int index,int option){
	switch (option)
	{
		case 1:{
			int withdraw=WithDraw(money,index);
			UpDateFile(lock,account,password,money,size);
			Transaction_History(account,option,index,0);
			break;
		}
		case 2:{
			int recharge=Recharge(money,index);
			UpDateFile(lock,account,password,money,size);
			Transaction_History(account,option,index,0);
			break;
		}
		case 3:{
			ViewAccount(money,index);
			Transaction_History(account,option,index,0);
			break;
		}
		case 4:{
			ChangePassword(password,index,size);
			UpDateFile(lock,account,password,money,size);
			Transaction_History(account,option,index,0);
			break;
		}
		case 5:	return 0;
	}
	return 1;
}
int  Question(){
	int option;
	cout<<"Do you want to transact  ?"<<endl;
	cout<<"1. YES"<<endl;
	cout<<"2. NO"<<endl;
	cout<<"Please enter your option : ";
	cin>>option;
	if(option==1) return 1;
	return 0;
}
int  WithDraw(long long money[],int index){
	int withdraw;
	cout<<"The amount you want to withdraw : ";
	cin>>withdraw;
	if(withdraw > money[index]) cout<<"Your money is not enough to make this transaction"<<endl;
	else
	{
		cout<<"Successful transaction !!!"<<endl;
		money[index]-=withdraw;
	}
	cout<<"Please press enter to continue ..."<<endl;
	getch();
	system("cls");
	return withdraw;
}
int  Recharge(long long money[],int index){
	int recharge;
	cout<<"The amount you want to recharge : ";
	cin>>recharge;
	cout<<"Successful transaction !!!"<<endl;
	money[index]+=recharge;
	cout<<"Please press enter to continue ..."<<endl;
	getch();
	system("cls");
	return recharge;
}
void ViewAccount(long long money[],int index){
	cout<<"Your money : "<<money[index]<<endl;
	cout<<"Please press enter to continue ..."<<endl;
	getch();
	system("cls");
}
void ChangePassword(int password[],int index,int size){
	int old_password,new_password;
	cout<<"Please enter your old password : ";
	cin>>old_password;
	bool status = false;
	while(!status)
	{
		if(Valid_Password(old_password))
		{

			for(int i=1;i<=size;i++)
				if(old_password == password[i])
				{
						status = true;
						break;
				}
			if(status ==  false)
			{
				cout<<"Your password is wrong !!!"<<endl;
				cout<<"Please re-enter your password : ";
				cin>>old_password;
				cout<<endl;
			}
		}
		else
		{
			cout<<"This password is invalid !!!"<<endl;
			cout<<"Please re-enter your old password : ";
			cin>>old_password;
			cout<<endl;
		}
	}
	status = false;
	cout<<"Please enter your new password : ";
	cin>>new_password;
	while(!status)
	{
		if(Valid_Password(new_password))
		{
			password[index] = new_password;
			status = true;
		}
		else
		{
			cout<<"This password is invalid !!!"<<endl;
			cout<<"Please re-enter your new password : ";
			cin>>new_password;
			cout<<endl;
		} 
	}
}
void DinhDangThoiGian(int a,string &s){
	s+=(a/10)+'0';
	s+=(a%10)+'0';
}
void LayThoiGian(int &year,string &month,string &day,string &hour,string &minite){

	time_t now = time(0);
   	tm *ltm = localtime(&now);

  	int years   = 1900 + ltm->tm_year;
   	int MONTH  = 1    + ltm->tm_mon;
   	int DAY    = ltm->tm_mday ;
   	int HOUR   = ltm->tm_hour;
   	int MINITE = ltm->tm_min ;
   	DinhDangThoiGian(MINITE,minite);
   	DinhDangThoiGian(HOUR,hour);
   	DinhDangThoiGian(DAY,day);
   	DinhDangThoiGian(MONTH,month);
}
void UpDateFile(int lock[],long long account[],int password[],long long money[],int size){
	int i=1;
	ofstream FileOut;
	FileOut.open("C:\\Users\\DELL\\OneDrive\\Desktop\\ThongTin.TXT",ios_base::out);
	while(i<=size)
	{
		FileOut<<lock[i]<<"	"<<account[i]<<"			"<<password[i]<<"			"<<money[i]<<endl;
		i++;
	}
	FileOut.close();
}
void Transaction_History(long long account[],int option,int index,int x){
	int year;
	string minite,hour,day,month;
	LayThoiGian(year,month,day,hour,minite);
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
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"View Account"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
	else if(option==4)
	{
		FileGD<<"|	"<<account[index]<<"		|	"<<hour<<":"<<minite<<" "<<day<<"/"<<month<<"/"<<year<<"	|	"<<"Change Password"<<endl;
		FileGD<<"|-------------------------------|-------------------------------|-------------------------"<<endl;
	}
}
























































