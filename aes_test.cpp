/**
 *  aes_test.cpp: Ricardo Quezada
 *  Example of usage of the aes.cpp and aes_tools.cpp.
**/

#include<bits/stdc++.h>
#include"aes.h"
#include"aes_tools.h"
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Test of 128 bits: " << endl;
	Array key1 = gen_key(KEY_SIZE_128);
	cout << "Key: ";
	print_hex(key1);
	Array data1;
	for(int i=0; i<16; i++) data1.push_back('a' + i);
	cout << "Plain text: ";
	print_data(data1);
	operate(data1, key1, ENCRYPTION_MODE);
	cout << "Cipher text: ";
	print_hex(data1);
	operate(data1, key1, DECRYPTION_MODE);
	cout << "Plain text: ";
	print_data(data1);
	cout << endl;

	cout << "Test of 192 bits: " << endl;
	Array key2 = gen_key(KEY_SIZE_192);
	cout << "Key: ";
	print_hex(key2);
	Array data2;
	for(int i=0; i<24; i++) data2.push_back('a' + i);
	cout << "Plain text: ";
	print_data(data2);
	operate(data2, key2, ENCRYPTION_MODE);
	cout << "Cipher text: ";
	print_hex(data2);
	operate(data2, key2, DECRYPTION_MODE);
	cout << "Plain text: ";
	print_data(data2);
	cout << endl;

	cout << "Test of 256 bits: " << endl;
	Array key3 = gen_key(KEY_SIZE_256);
	cout << "Key: ";
	print_hex(key3);
	Array data3;
	for(int i=0; i<32; i++) data3.push_back('a' + i);
	cout << "Plain text: ";
	print_data(data3);
	operate(data3, key3, ENCRYPTION_MODE);
	cout << "Cipher text: ";
	print_hex(data3);
	operate(data3, key3, DECRYPTION_MODE);
	cout << "Plain text: ";
	print_data(data3);
	cout << endl;
}
