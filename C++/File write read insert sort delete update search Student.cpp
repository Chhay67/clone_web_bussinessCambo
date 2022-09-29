#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;
class student{
	private:
		char id[10];
		char name[20];
		char sex[5];
		float score;
	public:
		char *getId(){return id;}
		float getScore(){return score;}
		void getData();
		void showData();
		static void header();
};//end class
void student::header()
{
	cout<<"========================================="<<endl;
	cout<<left<<setw(10)<<"ID"<<setw(20)<<"NAME"<<setw(5)<<"SEX"<<setw(10)<<"SCORE"<<endl;
	cout<<"========================================="<<endl;
}
void student::getData()
{
	cout<<"Input ID:";
	cin.seekg(0);
	cin.get(id,10);
	strupr(id);
	cout<<"Input Name:";
	cin.seekg(0);
	cin.get(name,20);
	strupr(name);
	cout<<"Input Sex:";
	cin.seekg(0);
	cin.get(sex,5);
	strupr(sex);
	cout<<"Input Score:";
	cin>>score;
}
void student::showData()
{
	cout<<left<<setw(10)<<id<<setw(20)<<name<<setw(5)<<sex<<setw(10)<<score<<endl;
}
void Option()
{
	cout<<"========================================="<<endl;
	cout<<"Hello Wellcome To Student Managment!!!"<<endl;
	cout<<"========================================="<<endl;
	cout<<"\t\t"<<"Option"<<endl;
	cout<<"========================================="<<endl;
	cout<<"[1].Write student obj to file"<<endl;
	cout<<"[2].Read student obj from file"<<endl;
	cout<<"[3].Read only position student obj from file"<<endl;
	cout<<"[4].Insert student obj to file"<<endl;
	cout<<"[5].Update Student obj"<<endl;
	cout<<"[6].Search Student obj by ID"<<endl;
	cout<<"[7].Sort Score Student obj"<<endl;
	cout<<"[8].Delete Student obj"<<endl;
	cout<<"[9].Exit program"<<endl;
	cout<<"========================================="<<endl;
}
//-----------------------------------------------------------------------
void WriteToFile(student stu[],int n)
{
	cout<<"How many student?:";
	cin>>n;
	ofstream file("StuArrayobj.bin",ios::binary);
	if(file.fail())
	{
		cout<<"Can not create file"<<endl;
	 	exit(0);
    }
    else
    {
    	for(int i=0;i<n;i++)
   		{
    		stu[i].getData();
    		file.write((char*)(&stu[i]),sizeof(student));
    		cout<<"========================================="<<endl;
		}
	cout<<"Write data to file successfully..."<<endl;
	}
	file.close();
}
//------------------------------------------------------------------------
void ReadAndDisplay(student stu[])
{
	ifstream file("StuArrayobj.bin",ios::in|ios::binary|ios::ate);
	if(file.fail())
    {			
		cout<<"can not open file\n";
	 	exit(0);
    }
    else
    {
    	long size=file.tellg()/sizeof(student);
    	cout<<"Read student data from file"<<endl;
    	student::header();
    	file.seekg(0,ios::beg);
    	for(int i=0;i<size;i++)
    	{
    		file.read((char*)(&stu[i]),sizeof(student));
    		stu[i].showData();
		}
	cout<<"========================================="<<endl;
	}
    file.close();
}
//------------------------------------------------------------------------
void ReadDataOnly(student stu[])
{
	ifstream file("StuArrayobj.bin",ios::in|ios::binary|ios::ate);
	if(file.fail())
    {			
		cout<<"can not open file\n";
	 	exit(0);
    }
    else
    {
    	long size=file.tellg()/sizeof(student);
    	file.seekg(0,ios::beg);
    	for(int i=0;i<size;i++)
    	{
    		file.read((char*)(&stu[i]),sizeof(student));
		}
	}
	file.close();
}
	void ReadPosFormFile(student stu[])
{
	student st;
	int num;
	ifstream file("StuArrayobj.bin",ios::binary|ios::in|ios::ate);
    if(file.fail())
   	{
		cout<<"can not open file\n";
		exit(0);
	}
	else
	{
		cout<<"Which student obj you want to read?:";
    	cin>>num;
    	long size=file.tellg()/sizeof(student);
		if(num>size)
		{
			cout<<"invaild student obj"<<endl;
			cout<<"Student obj have only:"<<size<<endl;
		}
		else
		{
			file.seekg((num-1)*sizeof(student),ios::beg);
			file.read((char *)(&st),sizeof(student));
			student::header();
			st.showData();
			cout<<"========================================="<<endl;
		}		
	}
	file.close();
}
//------------------------------------------------------------------------
void UpdateStuData(student stu[])
{
	int num,op,found=0;
	char update[10];
	student up;
	fstream file("StuArrayobj.bin",ios::binary|ios::in|ios::out|ios::ate);
	if(file.fail())
	{
	    cout<<"can not open file\n";
	    exit(0);
	}
	else
	{
		long size=file.tellg()/sizeof(student);
		cout<<"Which Stu obj you want to update ?.Stu obj have:"<<size<<endl;
		cout<<"[1].Update by select obj"<<endl;
		cout<<"[2].Update by ID"<<endl;
		cout<<"choose :";
		cin>>op;
		switch(op)
		{
			case 1:
				{
					cout<<"updating by select obj:";
					cin>>num;
					if(num>size)
					{
						cout<<"Invalid Stu obj"<<endl;
						cout<<"Stu obj has only:"<<size<<" obj."<<endl;
						break;
					}
					else
					{
						file.seekp((num-1)*sizeof(student),ios::beg);
    					up.getData();
						file.write((char*)(&up),sizeof(student));
						cout<<"Data Updated "<<endl; 
					}	
				};break;
			case 2:
				{
					cout<<"Input ID to Update:";
					cin.seekg(0);
					cin.get(update,10);
					strupr(update);
					file.seekg(0,ios::beg);
					for(int i=0;i<size;i++)
					{
						file.read((char*)(&stu[i]),sizeof(student));
						if(strcmp(stu[i].getId(),update)==0)
						{
							found++;
							file.seekp((i)*sizeof(student),ios::beg);
							up.getData();
							file.write((char*)(&up),sizeof(student));
							cout<<"Data Updated "<<endl; 	
						}
					}	
					if(found==0)
					{
						cout<<"Search Not Found!!!"<<endl;
					}
				};break;
				default:
					{
						cout<<"Input worng number!!!"<<endl;
					};break;
		}
	}
	file.close();
}
//-----------------------------------
void SearchStuFromFile(student stu[])
{
	int found=0;
	char search[10];
	ifstream file("StuArrayobj.bin",ios::out|ios::binary|ios::ate);
	if(file.fail())
	{
		cout<<"Can't open file!!!"<<endl;
		exit(0);
	}
	else
	{
		long size=file.tellg()/sizeof(student);
		cout<<"Which Stu obj you want to Search ?.Stu obj have:"<<size<<endl;
		cout<<"Input ID to search:";
		cin.seekg(0);
		cin.get(search,10);
		strupr(search);
		file.seekg(0,ios::beg);
		for(int i=0;i<size;i++)
		{
			file.read((char*)(&stu[i]),sizeof(student));
			if(strcmp(stu[i].getId(),search)==0)
			{
				found++;
				cout<<"Found :"<<found<<endl;
				student::header();
				stu[i].showData();
				cout<<"========================================="<<endl;
			}
		}	
		if(found==0)
		{
			cout<<"Search Not Found!!!"<<endl;
		}
	}
	file.close();
}
//----------------------------------------------------------------
void SortStuData(student stu[])
{
	student temp;
	fstream file("StuArrayobj.bin",ios::in|ios::out|ios::binary|ios::ate);
	if(file.fail())
	{
		cout<<"Can't open file "<<endl;
		exit(0);
	}
	else
	{
		long size=file.tellg()/sizeof(student);
		ReadDataOnly(stu);
		//sorting
		cout<<"Sort from higher -> lower:"<<endl;
		for(int i=0;i<size;i++)
		{
			for(int j=i+1;j<size;j++)
			{
				if(stu[i].getScore()<stu[j].getScore())
				{	
					temp=stu[i];	
					stu[i]=stu[j];
					stu[j]=temp;		
				}		
			}	
		}
		student::header();
		for(int i=0;i<size;i++)
		{
			stu[i].showData();
		}
		cout<<"========================================="<<endl;
	}
	file.close();
}
//--------------------------------------------
void InsertStuData(student stu[])
{
	student insert;
	ofstream file("StuArrayobj.bin",ios::binary|ios::app);
	if(file.fail())
	{
		cout<<"Can't open file"<<endl;
		exit(0);
	}
	else
	{
		cout<<"Inserting more Student Obj"<<endl;
		insert.getData();
		file.write((char*)(&insert),sizeof(student));
		cout<<"Insert Sucessfully..."<<endl;
	}
	file.close();
}
//-------------------------------------------------
void DeleteStuFromFile(student stu[])
{
	int found=0;
	char Delete[10];
	fstream file("StuArrayobj.bin",ios::in|ios::binary|ios::ate);
	fstream tempfile("tempfile.bin",ios::out|ios::binary|ios::ate);;
	//tempfile.open("tempfile.bin",ios::in|ios::binary|ios::ate);
	if(file.fail() && tempfile.fail())
	{
		cout<<"Can't open file!!!"<<endl;
		exit(0);
	}
	else
	{
		long size=file.tellg()/sizeof(student);
		ReadDataOnly(stu);
		cout<<"Which Student data you want to delete?"<<endl;
		cout<<"Input ID to Delete:";
		cin.seekg(0);
		cin.get(Delete,10);
		strupr(Delete);
		file.seekg(0,ios::beg);
		for(int i=0;i<size;i++)
		{
			if(strcmp(stu[i].getId(),Delete) == 0)
			{
				found++;
			}
		}
		if(found==0)
		{
			cout<<"Search to Delete not found!!!"<<endl;
		}
		else 
		{
			cout<<"Search found is:"<<found<<endl;
			for(int i=0;i<size;i++)
			{
				if(strcmp(stu[i].getId(),Delete) != 0)
				{
					tempfile.write((char*)(&stu[i]),sizeof(student));
				}
			}
			file.close();
			tempfile.close();
			remove("StuArrayobj.bin");
			rename("tempfile.bin","StuArrayobj.bin");
			cout<<"Deleted successful..."<<endl;
		}
		
	}
}
int main()
{
	int n,op;
	student stu[20];
	while(1)
	{
		system("cls");	
	Option();
		cout<<"Input Option:";
		cin>>op;
		switch(op)
		{
			case 1:WriteToFile(stu,n);break;
			case 2:ReadAndDisplay(stu);break;
			case 3:ReadPosFormFile(stu);break;
			case 4:InsertStuData(stu);break;
			case 5:UpdateStuData(stu);break;
			case 6:SearchStuFromFile(stu);break;
			case 7:SortStuData(stu);break;
			case 8:DeleteStuFromFile(stu);break;
			case 9:return 0;break;
			default:
				{
					cout<<"Input wrong number!!!"<<endl;
				}break;
		}
		cout<<"Press any key to continue..."<<endl; 
		getch();
	}
	
}
