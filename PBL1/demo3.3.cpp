#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

typedef struct UserAccount
{
    long long account_number;
    int password;
};

void menu();
void importFile(long long account[],int password[],long long money[],int lock[],int &size);
void login(UserAccount & account,int index);

bool checkUserAccount(long long account[], int password[],UserAccount userAccount,int & index,int size);
bool validateAccountNumber(const long long account_number); 
bool validatePassword(const int password); // coi mk co dung k

int  getUserOption();
int  transaction(long long account[],int password[],long long money[],int lock[],int size,int index,int option); 
int  otherTransaction(); 
int  withdrawCash(long long money[],int index); 
int  makeDeposit(long long money[],int index); 
void viewBalance(long long money[],int index); 
void changePassword(int password[],int index,int size); 

void formatTime(int time, string &s);
void getTime(int &year,string &month,string &day,string &hour,string &minite);
void updateFile(long long account[], int password[], long long money[], int lock[], int size); 
void storeData(long long account[],int option,int index,int x); 

int main(){
	long long account[100],money[100];
	int password[100],lock[100],size,index;
	int number_of_logins=0,number_of_transactions=0,maxInput=3,option;
	UserAccount userAccount;
	
	menu();
	importFile(account,password,money,lock,size);
	
	do
	{
		login(userAccount,index);
		int check=checkUserAccount(account,password,userAccount,index,size);
		
		if(!index){
			if(!validateAccountNumber(userAccount.account_number))		cout<<"This account is invalid !!!"<<endl<<endl;
			else
			{
				cout<<"Account does not exist"<<endl;
				cout<<"Please re-enter your account and password !!!"<<endl;
			}
		}
		else if(lock[index])
		{
			cout<<"Your account has been locked !"<<endl;
			return 0;
		}
		else if(check)	break;
		else{
				number_of_logins++;
				cout<<"Your password is wrong !!!"<<endl;
				if(number_of_logins==3){
					lock[index]=1;
					cout<<"Your account has been locked !"<<endl;
				}
				cout<<"You still have the number of entries : "<<maxInput-number_of_logins<<endl<<endl;
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
			cout<<"Thank you for using our service!!!"<<endl;
			cout<<"Hope You Have A Nice Day !!!"<<endl;
			return 0;
		}
		if(number_of_transactions == 5)
		{
			cout<<"You have reached maximum transaction times for a day !!!"<<endl;
			cout<<"Thank you for using our service!!!"<<endl;
			cout<<"Hope You Have A Nice Day !!!"<<endl;
			return 0;
		}
		if(otherTransaction()==0)
		{
			cout<<"Thank you for using our service!!!"<<endl;
			cout<<"Hope You Have A Nice Day !!!"<<endl;
			return 0;
		}
	}	while(number_of_transactions<5);
	
	return 0;
}


void menu(){
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<"'                             WELCOME TO ATM DT                            '"<<endl;
	cout<<"'                       SV:   Nguyen Tran My Duyen                         '"<<endl;
	cout<<"'                             Nguyen Phuoc Dai Toan                        '"<<endl;
	cout<<"'                     GVHD:   Tran Ho Thuy Tien                            '"<<endl;
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<endl;
}
void importFile(long long account[],int password[],long long money[],int lock[],int &size){
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
	
	if(index==0)
	{
		cout<<"Account		: ";
		cin>>userAccount.account_number;
		cout<<"Password	: ";
		cin>>userAccount.password;
	}
	else 
	{
		cout<<"Password	: ";
		cin>>userAccount.password;
	}
	cout<<endl;
}

bool checkUserAccount(long long account[], int password[],UserAccount userAccount,int & index,int size){
	for(int i=1;i<=size;i++)
		if(userAccount.account_number == account[i])
		{
			index=i;
			if(userAccount.password == password[i])	return true;
			break;
		}
	return false;
}
bool validateAccountNumber(const long long account_number){
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
	cout<<"+----------------------------------MENU------------------------------------+"<<endl;
	cout<<"'                           1. Withdraw Cash.                              '"<<endl;
	cout<<"'                           2. Make Deposit.                               '"<<endl;
	cout<<"'                           3. View Balance.                               '"<<endl;
	cout<<"'                           4. Change Password.                            '"<<endl;
	cout<<"'                           5. Exit.                                       '"<<endl;
	cout<<"+--------------------------------------------------------------------------+"<<endl;
	cout<<"Please enter your choice	: ";
	cin>>option;
	while (option > 5)
	{
		cout<<"Your choice is not valid !!!"<<endl<<endl;
		cout<<"Please re-enter your choice: ";
		cin>>option;
	}
	return option;
}
int  transaction(long long account[],int password[],long long money[],int lock[],int size,int index,int option){
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
		case 5:	return 0;
	}
	return 1;
}
int  otherTransaction(){
	int option;
	cout<<"Do you want others transaction ?"<<endl;
	cout<<"1. YES"<<endl;
	cout<<"2. NO"<<endl;
	cout<<"Please enter your choice : ";
	cin>>option;
	while(option>2)
	{
		cout<<"Your choice is not valid !!!"<<endl<<endl;
		cout<<"Please re-enter your choice: ";
		cin>>option;
	}
	if(option==1) return 1;
	return 0;
}
int  withdrawCash(long long money[],int index){
	int withdraw;
	cout<<"The amount you want to withdraw : ";
	cin>>withdraw;
	if(withdraw > money[index]) cout<<"Your money is not enough to make this transaction !"<<endl;
	else
	{
		cout<<"Successful transaction !!!"<<endl;
		money[index]-=withdraw;
	}
	cout<<"Please press enter to continue ..."<<endl;
	getch();
	return withdraw;
}
int  makeDeposit(long long money[],int index){
	int deposit;
	cout<<"The amount you want to deposit	: ";
	cin>>deposit;
	cout<<"Successful transaction !!!"<<endl;
	money[index]+=deposit;
	cout<<"Please press enter to continue ..."<<endl;
	getch();
	return deposit;
}
void viewBalance(long long money[],int index){
	cout<<"Your money 			: "<<money[index]<<endl;
	cout<<"Please press enter to continue ..."<<endl;
	getch();
}
void changePassword(int password[],int index,int size){
	int old_password,new_password;
	cout<<"Please enter your old password	: ";
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
				cout<<"Your password is wrong !!!"<<endl;
				cout<<"Please re-enter your password	: ";
				cin>>old_password;
				cout<<endl;
			}
		}
		else
		{
			cout<<"This password is invalid !!!"<<endl;
			cout<<"Please re-enter your password	: ";
			cin>>old_password;
			cout<<endl;
		}
	}
	status = false;
	cout<<"Please enter your new password	: ";
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
			cout<<"This password is invalid !!!"<<endl;
			cout<<"Please re-enter your new password : ";
			cin>>new_password;
			cout<<endl;
		} 
	}
	cout<<"Please press enter to continue ..."<<endl;	
	getch();
}


void formatTime(int time, string &s){
	s += (time/10) + '0';
	s += (time % 10) + '0';
}
void getTime(int &years,string &month,string &day,string &hour,string &minite){

	time_t now = time(0);
   	tm *ltm = localtime(&now);

  	int year   = 1900 + ltm->tm_year;
   	int MONTH  = 1    + ltm->tm_mon;
   	int DAY    = ltm->tm_mday ;
   	int HOUR   = ltm->tm_hour;
   	int MINITE = ltm->tm_min ;
 	years = year;
   	formatTime(MINITE,minite);
   	formatTime(HOUR,hour);
   	formatTime(DAY,day);
   	formatTime(MONTH,month);
}
void updateFile(long long account[], int password[], long long money[], int lock[], int size){
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
void storeData(long long account[],int option,int index,int x){
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



