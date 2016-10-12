/**
 *  aes_tools.cpp: Ricardo Quezada
 *  Functions for interact with the AES implementation:
 *  Generation of pseudo-random keys and modes of operations.
**/

#include<bits/stdc++.h>
#include"aes.h"
#include"aes_tools.h"
using namespace std;

/**
 *  gen_key: generate a random key of the given size.
 *  The default size is 256 bits.
 *  The key is returned as a vector of chars (Key type).
**/

Key gen_key(int key_size)
{
	int size = (key_size == KEY_SIZE_256) ? 32 :
			   (key_size == KEY_SIZE_192) ? 24 :
			   16;
	Key key;

	//Use a non-deterministic generator, if available.
	random_device r;
	default_random_engine engine(r());
	uniform_int_distribution<int> uniform_dist(0, 255);

	for(int i=0; i<size; i++)
		key.push_back(uniform_dist(engine));
	return key;
}

/**
 *  print_key: print the given key in the given stream.
 *  The key is printed in hexadecimal format.
 *  Each byte of the key is separated by a space character.
 *  The default stream is 'cout'.
**/

void print_key(Key &key, ostream &out)
{
	for(int i=0; i < key.size(); i++)
		//std::hex format only integers.
		out << hex << (255 & key[i]) << " ";
	out << endl;
}

/**
 *  read_key: read a key on the given stram.
 *  return a Key type (vector<char>).
 *  Since this is thinking on files, hera are no default value.
**/

Key read_key(istream &in)
{
	Key key;
	int tmp;
	while(in >> hex >> tmp)
		key.push_back(tmp);
	return key;
}