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

int init_x = 257;
int init_y = 257;
int init_z = 257;

int main(){
	char input = 0; //holds menu response

	auto tick = Clock::now(); //start of the timekeeping

	int num_bytes = init_x * init_y * init_z * sizeof(Vox);

	main_block = new Voraldo(init_x,init_y,init_z);

	auto tock = Clock::now(); //end of timekeeping
	cout<< "-----------------" << endl;
	cout<< "Dynamic memory allocation for " 
		<< init_x * init_y * init_z << " voxels took " 
		<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
		<< " milliseconds" << endl;

	cout<< "using " << std::setw(4) << float(num_bytes)/(1024.0*1024.0) 
		<< " megabytes" << endl;
	cout<< "-----------------" << endl;

	menu();

	input = user();

	tick = Clock::now();

	main_block->save_block_to_file();

	tock = Clock::now();

	cout<< "-----------------" << endl;
	cout<< "Saving the block to an image file for  " 
	<< init_x * init_y * init_z << " voxels took " 
	<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
	<< " milliseconds" << endl;
	cout<< "-----------------" << endl << endl;


	tick = Clock::now();

	main_block->display();

	tock = Clock::now();

	cout<< "-----------------" << endl;
	cout<< "Displaying the block of  " 
	<< init_x * init_y * init_z << " voxels took " 
	<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
	<< " milliseconds" << endl;
	cout<< "-----------------" << endl << endl;



	
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

void exit(){ //this deletes all allocated dynamic memory
	auto tick = Clock::now(); //start of the timekeeping
	delete main_block;
	auto tock = Clock::now(); //end of timekeeping

	int num_bytes = init_x * init_y * init_z * sizeof(Vox);

	cout<< "-----------------" << endl;
	cout<< "Dynamic memory deallocation took " 
		<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
		<< " milliseconds" << endl;

	cout<< "freeing " << std::setw(4) << float(num_bytes)/(1024.0*1024.0)
		<< " megabytes" << endl;
	cout<< "-----------------" << endl;

}