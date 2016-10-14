/**
 *  aes_test.cpp: Ricardo Quezada
 *  Example of usage of the aes.cpp and aes_tools.cpp.
**/

#include<bits/stdc++.h>
#include"aes.h"
#include"aes_tools.h"
using namespace std;

int find(int n, char *values[], string value)
{
	for(int i=0; i<n; i++)
		if(values[i] == value)
			return i;
	return 0;
}

int main(int argc, char *argv[])
{
	string option = argv[1];
	int tmp;

	if(option == "-k"){

		int size = KEY_SIZE_256;	//Default
		if(tmp = find(argc, argv, "-s")){
			size = atoi(argv[tmp + 1]);
			size = (size == 256) ? KEY_SIZE_256 : 
				   (size == 192) ? KEY_SIZE_192 :
				   KEY_SIZE_128;
		}

		fstream file_key (argv[2], ios::out);
		Array key = gen_key(size);
		print_hex(key, file_key);
		cout << "Key saved in " << argv[2] << endl;
		exit(0);

	}

	if(option == "-e" | option == "-d"){
		
		int mode = CBC_MODE;
		if(tmp = find(argc, argv, "-m")){
			string aux = argv[tmp + 1];
			if(aux == "CTR") mode = CTR_MODE;
		}

		int operation = (option == "-e") ? ENCRYPTION_MODE : DECRYPTION_MODE;
		fstream file_key (argv[2], ios::in);
		fstream file_in (argv[3], ios::in | ios::binary);
		fstream file_out (argv[4], ios::out | ios::binary);

		Array key = read_key(file_key);
		process(key, file_in, file_out, operation, mode);
		cout << ((operation == ENCRYPTION_MODE) ? "Ciphertext" : "Plaintext")
			 << " saved in " << argv[4] << endl;

	}
}
