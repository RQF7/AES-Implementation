/**
 *  aes.h: Ricardo Quezada
 *  Header interface for aes.cpp
**/

#ifndef __AES_H__
#define __AES_H__

#include<bits/stdc++.h>
using namespace std;

/**
 *  Data types.
 *  Only for shorter and clearer signatures on functions.
**/

typedef vector<unsigned char> Array;
typedef vector<vector<unsigned char>> Data;

/**
 *  Macros for identify the operation desired.
**/

#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 2

/**
 *  Macros that define the key size.
 *  These are the three sizes that AES offer.
 *  The number of rounds is determinated by the key size:
 *
 *  128 bit (16 bytes) --> 10 rounds
 *  192 bit (24 bytes) --> 12 rounds
 *  256 bit (32 bytes) --> 14 rounds
**/

#define KEY_SIZE_128 1
#define KEY_SIZE_192 2
#define KEY_SIZE_256 3

/**
 *  Public functions.
**/

Data key_schedule(Array key);
void operate(Array &data, Array key, int mode);

/**
 *  Private functions.
**/

Array schedule_core(Array &key, int iterator);
void rotate(Array &subkey);
void add_round_key(Array &data, Array &key);
void sub_bytes(Array &data, int mode);
void shift_rows(Array &data, int mode);
void shift_row(Array &data, int row, int shift);
void mix_columns(Array &data, int mode);

#endif