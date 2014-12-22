//
//  hash.h
//
//  Created by Aditya Sule and Aaryaman Sagar on 29/01/13.
//  Copyright (c) 2013 Sanskriti School. All rights reserved.
//

#ifndef __HASH_H__
#define __HASH_H__

#define PRIME (23099*2 + 1)
#define PRIM_ROOT (23099) // The value is such so that the values in the program never exceed the maximum range of int
//#define SYS_PASSWORD "qwerty"

class Hash {
public:
	// DEFAULT CONSTRUCTOR
	Hash() {}

	// The hash function
	// EFFECTS : This hash function returns the hash of any arbitrary sized object using a
	// 		 	 pseudorandom number generator
	char* HashDigest(char* arr, int lambda, int ClassSize = 0) const;

private:
	// EFFECTS : Converts a digit into its hexadecimal character, i.e. 0123456789abcdef
	char HexForm2(int x) const;


	// EFFECTS : Converts a string into its hexadecimal form, i.e. 0123456789abcdef
	void HexForm(char arr[]) const;


	// EFFECTS : Mods the sum of each individual corresponding character strings S1 and S2 by 16 upto LENGTH-1
	void Mod(char S1[], char S2[], int LENGTH) const; // Does not append '\0' at the end of the string


	// EFFECTS : byte is the byte to be converted into a binary string of length LENGTH, i.e. in this case 
	// 			 lambda*4. Uses Binary() function to make the pseudorandom stream into a 4 bit binary string
	// 			 puts resultant into arr
	// 			 Converts one byte into an entire pseudorandom binary stream of the required length by going 
	//			 4 bits at a time and concatenating them.
	void intoBinary(char arr[], int byte, int LENGTH) const;


	// EFFECTS : Returns the binary of a string
	void Binary(char arr[], int x, int ofLength) const;


	// EFFECTS : Concatenates S1 with the values of S2 starting from index Start to 4 values after it
	void Concat(char S1[], int Start, char S2[]) const;
	

	// EFFECTS : Returns precise hexadecimal equivalent string of binary string x
	char* Hex(char x[]) const;
	

	// EFFECTS : Converts an integer to a binary string of length 4 bits by XORing 4 bits at a 
	// 			 time of the integer with each other.
	void Into4BitBinary(char arr[], int x) const;
};
const Hash hashFunction;


#endif