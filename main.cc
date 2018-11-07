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
void menu(); //present options to user
void exit(); //exit
char user(); //get user input



int main(){
	char input = 0; //holds menu response

	auto tick = Clock::now(); //start of the timekeeping

	//put declaration of voraldo object here

	auto tock = Clock::now(); //end of timekeeping
	cout<< "Declaration took " << std::chrono::duration_cast<milliseconds>(tock-tick).count() << " milliseconds" << endl;

	menu();

	input = user();

	return 0;



}

void menu(){
	cout << "Welcome, you bitch. Enter a letter now." << endl;
	cout << ">";
}

char user(){
	char temp;
	cin >> temp;
	return temp;
}