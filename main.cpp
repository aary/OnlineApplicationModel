//
//  main.cpp
//  hash
//
//  Created by Aditya Sule and Aaryaman Sagar on 29/01/13.
//  Copyright (c) 2013 Sanskriti School. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <math.h>
using namespace std;


#define PRIME (23099*2 + 1)
#define PRIM_ROOT (23099) // The value is such so that the values in the program never exceed the maximum range of int
#define SYS_PASSWORD "qwerty"

enum Status {
    SUBMIT = 1,
    SAVE = 0
};
// int psi(int x);

//HEADER 1*********************************
int FastPower(int g, int A, int N);
int stringLength(const char* arr);
int Mypsi(int x);
void copy(char S1[], char S2[], int LENGTH);
void AND(char S1[], char S2[], int LENGTH);
char HexForm2(int x);
void HexForm(char arr[]);
void Mod(char S1[], char S2[], int LENGTH); // Does not append '\0' at the end of the string
void intoBinary(char arr[], int byte, int LENGTH);
//void SpecificValues(string &S1, int LENGTH, char* ptr, int phi);
void Binary(char arr[], int x, int ofLength);
//void SpecificPermute(char S1[], int LENGTH, char* ptr, int phi);
void Concat(char S1[], int Start, char S2[]);
char* Hex(char x[]);
char* HashDigest(char* arr, int lambda, int ClassSize);
void Into4BitBinary(char arr[], int x);
void XOR(char arr[], char arr2[], int LENGTH);
void Encrypt(char* ptr, char Key[], int classSize);
void Decrypt(char* ptr, char Key[], int classSize);
void Copy(char* tocopyto, char* tocopyfrom, int ClassSize);

int FastPower(int g, int A, int N) {
	int a = g, b = 1;
	for(;A > 0;) {
		if (A%2 == 1) b = (b*a)%N;
		a = (a*a)%N;
		A = A/2;
	}
	return b;
}

int Mypsi(int x, int a, int p) {
	return (FastPower(a,x,p));
}

int stringLength(const char* arr) {
    int i;
    for (i = 0; arr[i] != '\0'; i++) {}
    
    return i;
}

void copy(char S1[], char S2[], int LENGTH) {
    // Copies String S2 into S1 till length LENGTH
    
	for (int i = 0; i < LENGTH; i++)
		S1[i] = S2[i];
}

void AND(char S1[], char S2[], int LENGTH) {
    // Bitwise AND for strings
    
	for(int i = 0; i < LENGTH; i++) {
		if (S1[i] == '1' && S2[i] == '0') S1[i] = '0';
		else if (S1[i] == '1' && S2[i] == '1') S1[i] = '1';
		else if (S1[i] == '0' && S2[i] == '0') S1[i] = '1';
		else if (S1[i] == '0' && S2[i] == '1') S1[i] = '0';
	}
}

char HexForm2(int x) {
    // To convert integer into its hexadecimal character, i.e. 0123456789abcdef
    
	x += 48;
	if (x >= 58 && x <= 63) x += 39;
	
	return ( (char)x );
}

void HexForm(char arr[]) {
    // TO CONVERT STRING TO HEXADECIMAL CHARACTERS, i.e. 0123456789abcdef
    
	int LENGTH = stringLength(arr);
	for (int i = 0; i < LENGTH; i++) {
		arr[i] += 48;
		if (arr[i] >= 58 && arr[i] <= 63) arr[i] += 39;
	}
}

void Mod(char S1[], char S2[], int LENGTH) {
    // To mod the sum of each individual corresponding character strings S1 and S2 by 16 upto LENGTH-1
    
	int* S3 = new int[LENGTH];
	int* S4 = new int[LENGTH];
	for(int i = 0; i < LENGTH; i++) {
		if (S1[i] >= 48 && S1[i] <= 57) S3[i] = S1[i] - 48;
		else if (S1[i] >= 97 && S1[i] <= 102) S3[i] = S1[i] - 87;
		
		if (S2[i] >= 48 && S2[i] <= 57) S4[i] = S2[i] - 48;
		else if (S2[i] >= 97 && S2[i] <= 102) S4[i] = S2[i] - 87;
	}
    
    
	for(int i = 0; i < LENGTH; i++) {
		S3[i] = (S3[i] + S4[i]) % 16;
		S1[i] = HexForm2(S3[i]);
	}
    
	delete[] S3;
	delete[] S4;
}

void intoBinary(char arr[], int byte, int LENGTH) {
    // byte is the byte to be converted into a binary string of length LENGTH, i.e. in this case lambda*4
    // Uses Binary() function to make the pseudorandom stream into a 4 bit binary string
    // puts resultant into arr
    // Converts one byte into an entire pseudorandom binary stream of the required length by going 4 bits at a time and concatenating them.
	char temp[5];
	for(int i = 0; i < LENGTH/4; i++) {
		byte = FastPower(FastPower(PRIM_ROOT, i+1, PRIME), byte, PRIME); // Pseudorandom generator
		Into4BitBinary(temp, byte);
		Concat(arr, 4*i, temp);
	}
	arr[LENGTH] = '\0';
}

void Binary(char arr[], int x, int ofLength) {
	int remainder;
	for (int i = (ofLength - 1); i >= 0; i--) {
		remainder = x%2;
		x = x/2;
		arr[i] = remainder + 48;
	}
	arr[ofLength] = '\0'; // BECAUSE Hex() checks String Lenth and then operates!!!
}

void Concat(char S1[], int Start, char S2[]) {
    // Concatenates S1 with the values of S2 starting from index Start to 4 values after it
    
	for (int i = 0; i < 4; i++)
		S1[Start+i] = S2[i];
}

char* Hex(char x[]) {
    // Returns precise hexadecimal equivalent string of binary string x
    
    int LengthofBinary = stringLength(x), lambda;
    
    if (LengthofBinary % 4 == 0) lambda = LengthofBinary/4;
	else lambda = LengthofBinary/4 + 1;
    
    int sum = 0, k;
	char* Hexed = new char[lambda+1];
	
	for(int i = LengthofBinary - 1, j = 1; i >= 0; i = i - 4, j++) {
		sum = 0;
		for(k = 0; k < 4; k++) {
			if ( (i-k) < 0 ) break; //so that if last bit is reached the loop exits
			sum += pow(2,k) * (x[i-k] - 48);
		}
		Hexed[lambda-j] = HexForm2(sum);
	}
	
	Hexed[lambda] = '\0';
	return Hexed;
}

char* HashDigest(char* arr, int lambda, int ClassSize = 0) {
    
    /*	This Hash function converts the required value, i.e. the object of any misc data type, or a string by utilizing a pointer to the first byte of the
     data.
     It then starts converting each byte into a binary string of length lambda and then to hexadecimal form using the psi pseudorandom number generator and
     keeps modding the value to a FinalHash string which the function then returns.
     
     SECURITY depends on the security of the PRNG and the fact that you dont know what permutations took place evry time without knowing the main string
     */
    
    
	char* ptr = arr;
    int phi;
    int fordifference = FastPower(lambda,2,PRIME);
	if (ClassSize == 0)
		phi = stringLength(arr);
	else
		phi = ClassSize;
    
	char* BinaryString = new char[4*lambda + 1];
	char* Hexed;
	char* FinalHash = new char[lambda + 1];
	
	//Gives an initial value to FinalHash based on the length of the object or string being hashed
	for (int i = 0; i < lambda; i++) FinalHash[i] = '0'; //FinalHash[lambda] = '\0';
	intoBinary(BinaryString, phi, 4*lambda);
	Hexed = Hex(BinaryString);
	Mod(FinalHash, Hexed, lambda);
	delete[] Hexed;
	
	for(int i = 0; i < phi; i++) {
		// Converts the byte to binary of length 4*lambda
		intoBinary(BinaryString, *ptr + i + fordifference,4*lambda); // so thqt each ele gets a diff value on the virtue of its position and lambda
		
        //SpecificPermute(BinaryString, strlen(BinaryString), arr, strlen(arr));
		Hexed = Hex(BinaryString);
		
        //SpecificPermute(Hexed, strlen(Hexed), arr, strlen(arr));
		Mod(FinalHash, Hexed, lambda);
		ptr++;
		delete[] Hexed;
	}
	
	FinalHash[lambda] = '\0'; //To make it a readable string
	delete[] BinaryString;
	return FinalHash;
}

void Into4BitBinary(char arr[], int x) {
    // Converts an integer to a binary string of length 4 bits by XORing 4 bits at a time of the integer with each other.
    
	for(int i = 0; i < 4; i++) arr[i] = '0';
	char temparr[4];
	
	int binaryequivalent, tempx = x, noofiterations;
	for(binaryequivalent = 0; tempx != 0; binaryequivalent++) tempx = tempx/2;
	
	if (binaryequivalent%4 == 0) noofiterations = binaryequivalent/4;
	else noofiterations = binaryequivalent/4 + 1;
	
	for(int i = 0; i < noofiterations; i++) {
        // To create a 4 bit string from the current value of the integer
		for(int j = 3; j >= 0; j--) {
			if (x == 0)
				temparr[j] = '0';
			else {
				temparr[j] = x%2 + 48;
				x = x/2;
			}
		}
		XOR(arr,temparr, 4);
	}
	arr[4] = '\0';
}

void XOR(char arr[], char arr2[], int LENGTH) {
    // Computes XOR operation on arr1 and arr2
	for(int i = 0; i < LENGTH; i++) {
		if ( (arr[i] == '0' && arr2[i] == '1') || (arr[i] =='1' && arr2[i] == '0') )
			arr[i] = '1';
		else
			arr[i] = '0';
	}
}

void Encrypt(char* ptr, const char* Key, int classSize = 0) {
    // TO ENCRYPT THE CONTENTS OF AN OBJECT BITWISE USING KEY PASSWORD
    int length;
    if (classSize == 0)
        length = stringLength(ptr);
    else
        length = classSize;
    
	for (int i = 0; i < length; i++) {
		*ptr = ((*ptr + Key[i%6]) % 256) - 128; // Because range of char is -128 to 127
		ptr++;
	}
}

void Decrypt(char* ptr, const char* Key, int classSize = 0) {
    // TO DECRYPT THE CONTENTS OF AN OBJECT BITWISE USING KEY PASSWORD
    int length;
    if (classSize == 0)
        length = stringLength(ptr);
    else
        length = classSize;
    
	for (int i = 0; i < length; i++) {
		*ptr = ((*ptr - Key[i%6]) % 256) - 128; // Because range of char is -128 to 127
		ptr++;
	}
}

void Copy(char* tocopyto, char* tocopyfrom, int ClassSize) {
    // TO COPY THE CONTENTS OF "tocopyfrom" TO "tocopyto" BITWISE
	for (int i = 0; i < ClassSize; i++) {
		*tocopyto = *tocopyfrom;
		tocopyfrom++;
		tocopyto++;
	}
}

//HEADER 2*********************************
class Personal_Details {
    
public:
    int iscomplete;
    char FirstName[32];
    char LastName[32];
    char Address[256];
    char City[32];
    char State[32];
    char Country[32];
    char Email[64];
    char Phoneno[12];
};

class Family_Details {
    
public:
    int iscomplete;
    char Parent1FirstName[32];
    char Parent1LastName[32];
    char Parent1HigestDegree[256];
    char Parent1Email[64];
    char Parent1Phoneno[12];
    char Parent2FirstName[32];
    char Parent2LastName[32];
    char Parent2HigestDegree[256];
    char Parent2Email[64];
    char Parent2Phoneno[12];
};

class School_Details {
    
public:
    int iscomplete;
    char Name[32];
    char Address[256];
    char City[32];
    char State[32];
    char Country[32];
    char Phoneno[12];
};

class SchoolGrades_Details {
    
public:
    int iscomplete;
    char XSubject1Name[32];
    int XSubject1Marks;
    char XSubject2Name[32];
    int XSubject2Marks;
    char XSubject3Name[32];
    int XSubject3Marks;
    char XSubject4Name[32];
    int XSubject4Marks;
    char XSubject5Name[32];
    int XSubject5Marks;
    char XiiSubject1Name[32];
    int XiiSubject1Marks;
    char XiiSubject2Name[32];
    int XiiSubject2Marks;
    char XiiSubject3Name[32];
    int XiiSubject3Marks;
    char XiiSubject4Name[32];
    int XiiSubject4Marks;
    char XiiSubject5Name[32];
    int XiiSubject5Marks;
};

class Application {
    
public:
    Family_Details FamDet;
    School_Details SchDet;
    SchoolGrades_Details Marks;
};

class User {
    
public:
    char uName[16];
    Personal_Details PersDet;
    void changePersDetails();
    void viewPersDetails();
};

class Applicant: public User {
    
public:
    Applicant();
    int submitted;
    Application AppDet;
    void changeAppDetails();
    void viewApp();
    Status handler();
};

class Manager: public User {
    
public:
    void viewAllApps();
    void viewApp();
    void handler();
};

class Packet {
    
public:
    char PwdHash[65];
    char UsrName[16];
    void save();
    void submit();
    Applicant App;
};

class ManagerPacket {
    
public:
    char PwdHash[65];
    char UsrName[16];
    Manager App;
};

class SubmittedPacket {

public:
    Applicant App;
    char digitalSignature[65];
    SubmittedPacket();
};

void User::changePersDetails()
{
    cout << "Please Enter First Name : ";
    cin.ignore();
    cin.get(PersDet.FirstName, 32);
    cout << "Please Enter Last Name : ";
    cin.ignore();
    cin.get(PersDet.LastName, 32);
    cout << "Please Enter Address : ";
    cin.ignore();
    cin.get(PersDet.Address, 256);
    cout << "Please Enter City : ";
    cin.ignore();
    cin.get(PersDet.City, 32);
    cout << "Please Enter State : ";
    cin.ignore();
    cin.get(PersDet.State, 32);
    cout << "Please Enter Country : ";
    cin.ignore();
    cin.get(PersDet.Country, 32);
    cout << "Please Enter Email : ";
    cin.ignore();
    cin.get(PersDet.Email, 64);
    cout << "Please Enter Phone Number : ";
    cin.ignore();
    cin.get(PersDet.Phoneno, 12);
    PersDet.iscomplete = 1;
}

void User::viewPersDetails()
{
    if (PersDet.iscomplete) {
        cout << "First Name : ";
        puts(PersDet.FirstName);
        cout << "Last Name : ";
        puts(PersDet.LastName);
        cout << "Address : ";
        puts(PersDet.Address);
        cout << "City : ";
        puts(PersDet.City);
        cout << "State : ";
        puts(PersDet.State);
        cout << "Country : ";
        puts(PersDet.Country);
        cout << "Email : ";
        puts(PersDet.Email);
        cout << "Phone Number : ";
        puts(PersDet.Phoneno);
    } else {
        cout << "Personal Details section not complete" << endl;
    }
}

Applicant::Applicant() {
    submitted = 0;
}
void Applicant::changeAppDetails()
{
    cout << endl;
    int temp = 1;
    do {
        cout << endl;
        cout << "Select category" << endl;
        cout << "1) Family Details" << endl;
        cout << "2) School Details" << endl;
        cout << "3) Marks" << endl;
        cout << "0) Done!!!" << endl;
        cin >> temp;
        switch (temp) {
            case 0:
                temp = 0;
                break;
            case 1:
                cout << "Please Enter First Name of Parent 1: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent1FirstName, 32);
                cout << "Please Enter Last Name of Parent 1: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent1LastName, 32);
                cout << "Please Enter Highest Degree of Parent 1: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent1HigestDegree, 256);
                cout << "Please Enter Email of Parent 1: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent1Email, 64);
                cout << "Please Enter Phone Number of Parent 1: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent1Phoneno, 12);
                cout << "Please Enter First Name of Parent 2: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent2FirstName, 32);
                cout << "Please Enter Last Name of Parent 2: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent2LastName, 32);
                cout << "Please Enter Highest Degree of Parent 2: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent2HigestDegree, 256);
                cout << "Please Enter Email of Parent 2: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent2Email, 64);
                cout << "Please Enter Phone Number of Parent 2: ";
                cin.ignore();
                cin.get(AppDet.FamDet.Parent2Phoneno, 12);
                AppDet.FamDet.iscomplete = 1;
                break;
            case 2:
                cout << "Please Enter School Name : ";
                cin.ignore();
                cin.get(AppDet.SchDet.Name, 32);
                cout << "Please Enter Address : ";
                cin.ignore();
                cin.get(AppDet.SchDet.Address, 256);
                cout << "Please Enter School City : ";
                cin.ignore();
                cin.get(AppDet.SchDet.City, 32);
                cout << "Please Enter School State : ";
                cin.ignore();
                cin.get(AppDet.SchDet.State, 32);
                cout << "Please Enter School Country : ";
                cin.ignore();
                cin.get(AppDet.SchDet.Country, 32);
                cout << "Please Enter Phone Number : ";
                cin.ignore();
                cin.get(AppDet.SchDet.Phoneno, 12);
                AppDet.SchDet.iscomplete = 1;
                break;
            case 3:
                cout << "Class X Details : " << endl << endl;
                cout << "Please Enter Subject 1 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XSubject1Name, 32);
                cout << "Please Enter Subject 1 Marks : ";
                cin >> AppDet.Marks.XSubject1Marks;
                cout << "Please Enter Subject 2 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XSubject2Name, 32);
                cout << "Please Enter Subject 2 Marks : ";
                cin >> AppDet.Marks.XSubject2Marks;
                cout << "Please Enter Subject 3 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XSubject3Name, 32);
                cout << "Please Enter Subject 3 Marks : ";
                cin >> AppDet.Marks.XSubject3Marks;
                cout << "Please Enter Subject 4 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XSubject4Name, 32);
                cout << "Please Enter Subject 4 Marks : ";
                cin >> AppDet.Marks.XSubject4Marks;
                cout << "Please Enter Subject 5 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XSubject5Name, 32);
                cout << "Please Enter Subject 5 Marks : ";
                cin >> AppDet.Marks.XSubject5Marks;
                cout << "Class XII Details : " << endl << endl;
                cout << "Please Enter Subject 1 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XiiSubject1Name, 32);
                cout << "Please Enter Subject 1 Marks : ";
                cin >> AppDet.Marks.XiiSubject1Marks;
                cout << "Please Enter Subject 2 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XiiSubject2Name, 32);
                cout << "Please Enter Subject 2 Marks : ";
                cin >> AppDet.Marks.XiiSubject2Marks;
                cout << "Please Enter Subject 3 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XiiSubject3Name, 32);
                cout << "Please Enter Subject 3 Marks : ";
                cin >> AppDet.Marks.XiiSubject3Marks;
                cout << "Please Enter Subject 4 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XiiSubject4Name, 32);
                cout << "Please Enter Subject 4 Marks : ";
                cin >> AppDet.Marks.XiiSubject4Marks;
                cout << "Please Enter Subject 5 Name : ";
                cin.ignore();
                cin.get(AppDet.Marks.XiiSubject5Name, 32);
                cout << "Please Enter Subject 5 Marks : ";
                cin >> AppDet.Marks.XiiSubject5Marks;
                AppDet.Marks.iscomplete = 1;
                break;
                
            default:
                break;
        }
    } while (temp);
}

void Applicant::viewApp()
{
    cout << "PERSONAL DETAILS : " << endl;
    viewPersDetails();
    
    cout << endl << "FAMILY DETAILS : " << endl;
    if (AppDet.FamDet.iscomplete) {
        cout << "First Name of Parent 1: ";
        puts(AppDet.FamDet.Parent1FirstName);
        cout << "Last Name of Parent 1: ";
        puts(AppDet.FamDet.Parent1LastName);
        cout << "Highest Degree of Parent 1: ";
        puts(AppDet.FamDet.Parent1HigestDegree);
        cout << "Email of Parent 1: ";
        puts(AppDet.FamDet.Parent1Email);
        cout << "Phone Number of Parent 1: ";
        puts(AppDet.FamDet.Parent1Phoneno);
        cout << "First Name of Parent 2: ";
        puts(AppDet.FamDet.Parent2FirstName);
        cout << "Last Name of Parent 2: ";
        puts(AppDet.FamDet.Parent2LastName);
        cout << "Highest Degree of Parent 2: ";
        puts(AppDet.FamDet.Parent2HigestDegree);
        cout << "Email of Parent 2: ";
        puts(AppDet.FamDet.Parent2Email);
        cout << "Phone Number of Parent 2: ";
        puts(AppDet.FamDet.Parent2Phoneno);
    } else {
        cout << "Family Details section not complete" << endl;
    }
    
    cout << endl << "SCHOOL DETAILS : " << endl;
    if (AppDet.SchDet.iscomplete) {
        cout << "School Name : ";
        puts(AppDet.SchDet.Name);
        cout << "Address : ";
        puts(AppDet.SchDet.Address);
        cout << "School City : ";
        puts(AppDet.SchDet.City);
        cout << "School State : ";
        puts(AppDet.SchDet.State);
        cout << "SchoolCountry : ";
        puts(AppDet.SchDet.Country);
        cout << "Phone Number : ";
        puts(AppDet.SchDet.Phoneno);
    } else {
        cout << "School Details section not complete" << endl;
    }
    
    cout << endl << "MARKS : " << endl;
    if (AppDet.Marks.iscomplete) {
        cout << "Class X Details : " << endl;
        cout << "Subject 1 Name : ";
        puts(AppDet.Marks.XSubject1Name);
        cout << "Subject 1 Marks : ";
        cout << AppDet.Marks.XSubject1Marks;
        cout << "\nSubject 2 Name : ";
        puts(AppDet.Marks.XSubject2Name);
        cout << "Subject 2 Marks : ";
        cout << AppDet.Marks.XSubject2Marks;
        cout << "\nSubject 3 Name : ";
        puts(AppDet.Marks.XSubject3Name);
        cout << "Subject 3 Marks : ";
        cout << AppDet.Marks.XSubject3Marks;
        cout << "\nSubject 4 Name : ";
        puts(AppDet.Marks.XSubject4Name);
        cout << "Subject 4 Marks : ";
        cout << AppDet.Marks.XSubject4Marks;
        cout << "\nSubject 5 Name : ";
        puts(AppDet.Marks.XSubject5Name);
        cout << "Subject 5 Marks : ";
        cout << AppDet.Marks.XSubject5Marks;
        cout << "\n\nClass XII Details : " << endl;
        cout << "Subject 1 Name : ";
        puts(AppDet.Marks.XiiSubject1Name);
        cout << "Subject 1 Marks : ";
        cout << AppDet.Marks.XiiSubject1Marks;
        cout << "\nSubject 2 Name : ";
        puts(AppDet.Marks.XiiSubject2Name);
        cout << "Subject 2 Marks : ";
        cout << AppDet.Marks.XiiSubject2Marks;
        cout << "\nSubject 3 Name : ";
        puts(AppDet.Marks.XiiSubject3Name);
        cout << "Subject 3 Marks : ";
        cout << AppDet.Marks.XiiSubject3Marks;
        cout << "\nSubject 4 Name : ";
        puts(AppDet.Marks.XiiSubject4Name);
        cout << "Subject 4 Marks : ";
        cout << AppDet.Marks.XiiSubject4Marks;
        cout << "\nSubject 5 Name : ";
        puts(AppDet.Marks.XiiSubject5Name);
        cout << "Subject 5 Marks : ";
        cout << AppDet.Marks.XiiSubject5Marks;
    } else {
        cout << "Marks section not complete" << endl;
    }
}

Status Applicant::handler()
{
    int temp = 1;
    if (submitted) {
        cout << "Your application has been submitted, please wait for it to be processed. You shall be notified of your admission decision on your email on the dates mentioned on our website.";
    }
    else {
        do {
            cout << "\nWhat do you want to do?" << endl;
            cout << "1) Edit Personal Details" << endl;
            cout << "2) Edit Application" << endl;
            cout << "3) View Application" << endl;
            cout << "4) Submit" << endl;
            cout << "0) Save and Exit" << endl;
            cin >> temp;
            switch (temp) {
                case 0:
                    temp = 0;
                    break;
                case 1:
                    changePersDetails();
                    break;
                case 2:
                    changeAppDetails();
                    break;
                case 3:
                    viewApp();
                    break;
                case 4:
                    if (PersDet.iscomplete && AppDet.FamDet.iscomplete && AppDet.SchDet.iscomplete && AppDet.Marks.iscomplete) {
                        return SUBMIT;
                    }
                    else
                        cout << "You have yet to complete your application. Please complete it before you submit it!";
                    break;
                    
                default:
                    break;
            }
        } while (temp);
    }
    return SAVE;
}

void Packet::save()
{
    fstream file("saved.dat", ios::binary);
    Packet find;
    
    long int position;
    if (file) {
        while (file.eof() == 0) {
            position = file.tellg();
            file.read((char*)&find, sizeof(Packet));
            
            if (!strcmp(UsrName, find.UsrName))
            {
                Encrypt(UsrName, SYS_PASSWORD);
                Encrypt((char*)&App, SYS_PASSWORD, sizeof(Applicant));
                file.seekp(position);
                
                file.write((char*)this, sizeof(Packet));
                break;
            }
        }
    }
    
    file.close();
    ofstream fout;

    if (!file) {
        fout.open("saved.dat", ios::out | ios::binary);
        Encrypt(UsrName, SYS_PASSWORD);
        Encrypt((char*)&App, SYS_PASSWORD, sizeof(Applicant));
        fout.write((char*)this, sizeof(Packet));
        fout.close();
    }
}

void Packet::submit()
{
    ofstream fout("submitted.dat", ios::binary | ios::app);
    SubmittedPacket application;
    application.App = this -> App;
    
    // For verification through a digital signature
    char* temp = HashDigest((char*)&application.App, 64, sizeof(Applicant));
    strcpy(application.digitalSignature, temp);
    delete[] temp;
    
    this -> App.submitted = 1;

    Encrypt((char*)&application, SYS_PASSWORD, sizeof(SubmittedPacket));
    
    fout.write((char*)&application, sizeof(SubmittedPacket));
    fout.close();

}

void Manager::viewAllApps()
{
    ifstream fin("submitted.dat", ios::binary);
    SubmittedPacket appToView;
    char* temp;
    
    if (fin) {
        while (!fin.eof()) {
            fin.read((char*)&appToView, sizeof(SubmittedPacket));
            Decrypt((char*)&appToView, SYS_PASSWORD, sizeof(SubmittedPacket));
            temp = HashDigest((char*)&appToView.App, 64, sizeof(Applicant));
            
            if (fin.eof()) break;

            if ((!strcmp(appToView.digitalSignature, temp)) == 0) {
                cout << "\nThe username " << appToView.App.uName << " has been corrupted.\n";
            } else {
                cout << "\n\nUser Name : ";
                puts(appToView.App.uName);
                appToView.App.viewApp();
            }
            
            delete[] temp;
            
        }
    } else {
        cout << "No application has been submitted yet";
    }
    
    fin.close();
}

void Manager::viewApp()
{
    ifstream fin("submitted.dat", ios::binary);
    char username[16];
    char* temp;
    
    if (fin) {
        cout << "Enter User Name : ";
        cin.ignore();
        cin.get(username, 16);
        SubmittedPacket appToView;
        
        while (!fin.eof()) {
            fin.read((char*)&appToView, sizeof(SubmittedPacket));
            Decrypt((char*)&appToView, SYS_PASSWORD, sizeof(SubmittedPacket));
            temp = HashDigest((char*)&appToView.App, 64, sizeof(Applicant));
            
            if ((!strcmp(appToView.digitalSignature, temp)) == 0 && (!strcmp(appToView.App.uName, username))) {
                cout << "\nThe username " << appToView.App.uName << "'s application has been corrupted.\n";
            } else if (!strcmp(appToView.App.uName, username)){
                cout << "User Name : ";
                puts(appToView.App.uName);
                appToView.App.viewApp();
                return;
            }
        }
        
        cout << "Username not found!";
        
    } else {
        cout << "No application has been submitted yet";
    }
    fin.close();
}

void Manager::handler()
{
    int temp = 1;
    do {
        cout << "\nWhat do you want to do?" << endl;
        cout << "1) See all Applications" << endl;
        cout << "2) See Particular Application" << endl;
        cout << "3) Change Personal Details" << endl;
        cout << "0) Exit" << endl;
        cin >> temp;
        switch (temp) {
            case 0:
                temp = 0;
                break;
            case 1:
                viewAllApps();
                break;
            case 2:
                viewApp();
                break;
            case 3:
                changePersDetails();
                break;
                
            default:
                break;
        }
    } while (temp);
}

SubmittedPacket::SubmittedPacket() {
    App.submitted = 1;
}

void handle(); // This function will handle the main UI
void handleApplicantLogin(); // This function will handle an attempt to login by an applicant
void handleManagerLogin(); //This function will handel an attempt to login by a manager
void newApplicant(); // Create new user for applicant
void newManager(); // create new user for manager
void changePassword();

int main(int argc, char* argv[])
{
    cout << "Welcome to the Admission Application of the Imperial college at the University of Corusant." << endl << endl;
    // enter main UI
    handle();
}

void handle()
{
    int temp = 0;
    char pwd[1024];
    do {
        cout << "\nWhat do you want to do?" << endl;
        cout << "1) Login (Applicant)" << endl;
        cout << "2) New Applicant" << endl;
        cout << "3) Login Manager" << endl;
        cout << "4) New Manager" << endl;
        cout << "5) Forgot Password" << endl;
        cout << "0) Exit" << endl;
        cin >> temp;
        switch (temp) {
            case 0:
                temp = 0;
                break;
            case 1:
                handleApplicantLogin();
                break;
            case 2:
                newApplicant();
                break;
            case 3:
                handleManagerLogin();
                break;
            case 4:
                cout << "Enter Master System Password : ";
                cin.ignore();
                cin.get(pwd, 16);
                if (!strcmp(pwd, SYS_PASSWORD)) {
                    newManager();
                } else {
                    cout << "Wrong Password" << endl;
                }
                break;
            case 5:
                changePassword();
            default:
                break;
        }
    } while (temp);
}

void handleApplicantLogin()
{
    char uname[16], upwd[16];
    int flag = 1;
    Packet application;
    ifstream file("saved.dat", ios::binary);
    
    Status toSubmit;
    
    cout << "Enter User Name : ";
    cin.ignore();
    cin.get(uname, 16);
    cout << "Enter Password : ";
    cin.ignore();
    cin.get(upwd, 16);
    
    char* upwdhash = HashDigest(upwd, 64);
    
    if (file) {
        while (!file.eof()) {
            file.read((char*)&application, sizeof(Packet));
            if (!strcmp(application.PwdHash, upwdhash)) {
                Decrypt(application.UsrName, SYS_PASSWORD);
                if (!strcmp(application.UsrName, uname)) {
                    Decrypt((char*)&application.App, SYS_PASSWORD, sizeof(Applicant));
                    toSubmit = application.App.handler();
                    
                    if (toSubmit == SAVE)
                        application.save();
                    else {
                        application.submit();
                        application.save();
                        cout << "Your application has been submitted successfully" << endl;
                    }
                    
                    flag = 0;
                    break;
                }
            }
        }
    }
    
    if (flag) {
        cout << "Wrong User name or Password" << endl;
    }
    
    file.close();
}

void handleManagerLogin()
{
    char uname[16], upwd[16];
    char* upwdhash;
    int flag = 0;
    ManagerPacket manager;
    ifstream fin("managers.dat", ios::binary);
    
    cout << "Enter Username : ";
    cin.ignore();
    cin.get(uname, 16);
    cout << "Enter Password : ";
    cin.ignore();
    cin.get(upwd, 16);
    
    upwdhash = HashDigest(upwd, 64);
    
    if (fin) {
        while (!fin.eof()) {
            fin.read((char*)&manager, sizeof(ManagerPacket));
            Decrypt(manager.UsrName, SYS_PASSWORD);
            if (!strcmp(manager.UsrName, uname)) {
                if (!strcmp(manager.PwdHash, upwdhash)) {
                    Decrypt((char*)&manager.App, SYS_PASSWORD, sizeof(manager.App));
                    manager.App.handler();
                    flag = 1;
                }
            }
        }
    }
    
    fin.close();
    delete[] upwdhash;
    
    if (flag == 0) {
        cout << "Wrong username or Password" << endl;
    }
}

void newApplicant()
{
    ifstream fin("saved.dat", ios::binary);
    
    char UName[16], UPwd[16];
    char* UPwdHash;
    Packet Check, NewApplicant;
    int flag = 1;
    
    cout << "Enter new username : ";
    cin.ignore();
    cin.get(UName, 16);

    if (fin) {
        while (!fin.eof()) {
            fin.read((char*)&Check, sizeof(Check));
            Decrypt(Check.UsrName, SYS_PASSWORD);
            if (!strcmp(Check.UsrName, UName)) {
                flag = 0;
                break;
            }
        }
    }
    
    fin.close();
    ofstream fout("saved.dat", ios::binary | ios::app);
    
    if (flag) {
        cout << "Enter new Password : ";
        cin.ignore();
        cin.get(UPwd, 16);
        
        UPwdHash = HashDigest(UPwd, 64);
        strcpy(NewApplicant.App.uName, UName);
        Encrypt(UName, SYS_PASSWORD);
        
        strcpy(NewApplicant.UsrName, UName);
        strcpy(NewApplicant.PwdHash, UPwdHash);
        
        NewApplicant.App.PersDet.iscomplete = 0;
        NewApplicant.App.AppDet.FamDet.iscomplete = 0;
        NewApplicant.App.AppDet.SchDet.iscomplete = 0;
        NewApplicant.App.AppDet.Marks.iscomplete = 0;
        
        Encrypt((char*)&NewApplicant.App, SYS_PASSWORD, sizeof(NewApplicant.App));
        
        fout.write((char*)&NewApplicant, sizeof(NewApplicant));
        
        cout << "New User created succesfully! Please login to continue." << endl;
        
        delete [] UPwdHash;
    } else {
        cout << "Username already exists" << endl;
        newApplicant();
    }
    
    fout.close();
}

void newManager()
{
    ifstream fin("managers.dat", ios::binary);
    
    char UName[16], UPwd[16];
    char* UPwdHash;
    ManagerPacket Check, NewManager;
    int flag = 1;
    
    cout << "Enter new username : ";
    cin.ignore();
    cin.get(UName, 16);
    
    if (fin) {
        while (!fin.eof()) {
            fin.read((char*)&Check, sizeof(Check));
            Decrypt(Check.UsrName, SYS_PASSWORD);
            if (!strcmp(Check.UsrName, UName)) {
                flag = 0;
                break;
            }
        }
    }
    
    fin.close();
    ofstream fout("managers.dat", ios::binary | ios::ate);
    
    if (flag) {
        cout << "Enter new Password : ";
        cin.ignore();
        cin.get(UPwd, 16);
        UPwdHash = HashDigest(UPwd, 64);

        Encrypt(UName, SYS_PASSWORD);
        
        strcpy(NewManager.UsrName, UName);
        strcpy(NewManager.PwdHash, UPwdHash);
        
        NewManager.App.changePersDetails();
        
        Encrypt((char*)&NewManager.App, SYS_PASSWORD, sizeof(Manager));
        
        fout.write((char*)&NewManager, sizeof(ManagerPacket));
        
        cout << "New Manager User created succesfully! Please login to continue." << endl;
        
        delete[] UPwdHash;
    } else {
        cout << "Username already exists" << endl;
        newManager();
    }
    
    fout.close();
}

void changePassword() {
    ifstream file;
    ofstream fout;
    file.open("saved.dat", ios::binary | ios::in);
    if (!file) cout << "unable to open file";
    
    Packet find;
    
    char UsrName[16], newPassword[16];
    char* temp;
    cout << "Enter your username ";
    cin.ignore();
    cin.get(UsrName, 16);
    
    long int position;
    if (file) {
        while (file.eof() == 0) {
            position = file.tellg();
            file.read((char*)&find, sizeof(Packet));
            Decrypt((char*)&find.UsrName, SYS_PASSWORD);
            
            if (!strcmp(UsrName, find.UsrName))
            {
                fout.open("saved.dat", ios::binary | ios::out);
                cout << "Enter you new password ";
                cin.ignore();
                cin.get(newPassword, 16);
                
                temp = HashDigest(newPassword, 64);
                
                strcpy(find.PwdHash, temp);
                Encrypt((char*)&find.UsrName, SYS_PASSWORD);
                delete[] temp;
                
                fout.seekp(position);
                fout.write((char*)&find, sizeof(Packet));
                file.close();
                cout << "\nNew password successfully saved\n";
                return;
            }
        }
        cout << "Wrong username\n";
    } else if (!file) {
        cout << "\nNo application has been created yet\n";
    }
    
    file.close();
    
}