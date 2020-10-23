#include<iostream>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include <fstream>
#include<cstdlib>
#include<string>
using namespace std;
void entry_menu();
void main_menu();
class student {

    public:
        int rollno;
        char name[20];
        float marks;
        char grade;
        float percentage;
        float phy, chem, math, eng, cmp;
    void getdata()
    {
     cout << "Please Enter the Details of new Student\n\n" << endl;
     cout << "Enter the roll no of the student :" << endl; cin >> rollno;
     cout << "Enter the name of the student :" << endl; cin >> name;
     cout << "Enter the marks in physics out of 100 :" << endl; cin >> phy;
     cout << "Enter the marks in chemistry out of 100 :" << endl; cin >> chem;
     cout << "Enter the marks in Math out of 100 :" << endl; cin >> math;
     cout << "Enter the marks in English out of 100 :" << endl; cin >> eng;
     cout << "Enter the marks in Computer out of 100 :" << endl; cin >> cmp;
     cout << "Student Record Has been created" << endl;
         calculate();

    }
    void calculate()
    {
         marks = phy + chem + math + eng + cmp;
     percentage = (marks / 500) * 100;
     if(percentage >= 85)
     {
             grade = 'A';
     }
     else if (percentage<85 && percentage >= 75)
     {
             grade = 'B';

     }
     else  if (percentage<75 && percentage >= 65)
     {
             grade = 'C';
     }
     else  if (percentage<65 && percentage >= 60)
      {
          grade = 'D';
       }
     else  if (percentage<60)
          {
          grade = 'F';
       }
    }

     void showdata()
        {
        cout << "Students details are\n\n" << endl; 
        cout << "Roll no of the student :"<<rollno<<endl;
        cout << "Name of the student :"<<name<< endl;
        cout << "Marks in physics out of 100 :"<< phy << endl;
        cout << "Marks in chemistry out of 100 :" << chem << endl;
        cout << "Marks in Math out of 100 :"<< math << endl;
        cout << "Marks in English out of 100 :"<< eng << endl;
        cout << "Marks in Computer out of 100 :"<< cmp << endl;
        cout << "Marks of the student : "<< marks << endl;
        cout << "Percentage of the student : "<< percentage << endl;
        cout << "grade of the student :"<< grade << endl;
        }
        void show_tabular()
       {    
	    cout<<rollno<<"     "<<setw(25)<<" "<<name<<setw(10)<<phy<<setw(4)<<chem<<setw(4)<<math<<setw(4)
		<<eng<<setw(4)<<cmp<<setw(6)<<percentage<<setw(6)<<" "<<grade<<endl;
       }

     int retrollno()
                {
        return rollno;
                }
};
void write_record()                            //Function to write records as binary
{
	student st;
	ofstream outFile;
	outFile.open("student.txt",ios::app);
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
    cout<<"\nStudent record Has Been Created...Press any key to continue:";
	cin.ignore();
	getch();
}
void display()                            //Function to display all saved records
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::app);
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
void search(int n)          //Function to display a specific roll no record
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::app);
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
void modify_record(int n)             //Function to modify a specific record
{
	int found=0;
	student st;
	fstream File;
	File.open("student.txt",ios::app|ios::in|ios::out);
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
void delete_record(int n)                  //function to delete a specific record
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::app);
	if(!inFile)
	{
		cout<<"File could not be open !! "<<endl;
		cout<<"Press any key to continue..";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.txt",ios::out);
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
	remove("student.txt");
	rename("Temp.txt","student.txt");
	cout<<"\n\n\tRecord Deleted .."<<endl;
	cout<<"Press any key to continue..";
	getch();
	
}	
void class_result()                          //function to display all binary records in tabular form
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::app);
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
void result_menu()
{
	int option;
	int rno;
	cout<<"RESULT MENU"<<endl;
	cout<<"01:Class Result"<<endl;
	cout<<"02:Student Report Card"<<endl;
	cout<<"03:Back to Main Menu"<<endl;
	cout<<"Enter Choice(1-3):";
	cin>>option;
	switch(option)
	{
		case 1:
	 {
	   class_result();
	   main_menu();
	   break;
	  }                        //Back to main menu
	case 2:
	{
	 cout<<"\nEnter Roll Number Of Student : ";
	 cin>>rno;
	 search(rno);
	 main_menu();
	 break;
    }
	case 3:
	{
		main_menu();
		break;
	}
	default:
		{
			cout<<"\a";
		}
    }
}
void entry_menu()
{
	  int num; 
 	  int z; 
	  cout << "ENTRY MENU" << endl;
      cout << "1. CREATE STUDENT RECORD" << endl;
      cout << "2. DISPLAY ALL STUDENTS RECORDS" << endl;
      cout << "3. Search STUDENT REOCRD " << endl;
      cout << "4. Modify STUDENT RECORD" << endl;
      cout << "5. DELETE STUDENT RECORD" << endl;
      cout << "6. BACK TO PREVIOUS MENU " << endl;
      cout<<"Enter choice:";
      cin>>z;
      switch(z)
      {
      	case 1:
      		{
      			write_record();
      			main_menu();
      			break;
      		}
      	case 2:
      		{
      			display();
      			main_menu();
      			break;
      		}
      	case 3:
      		{
      			cout<<"Please enter the roll no:";
      			cin>>num;
      			search(num);
      			main_menu();
      			break;
      			
      		}
      	case 4:
      		{
      			cout<<"Enter the roll no:";
      			cin>>num;
      			modify_record(num);
      			main_menu();
      			break;
      		}
      	case 5:
      		{
      			cout<<"Enter the roll no:";
      			cin>>num;
      			delete_record(num);
      		    main_menu();
      		    break;
      		}
      	case 6:
      		{
      			main_menu();
      			break;
      		}
      		default:
      		{
      			cout<<"\a";
      		}
      }
}

void main_menu()
{
	    int p;
	    do
	    {
	    
        cout << "MAIN MENU" << endl;
        cout << "1. RESULT MENU" << endl;
        cout << "2. Entry/edit MENU" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select your option (1-3)" << endl;
        cin>>p;
        switch(p)
        {
        	case 1:
        		{
        			result_menu();
        			break;
        			
        	    }
        case 2:
                {
        			entry_menu();
        			break;
        			
        		}
        case 3:
        		{
        			break;
        		}
        default:
        	{
        		cout<<"\a";
        	}
        }
    }while(p!=3);
}

int main()
{
	cout<<"Welcome to porn industry..Scratch your balls to continue"<<endl;
	main_menu();
}
	
