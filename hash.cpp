//
//  hash.cpp
//
//  Created by Aditya Sule and Aaryaman Sagar on 29/01/13.
//  Copyright (c) 2013 Sanskriti School. All rights reserved.
//
#include "hash.h"
#include "utilities.h"
#include <cmath>

char* Hash::HashDigest(char* arr, int lambda, int ClassSize ) const {
    
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
	this->intoBinary(BinaryString, phi, 4*lambda);
	Hexed = Hex(BinaryString);
	this->Mod(FinalHash, Hexed, lambda);
	delete[] Hexed;
	
	for(int i = 0; i < phi; i++) {
		// Converts the byte to binary of length 4*lambda
		this->intoBinary(BinaryString, *ptr + i + fordifference,4*lambda); // so thqt each ele gets a diff value on the virtue of its position and lambda
		
        //SpecificPermute(BinaryString, strlen(BinaryString), arr, strlen(arr));
		Hexed = this->Hex(BinaryString);
		
        //SpecificPermute(Hexed, strlen(Hexed), arr, strlen(arr));
		this->Mod(FinalHash, Hexed, lambda);
		ptr++;
		delete[] Hexed;
	}
	
	FinalHash[lambda] = '\0'; //To make it a readable string
	delete[] BinaryString;
	return FinalHash;
}


char Hash::HexForm2(int x) const {
// EFFECTS : Converts a digit into its hexadecimal character, i.e. 0123456789abcdef
    
	x += 48;
	if (x >= 58 && x <= 63) x += 39;
	
	return ( (char)x );
}

void Hash::HexForm(char arr[]) const {
// EFFECTS : Converts a string into its hexadecimal form, i.e. 0123456789abcdef
    
	int LENGTH = stringLength(arr);
	for (int i = 0; i < LENGTH; i++) {
		arr[i] += 48;
		if (arr[i] >= 58 && arr[i] <= 63) arr[i] += 39;
	}
}

void Hash::Mod(char S1[], char S2[], int LENGTH) const {
// EFFECTS : Mods the sum of each individual corresponding character strings S1 and S2 by 16 upto LENGTH-1
    
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

void Hash::intoBinary(char arr[], int byte, int LENGTH) const {
// EFFECTS : byte is the byte to be converted into a binary string of length LENGTH, i.e. in this case 
// 			 lambda*4. Uses Binary() function to make the pseudorandom stream into a 4 bit binary string
// 			 puts resultant into arr
// 			 Converts one byte into an entire pseudorandom binary stream of the required length by going 
//			 4 bits at a time and concatenating them.

	char temp[5];
	for(int i = 0; i < LENGTH/4; i++) {
		byte = FastPower(FastPower(PRIM_ROOT, i+1, PRIME), byte, PRIME); // Pseudorandom generator
		Into4BitBinary(temp, byte);
		Concat(arr, 4*i, temp);
	}
	arr[LENGTH] = '\0';
}

void Hash::Binary(char arr[], int x, int ofLength) const {
// EFFECTS : Returns the binary of a string
	int remainder;
	for (int i = (ofLength - 1); i >= 0; i--) {
		remainder = x%2;
		x = x/2;
		arr[i] = remainder + 48;
	}
	arr[ofLength] = '\0'; // BECAUSE Hex() checks String Lenth and then operates!!!
}

void Hash::Concat(char S1[], int Start, char S2[]) const {
// EFFECTS : Concatenates S1 with the values of S2 starting from index Start to 4 values after it
    
	for (int i = 0; i < 4; i++)
		S1[Start+i] = S2[i];
}

char* Hash::Hex(char x[]) const {
// EFFECTS : Returns precise hexadecimal equivalent string of binary string x
    
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


void Hash::Into4BitBinary(char arr[], int x) const {
// EFFECTS : Converts an integer to a binary string of length 4 bits by XORing 4 bits at a 
// 			 time of the integer with each other.
    
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