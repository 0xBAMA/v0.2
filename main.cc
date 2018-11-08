#include <iostream>
#include <string>
#include <chrono>
#include "includes/voraldo/V2.h"

//stream class aliases
using std::cout;
using std::endl;
using std::cin;

//Chrono class aliases
using Clock=std::chrono::high_resolution_clock;
using milliseconds=std::chrono::milliseconds;

//menu functions
void menu(); //present options and prompt to user
char user(); //get user input

void exit(); //responsible for deallocating memory 

Voraldo *main_block = NULL;



int main(){
	char input = 0; //holds menu response

	auto tick = Clock::now(); //start of the timekeeping

	main_block = new Voraldo(256,256,256);

	main_block->save_block_to_file();

	auto tock = Clock::now(); //end of timekeeping
	cout<< "Declaration took " 
		<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
		<< " milliseconds" << endl;

	menu();

	input = user();

	exit();

	return 0;

}

void menu(){
	cout << endl << endl 
		<< "Hit any letter, followed by enter, to exit." 
		<< endl << endl;

	cout << "Enter a letter." << endl;
	cout << ">";
}

char user(){
	char temp;
	cin >> temp;
	return temp;
}

void exit(){
	delete main_block;
}