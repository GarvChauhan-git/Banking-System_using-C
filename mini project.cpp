#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cctype>
#include<iomanip>
using namespace std;
void create_account();
void display(int);
void display_all();
void deposit_amt(int);
void withdraw_amt(int);
void balance_enq(int);
void modify_acc(int);
void delete_acc(int);
class Bank
{
  char name[50];
  int acno;
  char acty;
  int balance;
  public:
      void openaccount()
      {
         cout<<"Enter Account Holder Name:";
         cin.ignore();
         cin.getline(name,50);
         cout<<"Enter Account Number:";
         cin>>acno;
         cout<<"Enter Account Type Current(C) OR Savings(S):";
         cin>>acty;
         cout<<"Enter the amount of money you want to deposit \n A Minimum Balance Of 500Rs Is Required In Account:";
         cin>>balance;
         cout<<"Your account has been created.";
      }
      void deposit(int d)
      {
          balance=balance+d;
      }
      void withdraw(int d)
      {
          balance=balance-d;
      }
      void modify()
      {
         cout<<"Account Number:\n"<<acno;
         cout<<"Enter Modified Account Holder Name:";
         cin.ignore();
         cin.getline(name,50);
         cout<<"\nBalance:"<<balance;
         cout<<"\nEnter Modified Account Type Current(C) OR Savings(S):";
         cin>>acty;
         cout<<"\nYour account has been modified.";
      }
      void show()
      {
          cout<<"ACCOUNT HOLDER NAME:"<<name<<"  ACCOUNT NUMBER:"<<acno<<"  ACCOUNT TYPE:"<<acty<<"  BALANCE:"<<balance;
          cout<<"\n";
      }
      int retacno()
      {
          return (acno);
      }
      int retbal()
      {
          return (balance);
      }

};
int main()
{
    int ch,num;
    char choice;
    do
    {
        cout<<"MAIN MENU";
        cout<<"\n1: NEW ACCOUNT";
        cout<<"\n2: DISPLAY DETAILS OF AN ACCOUNT";
        cout<<"\n3: DISPLAY DETAILS OF ALL ACCOUNTS";
        cout<<"\n4: DEPOSIT";
        cout<<"\n5: WITHDRAW";
        cout<<"\n6: BALANCE ENQUIRY";
        cout<<"\n7: MODIFY DETAILS AN ACCOUNT";
        cout<<"\n8: CLOSE AN ACCOUNT";
        cout<<"\n9: EXIT";
        cout<<"\nSelect Your Option (1-9)";
        cin>>ch;
        switch(ch)
        {
        case 1:
            create_account();
            break;
        case 2:
            cout<<"Enter the account number:";
            cin>>num;
            display(num);
            break;
        case 3:
            display_all();
            break;
        case 4:
            cout<<"Enter the account number:";
            cin>>num;
            deposit_amt(num);
            break;
        case 5:
            cout<<"Enter the account number:";
            cin>>num;
            withdraw_amt(num);
            break;
        case 6:
            cout<<"Enter the account number:";
            cin>>num;
            balance_enq(num);
            break;
        case 7:
            cout<<"Enter the account number to be modified:";
            cin>>num;
            modify_acc(num);
            break;
        case 8:
            cout<<"Enter the account number to be closed";
            cin>>num;
            delete_acc(num);
            break;
        case 9:
            exit(0);
            break;
        }
        cout<<"Do you want to continue Y/N";
        cin>>choice;
    }while(choice == 'Y');
}
void create_account()
{
    Bank ac;
    ofstream fout;
    fout.open("mm",ios::app | ios::binary);
    ac.openaccount();
    fout.write(reinterpret_cast<char*> (&ac),sizeof(Bank));
    fout.close();
}
void display(int n)
{
    int f=0;
    Bank ac;
    ifstream fin;
    fin.open("mm",ios::in | ios::binary);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
        {
            if(ac.retacno() == n)
            {
                cout<<"\n Account Details\n";
                ac.show();
                f=1;
            }
        }
    fin.close();
    if(f == 0)
    {
        cout<<"ACCOUNT DOESNOT EXISTS ";
    }
}
void display_all()
{
     Bank ac;
    ifstream fin;
    fin.open("mm",ios::in | ios::binary);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
     cout<<"\n Account Details\n";
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
    {
       ac.show();
    }
    fin.close();
}
void balance_enq(int n)
{
    int f=0;
    Bank ac;
    ifstream fin;
    fin.open("mm",ios::in | ios::binary);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
    {
     if(ac.retacno() == n)
     {
         cout<<"Balance:"<<ac.retbal();
         f=1;
     }
    }
    fin.close();
    if(f == 0)
    {
        cout<<"ACCOUNT DOESNOT EXISTS";
    }
}
void deposit_amt(int n)
{
    int d,f=0,pos;
    Bank ac;
    fstream fin;
    fin.open("mm",ios::in | ios::binary | ios::out);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
    cout<<"Enter the amount you want to deposit";
    cin>>d;
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
    {
     if(ac.retacno() == n)
     {
         ac.deposit(d);
         cout<<"Balance:"<<ac.retbal();
         pos=(-1)*static_cast<int>(sizeof(ac));
         fin.seekp(pos,ios::cur);
         fin.write((char*)&ac,sizeof(Bank));
         cout<<"Record Updated";
         f=1;
     }
    }
    fin.close();
    if(f == 0)
    {
        cout<<"ACCOUNT DOESNOT EXISTS";
    }
}
void withdraw_amt(int n)
{
    int d,f=0,pos;
    Bank ac;
    fstream fin;
    fin.open("mm",ios::in | ios::binary | ios::out);
    if(!fin)
    {

        cout<<"File could not be opened";
        return;
    }
    cout<<"Enter the amount you want to withdraw";
    cin>>d;
    if(d>=ac.retbal())
    {
       cout<<"Withdrawal amount is more than balance in your account and A Minimum Balance Of 500Rs Is Required In Account";
    }
    else
    {
      while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
      {
       if(ac.retacno() == n)
       {
         ac.withdraw(d);
         cout<<"Balance:"<<ac.retbal();
         pos=(-1)*static_cast<int>(sizeof(ac));
         fin.seekp(pos,ios::cur);
         fin.write((char*)&ac,sizeof(Bank));
         cout<<"Record Updated";
         f=1;
       }
      }
      fin.close();
      if(f == 0)
      {
        cout<<"ACCOUNT DOESNOT EXISTS";
     }
   }
}
void modify_acc(int n)
{
    int f=0,pos;
    Bank ac;
    fstream fin;
    fin.open("mm",ios::in | ios::binary | ios::out);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
     {
       if(ac.retacno() == n)
       {
           ac.show();
           ac.modify();
           pos=(-1)*static_cast<int>(sizeof(Bank));
           fin.seekp(pos,ios::cur);
           fin.write(reinterpret_cast<char*> (&ac),sizeof(Bank));
           cout<<"Record Updated";
           f=1;
       }
     }
    fin.close();
    if(f == 0)
    {
        cout<<"ACCOUNT DOESNOT EXISTS";
    }
}
void delete_acc(int n)
{
    Bank ac;
    ifstream fin;
    ofstream fout;
    fin.open("mm",ios::in | ios::binary | ios::out);
    if(!fin)
    {
        cout<<"File could not be opened";
        return;
    }
    fout.open("temp",ios::binary | ios::out);
    fin.seekg(0,ios::beg);
    while(fin.read(reinterpret_cast<char*> (&ac),sizeof(Bank)))
    {
       if(ac.retacno() != n)
       {
           fout.write(reinterpret_cast<char*> (&ac), sizeof(Bank));
       }
    }
    fin.close();
    fout.close();
    remove("mm");
    rename("temp","mm");
    cout<<"\n\n Record Deleted";
}
