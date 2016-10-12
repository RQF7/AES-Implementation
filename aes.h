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

typedef vector<unsigned char> Key;
typedef vector<vector<unsigned char>> Keys;

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

Keys key_schedule(Key &key);

/**
 *  Private functions.
**/

Key schedule_core(Key &key, int iterator);
void rotate(Key &subkey);

#endif