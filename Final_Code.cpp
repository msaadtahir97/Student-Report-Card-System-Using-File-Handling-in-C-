#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
void main_menu();                                     //Prototype for Main Menu
class student{                                        //Student Class
	public:
		int rollno;
		char name[20];
		int eng,chem,phys,maths,cs;
		char grade;
		float percent; 
		void getdata()                                          //Function to get data
		{
			cout<<"Enter The roll number of student:";
	        cin>>rollno;
	        cout<<"Enter The Name of student:";
	        cin>>name;
	        cout<<"Enter The marks in physics out of 100 : ";
	        cin>>phys;
	        cout<<"Enter The marks in chemistry out of 100 : ";
	        cin>>chem;
	        cout<<"Enter The marks in maths out of 100 : ";
	        cin>>maths;
	        cout<<"Enter The marks in english out of 100 : ";
	        cin>>eng;
	        cout<<"Enter The marks in computer science out of 100 : ";
	        cin>>cs;
	        calculate();
		}
		void calculate()                                         //Function to calculate percentage and grade
		{
			percent=(phys+chem+eng+maths+cs)/5;
			if(percent>=85)
			{
			 grade='A';
			}
	        else if(percent>=70)
			{
	         grade='B';
	        }
	        else if(percent>=60)
		    {
		     grade='C';
		    }
	        else
		    {  
		     grade='F';
		    }
	    }
		void showdata()                                         //Function to show data
		{
			cout<<"Roll number of student : "<<rollno<<endl;
	        cout<<"Name of student : "<<name<<endl;
	        cout<<"Marks in Physics : "<<phys<<endl;
	        cout<<"Marks in Chemistry : "<<chem<<endl;
         	cout<<"Marks in Maths : "<<maths<<endl;
        	cout<<"Marks in English : "<<eng<<endl;
	        cout<<"Marks in Computer Science :"<<cs<<endl;
         	cout<<"Percentage of student is  :"<<percent<<endl;
	        cout<<"Grade of student is :"<<grade<<endl;
		}
		void show_tabular()
		{
			cout<<rollno<<setw(6)<<"         "<<name<<setw(10)<<phys<<setw(4)<<chem<<setw(4)<<maths<<setw(4)
		<<eng<<setw(4)<<cs<<setw(6)<<" "<<percent<<setw(6)<<" "<<grade<<endl;
        } 
		
		int retrollno()
		{
				return rollno;

		}
};
void write_student()                            //Function to write records as binary
{
	student st;
	ofstream outFile;
	outFile.open("student.txt");
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
    cout<<"\nStudent record Has Been Created...Press any key to continue:";
	cin.ignore();
	getch();
}
void display_all()                            //Function to display all saved records
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cout<<"Press any key to continue..";
	getch();
}	
void display_sp(int n)          //Function to display a specific roll no record
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!"<<endl;
		cout<<"Press any key to continue..";
		getch();
		return;
	}

	int flag=0;
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()==n)
		{
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nrecord not exist";
		cout<<"Press any key to continue...";
	    getch();
	
}	
void modify_student(int n)             //Function to modify a specific record
{
	int found=0;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!"<<endl;
		cout<<"Press any key to continue..";
		getch();
		return;
	}
	while(File.read((char *) &st, sizeof(student)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*sizeof(st);
		    	File.seekp(pos,ios::cur);
		    	File.write((char *) &st, sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found "<<endl;
		cout<<"Press any key to continue..";
	getch();
}	
void delete_student(int n)                  //function to delete a specific record
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! "<<endl;
		cout<<"Press any key to continue..";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char *) &st, sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted .."<<endl;
	cout<<"Press any key to continue..";
	getch();
	
}	
void class_result()                          //function to display all binary records in tabular form
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"===================================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS     %age          Grade"<<endl;
	cout<<"===================================================================\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.show_tabular();
	}
	cout<<endl<<"Press any key to continue..";
	getch();
	inFile.close();
}	
void result()                                     //Function for result menu
{
	int option;
	int rno;
	cout<<"RESULT MENU"<<endl;
	cout<<"01:Class Result"<<endl;
	cout<<"02:Student Report Card"<<endl;
	cout<<"03:Back to Main Menu"<<endl;
	cout<<"Enter Choice(1-3):";
	cin>>option;
	if(option==1)
	{
	 class_result();
	 main_menu();                        //Back to main menu
	}
	if(option==2)
	{
	 cout<<"\nEnter Roll Number Of Student : ";
	 cin>>rno;
	 display_sp(rno);
	 main_menu();
    }
	if(option==3)
	{
		main_menu();
	}
	else
	{
		cout<<"Wrong choice..Select again:";
		main_menu();
	}
}	
void intro()                                    //Function to Intro menu
{
	cout<<"Welcome to Student Report Card Database"<<endl;
	cout<<"Project Submitted By: M. Saad Tahir"<<endl;
    cout<<"Press any key to continue:";
    getch();
}		
void entry_menu()                             //Functiom to entry menu
{
	int choice;
	int num;
	cout<<"\nENTRY MENU"<<endl;
	cout<<"01:CREATE STUDENT RECORD"<<endl;
	cout<<"02:DISPLAY ALL STUDENTS RECORDS"<<endl;
	cout<<"03:SEARCH STUDENT RECORD "<<endl;
	cout<<"04:MODIFY STUDENT RECORD"<<endl;
	cout<<"05:DELETE STUDENT RECORD"<<endl;
	cout<<"06:BACK TO MAIN MENU"<<endl;
	cout<<"Please Enter Your Choice(1-6):";
	cin>>choice;
	if(choice==1)
	{
	  write_student();
	  main_menu();                    //goes to main menu after writing one record
    }
	if(choice==2)
	{
	  display_all();
	  main_menu();
    }
	if(choice==3)
	{
	  cout<<"\nPlease Enter The roll number:";
	  cin>>num;
	  display_sp(num);
	  main_menu();
    }
	if(choice==4)
	{
	  cout<<"\nPlease Enter The roll number: "; 
	  cin>>num;
	  modify_student(num);
	  main_menu();
    }
	if(choice==5)
	{
	  cout<<"\nPlease Enter The roll number: ";
	  cin>>num;
	  delete_student(num);
	  main_menu();
    }
	if(choice==6)                                                 //Going Back to Main Menu Function
	{
		main_menu();
    }
	else
	{
		cout<<"Wrong Selection..Enter Again:"<<endl;            //Wrong Selection
	    entry_menu();
	}
}
void main_menu()                                                //Main Menu Function
{
	int select;
	do
	{
		
		cout<<"\nMAIN MENU\n";
		cout<<"01:RESULT MENU\n";
		cout<<"02:ENTRY/EDIT MENU\n";
		cout<<"03:EXIT\n";
		cout<<"Please Select Your Option (1-3):";
		cin>>select;
		
		if(select==1)                              //selection conditions for main menu
		{
		 result();
	    }
	    if(select==2)
	    {
	     entry_menu();
	    }
		if(select==3)
		{
			cout<<"Thanks for using me!";
			break;
		}
		else                                      //wrong selection for main menu
		{
			cout<<"Wrong choice..Select again:";
			cin>>select;
		if(select==1)
		{
		 result();
	    }
	    if(select==2)
	    {
	     entry_menu();
	    }
		if(select==3)
		{
			cout<<"Thanks for using me!";
			break;
		}	
	    }
		}while(select!='3');

}	
int main()
{
	
	cout.setf(ios::fixed|ios::showpoint);
	intro();                                           //Intro Function Called
	main_menu();
	getch();                                      //Main Menu Called
}
