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
 *  The key is returned as a vector of chars (Array type).
**/

Array gen_key(int key_size)
{
	int size = (key_size == KEY_SIZE_256) ? 32 :
			   (key_size == KEY_SIZE_192) ? 24 :
			   16;
	Array key;

	//Use a non-deterministic generator, if available.
	random_device r;
	default_random_engine engine(r());
	uniform_int_distribution<int> uniform_dist(0, 255);

	for(int i=0; i<size; i++)
		key.push_back(uniform_dist(engine));
	return key;
}

/**
 *  print_hex: print the given data in the given stream.
 *  The data is printed in hexadecimal format.
 *  Each byte of the key is separated by a space character.
 *  The default stream is 'cout'.
**/

void print_hex(Array &key, ostream &out)
{
	for(int i=0; i < key.size(); i++)
		//std::hex format only integers.
		out << hex << (255 & key[i]) << " ";
	out << endl;
}

/**
 *  print_data: print the given data in the given stream.
 *  The data is printed in ASCII format.
 *  The default stream is 'cout'.
**/

void print_data(Array &key, ostream &out)
{
	for(int i=0; i < key.size(); i++)
		out << key[i];
	out << endl;
}

/**
 *  read_key: read a key on the given stream.
 *  return a Array type (vector<char>).
 *  Since this is made thinking on files, here are no default value.
**/

Array read_key(istream &in)
{
	Array key;
	int tmp;
	while(in >> hex >> tmp)
		key.push_back(tmp);
	return key;
}

void process(Array key, istream &input, ostream &output , 
			int operation, int mode){

	long long int size, num_blocks;
	int block_size = key.size();

	//Generate the AES expansion keys
	Data keys = key_schedule(key);

	if(operation == ENCRYPTION_MODE){

		//A cipher text is already fixed
		streampos start = input.tellg();
	    input.seekg(0, ios::end);
	    streampos final = input.tellg();
	    size = final - start;
	    num_blocks = ceil(size / (double) block_size);
	    input.seekg(0, ios::beg);
	    int gap = (block_size - (size % block_size)) % block_size;

	    //Create and save the inizialitation vector
	    Array iv = gen_key((block_size == 32) ? KEY_SIZE_256 : 
	    				   (block_size == 24) ? KEY_SIZE_192 : 
	    				   KEY_SIZE_128);
	    write_block(iv, output);
	    //Save the REAL length
	    output << size;

	    if(mode = CBC_MODE)
	    	cbc(keys, iv, num_blocks, gap, input, output);
	    else
	    	ctr(keys, iv, num_blocks, gap, input, output, operation);

	}else{

		//Read the initialization vector
		Array iv = read_block(block_size, input);
		//Read the real length
		input >> size;

		if(mode = CBC_MODE)
	    	cbc_inverse(keys, iv, size, input, output);
	    else{
			num_blocks = ceil((double)size / block_size);
			int gap = size % block_size;
	    	ctr(keys, iv, num_blocks, gap, input, output, operation);
	    }

	}

}

void write_block(Array &block, ostream &out)
{
	int size = block.size();
	unsigned char aux[size];
	for(int i=0; i<size; i++) aux[i] = block[i];
	out.write((char*)aux, size);
}

Array read_block(int block_size, istream &in)
{
	unsigned char aux[block_size];
	in.read((char*)aux, block_size);
	Array res;
	for(int i=0; i<block_size; i++) res.push_back(aux[i]);
	return res;
}

Array& add(Array &a, Array &b)
{
	for(int i=0; i<a.size(); i++)
		a[i] ^= b[i];
	return a;
}

Array copy(Array &org)
{
	Array res;
	for(int i=0; i<org.size(); i++)
		res.push_back(org[i]);
	return res;
}

Array increment(Array a, int n)
{
	Array aux = copy(a);
	aux[a.size() - 1] += n;
	return aux;
}

void cbc(Data &keys, Array &iv, long long int num_blocks, int gap, 
	istream &input, ostream &output)
{
	int block_size = iv.size();
	if(num_blocks != 1){

	    Array aux = read_block(block_size, input);	  //Everithing is done 
	    operate(add(aux, iv), keys, ENCRYPTION_MODE); //over the same Array
	    write_block(aux, output);

	    for(int i=1; i<num_blocks - 1; i++){
	    	Array aux2 = read_block(block_size, input);
	    	operate(add(aux, aux2), 
	    			keys,  ENCRYPTION_MODE);
	    	write_block(aux, output);
	    }

	    Array last = read_block(block_size - gap, input);
	    for(int i=0; i<gap; i++) last.push_back('z');
	    operate(add(aux, last), keys,  ENCRYPTION_MODE);
	    write_block(aux, output);

	}else{

		//Only one block
		Array last = read_block(block_size - gap, input);
		for(int i=0; i<gap; i++) last.push_back('z');
		operate(add(last, iv), keys,  ENCRYPTION_MODE);
	    write_block(last, output);

	}
}

void cbc_inverse(Data &keys, Array &iv, long long int size, 
	istream &input, ostream &output)
{
	int block_size = iv.size();
	int num_blocks = size / block_size;
	int gap = size % block_size;
	Array aux, aux2, aux3;

	if(num_blocks != 0){

		aux = read_block(block_size, input);
		aux2 = copy(aux);
		operate(aux, keys, DECRYPTION_MODE);
		write_block(add(aux, iv), output);

		for(int i=1; i<num_blocks; i++){
			aux = read_block(block_size, input);
			(i & 1) ? aux3 = copy(aux) : aux2 = copy(aux);
			operate(aux, keys, DECRYPTION_MODE);
			(i & 1) ? write_block(add(aux, aux2), output) : 
					  write_block(add(aux, aux3), output) ;
		}

	}

	if(gap != 0){

		aux = read_block(block_size, input);
		operate(aux, keys, DECRYPTION_MODE);
		for(int i = 0; i < block_size - gap; i++)
			aux.pop_back();
		if(num_blocks != 0){
			(num_blocks & 1) ? 
				write_block(add(aux, aux2), output) : 
				write_block(add(aux, aux3), output) ;
		}else write_block(add(aux, iv), output) ;

	}
}

void ctr(Data &keys, Array &iv, long long int num_blocks, int gap, 
	istream &input, ostream &output, int mode)
{
	int block_size = iv.size();
	Array iv_original = copy(iv), aux;
	if(num_blocks != 1){

	    aux = read_block(block_size, input);
	    operate(iv, keys, mode);
	    add(iv, aux);
	    write_block(iv, output);

	    for(int i=1; i<num_blocks - 1; i++){
	    	aux = read_block(block_size, input);
	    	iv = increment(iv_original, i);
	    	operate(iv, keys,  mode);
	    	add(iv, aux);
	    	write_block(iv, output);
	    }

	}

	//At least one block
	if(mode == ENCRYPTION_MODE){

		Array last = read_block(block_size - gap, input);
	    for(int i=0; i<gap; i++) last.push_back('z');
	    iv = increment(iv_original, (num_blocks == 1) ? 1 : num_blocks - 1);
	    operate(iv, keys, mode);
	    add(iv, last);
	    write_block(iv, output);

	}else{

		aux = read_block(block_size, input);
		iv = increment(iv_original, (num_blocks == 1) ? 1 : num_blocks - 1);
		operate(iv, keys, mode);
	    add(iv, aux);
	    for(int i = 0; i < block_size - gap; i++)
			iv.pop_back();
		write_block(iv, output);

	}

}
