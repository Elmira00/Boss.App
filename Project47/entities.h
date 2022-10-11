#pragma once

struct CV {
	double salary;
	int experience;
	char* languages;
	char* about;
};

struct Notification {
	char* message;
	const char* date;
};

struct Worker {
	char* username;
	char* fullname;
	char* speciality;
	CV* cv;
	Notification** notifications;
	int count = 0;//notification count
};

//Advertisement -elan
struct AD {
	int id = 0;
	char* title;//
	double salary;// verilen maas
	Worker** appliers;//hemen ish elanina muraciet edenler
	int app_count = 0;//muraciet edenlerin sayi
};
struct Employer {
	char* username;
	char* fullname;
	char* company;
	AD** ads;//ishcinin paylashdigi  elanlar
	int count = 0; //ishcinin paylashdigi  elanlar sayi
};
#pragma once
