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
#define ECB_MODE 3

/**
 *  Public functions.
 *  Pay atention to the defaults arguments.
**/

Array gen_key(int key_size = KEY_SIZE_256);
void print_hex(Array &key, ostream &out = cout);
void print_data(Array &key, ostream &out = cout);
Array read_key(istream &in);

#endif