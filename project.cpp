//Project On Bank Management
#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>


//FUNCTION THAT DISPLAYS MESSAGE AT BOTTOM OF SCREEN

void message(char mess[80])
{
gotoxy(2,2);
textcolor(BLACK);
textbackground(WHITE);
cout<<" ";
gotoxy(2,24);
clreol();
cprintf("%s",mess);
textcolor(WHITE);
textbackground(BLACK);
}


// MAIN CLASS

class account
{
int acno;
char name[50];
int deposit;
char type;
public:
void create_account();//Function to get data from user
void show_account(); //Function to show data on screen
void modify(); //Function to get new data from user
void dep(int); //Function to accept amount and add to balance amount
void draw(int); //Function to accept amount and subtract from balance
void report(); //Function to show data in tabular format
int retacno(); //Function to return account number
int retdeposit(); //Function to return balance amount
char rettype(); //Function to return type of account
};

//Function to get data from user

void account::create_account()
{
 cout<<"\t\t\tWelcome... Create your New Account \n";
 cout<<"\nEnter The account No.";
 cin>>acno;
 cout<<"\n\nEnter The Name of The account Holder : ";
 gets(name);
 cout<<"\nEnter Type of The account (C/S) : ";
 cin>>type;
 type=toupper(type);
 cout<<"\nEnter The Initial amount(>=500 for Saving an=>=1000 for current) : ";
 cin>>deposit;
 message("Account Created..");
}

//Function to show data on screen

void account::show_account()
{
 cout<<"\nAccount No. : "<<acno;
 cout<<"\nAccount Holder Name : ";
 cout<<name;
 cout<<"\nType of Account : "<<type;
 cout<<"\nBalance amount : "<<deposit;
}

//Function to get new data from user

void account::modify()
{
 cout<<"\nThe account No."<<acno;
 cout<<"\n\nEnter The Name of The account Holder : ";
 gets(name);
 cout<<"\nEnter Type of The account (C/S) : ";
 cin>>type;
 type=toupper(type);
 cout<<"\nEnter The amount : ";
 cin>>deposit;
}

//Function to accept amount and add to balance amount

void account::dep(int x)
{
 deposit+=x;
}

//Function to accept amount and subtract from balance

void account::draw(int x)
{
deposit-=x;
}

//Function to show data in tabular format

void account::report()
{
cout<<acno<<setw(10)<<" "<<name<<setw(20)<<""<<type<<setw(10)<<deposit<<endl;
}

//Function to return account number

int account::retacno()
{
return acno;
}

//Function to return balance amount

int account::retdeposit()
{
return deposit;
}

//Function to return type of account

char account::rettype()
{
return type;
}

// Function declaration

void write_account(); //function to write record in binary file
void display_sp(int); //function to display account details given by user
void modify_account(int); //function to modify record of file
void delete_account(int); //function to delete record of file
void display_all(); //function to display all account details
void deposit_withdraw(int, int); // function to deposit/withdraw amount
void intro(); //introductory screen function




// MAIN FUNCTION HAVING MAIN MENU
void main()
{
 textcolor(WHITE);
 textbackground(BLACK);
 char ch;
 int num;
 clrscr();
 gotoxy(25,5);
 cout<<"BANK MANAGMENT SYSTEM ";
 gotoxy(25,8);
 cout<<"Done by Sahil Aggarwal and Jagjot singh";
 gotoxy(25,10);
 cout<<"CLASS : XII-A";
 gotoxy(25,12);
 cout<<"Roll No. : 20 and 14 ";
 message("Press any key to continue");
 getch();

 do
 {
  clrscr();
  cout<<"\n\n\n\tMAIN MENU";
  cout<<"\n\n\t01. NEW ACCOUNT";
  cout<<"\n\n\t02. DEPOSIT AMOUNT";
  cout<<"\n\n\t03. WITHDRAW AMOUNT";
  cout<<"\n\n\t04. BALANCE ENQUIRY";
  cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
  cout<<"\n\n\t06. CLOSE AN ACCOUNT";
  cout<<"\n\n\t07. MODIFY AN ACCOUNT";
  cout<<"\n\n\t08. EXIT";
  message("Select Your Option (1-8) : ");
  cin>>ch;
  clrscr();
  switch(ch)
  {
   case '1':
   write_account();
   break;
   case '2':
   cout<<"Enter The account No. : "; cin>>num;
   deposit_withdraw(num,1);
   break;
   case '3':
   cout<<"Enter The account No. : "; cin>>num;
   deposit_withdraw(num, 2);
   break;
   case '4':
   cout<<"\n\n\tEnter The account No. : "; cin>>num;
   display_sp(num);
   break;
   case '5':
   display_all();
   break;
   case '6':
   cout<<"\n\n\tEnter The account No. : "; cin>>num;
   delete_account(num);
   break;
   case '7':
   cout<<"\n\n\tEnter The account No. : "; cin>>num;
   modify_account(num);
   break;
   case '8':
   message("Thanks for using bank managemnt system ");
   break;
   default :cout<<"\a";
  }
 getch();
 }while(ch!='8');
}

// Function to write in file

void write_account()
{
account ac;
ofstream outFile;
outFile.open("account.dat",ios::binary|ios::app);
ac.create_account();
outFile.write((char *) &ac, sizeof(account));
outFile.close();
}


// Function to read specific record from file

void display_sp(int n)
{
 account ac;
 int flag=0;
 ifstream inFile;
 inFile.open("account.dat",ios::binary);
 if(!inFile)
  {
   cout<<"File could not be open !! Press any Key...";
   return;
  }
 cout<<"\nBALANCE DETAILS\n";
 while(inFile.read((char *) &ac, sizeof(account)))
 {
  if(ac.retacno()==n)
  {
   ac.show_account();
   flag=1;
  }
}
inFile.close();
if(flag==0)
cout<<"\n\nAccount number does not exist";
}

// Function to modify record of file

void modify_account(int n)
{
int found=0;
account ac;
fstream File;
File.open("account.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
return;
}
while(File.read((char *) &ac, sizeof(account)) && found==0)
{
if(ac.retacno()==n)
{
ac.show_account();
cout<<"\n\nEnter The New Details of account"<<endl;
ac.modify();
int pos=(-1)*sizeof(account);
File.seekp(pos,ios::cur);
File.write((char *) &ac, sizeof(account));
cout<<"\n\n\t Record Updated";
found=1;
}
}
File.close();
if(found==0)

cout<<"\n\n Record Not Found ";
}

// Function to delete record of file

void delete_account(int n)
{
account ac;
ifstream inFile;
ofstream outFile;
inFile.open("account.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
return;
}
outFile.open("Temp.dat",ios::binary);
inFile.seekg(0,ios::beg);
while(inFile.read((char *) &ac, sizeof(account)))
{
if(ac.retacno()!=n)
{
outFile.write((char *) &ac, sizeof(account));
}

}
inFile.close();
outFile.close();
remove("account.dat");
rename("Temp.dat","account.dat");
cout<<"\n\n\tRecord Deleted ..";
cout<<"”\n \n \n Your account was successfully deleted”";
}

// Function to display all accounts deposit list

void display_all()
{
 account ac;
 ifstream inFile;
 inFile.open("account.dat",ios::binary);
 if(!inFile)
 {
  cout<<"File could not be open !! Press any Key...";
  return;
 }
 gotoxy(25,5);
 cout<<"ACCOUNT HOLDER LIST";
 cout<<endl;
 while(inFile.read((char *) &ac, sizeof(account)))
 {
  ac.report();
 }
 message("The Details are in the oreder : (A/c no.-NAME-Type-Balance)");
 inFile.close();
}

// function to deposit and withdraw amounts

void deposit_withdraw(int n, int option)
{
 int amt;
 int found=0;
 account ac;
 fstream File;
 File.open("account.dat", ios::binary|ios::in|ios::out);
 if(!File)
 {
  cout<<"File could not be open !! Press any Key...";
  return;
 }
 while(File.read((char *) &ac, sizeof(account)) && found==0)
 {
  if(ac.retacno()==n)
  {
   ac.show_account();
   if(option==1)
   {
    cout<<"\n\n\tTO DEPOSIT AMOUNT ";
    cout<<"\n\nEnter The amount to be deposited";
    cin>>amt;
    ac.dep(amt);
   }
   if(option==2)
   {
    cout<<"\n\n\tTO WITHDRAW AMOUNT ";
    cout<<"\n\nEnter The amount to be withdrawn.";
    cin>>amt;
    int bal=ac.retdeposit()-amt;
    if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
    {
     cout<<"Insufficient  balance";
    }
    else
    {
     ac.draw(amt);
    }
   }
   int pos=(-1)* sizeof(ac);
   File.seekp(pos,ios::cur);
   File.write((char *) &ac, sizeof(account));
   cout<<"\n\n\t Record Updated";
   found=1;
   }
 }
 File.close();
 if(found==0)
 cout<<"\n\n Record Not Found ";
}
