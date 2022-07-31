#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Student
{
private:
	string name;
	int roll;
	float english, history, geography, science, maths, average;
public:

	//This function assigns values to all fields. A function is used instead of a constructor because dynamic memory 
	//extension using vector is troublesome with constructors. Otherwise, We will have to create a parameter-less constructor.

	void InsertData(string n, int r, float eng, float his, float geo, float sci, float math)
	{
		name = n;
		roll = r;
		english = eng;
		history = his;
		geography = geo;
		science = sci;
		maths = math;

		average = (english + history + geography + science + maths) / 5;
		 char grade;
		if(average>=60)
              grade= 'A';
        else if(average>=50)
                 grade='B';
        else if(average>=33)
                 grade='C';
        else
                grade='F';
	}

	int GetRoll()
	{
		return roll;
	}

	void Report()
	{
       system("cls");
		cout << "\nSTUDENT REPORT" << endl;
		cout << "==============" << endl << endl;
		cout << "Name: " << name << endl;
		cout << "Roll: " << roll << endl;
		cout << "English Marks: " << english << endl;
		cout << "History Marks: " << history << endl;
		cout << "Geography Marks: " << geography << endl;
		cout << "Science Marks: " << science << endl;
		cout << "Maths Marks: " << maths << endl;
		cout << "Average Marks: " << average << endl;
		cout << "GPA: " << average / 10 << endl;
	}
};

 

//Vector is used instead of an array due to its flexibility in size extension

vector<Student> database;
int databaseSize;

void PrintReport(int roll)
{
	system("cls");
	for (int i = 0; i < databaseSize; i++)
		if (database[i].GetRoll() == roll)
		{
			database[i].Report();
			return;
		}

	cout << "\nTHE ENTERED ROLL(" << roll << ") DOES NOT EXIST.\n" << endl;
}

void ResizeDatabase()
{
	database.resize(databaseSize);
}

void ShowStats()
{
	system("cls");
	cout << "\nSIZE: " << databaseSize << endl;
	cout << "STUDENT LIST (ROLL): ";

	if (databaseSize == 0)
	{
		cout << "DATABASE IS EMPTY\n" << endl;
		return;
	}

	for (int i = 0; i < databaseSize; i++)
		cout << database[i].GetRoll() + " ";

	cout << "\n" << endl;
}

void Add()
{
	system("cls");
	fstream file;
	string name;
	int roll;
	float english, history, geography, science, maths;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------------- PLEASE ENTER THE DETAILS OF THE STUDENT ---------------------------------------------" << endl;
	cout << " NAME OF STUDENT: ";
	cin.ignore();
	getline(cin, name);
	cout << "ROLL NO OF STUDENT: ";
	cin >> roll;
	cout << "MARKS IN ENGLISH: ";
	cin >> english ;
	cout << "MARKS IN HISTORY: ";
	cin >>history ;
	cout << "MARKS IN GEOGRAPHY: ";
	cin >> geography ;
	cout << "MARKS IN SCIENCE: ";
	cin >>  science ;
	cout << "MARKS IN MATHS: ";
	cin >>maths ;

	
	cout << "\nSTUDENT DATA ADDED TO DATABASE" << endl;

	databaseSize++;
	ResizeDatabase();
	database[databaseSize - 1].InsertData(name, roll, english, history, geography, science, maths);
	file.open("studentRecord.txt", ios::app | ios::out);
    file << " " << name << " " << roll << " " << english << " " << history << " " <<geography << " " <<science  <<" "<<maths <<"\n";
    file.close();
}

void Delete(int roll)

{
	system("cls");
	fstream file, file1;
	int found = 0;
	string name;

	float english, history, geography, science, maths;
 
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Student Details ------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\nEnter Roll No. of Student which you want Delete Data: ";
        cin >> roll;
        file1.open("record.txt", ios::app | ios::out);
        file >> name >> roll >>english  >> history >>geography  >>science>>maths;
        while (!file.eof())
        {
            if (roll != roll)
            {
                file1 <<" " << name << " " << roll << " " << english << " " << history << " " <<geography << " " <<science  <<" "<<maths<< "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
            }
            file >> name >> roll >>english  >> history >>geography  >>science>>maths;
        }
        if (found == 0)
        {
            cout << "\n\t\t\t Student Roll NO. Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
	for (int i = 0; i < databaseSize; i++)
		if (database[i].GetRoll() == roll)
		{
			database.erase(database.begin() + i);
			cout << "\nSTUDENT WITH ROLL " << roll << " HAS BEEN REMOVED FROM THE DATABASE\n" << endl;
			databaseSize--;
			return;
		}

	cout << "\nTHE ENTERED ROLL(" << roll << ") DOES NOT EXIST.\n" << endl;
}

 
int main()
{
	cout<<"\n\n\n\n\n\n\n\n\n";
	cout<<"------------------------------------------------------------";
    cout<<"------------------------------------------------------------";
    cout<<"------------------------------------------------------------";
    cout<<"------------------------------------------------------------";
	cout<<"\t\t\t\t\t\tSTUDENT REPORT CARD PROJECT";
	cout<<"\n\n\n\tMADE BY :Elif Nur Aslihan Celepoglu";
	cout<<"\n\tSCHOOL : BEYKOZ UNIVERSITY"<<endl;
	cout<<"------------------------------------------------------------";
	cout<<"------------------------------------------------------------";
	cout<<"------------------------------------------------------------";
    cout<<"------------------------------------------------------------";
    
	cout<<" \n\n\n\t\tPress 'ENTER' to continue ";
 
	cin.get();
	system("cls");
	
	int choice, roll;

	cout << "STUDENT REPORT CARD" << endl;
	cout << "==================================" << endl;

	do
	{
		cout << "\n1. ADD NEW STUDENT \n2. DELETE STUDENT \n3. PRINT REPORT\n4. DATABASE STATS\n0. EXIT" << endl;
		cout << "YOUR CHOICE: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			Add();
			break;

		case 2:
			cout << "ROLL: ";
			cin >> roll;
			Delete(roll);
			break;

		case 3:
			cout << "ROLL: ";
			cin >> roll;
			PrintReport(roll);
			break;

		case 4:
			ShowStats();
			break;

		case 0:
			break;

		default:
			cout << "\nINVALID CHOICE\n" << endl;
			break;
		}
	} while (choice);

	return 0;
}
