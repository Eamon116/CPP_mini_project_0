//=================================
// include guard
#ifndef __ENCRYPTION_HEADER_INCLUDED__
#define __ENCRYPTION_HEADER_INCLUDED__

#include <iostream>  // in/out 
#include <fstream>   // file
#include <string>    // string
#include <sstream>   // string stream

using namespace std; // standard namespacing eliminates std:: from code


//------------------------------------------------------------------------
// mutliple calls of the same class demonstrates data adstraction
//------------------------------------------------------------------------
// the use of class causes encapsulation to be implemented 
//------------------------------------------------------------------------
class encryption 
{	
	public:
		
		//-------------------------------------------------------
		// techically an accessor as it can be used to access
		// pointed to data
		//-------------------------------------------------------
		int * p;   
		
		//-------------------------------------------------------
		// constructer
		// techically an mutator as it is used to mutate the
		// values stored in memory using the pointer
		//-------------------------------------------------------		                    
		encryption(const string&); 
		
		//-------------------------------------------------------
		// functions to encrypt data - overload for polymorphism
		//-------------------------------------------------------		
		int encrypt_function(const int&);
		string encrypt_function(const string&);
		
		//-------------------------------------------------------
		// functions to decrypt data - overload for polymorphism
		// singleton implemented as functionality is exactly the 
		// same as encrypt_function
		//-------------------------------------------------------		
		int decrypt_function(const int& val){return encrypt_function(val);};
		string decrypt_function(const string& str){return encrypt_function(str);};
		
		//-------------------------------------------------------
		// destructor
		//-------------------------------------------------------		
		~encryption();

};

//------------------------------------------------------------------------
// interitance used here to include the functionality of the encrytion 
// class as the encrypt function can be used on strings extraced from
// a file - public members in base become protected in derived
//------------------------------------------------------------------------
class file_encryption : public encryption
{
	public:
		
		
		//-------------------------------------------------------
		// constructer
		// calls base constructor
		//-------------------------------------------------------		                    
		file_encryption(const string& file_name_2) : encryption(file_name_2){}
		
		//-------------------------------------------------------
		// function to encrypt file
		//-------------------------------------------------------
		void encrypt_file(const string&, const string&);
		
		
		//-------------------------------------------------------
		// function to decrypt file
		// singleton implemented as functionality is exactly the 
		// same as encrypt_file
		//-------------------------------------------------------
		void decrypt_file(const string& s , const string& s2){encrypt_file(s, s2);};
};

//------------------------------------------------------------------------
// constructor for encryption class - extracts XOR values for encryption
//------------------------------------------------------------------------
encryption::encryption (const string& file_name)
{
	string line_in;
	unsigned int input_value;	
    ifstream val_file (file_name.c_str());
	
	//------------------------------------------------------
	// allocate memory for values to be extracted from file
	//------------------------------------------------------
	p = new int[10];

	//------------------------------------------------------
	// if the file is open get values line by line and
	// place values at memory position pointer to by p
	//------------------------------------------------------
	if (val_file.is_open())
	{
		while (getline(val_file, line_in))
		{
			//------------------------------------------------------
			// extract values to a string stream and convert the 
			// stream to hexadecimal variable of type mytemp
			//------------------------------------------------------
	        istringstream line_out(line_in);
			line_out >> hex >> input_value;
			
			//------------------------------------------------------
			// place variable of type mytemp into memory allocation
			// and increment the pointer ofr the next value to be 
			// stored in memory
			//------------------------------------------------------
			*p = input_value;
			p++;
		}
		
		//------------------------------------------------------
		// decrement pointer so it points at original value 
		// stored and close the file used for extraction
		//------------------------------------------------------
		p -= 10;
		val_file.close();
	}
	//------------------------------------------------------
	// if the file is not found output error message
	//------------------------------------------------------
	else
	{
		cout << "file not found" << '\n';
	}
}

//------------------------------------------------------------------------
// function to encrypt input data by XORing input value - integer
//------------------------------------------------------------------------
int encryption::encrypt_function(const int& input_en)
{
	int output_en = input_en;
	
	//------------------------------------------------------
	// for loop loops through values stored at pointed to 
	// memory but does not imcrement the pointer. this is 
	// done so when decrypting the pointer does not need to
	// be decremented before, reducing overhead
	//------------------------------------------------------
	for (int k = 0; k < 10; k++)
	{
		output_en ^= *(p+k);
	}
	return output_en;
}

//------------------------------------------------------------------------
// function to encrypt input data by XORing input value - string 
//------------------------------------------------------------------------
string encryption::encrypt_function(const string& input_en_string)
{
	unsigned int stg_output_en ;
	string inter_string;
	char input_buffer [8], buffer [8];
    int n;
   
   //-------------------------------------------------------
	// switch statement to round string to a multple of 8
	// this is done as 32 bit hex values are used to encrypt
	// the string which consists of 8 characters
	//-------------------------------------------------------		                    
	switch (input_en_string.length()%8){
   	
   	case 0:
   		inter_string = input_en_string;
   		break;
   	case 1:
   		inter_string = input_en_string+"       ";
   		break;
   	case 2:
   		inter_string = input_en_string+"      ";
   		break;
   	case 3:
   		inter_string = input_en_string+"     ";
   		break;
   	case 4:
   		inter_string = input_en_string+"    ";
   		break;
   	case 5:
   		inter_string = input_en_string+"   ";
   		break;
   	case 6:
   		inter_string = input_en_string+"  ";
   		break;
   	case 7:
   		inter_string = input_en_string+" ";
   		break;	
   }
    
    //-------------------------------------------------------
    // define new output buffer to match new string length
    //-------------------------------------------------------
    char output_buffer[inter_string.length()];
    
    //-------------------------------------------------------
    // loop to extract 8 character of the string at a time
    //-------------------------------------------------------
	for (int i = 0; i < ((inter_string.length())/8); i++)
	{
		//-------------------------------------------------------
		// loop to extract each individual characters
		//-------------------------------------------------------
	    for (int j = 0; j < 8; j++)
	    {
	    	input_buffer[j] = inter_string[j+(i*8)];
		}
		
		//-------------------------------------------------------
		// used to clip any trailing characters 
		//-------------------------------------------------------
		input_buffer[8] = '\0';
		 
		 //-------------------------------------------------------
		 // loop to proform XOR of the string and the key
		 //-------------------------------------------------------
		for (int k = 0; k < 10; k++)
		{
			stg_output_en = *(p+k);
			//-------------------------------------------------------
			// convert integer to character array
			//-------------------------------------------------------
			n=sprintf (buffer, "%x", stg_output_en);			

			//-------------------------------------------------------
			// loop for individual character XORing
			//-------------------------------------------------------
			for(int l = 0; l < 8; l++)
			{
				input_buffer[l] ^= buffer[l] ;
			}	
		}
		
		//-------------------------------------------------------
		// loop to reassemble encrypted string
		//-------------------------------------------------------
		for (int m = 0; m < 8; m++)
	    {
	    	output_buffer[m+(i*8)] = input_buffer[m];
		}
	}
	
	//-------------------------------------------------------	
	// used to clip any trailing characters and 
	// to resize string to input string length
	//-------------------------------------------------------
	output_buffer[input_en_string.length()] ='\0';
	
	return output_buffer ;
}

//-------------------------------------------------------
// function to extract strings from a file and encrypt
// them and then place them into an output file
// output file is ammended with an input label
//-------------------------------------------------------
void file_encryption::encrypt_file(const string& input_filename, const string& output_file_ext)
{
	string line_in, output_string, output_filename = "output_"+output_file_ext+".txt";
	ifstream en_file (input_filename.c_str());
	ofstream output_file (output_filename.c_str());
	
	//-------------------------------------------------------
	// if the file is open
	//-------------------------------------------------------
	if (en_file.is_open())
	{
		//-------------------------------------------------------
		// grab a new line each loop until file empty
		//-------------------------------------------------------
		while (getline(en_file, line_in))
		{
			//-------------------------------------------------------
			// encrypt string frtom file
			//-------------------------------------------------------
			output_string = encryption::encrypt_function(line_in);
			
			//-------------------------------------------------------
			// input encrypted string into file and take a new line
			//-------------------------------------------------------
			output_file << output_string << '\n';
			
		}
		
		en_file.close();		
	}
	//------------------------------------------------------
	// if the file is not found output error message
	//------------------------------------------------------
	else
	{
		cout << "file to be encrypted was not found!!!" << '\n';
	}
	
	output_file.close();
	
}

//-------------------------------------------------------
// destructor function to clear used memory
//-------------------------------------------------------
encryption::~encryption(void)
{
    cout << "Freeing memory!" << endl;
    delete p;
}

#endif // __ENCRYPTION_HEADER_INCLUDED__ 
