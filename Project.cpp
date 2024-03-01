#include<iostream> 
#include <iomanip>
#include<fstream>       
#include<string>        
#include<stdlib.h>
#include <conio.h>

using namespace std;

int num_admins = 0;
int num_officers = 0;
int num_criminals = 0;
int num_crimes = 0;


//FUNCTIONS
void login();
void read();
bool checkadmin();
bool checkofficer();
void output_admin();
int output_officer(int);
void addcrime();
void removecrime();
void updatecrime();
void searchcrime();
void allcrime();
void searchcriminal();
void write();


//STRUCTS
struct admin_login
{
	string username;
	string password;
	string ID;
}admin[10];

struct officer_login
{
	string username;
	string password;
	string officerID;
	int num_assignedcases = 0;
	int assignedcaseid[10];
	int num_ongoingcrimes = 0;
}officer[10];

struct crimesdata {

	string crimetype;
	string crimeid;
	string criminal;
	string status;
	string date;
}crimes[10];

struct criminals {

	string name;
	string criminalid;
	int age;

}criminals[10];

int main() {

	read();
	login();

}

void read()
{
	string admin_email, admin_pass, admin_ID;
	ifstream Admin("Admin.txt");

	while ((Admin.peek()) != EOF)
	{
		getline(Admin, admin_email);
		getline(Admin, admin_pass);
		getline(Admin, admin_ID);

		admin[num_admins].username = admin_email;
		admin[num_admins].password = admin_pass;
		admin[num_admins].ID = admin_ID;

		num_admins++;
	}
	Admin.close();


	string officer_email, officer_pass, officer_id, number_assignedcases1, crime_ID, number_ongoing, assignedcaseid;
	ifstream Officer("Officer.txt");

	while (Officer.peek() != EOF)
	{
		getline(Officer, officer_email);
		getline(Officer, officer_pass);
		getline(Officer, officer_id);
		getline(Officer, number_assignedcases1);



		officer[num_officers].username = officer_email;
		officer[num_officers].password = officer_pass;
		officer[num_officers].officerID = officer_id;
		officer[num_officers].num_assignedcases = stoi(number_assignedcases1);


		for (int i = 0; i < stoi(number_assignedcases1); i++)
		{
			getline(Officer, assignedcaseid);
			officer[num_officers].assignedcaseid[i] = stoi(assignedcaseid);
		}

		getline(Officer, number_ongoing);
		officer[num_officers].num_ongoingcrimes = stoi(number_ongoing);
		num_officers++;
	}
	Officer.close();

	string crimetype1, criminal1, date1, crimetype, criminal, date, status1, status, crimeid, crimeid1;
	ifstream Crime("Crime.txt");

	while (Crime.peek() != EOF)
	{
		getline(Crime, crimeid1);
		getline(Crime, crimetype1);
		getline(Crime, status1);
		getline(Crime, criminal1);
		getline(Crime, date1);


		crimes[num_crimes].crimetype = crimetype1;
		crimes[num_crimes].crimeid = crimeid1;
		crimes[num_crimes].status = status1;
		crimes[num_crimes].criminal = criminal1;
		crimes[num_crimes].date = date1;

		num_crimes++;
	}
	Crime.close();

	string criminalname, criminalname1, age1, criminalid1, criminalid;
	int age;
	ifstream Criminal("Criminal.txt");

	while (Criminal.peek() != EOF)
	{
		getline(Criminal, criminalid1);
		getline(Criminal, criminalname1);
		getline(Criminal, age1);

		criminals[num_criminals].criminalid = criminalid1;
		criminals[num_criminals].name = criminalname1;
		criminals[num_criminals].age = stoi(age1);


		num_criminals++;
	}
	Criminal.close();
}




void login() {

	int c;

	cout << "\n\n\n\n\t\t\t\t*** WELCOME TO CRIMINAL INVESTIGATION PROGRAM!***" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "    If you want to login as Admin press 1" << endl;
	cout << "    If you want to login as Officer press 2" << endl << endl << endl;
	cout << "    Enter your choice: ";
	cin >> c;

	if(c != 1 && c != 2) {
		cout << "  Incorrect choice please choose again!" << endl;
		cout << "  Enter your choice: ";
		cin >> c;
	}
	
	if (c == 1) {
		bool verify = checkadmin();
		if (verify == true) {
			output_admin();
		}

	}
	else {
		bool verify = checkofficer();

	}
}



bool checkadmin() {
	bool verify = false;
	string user, pass;

	cout << "\n\n\n\n\n\t\t\t\t  ENTER USERNAME: ";
	cin >> user;
	cout << endl;
	cout << "\n\n\t\t\t\t  ENTER PASSWORD: ";
	cin >> pass;

	for (int i = 0; i < 10; i++)
	{
		if ((user == admin[i].username) && (pass == admin[i].password))
		{
			output_admin();
			verify = true;
			break;
		}
	}

	if (verify == false)
	{
		cout << " Invalid username or password!" << endl;
		cout << endl;
		cout << "Try again" << endl;
		checkadmin();
	}
	return verify;
}


bool checkofficer() {

	bool verify = false;
	int index;
	string user, pass;

	cout << "\n\n\n\n\n\t\t\t\t  ENTER USERNAME: ";
	cin >> user;
	cout << endl;
	cout << "\n\n\t\t\t\t  ENTER PASSWORD: ";
	cin >> pass;
	for (int i = 0; i < 10; i++)
	{
		if ((user == officer[i].username) && (pass == officer[i].password))
		{
			index = i;
			output_officer(index);
			verify = true;
			break;
		}
	}

	if (verify == false)
	{
		cout << " Invalid username or password!" << endl;
		cout << "Try again" << endl;
		checkofficer();
	}
	return verify;
}


void output_admin() {

	int c;
	system("cls");
	cout << "\n\n\n\n\t\t\t\t\t\t*** WELCOME ***" << endl;
	cout << "\t\t\t\t\tLogged in successfully as ADMIN!" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	do {
		cout << "  CHOOSE ONE OF THE FOLLOWING: " << "  \n\n  [1] Add new crime/criminal"
			<< "  \n\n  [2] Delete crime/criminal" << " \n\n  [3] Search for a crime" << "  \n\n  [4] Search for a criminal"
			<< "  \n\n  [5] Check all crimes/criminals" << "\n\n  [6] Update any data" << "  \n\n  [7] Exit" << endl;
		cout << "\n  ENTER YOUR CHOICE: ";
		cin >> c;


		switch (c) {
		case 1: addcrime(); break;
		case 2: removecrime(); break;
		case 3:searchcrime(); break;
		case 4:searchcriminal(); break;
		case 5: allcrime(); break;
		case 6: updatecrime(); break;
		case 7:
		{
			write();
			cout << "\n\n\t\t\t\t\t***Thank you!***"; 
			break;
		}

		default:
		{
			cout << endl;
			cout << "Invalid option" << endl;
			output_admin();
			break;
		}
		}

	} while (c != 7);
}


void addcrime() {

	int c;
	char c2;
	bool verified;
	do {
		system("cls");
		cout << "\n\n\n  To add new Crime please enter 1\n\n\n  To add new criminal please enter 2\n" << endl;
		cout << "  Enter your choice: "; cin >> c;
		if (c != 1 && c != 2) {
			cout << "Invalid choice please choose again!" << endl;
			cout << "Enter your choice: "; cin >> c;
		}
		system("cls");
		if (c == 1) {
			cout << "\n\n\n\n  Enter crime ID: "; cin >> crimes[num_crimes].crimeid;
			cout << "  Enter crime type: "; cin >> crimes[num_crimes].crimetype;
			cout << "  Enter crime status: "; cin >> crimes[num_crimes].status;
			cout << "  Enter criminal name: "; cin >> crimes[num_crimes].criminal;
			cout << "  Enter crime date: "; cin >> crimes[num_crimes].date;
			num_crimes++;
		}
		else {
			cout << "  Enter Criminal ID: "; cin >> criminals[num_criminals].criminalid;
			cout << endl;
			cout << "  Enter Criminal name: "; cin >> criminals[num_criminals].name;
			cout << endl;
			cout << "  Enter Criminal age: "; cin >> criminals[num_criminals].age;
			num_criminals++;
		}
		system("cls");
		cout << "\n\n\n  If you want to add new Crime/Criminal enter Y \n\n  If you want to exit enter N" << endl;
		cout << "\n\n\n  ENTER YOUR CHOICE: "; cin >> c2;
		if (c2 == 'Y' || c2 == 'y') {
			verified = true;
		}
		else if (c2 == 'N' || c2 == 'n') {
			system("cls");
			cout << "\n\n\n\t\t\tYour data has been added!" << endl;
			verified = false;
		}
	} while (verified);


}


void removecrime() {

	int c;
	bool verify;
	char c2;
	do {
		system("cls");
		cout << "\n\n  TO REMOVE CRIME ENTER 1\n\n  TO REMOVE CRIMINAL ENTER 2" << endl;
		cout << endl;
		cout << "\n  Enter your choice: "; cin >> c; cout << endl;
		if (c != 1 && c != 2) {
			cout << "INVALID CHOICE, Please choose again!";
			removecrime();
		}
		if (c == 1) {
			string search;
			int searchi = -1;
			system("cls");
			cout << "\n\n  PLEASE ENTER CRIME ID: "; cin >> search; cout << endl;

			for (int i = 0; i < num_crimes; i++) {
				if (search == crimes[i].crimeid)
				{
					searchi = i;
				}
			}
			if (searchi == -1)
			{
				cout << "Invalid Crime ID" << endl;
			}
			else {
				for (int i = searchi; i < num_crimes - 1; i++)
				{
					crimes[i].crimeid = crimes[i + 1].crimeid;
					crimes[i].crimetype = crimes[i + 1].crimetype;
					crimes[i].status = crimes[i + 1].status;
					crimes[i].criminal = crimes[i + 1].criminal;
					crimes[i].date = crimes[i + 1].date;
				}
				
				cout << "\n\n   Crime removed successfully";
				num_crimes--;
			}

		}
		else {
			string search;
			int searchi = -1;
			system("cls");
			cout << "\n\n  PLEASE ENTER CRIMINAL ID: "; cin >> search; cout << endl;

			for (int i = 0; i < num_crimes; i++) {
				if (search == criminals[i].criminalid)
				{
					searchi = i;
				}
			}
			if (searchi == -1)
			{
				cout << "  Invalid Criminal ID" << endl;
			}
			else {
				for (int i = searchi; i < num_crimes - 1; i++)
				{
					criminals[i].criminalid = criminals[i + 1].criminalid;
					criminals[i].name = criminals[i + 1].name;
					criminals[i].age = criminals[i + 1].age;
				}

				cout << "\n\n\n    Criminal removed successfully";
				num_criminals--;
			}
		}
		system("cls");
		cout << "\n\n\n   Would you like to remove another crime/criminal?\n\n   If Yes enter Y\n\n   If No enter N" << endl;
		cout << "\n\n\n\n   Enter your choice: "; cin >> c2;

		if (c2 == 'n' || c2 == 'N') {
			system("cls");
			cout << "\n\n\n\n\t\t\tData has been modified!";
			verify = false;
		}
		else if (c2 == 'y' || c2 == 'Y') {
			verify = true;
		}
	} while (verify);
}

 
void searchcrime() {
	string search;
	int searchi = -1;
	int c;
	char c2;
	bool verify;
	do {
		system("cls");
		string search;
		int searchi = -1;
		system("cls");
		cout << "\n\n\n  PLEASE ENTER CRIME ID: "; cin >> search; cout << endl;
		for (int i = 0; i < num_crimes; i++) {
			if (search == crimes[i].crimeid)
			{
				searchi = i;
			}
		}
		if (searchi == -1)
		{
			cout << "  Invalid Crime ID" << endl;
		}
		else {
			cout << "\n\n  Crime data: \n\n" << "  ID: " << crimes[searchi].crimeid << "\n" << "  TYPE: " << crimes[searchi].crimetype << "\n" << "  Criminal name : "
				<< crimes[searchi].criminal << "\n" << "  STATUS: " << crimes[searchi].status << "\n" << "  DATE: " << crimes[searchi].date << endl;

		}
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;

		cout << " Would you like to search another crime?\n\n  If Yes enter Y\n\n  If No enter N" << endl;
		cout << "\n\n Enter your choice: "; cin >> c2;

		if (c2 == 'n' || c2 == 'N') {
			system("cls");
			cout << "Data has been modified";
			verify = false;
		}
		else if (c2 == 'y' || c2 == 'Y') {
			verify = true;
		}

	} while (verify);

}

 
void searchcriminal() {


	string search;
	int searchi = -1;
	bool verify;
	char c2;
	do {
		system("cls");
		cout << "\n\n\n  PLEASE ENTER CRIMINAL ID: "; cin >> search; cout << endl;
		for (int i = 0; i < num_criminals; i++) {
			if (search == criminals[i].criminalid)
			{
				searchi = i;
			}
		}
		if (searchi == -1)
		{
			cout << "  Invalid ID of criminal" << endl;
		}
		else {
			cout << "\n\n  Criminal data: \n\n" << "ID: " << criminals[searchi].criminalid << "\n" << "  NAME: " << criminals[searchi].name << "\n" << "  AGE : "
				<< criminals[searchi].age << endl;

		}

		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;

		cout << "  Would you like to search another crime?\n\n  If Yes enter Y\n\n  If No enter N" << endl;
		cout << "\n\n Enter your choice: "; cin >> c2;

		if (c2 == 'n' || c2 == 'N') {
			system("cls");
			cout << "Data has been modified";
			verify = false;
		}
		else if (c2 == 'y' || c2 == 'Y') {
			verify = true;
		}
	} while (verify);
}


void allcrime() {

	for (int i = 0; i < num_crimes; i++) {
		cout << right <<  setw(10) << "ID: " << crimes[i].crimeid;
		cout << right << setw(10) << "TYPE: " << crimes[i].crimetype;
		cout << right << setw(20) << "CRIMINAL: " << crimes[i].criminal;
		cout << right <<  setw(10) << "STATUS: " << crimes[i].status;
		cout << right << setw(10) << "DATE: " << crimes[i].date << endl;
	
	}
	cout << endl;
	cout << endl;
}


void updatecrime() {

	string search;
	int searchi = -1;
	string newcrimetype, newstatus, newcriminal, newdate;

	int c;
	bool verify;
	char c2;
	do {
		cout << "\n\n\n  PLEASE ENTER CRIME ID: "; cin >> search; cout << endl;
		for (int i = 0; i < num_crimes; i++) {
			if (search == crimes[i].crimeid)
			{
				searchi = i;
			}
		}
		if (searchi == -1)
		{
			cout << "  Invalid Crime ID" << endl;
		}
		else {
			cout << "\n  [1] Change crime type\n\n" << "  [2]Status\n\n" << "  [3]Criminal\n\n" << "  [4]Date\n\n" << endl;
			cout << "\n  Enter your choice: "; cin >> c;

			switch (c) {
			case 1:
			{
				cout << "\n\n  Enter new crime type: "; cin >> newcrimetype; cout << endl;
				crimes[searchi].crimetype = newcrimetype;
				cout << "\t\tData has been modified successfully!" << endl;
				break;
			}
			case 2:
			{
				cout << "\n\n  Enter new crime status: "; cin >> newstatus; cout << endl;
				crimes[searchi].status = newstatus;
				cout << "\t\tData has been modified successfully!" << endl;
				break;
			}

			case 3:
			{
				cout << "\n\n  Enter new crime criminal: "; cin >> newcriminal; cout << endl;
				crimes[searchi].criminal = newcriminal;
				cout << "\t\tData has been modified successfully!" << endl;
				break;
			}
			case 4:
			{
				cout << "\n\n  Enter new crime date: "; cin >> newdate; cout << endl;
				crimes[searchi].date = newdate;
				cout << "\t\tData has been modified successfully!" << endl;
				break;
			}

			default:
			{
				cout << "Invalid choice" << endl;
				cout << "[1] Change crime type\n\n" << "[2]Status\n\n" << "[3]Criminal\n\n" << "[4]Date\n\n" << endl;
				cout << "Enter your choice: "; cin >> c;
				break;
			}

			}
		}

		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;

		cout << "\n  Would you like to edit another crime?\n\n  If Yes enter Y\n\n  If No enter N" << endl;
		cout << "\n\n  Enter your choice: "; cin >> c2;

		if (c2 == 'n' || c2 == 'N') {
			system("cls");
			cout << "\n\n\n\t\tData has been modified!";
			verify = false;
		}
		else if (c2 == 'y' || c2 == 'Y') {
			verify = true;
		}
	} while (verify);
}




int output_officer(int index) {

	int index1 = index;
	int c;
	do {
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\t\t*** WELCOME ***" << endl;
		cout << "\t\t\t\t\tLogged in successfully as OFFICER!" << endl;
		cout << endl;
		cout << " CHOOSE ONE OF THE FOLLOWING: " << "\n\n [1] Check assigned cases"
			<< "\n\n [2] Update status" << "\n\n [3] Exit" << endl;
		cout << "\n ENTER YOUR CHOICE: ";
		cin >> c;
		if (c < 1 || c>3) {
			cout << "Incorrect choice please choice from the following only :" << "\n [1] Check assigned cases"
				<< "\n [2] Update status" << "\n [3] Exit" << endl;
		}
		else {
			switch (c) {
			case 1: {
				if (officer[index1].num_assignedcases == 0)
				{
					cout << "  No Assigned Cases\n\n";
					break;
				}
				else
				{

					for (int i = 0; i < officer[index1].num_assignedcases; i++) {
						cout << "Crime ID: " << officer[index1].assignedcaseid[i];
						cout << endl;
						system("pause");
					}
				}
				break;
			}
			case 2: {
				updatecrime();
				break;
			}
			case 3: {
				write();
				cout << "THANK YOU!";
				break;
			}
			default: {
				cout << "INCORRECT CHOICE, PLEASE TRY AGAIN!" << endl;
				output_officer(index);
			}
				   break;


			}
		}
	} while (c != 3);
	return 0;
}


void write() {

	ofstream Admin("Admin.txt", std::ofstream::trunc); //delete
	Admin.close();

	ifstream Admininput;
	ofstream Adminoutput;

	Admininput.open("Admin.txt");
	Adminoutput.open("Admin.txt", ios::app); //add

	if (Admininput.is_open())
	{
		for (int i = 0; i < num_admins; i++)
		{
			Adminoutput << admin[i].username << endl;
			Adminoutput << admin[i].password << endl;
			Adminoutput << admin[i].ID << endl;
		}
	}


	ofstream Crime("Crime.txt", std::ofstream::trunc);
	Crime.close();

	ifstream Crimeinput;
	ofstream Crimeoutput;

	Crimeinput.open("Crime.txt");
	Crimeoutput.open("Crime.txt", ios::app); //add

	if (Crimeinput.is_open())
	{
		for (int i = 0; i < num_crimes; i++)
		{
			Crimeoutput << crimes[i].crimeid << endl;
			Crimeoutput << crimes[i].crimetype << endl;
			Crimeoutput << crimes[i].status << endl;
			Crimeoutput << crimes[i].criminal << endl;
			Crimeoutput << crimes[i].date << endl;

		}
	}

	ofstream Criminal("Criminal.txt", std::ofstream::trunc);
	Criminal.close();

	ifstream Criminalinput;
	ofstream Criminaloutput;

	Criminalinput.open("Criminal.txt");
	Criminaloutput.open("Criminal.txt", ios::app); //add

	if (Criminalinput.is_open())
	{
		for (int i = 0; i < num_criminals; i++)
		{
			Criminaloutput << criminals[i].name << endl;
			Criminaloutput << criminals[i].criminalid << endl;
			Criminaloutput << criminals[i].age << endl;

		}
	}
}