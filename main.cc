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

	Vox  type0,  type1,  type2,  type3;
	Vox  type4,  type5,  type6,  type7;
	Vox  type8,  type9, type10, type11;
	Vox type12, type13, type14, type15;
	Vox type16;

	type0.color = main_block->get_RGB_for_state(0);
	type1.color = main_block->get_RGB_for_state(1);
	type2.color = main_block->get_RGB_for_state(2);
	type3.color = main_block->get_RGB_for_state(3);
	type4.color = main_block->get_RGB_for_state(4);
	type5.color = main_block->get_RGB_for_state(5);
	type6.color = main_block->get_RGB_for_state(6);
	type7.color = main_block->get_RGB_for_state(7);
	type8.color = main_block->get_RGB_for_state(8);
	type9.color = main_block->get_RGB_for_state(9);
	type10.color = main_block->get_RGB_for_state(10);
	type11.color = main_block->get_RGB_for_state(11);
	type12.color = main_block->get_RGB_for_state(12);
	type13.color = main_block->get_RGB_for_state(13);
	type14.color = main_block->get_RGB_for_state(14);
	type15.color = main_block->get_RGB_for_state(15);

	type16.color = main_block->get_RGB_for_state(16);

	type0.size = 1;
	type1.size = 1;
	type2.size = 1;
	type3.size = 1;
	type4.size = 1;
	type5.size = 1;
	type6.size = 1;
	type7.size = 1;
	type8.size = 1;
	type9.size = 1;
	type10.size = 1;
	type11.size = 1;
	type12.size = 1;
	type13.size = 1;
	type14.size = 1;
	type15.size = 1;
	type16.size = 0;


	type0.mask = false;
	type1.mask = false;
	type2.mask = false;
	type3.mask = false;
	type4.mask = false;
	type5.mask = false;
	type6.mask = false;
	type7.mask = false;
	type8.mask = false;
	type9.mask = false;
	type10.mask = false;
	type11.mask = false;
	type12.mask = false;
	type13.mask = false;
	type14.mask = false;
	type15.mask = false;

	type16.mask = false;

	type0.alpha = 1.0;
	type1.alpha = 1.0;
	type2.alpha = 1.0;
	type3.alpha = 1.0;
	type4.alpha = 1.0;
	type5.alpha = 1.0;
	type6.alpha = 1.0;
	type7.alpha = 1.0;
	type8.alpha = 1.0;
	type9.alpha = 1.0;
	type10.alpha = 1.0;
	type11.alpha = 1.0;
	type12.alpha = 1.0;
	type13.alpha = 1.0;
	type14.alpha = 1.0;
	type15.alpha = 1.0;

	type16.alpha = 0.0;



/*
	//Jack with Triangle
	

	main_block->draw_ellipsoid(128,128,128,64,16,16,12);
	main_block->draw_ellipsoid(128,128,128,16,64,16,17);
	main_block->draw_ellipsoid(128,128,128,16,16,64,22);

	main_block->draw_sphere(192,128,128,22,11);
	main_block->draw_sphere(128,192,128,22,16);
	main_block->draw_sphere(128,128,192,22,21);

	main_block->draw_sphere( 64,128,128,22, 9);
	main_block->draw_sphere(128, 64,128,22,14);
	main_block->draw_sphere(128,128, 64,22,19);


	main_block->draw_triangle(vec(192,128,128), vec(128,192,128), vec(128,128,192), 30);

	main_block->draw_line_segment(vec(192,128,128),vec(128,192,128),11); //from +x to +y
	main_block->draw_line_segment(vec(128,192,128),vec(128,128,192),16); //from +y to +z
	main_block->draw_line_segment(vec(128,128,192),vec(192,128,128),21); //from +z to +x
*/

/* the building thing
	int grass = 7; //VORALDO_STATE_BASIC_GREEN_LEVEL0

	main_block->draw_blockoid(0,256,0,50,0,256,grass);

	main_block->draw_blockoid(32,224,20,200,32,224, 9);
	main_block->draw_blockoid(35,221,23,197,35,221, 8);

	main_block->draw_blockoid(38,218,25,195,38,218, 29);
	main_block->draw_blockoid(38,218,27,195,38,218,  0);
	main_block->draw_blockoid(38,218,75,195,38,218,  8);
	main_block->draw_blockoid(38,218,77,195,38,218, 29);
	main_block->draw_blockoid(38,218,79,195,38,218,  0);

	main_block->draw_blockoid(128,256,25,256,128,256, 0);
*/


//cardinal arrows

	main_block->draw_ellipsoid(128,128,128,64,16,16,type14); //x shell - 
	main_block->draw_ellipsoid(128,128,128,16,64,16,type14); //y shell - 
	main_block->draw_ellipsoid(128,128,128,16,16,64,type14); //z shell - 

	main_block->draw_ellipsoid(128,128,128,64,10,10,type6); //x lobe - 
	main_block->draw_ellipsoid(128,128,128,10,64,10,type11); //y lobe - 
	main_block->draw_ellipsoid(128,128,128,10,10,64,type8); //z lobe - 

	main_block->draw_blockoid(100,156,100,156,100,156,type16); //negative space at center


	tock = Clock::now();

	cout<< "-----------------" << endl;
	cout<< "all drawing took " 
	<< std::chrono::duration_cast<milliseconds>(tock-tick).count() 
	<< " milliseconds" << endl;
	cout<< "-----------------" << endl << endl;

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