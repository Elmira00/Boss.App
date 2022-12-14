#pragma once

#include<iostream>
#include "Entities.h"
#include<Windows.h>
using namespace std;
void ShowIntro();
void Start() {
	while (true)
	{
		ShowIntro();
		system("cls");
	}
}

void mysetcolor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

Worker* isWorkerExist(Worker** workers, int count, const char* username) {
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(workers[i]->username, username) == 0) {
			return workers[i];
		}
	}
	return nullptr;
}

void ShowWorkerMenu(const Worker* worker) {
	cout << "Advertisements     1 : " << endl;
	cout << "Create your own CV 2 : " << endl;
	cout << "Notifications";
	mysetcolor(6, 0);
	cout << " (" << worker->count << ") ";
	mysetcolor(7, 0);
	cout << 3 << " :  " << endl;
	cout << "Observe your cv  4 : " << endl;
	cout << "Uptade your CV 5 : " << endl;
}
void DeleteNotification(int notification_index, Worker* worker) {
	auto newNotifications = new Notification * [worker->count - 1] {};
	int index = 0;
	for (size_t i = 0; i < notification_index; i++, index++) {
		newNotifications[index] = worker->notifications[i];
	}
	for (size_t i = notification_index + 1; i < worker->count; i++, index++) {
		newNotifications[index] = worker->notifications[i];
	}
	if (worker->notifications != nullptr) {
		delete[]worker->notifications;
	}
	worker->notifications = newNotifications;
	worker->count--;
	newNotifications = nullptr;
}
void ShowNotifications(Worker* worker) {
	if (worker->count == 0) {
		cout << "You do not have any notifications" << endl;
	}
	else {
		for (size_t i = 0; i < worker->count; i++)
		{
			mysetcolor(2, 0);
			cout << "Notification content : ";
			mysetcolor(7, 0);
			cout << worker->notifications[i]->message << endl;
			mysetcolor(2, 0);
			cout << "Date : ";
			mysetcolor(7, 0);
			cout << worker->notifications[i]->date << endl;

		}
		cout << endl;
	}
	system("pause");
}


void SendNotificationToApplier(Notification* notification, Worker* applier) {
	auto newnotifications = new Notification * [applier->count + 1] {};
	for (size_t i = 0; i < applier->count; i++)
	{
		newnotifications[i] = applier->notifications[i];
	}
	newnotifications[applier->count] = notification;
	applier->notifications = newnotifications;
	applier->count++;

	newnotifications = nullptr;
}

void ShowCV(const CV* cv) {
	mysetcolor(3, 0);
	cout << "CV INFO" << endl;
	mysetcolor(7, 0);
	cout << "Experience : " << cv->experience << "years" << endl;
	cout << "Salary requirement : " << cv->salary << "$" << endl;
	cout << "Languages : " << cv->languages << endl;
	cout << "About YOU : \n" << cv->about << endl;
}
bool hasCV = false;
CV* getNewCV() {
	cout << "Enter salary requirement " << endl;
	double salary = 0;
	cin >> salary;
	cout << "Enter your experience " << endl;
	int experience = 0;
	cin >> experience;
	cin.ignore();
	cin.clear();
	cout << "Enter languages skills " << endl;
	char* languages = new char[200] {};
	cin.getline(languages, 200);
	cout << "Enter about you " << endl;
	char* about = new char[250] {};
	cin.getline(about, 250);
	auto cv = new CV{ salary,experience,languages,about };
	hasCV = true;
	return cv;
}




Worker** workers = new Worker * [] {
	new Worker{ new char[] {"elvin123"},new char[] {"Elvin"},new char[] {"Programmer"},
		new CV{2000,3,new char[] {"english"},new char[] {"- Fluent in English\n- Time management"}},NULL },
		new Worker{ new char[] {"john26"},new char[] {"John"},new char[] {"Designer"},
			new CV{2000,3,new char[] {"Spanish"},new char[] {"- Fluent in Spanish\n- Time management"}},NULL }
};

Employer** employers = new Employer * [] {
	new Employer{ new char[] {"rafiq123"},new char[] {"Rafiq Eliyev"},new char[] {"Rafiq\'s MMC"},
	new AD * [] {
	new AD{1,new char[] {"C#"},5000,NULL,0},
	new AD{2,new char[] {"Python Developer"},3000,NULL,0}
	},
	2 }
};

Employer* isEmployerExist(const char* username, int count) {
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(employers[i]->username, username) == 0) {
			return employers[i];
		}
	}
	return nullptr;
}
int global_id = 2;
AD* getNewAD() {
	cin.ignore();
	cin.clear();
	cout << "Enter advertisement title" << endl;
	char* title = new char[100] {};
	cin.getline(title, 100);
	cout << "Enter max salary : " << endl;
	double salary = 0;
	cin >> salary;
	++global_id;
	AD* ad = new AD{ global_id,title,salary };
	return ad;
}

void AddADToEmployer(Employer* employer, AD* ad) {
	auto newads = new AD * [employer->count + 1] {};
	for (size_t i = 0; i < employer->count; i++)
	{
		newads[i] = employer->ads[i];
	}
	newads[employer->count] = ad;
	employer->ads = newads;
	newads = nullptr;
	employer->count++;
}

void ShowWorker(const Worker* worker);
void ShowEmployerMenu() {
	cout << "Add advertisement  1 : " << endl;
	cout << "Show appliers      2 : " << endl;
}

void ShowEmployerAds(Employer* employer) {
	for (size_t i = 0; i < employer->count; i++)
	{
		mysetcolor(6, 0);
		cout << "=========ADS===========ID : " << employer->ads[i]->id << endl;
		mysetcolor(7, 0);
		cout << "TITLE : " << employer->ads[i]->title << endl;
		cout << "SALARY : " << employer->ads[i]->salary << endl;
		for (size_t k = 0; k < employer->ads[i]->app_count; k++)//eger kimse elana muraciet edirse for ishleyir cunki count+1 olur
		{

			cout << "\t\t\t\n\n";
			mysetcolor(12, 0);
			cout << "- - -A P P L I E R S- - -\n" << endl;
			mysetcolor(7, 0);
			ShowWorker(employer->ads[i]->appliers[k]);
		}
	}
}

void ShowAllADS(Employer** employers, int e_count) {
	for (size_t i = 0; i < e_count; i++)
	{
		ShowEmployerAds(employers[i]);
	}
}

AD* getADSById(Employer** employers, int e_count, int id) {
	for (size_t i = 0; i < e_count; i++)
	{
		for (size_t k = 0; k < employers[i]->count; k++)
		{
			if (employers[i]->ads[k]->id == id) {
				return employers[i]->ads[k];
			}
		}
	}
	return nullptr;
}

void addApplierToAds(AD* ads, Worker* worker) {
	auto newappliers = new Worker * [ads->app_count + 1] {};
	for (size_t i = 0; i < ads->app_count; i++)
	{
		newappliers[i] = ads->appliers[i];
	}
	newappliers[ads->app_count] = worker;
	ads->appliers = newappliers;
	newappliers = nullptr;
	ads->app_count++;
}

void BidToAds(Employer** employers, int count, Worker* worker, int id) {
	auto ads = getADSById(employers, count, id);
	if (ads != nullptr) {
		addApplierToAds(ads, worker);
		cout << "Your BID added successfully" << endl;
	}
	else {
		cout << "Incorrect input" << endl;
	}
}

void ShowWorker(const Worker* worker) {
	mysetcolor(9, 0);
	cout << "Worker INFO" << endl;
	mysetcolor(7, 0);
	cout << "Username : " << worker->username << endl;
	cout << "Fullname : " << worker->fullname << endl;
	cout << "Specialty : " << worker->speciality << endl;
	ShowCV(worker->cv);
	cout << endl;
}

void ShowAppliersAndADS(Employer* employer) {

	/*int no = 1;
	for (size_t i = 0; i < employer->count; i++)
	{
		for (size_t k = 0; k < employer->ads[i]->app_count; k++)
		{
			cout <<"NO : "<< no++ << endl;
			ShowWorker(employer->ads[i]->appliers[k]);
		}
	}*/

}
AD* getADByName(Employer* employer, const char* username) {
	for (size_t i = 0; i < employer->count; i++)
	{
		for (size_t k = 0; k < employer->ads[i]->app_count; k++)
		{
			if (strcmp(employer->ads[i]->appliers[k]->username, username) == 0) {
				return employer->ads[i];
			}
		}
	}
	return nullptr;
}
void DeleteAds(Employer* employer, const char* username) {
	auto Ad = getADByName(employer, username);
	cout << "it is ad : " << Ad << endl;
	if (Ad != nullptr) {
		auto newads = new AD * [employer->count - 1] {};
		int index = 0;
		for (size_t i = 0; i < Ad->id - 1; i++, index++)//id 0-dan bashlamir
		{
			newads[index] = employer->ads[i];
		}
		for (size_t i = Ad->id; i < employer->count; i++, index++) {
			newads[index] = employer->ads[i];
		}
		if (employer->ads != nullptr) {
			delete[]employer->ads;
		}
		employer->ads = newads;
		newads = nullptr;
		employer->count--;
	}
}
void ShowIntro() {
	cout << "====================" << endl;
	cout << "Worker(w) or Employer(e)" << endl;
	char select = ' ';
	cin >> select;
	if (select == 'w') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username = new char[100] {};
		cin.getline(username, 100);
		auto worker = isWorkerExist(workers, 2, username);
		if (worker != nullptr) {
			ShowWorkerMenu(worker);
			int select = 0;
			cin >> select;
			if (select == 1) {
				ShowAllADS(employers, 1);
				cout << "Select ADS id for BID : " << endl;
				int id = 0;
				cin >> id;
				BidToAds(employers, 1, worker, id);
				system("pause");
			}
			else if (select == 2) {
				auto cv = getNewCV();
				worker->cv = cv;

			}
			else if (select == 3) {
				ShowNotifications(worker);
				if (worker->count != 0) {
					int index = worker->count;
					for (size_t i = 0; i < index; i++)
					{
						DeleteNotification(i, worker);
					}
				}
			}
			else if (select == 4) {
				ShowCV(worker->cv);
				system("pause");
			}
			else if (select == 5) {
				if (hasCV) {
					auto cv = getNewCV();
					if (worker->cv != nullptr) {
						delete worker->cv;
					}
					worker->cv = cv;
					mysetcolor(2, 0);
					cout << "CV updated successfully " << endl;
					mysetcolor(7, 0);
					system("pause");
				}
				else {
					mysetcolor(4, 0);
					cout << "There is no CV \nPlease create your own CV !" << endl;
					mysetcolor(7, 0);
					system("pause");
				}
			}
		}
		else {
			cout << "This user does not exist" << endl;
			Sleep(2000);
		}
	}
	else if (select == 'e') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username_employer = new char[100] {};
		cin.getline(username_employer, 100);
		auto employer = isEmployerExist(username_employer, 1);
		if (employer != nullptr) {
			ShowEmployerMenu();
			int select = 0;
			cin >> select;
			if (select == 1) {
				auto ads = getNewAD();
				AddADToEmployer(employer, ads);
			}
			else if (select == 2) {
				ShowEmployerAds(employer);
				cin.ignore();
				cin.clear();
				cout << "Enter username : " << endl;
				//IT SHOULD BE SEARCH BY NO
				char* username = new char[100] {};
				cin.getline(username, 100);
				auto applier = isWorkerExist(workers, 2, username);//2 eded workerimiz var deye count 2-dir
				if (applier != nullptr) {
					cout << "Accept [a] Reject [r]" << endl;
					char symbol = ' ';
					cin >> symbol;
					cin.ignore();
					cin.clear();
					cout << "Enter message" << endl;
					char* message = new char[100] {};
					cin.getline(message, 100);
					if (symbol == 'a') {
						auto newnotify = new Notification{ message ,__DATE__ };
						SendNotificationToApplier(newnotify, applier);
						DeleteAds(employer, username);
					}
					else if (symbol == 'r') {
						auto newnotify = new Notification{ message ,__DATE__ };
						SendNotificationToApplier(newnotify, applier);
					}

				}

			}
		}
		else {
			cout << "This employer does not exist" << endl;
		}
	}
	else {
		cout << "Incorrect input" << endl;
	}
}


//1.Notification oxunandan sonra silinsin
//2.Ishci artiq accept olunubsa hemen elan silinsin
//3.CV update etmek#pragma once
