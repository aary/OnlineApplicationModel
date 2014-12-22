//
//  utilities.cpp
//
//  Created by Aditya Sule and Aaryaman Sagar on 29/01/13.
//  Copyright (c) 2013 Sanskriti School. All rights reserved.
//

#include "utilities.h"
#include <cmath>

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


void XOR(char arr[], char arr2[], int LENGTH) {
    // Computes XOR operation on arr1 and arr2
	for(int i = 0; i < LENGTH; i++) {
		if ( (arr[i] == '0' && arr2[i] == '1') || (arr[i] =='1' && arr2[i] == '0') )
			arr[i] = '1';
		else
			arr[i] = '0';
	}
}

void Encrypt(char* ptr, const char* Key, int classSize) {
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

void Decrypt(char* ptr, const char* Key, int classSize) {
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
