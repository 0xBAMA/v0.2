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

//#include <bitset> 
//not in use right now

using vec = linalg::aliases::double4;
using vec2 = linalg::aliases::double2;
using mat = linalg::aliases::double4x4;
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
/*
 ┬─┐┌─┐┌┐ 
 ├┬┘│ ┬├┴┐
 ┴└─└─┘└─┘
*/

	int red;
	int green;
	int blue;
};

struct Palette_entry{
	const unsigned char *point_color;
	double point_alpha;
	bool draw_point;

	const unsigned char *circle_color;
	int radius;
	double circle_alpha;
	bool draw_circle;
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

	Palette_entry get_palette_for_state(int state);
	//this will need to adapt to the new file storage

	const unsigned char 	 some_random_orange[3] = {255,128, 64};
	const unsigned char	  		some_random_red[3] = { 98, 12, 14};
	const unsigned char		 some_random_purple[3] = { 128, 4,168};

	const unsigned char 				  black[3] = {  0,  0,  0};

	//greys
	const unsigned char 		  		grey_01[3] = {  5,  5,  5};
	const unsigned char 		  		grey_02[3] = { 10, 10, 10};
	const unsigned char 		  		grey_03[3] = { 15, 15, 15};
	const unsigned char 		  		grey_04[3] = { 20, 20, 20};
	const unsigned char 		  		grey_05[3] = { 25, 25, 25};
	const unsigned char 		  		grey_06[3] = { 30, 30, 30};
	const unsigned char 		  		grey_07[3] = { 35, 35, 35};
	const unsigned char 		  		grey_08[3] = { 40, 40, 40};
	const unsigned char 		  		grey_09[3] = { 45, 45, 45};
	const unsigned char 		  		grey_10[3] = { 50, 50, 50};
	const unsigned char 		  		grey_11[3] = { 55, 55, 55};
	const unsigned char 		  		grey_12[3] = { 60, 60, 60};
	const unsigned char 		  		grey_13[3] = { 65, 65, 65};
	const unsigned char 		  		grey_14[3] = { 70, 70, 70};
	const unsigned char 		  		grey_15[3] = { 75, 75, 75};
	const unsigned char 		  		grey_16[3] = { 80, 80, 80};
	const unsigned char 		  		grey_17[3] = { 85, 85, 85};
	const unsigned char 		  		grey_18[3] = { 90, 90, 90};
	const unsigned char 		  		grey_19[3] = { 95, 95, 95};
	const unsigned char 		  		grey_20[3] = {100,100,100};
	const unsigned char 		  		grey_21[3] = {105,105,105};
	const unsigned char 		  		grey_22[3] = {110,110,110};
	const unsigned char 		  		grey_23[3] = {115,115,115};
	const unsigned char 		  		grey_24[3] = {120,120,120};
	const unsigned char 		  		grey_25[3] = {125,125,125};
	const unsigned char 		  		grey_26[3] = {130,130,130};
	const unsigned char 		  		grey_27[3] = {135,135,135};
	const unsigned char 		  		grey_28[3] = {140,140,140};
	const unsigned char 		  		grey_29[3] = {145,145,145};
	const unsigned char 		  		grey_30[3] = {150,150,150};
	const unsigned char 		  		grey_31[3] = {155,155,155};
	const unsigned char 		  		grey_32[3] = {160,160,160};
	const unsigned char 		  		grey_33[3] = {165,165,165};
	const unsigned char 		  		grey_34[3] = {170,170,170};
	const unsigned char 		  		grey_35[3] = {175,175,175};
	const unsigned char 		  		grey_36[3] = {180,180,180};
	const unsigned char 		  		grey_37[3] = {185,185,185};
	const unsigned char 		  		grey_38[3] = {190,190,190};
	const unsigned char 		  		grey_39[3] = {195,195,195};
	const unsigned char 		  		grey_40[3] = {200,200,200};
	const unsigned char 		  		grey_41[3] = {205,205,205};
	const unsigned char 		  		grey_42[3] = {210,210,210};
	const unsigned char 		  		grey_43[3] = {215,215,215};
	const unsigned char 		  		grey_44[3] = {220,220,220};
	const unsigned char 		  		grey_45[3] = {225,225,225};
	const unsigned char 		  		grey_46[3] = {230,230,230};
	const unsigned char 		  		grey_47[3] = {235,235,235};
	const unsigned char 		  		grey_48[3] = {240,240,240};
	const unsigned char 		  		grey_49[3] = {245,245,245};
	const unsigned char 		  		grey_50[3] = {250,250,250};


	const unsigned char				  	  white[3] = {255,255,255};


	//reds
	const unsigned char 		  		red_05[3] = { 25,  0,  0};
	const unsigned char 		  		red_15[3] = { 75,  0,  0};
	const unsigned char 		  		red_25[3] = {125,  0,  0};
	const unsigned char 		  		red_36[3] = {180,  0,  0};
	const unsigned char 		  		red_47[3] = {235,  0,  0};

	const unsigned char 		  		green_05[3] = {0, 25,  0};
	const unsigned char 		  		green_15[3] = {0, 75,  0};
	const unsigned char 		  		green_25[3] = {0,125,  0};
	const unsigned char 		  		green_36[3] = {0,180,  0};
	const unsigned char 		  		green_47[3] = {0,235,  0};

	const unsigned char 		  		blue_05[3] = {0,0, 25};
	const unsigned char 		  		blue_15[3] = {0,0, 75};
	const unsigned char 		  		blue_25[3] = {0,0,125};
	const unsigned char 		  		blue_36[3] = {0,0,180};
	const unsigned char 		  		blue_47[3] = {0,0,235};

	void draw_point(int x, int y, int z, int state);
	void draw_line_segment(int x1, int x2, int y1, int y2, int z1, int z2, int state);
	void draw_triangle(int x0, int y0, int z0, int x1, int y1, int z1, int x2, int y2, int z2, int state);
	void draw_sphere(int x, int y, int z, int radius, int state);
	void draw_ellipsoid(int x, int y, int z, int xrad, int yrad, int zrad, int state);
	void draw_cylinder();
	void draw_blockoid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int state);


private:

	Block* Vblock;

};