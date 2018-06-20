/*      Author:         Jefferson Crelia        (JeffersonCrelia@gmail.com)
        Date:           November 15, 2016
        Instructor:     David M. Keathly
        Description:    This program encrypts or decrypts a file based on user input
*/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>



using namespace std;

void header();
/*
============================================================================
Function :	header
Parameters :	none
Return : 	none
Description :	This function prints the required header to the console
============================================================================
*/


void get_stream(ifstream& in_s, ofstream& out_s);
/*
============================================================================
Function :	get_stream
Parameters :	in_s and out_s which represent the inout an output files
Return :        none
Description :	This function gets the input and output files from the user
============================================================================
*/


void e_or_d(char& enc_or_dec);
/*
============================================================================
Function :	e_or_d
Parameters :	char enc_or_dec which representsthe coice between encrypt
		and decrypt
Return :        none
Description :	This function prompts the user to decide between encryption
		and decryption
============================================================================
*/


void getkey(char key[]);
/*
============================================================================
Function :	getkey
Parameters :	char array key[] whihc represents the 5 character key
Return :        none
Description :	This function prompts the user to enter a 5 letter key
============================================================================
*/


void check_i(int& i);
/*
============================================================================
Function :	check_i
Parameters :	int i which represents the index for the key
Return :        none
Description :	This function makes sure that the keyalways uses the correct
		values
============================================================================
*/


void encrypt(ifstream& in_s, ofstream& out_s, char& cypher, char key[]);
/*
============================================================================
Function :	encrypt
Parameters :	in_s and out_s whihc represent the input and output files,
		char cypher whihc represents the cyphertext, and char
		array key[] whihc represents the user entered key
Return :        none
Description :	This function encrypts a file character by character
============================================================================
*/


void decrypt(ifstream& in_s, ofstream& out_s, char& cypher, char key[]);
/*
============================================================================
Function :	decrypt
Parameters :	in_s and out_s whihc represent the input and output files,
                char cypher whihc represents the cyphertext, and char
                array key[] whihc represents the user entered key
Return :        none
Description :	This function decrpyts a file character by character
============================================================================
*/


int main ()
{
	header();


        char enc_or_dec, key[6], cypher; //declare character variables


        ifstream in_s; // declaration of the stream of type input
        ofstream out_s; // declaration of the stream of the type input

	e_or_d(enc_or_dec); // ask user to encrypt or decrypt
	get_stream(in_s, out_s); // run void to get file names
	getkey(key); // prompt for key

        if (enc_or_dec == 'e' || enc_or_dec == 'E') //user chooses encrypt
	{
		encrypt(in_s, out_s, cypher, key); // run encrypt function

		cout << "The text has been encrypted and can be found in the output file entered.\n" << endl;
        }
        else if (enc_or_dec == 'd' || enc_or_dec == 'D') //user chooses decrypt
        {
		decrypt(in_s, out_s, cypher, key);//run decrypt function

		cout << "The text has been decrypted and can be found in the output file entered.\n" << endl;
        }
	else //something goes wrong
	{
		cout << "Oops! Something went wrong. Please try again." << endl; //display error statement
	}

        in_s.close(); // close the file
        out_s.close(); // close the file

        return 0;
}




void header()
{
 cout << "\n\n\n";
        cout <<"x" << string(47, '-') << "x\n";
        cout << "|\t~Course Number: CSCE 1030~\t\t|\n";
        cout << "|\t~Program Number: Section 002~\t\t|\n";
        cout << "|\t~Name: Jefferson Crelia~\t\t|\n";
        cout << "|\t~Email: JeffersonCrelia@my.unt.edu~\t|\n";
        cout << "x" << string(47, '-') << "x" << endl;
        cout << "\n\n\n";
        // display header with border around it
}




void get_stream(ifstream& in_s, ofstream& out_s)
{
        char input_file[100], output_file[100]; // declare file variables


        cout << "Please enter the file you would like to read from: "; // get the file name
                cin >> input_file;
		cout << endl;

        in_s.open(input_file); // connecty to the input file and test


        if(in_s.fail())
        {
                cout << "Input file opening failed. \n";
                exit(EXIT_FAILURE); //exit if cannot open file
        }


        cout << "Please enter the file you would like to write to: "; // get file name
                cin >> output_file;
		cout << endl;

        out_s.open(output_file); // connect to output file



        if (out_s.fail())
	 {
                cout << "Output file opening failed. \n";

                exit(EXIT_FAILURE); // exit if cannot open
        }
}




void e_or_d(char& enc_or_dec)
{
	cout << "Would you like to encrypt or decrypt (e or d): ";
		cin >> enc_or_dec; // choice to encrypt or decrypt
		cout << endl;


	while(enc_or_dec != 'e' && enc_or_dec != 'E' && enc_or_dec != 'd' && enc_or_dec != 'D') //check for valid input
	{
		cout << "Must be either 'e' or 'd' for encrypt or decrypt: ";
			cin >> enc_or_dec;
			cout << endl;
	}

}




void getkey(char key[])
{
	cout << "Please enter a 5 character key: ";
		cin >> key;
		cout << endl;

	for (int j = 0; j < 5; j++)
	{
		if (islower(key[j]))
		{
			key[j] = toupper(key[j]); // change to upper for future use
		}
	}
}




void check_i(int& i) //keep i withing the constraints of the array
{
	if(i > 4)
	{
		i = 0;
	}
}




void encrypt(ifstream& in_s, ofstream& out_s, char& cypher, char key[])
{
	int i = 0;
	char plain;

	while (in_s.get(plain)) // read until EOF
	{
		if (isalpha(plain)) //make sure char is alphabetic
		{
			if(isupper(plain))
			{
				cypher = ((plain - 65 + key[i] - 65) % 26 ) + 65; // if upper run decryption algorithm
			}
			else
			{
				plain = toupper(plain);
				cypher = ((plain - 65 + key[i] - 65) % 26 ) + 65;
				cypher = tolower(cypher); // if lower change to upper,, run encryptiom, change back to lower
			}

			out_s.put(cypher); // print the character to the file
			i++; //add one to to i
		}

		else
		{
			out_s.put(plain); // if blank print the plaintext to the file
		}

		check_i(i); // check if i is valid
	}

}



void decrypt(ifstream& in_s, ofstream& out_s, char& cypher, char key[])
{
	int i = 0; //set i equal to 0 for start of loop
	char plain; // declare plain

	while(in_s.get(cypher)) // while not eof
	{
		if(isalpha(cypher)) // check if letter
		{
			if(isupper(cypher)) //if uppercase
			{
				plain = (( 26 + (cypher - 65) - (key[i] - 65)) % 26 ) + 65; // function for encryption
			}
			else // if lowercase
			{
				cypher = toupper(cypher); // change to uppercase
				plain = (( 26 + (cypher - 65) - (key[i] - 65)) % 26 ) + 65; //function for encryption
				plain = tolower(plain); // change back to lower
			}

			out_s.put(plain); // print decrpyted character to file
			i++; // add one to  i
		}
		else // if not letter
		{
			out_s.put(cypher); // print to file
		}

		check_i(i); // check if i is valid
	}
}
