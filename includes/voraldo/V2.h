#include "../CImg.h"		//single-header library for image display and saving	
//License below


#include "../json.hpp"  	//single-header library for output file formatting		
//MIT License


#include "../linalg.h"      //single-header library for linear algebra (vectors)	
//Public Domain License

//  [..         [..          
//   [..       [..  [. [..   
//    [..     [..  [.     [..
//     [..   [..        [..  
//      [.. [..       [..    
//       [....      [..      
//        [..      [........ 

//Cimg license - from Cimg.eu - CImg is a free, open-source library distributed 
//under the CeCILL-C (close to the GNU LGPL) or CeCILL (compatible with the GNU GPL) 
//licenses. It can be used in commercial applications.

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>

//#include <bitset> 
//not in use right now

using vec = linalg::aliases::double3;
using vec2 = linalg::aliases::double2;
using mat = linalg::aliases::double3x3;
using intvec = linalg::aliases::int3;
using veContainer = std::vector<vec>;

//V2 block class

struct Vox {
	unsigned int state;
	bool mask;
};

class Block{
/*
╔╗ ┬  ┌─┐┌─┐┬┌─
╠╩╗│  │ ││  ├┴┐
╚═╝┴─┘└─┘└─┘┴ ┴

This time, the array becomes 1-Dimensional.
doing this does a couple of things - 

	>simplifying declaration of dynamic memory
	>reducing memory overhead of a 3 dimensional array

Right now, the interface is intact, with respect to how it is used
in V1 - that is, get_data_by_index(x,y,z) will still get the data 
at the x,y,z index.
 */

public:
	
	Block();
	~Block();

	void init(int x, int y, int z);


/*  
╔═╗┌─┐┌┬┐  
║ ╦├┤  │   
╚═╝└─┘ ┴   
 ┬         
┌┼─        
└┘         
╔═╗┌─┐┌┬┐  
╚═╗├┤  │   
╚═╝└─┘ ┴ 

  These two functions are logically identical to those in
  V1, by accessing the 1D array as if it was a 3D array.
  Keeping this interface transparent allows me to bring a 
  lot of code over from the first iteration.

  There have been some changes, however.

  Rather than returning a single integer state, we are looking
  at a struct "Vox", holding a unsigned integer and a boolean
  for the masking. There will need to be changes in how this is 
  handled - I want to reduce the amount of memory it uses to a
  single bit per voxel but that's really not a priority right 
  now.
*/

	int get_x_res(){return x_res;}
	int get_y_res(){return y_res;}
	int get_z_res(){return z_res;}

	void set_data_by_3d_index(int x, int y, int z, int set);	
	Vox  get_data_by_3d_index(int x, int y, int z);

	Vox  get_data_by_array_index(int index){return data[index];}


private:


//  ╦═╗┌─┐┌─┐┌─┐┬  ┬ ┬┌┬┐┬┌─┐┌┐┌
//  ╠╦╝├┤ └─┐│ ││  │ │ │ ││ ││││
//  ╩╚═└─┘└─┘└─┘┴─┘└─┘ ┴ ┴└─┘┘└┘


	int x_res; //how many voxels along x axis
	int y_res; //how many voxels along y axis
	int z_res; //how many voxels along z axis

	int num_cells;

	Vox *data;

	int get_array_index_by_xyz(int x, int y, int z);

};

struct RGB{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct Palette_return_object{
	RGB point_color;
	double point_alpha;
	bool draw_point;

	RGB first_circle_color;
	int first_circle_radius;
	double first_circle_alpha;
	bool draw_first_circle;

	RGB second_circle_color;
	int second_circle_radius;
	double second_circle_alpha;
	bool draw_second_circle;
};

class Palette{
public:
	Palette();

	Palette_return_object return_object;

	std::map<std::string, RGB> color_map;
	void color_map_setup();

	static const int VORALDO_TEST_STATE_EMPTY = 0;

	static const int VORALDO_TEST_STATE_WHITE_LEVEL0 = 1;
	static const int VORALDO_TEST_STATE_WHITE_LEVEL1 = 2;
	static const int VORALDO_TEST_STATE_WHITE_LEVEL2 = 3;
	static const int VORALDO_TEST_STATE_WHITE_LEVEL3 = 4;
	static const int VORALDO_TEST_STATE_WHITE_LEVEL4 = 5;
	static const int VORALDO_TEST_STATE_WHITE_LEVEL5 = 6;

	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL0 = 7;
	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL1 = 8;
	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL2 = 9;
	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL3 = 10;
	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL4 = 11;
	static const int VORALDO_TEST_STATE_BRIGHT_RED_LEVEL5 = 12;

	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL0 = 13;
	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL1 = 14;
	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL2 = 15;
	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL3 = 16;
	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL4 = 17;
	static const int VORALDO_TEST_STATE_BRIGHT_GREEN_LEVEL5 = 18;

	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL0 = 19;
	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL1 = 20;
	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL2 = 21;
	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL3 = 22;
	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL4 = 23;
	static const int VORALDO_TEST_STATE_BRIGHT_BLUE_LEVEL5 = 24;

	static const int VORALDO_TEST_STATE_BLACK_LEVEL0 = 25;
	static const int VORALDO_TEST_STATE_BLACK_LEVEL1 = 26;
	static const int VORALDO_TEST_STATE_BLACK_LEVEL2 = 27;
	static const int VORALDO_TEST_STATE_BLACK_LEVEL3 = 28;
	static const int VORALDO_TEST_STATE_BLACK_LEVEL4 = 29;
	static const int VORALDO_TEST_STATE_BLACK_LEVEL5 = 30;

	static const int VORALDO_TEST_STATE_GOLD_LEVEL0 = 31;
	static const int VORALDO_TEST_STATE_GOLD_LEVEL1 = 32;
	static const int VORALDO_TEST_STATE_GOLD_LEVEL2 = 33;
	static const int VORALDO_TEST_STATE_GOLD_LEVEL3 = 34;
	static const int VORALDO_TEST_STATE_GOLD_LEVEL4 = 35;
	static const int VORALDO_TEST_STATE_GOLD_LEVEL5 = 36;


};

class Voraldo{ 
//   ██▒   █▓ ▒█████   ██▀███   ▄▄▄       ██▓    ▓█████▄  ▒█████  
//  ▓██░   █▒▒██▒  ██▒▓██ ▒ ██▒▒████▄    ▓██▒    ▒██▀ ██▌▒██▒  ██▒
//   ▓██  █▒░▒██░  ██▒▓██ ░▄█ ▒▒██  ▀█▄  ▒██░    ░██   █▌▒██░  ██▒
//    ▒██ █░░▒██   ██░▒██▀▀█▄  ░██▄▄▄▄██ ▒██░    ░▓█▄   ▌▒██   ██░
//     ▒▀█░  ░ ████▓▒░░██▓ ▒██▒ ▓█   ▓██▒░██████▒░▒████▓ ░ ████▓▒░
//     ░ ▐░  ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ▒░▓  ░ ▒▒▓  ▒ ░ ▒░▒░▒░ 
//     ░ ░░    ░ ▒ ▒░   ░▒ ░ ▒░  ▒   ▒▒ ░░ ░ ▒  ░ ░ ▒  ▒   ░ ▒ ▒░ 
//       ░░  ░ ░ ░ ▒    ░░   ░   ░   ▒     ░ ░    ░ ░  ░ ░ ░ ░ ▒  
//        ░      ░ ░     ░           ░  ░    ░  ░   ░        ░ ░  
//       ░                                        ░           


public:

	Voraldo(int x, int y, int z);

	Voraldo();
	~Voraldo();

	void display();


	//save
	void save_block_to_file(); 
	//save format will be a little different in V2 - the JSON
	//formatted file will have a field for filename, and will 
	//hold information such as dimensions and other pieces of
	//data of that sort. The filename will refer to a PNG
	//image in the same directory.

	//load
	void load_block_from_file();

	Palette_return_object get_palette_for_state(int state);
	//this will need to adapt to the new file storage

	const unsigned char 	 some_random_orange[3] = {255,128, 64};
	const unsigned char	  		some_random_red[3] = { 98, 12, 14};
	const unsigned char		 some_random_purple[3] = { 128, 4,168};

	void draw_point(int x, int y, int z, int state);
	void draw_line_segment(vec v1, vec v2, int state);
	void draw_triangle(vec v0, vec v1, vec v2, int state);
	void draw_sphere(int x, int y, int z, int radius, int state);
	void draw_ellipsoid(int x, int y, int z, int xrad, int yrad, int zrad, int state);
	void draw_cylinder();
	void draw_blockoid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int state);


private:

	Block* Vblock;
	Palette pal;

};