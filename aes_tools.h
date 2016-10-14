/**
 *  aes_tools.h: Ricardo Quezada
 *  Header interface for aes_tools.cpp
**/

#ifndef __AES_TOOLS_H__
#define __AES_TOOLS_H__

#include<bits/stdc++.h>
using namespace std;

/**
 *  Macros for identify the mode of operation.
**/

#define CBC_MODE 1
#define CTR_MODE 2

/**
 *  Public functions.
 *  Pay atention to the defaults arguments.
**/

Array gen_key(int key_size = KEY_SIZE_256);
void print_hex(Array &key, ostream &out = cout);
void print_data(Array &key, ostream &out = cout);
Array read_key(istream &in);
void process(Array key, istream &input, ostream &output = cout, 
	int operation = ENCRYPTION_MODE, int mode = CBC_MODE);

/**
 *  Private functions.
**/

void cbc(Data &keys, Array &iv, long long int num_blocks, int gap, 
	istream &input, ostream &output);
void cbc_inverse(Data &keys, Array &iv, long long int size, 
	istream &input, ostream &output);
void ctr(Data &keys, Array &iv, long long int num_blocks, int gap, 
	istream &input, ostream &output, int mode);
Array& add(Array &a, Array &b);
Array copy(Array &org);
void write_block(Array &block, ostream &out);
Array read_block(int block_size, istream &in);
Array increment(Array a);

#endif