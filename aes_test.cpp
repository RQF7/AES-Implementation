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
	fstream file1 ("key256.txt", ios::out);
	fstream file2 ("key192.txt", ios::out);
	fstream file3 ("key128.txt", ios::out);

	Key key1 = gen_key();
	cout << "256 key: " << endl;
	print_key(key1);
	print_key(key1, file1);
	file1.close();

	Key key2 = gen_key(KEY_SIZE_192);
	cout << "192 key: " << endl;
	print_key(key2);
	print_key(key2, file2);
	file2.close();

	Key key3 = gen_key(KEY_SIZE_128);
	cout << "128 key: " << endl;
	print_key(key3);
	print_key(key3, file3);
	file3.close();

	cout << endl <<  "Los archivos se cierran y se vuelven a abrir..." << endl;

	file1.open("key256.txt", ios::in);
	file2.open("key192.txt", ios::in);
	file3.open("key128.txt", ios::in);

	key1 = read_key(file1);
	key2 = read_key(file2);
	key3 = read_key(file3);

	cout << endl << "256 key: " << endl;
	print_key(key1);
	cout << "Key expansion: " << endl;
	Keys keys1 = key_schedule(key1);
	for(int i=0; i<keys1.size(); i++){
		cout << i+1 << ".- ";
		print_key(keys1[i]);
	}

	cout << endl << "192 key: " << endl;
	print_key(key2);
	cout << "Key expansion: " << endl;
	Keys keys2 = key_schedule(key2);
	for(int i=0; i<keys2.size(); i++){
		cout << i+1 << ".- ";
		print_key(keys2[i]);
	}

	cout << endl << "128 key: " << endl;
	print_key(key3);
	cout << "Key expansion: " << endl;
	Keys keys3 = key_schedule(key3);
	for(int i=0; i<keys3.size(); i++){
		cout << i+1 << ".- ";
		print_key(keys3[i]);
	}
}