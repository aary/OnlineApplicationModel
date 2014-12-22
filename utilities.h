//
//  utilities.h
//
//  Created by Aditya Sule and Aaryaman Sagar on 29/01/13.
//  Copyright (c) 2013 Sanskriti School. All rights reserved.
//

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// EFFECTS : Algorithm for computing g^A mod N
int FastPower(int g, int A, int N);

// EFFECTS : Returns the length of a string
int stringLength(const char* arr);

// EFFECTS : A pseudorandom number generator
int Mypsi(int x);

// EFFECTS : Copies string C1 into C2
void copy(char S1[], char S2[], int LENGTH);

// EFFECTS : Computes logical and
void AND(char S1[], char S2[], int LENGTH);

// EFFECTS : Computes an XOR operation
void XOR(char arr[], char arr2[], int LENGTH);

// EFFECTS : Encrypts an object of arbitrary length
void Encrypt(char* ptr, const char Key[], int classSize = 0);

// EFFECTS : Decrypts an object of arbitrary length
void Decrypt(char* ptr, const char Key[], int classSize = 0);

// EFFECTS : Copies string tocopyfrom into tocopyto
void Copy(char* tocopyto, char* tocopyfrom, int ClassSize);



#endif