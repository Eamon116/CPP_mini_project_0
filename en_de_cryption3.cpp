#include "encryption4.h"  // encryption header containing encryption class and file encryption class
#include <iostream>       // in/out 
#include <fstream>        // file
#include <string>         // string
#include <sstream>        // string stream

using namespace std;      // standard namespacing eliminates std:: from code

int main()
{	
	encryption data_to_encrypt("input_values.txt");
	string line_in, string_out;
	stringstream line_out;
	unsigned int int_out, hex_out;
	
	//-------------------------------------------------------------
	// example of data abstraction 
	//-------------------------------------------------------------
	file_encryption file_to_encrypt("input_values.txt");
	file_encryption file_to_decrypt("input_values.txt");
	string file_name;
	
	cout << "enter a 32 bit hex value to be in encrypted:" << '\n' ;
	getline(cin, line_in);
	cout << '\n';
	
	line_out << hex << line_in ;
	line_out >> int_out;
	
	cout << "enter a string to be in encrypted:" << '\n' ;
	getline(cin, line_in);
	cout << '\n';
	
	//-------------------------------------------------------------
	// example of polymorphism being used
	// polymorph - encrypt_function variable for int and string
	//-------------------------------------------------------------
	hex_out = data_to_encrypt.encrypt_function(int_out);
	string_out = data_to_encrypt.encrypt_function(line_in);
	
	cout << "the encrypted integer data is: " << hex << hex_out << '\n' << '\n';
	cout << "the encrypted string data is: " << string_out << '\n' << '\n';

	//-------------------------------------------------------------
	// example of singleton and polymorphism being used
	// singleton - decrypt_function derived from encrypt_function
	// polymorph - decrypt_function variable for int and string
	//-------------------------------------------------------------
	hex_out = data_to_encrypt.decrypt_function(hex_out);          
	string_out = data_to_encrypt.decrypt_function(string_out);    
	
	cout << "the decrypted integer data is: " << hex << hex_out << '\n'<< '\n';
	cout << "the decrypted string data is: " << string_out << '\n'<< '\n';
	
	cout << "input file name which contains data to encrypt: " ;
    getline(cin, file_name);
	
	file_to_encrypt.encrypt_file(file_name, "file_en");
	
	
	cout << "input file name which contains data to decrypt: " ;
    getline(cin, file_name);
	
	//-------------------------------------------------------------
	// example of singleton being used
	// singleton - decrypt_file derived from encrypt_file
	//-------------------------------------------------------------
	file_to_decrypt.decrypt_file(file_name, "file_de");
	

	return 0;
}
