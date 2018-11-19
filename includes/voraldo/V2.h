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

struct RGB{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct Vox {
	RGB color;

	//unsigned char light_intensity;
	//unsigned char ao_intensity;

	unsigned char size;

	float alpha;

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
	
	Block(){
	RGB black = {0,0,0};
	color_map["black"] = black;

	RGB white = {255,255,255};
	color_map["white"] = white;

	RGB bright_red = {255,0,0};
	color_map["bright_red"] = bright_red;

	RGB bright_green = {0,255,0};
	color_map["bright_green"] = bright_green;

	RGB bright_blue = {0,0,255};
	color_map["bright_blue"] = bright_blue;

	RGB bright_cyan = {0,255,255};
	color_map["bright_cyan"] = bright_cyan;

	RGB bright_magenta = {255,0,255};
	color_map["bright_magenta"] = bright_magenta;

	RGB bright_yellow = {255,255,0};
	color_map["bright_yellow"] = bright_yellow;

	RGB maroon = {128,0,0};
	color_map["maroon"] = maroon;

	RGB olive = {128,128,0};	
	color_map["olive"] = olive;

	RGB green = {0,128,0};
	color_map["green"] = green;

	RGB purple = {128,0,128};
	color_map["purple"] = purple;

	RGB teal = {0,128,128};
	color_map["teal"] = teal;

	RGB navy = {0,0,128};
	color_map["navy"] = navy;

	RGB coral = {255,127,80};
	color_map["coral"] = coral;

	RGB tomato = {255,99,71};
	color_map["tomato"] = tomato;

	RGB salmon = {250,128,114};
	color_map["salmon"] = salmon;

	RGB orange = {255,165,0};
	color_map["orange"] = orange;

	RGB dark_orange = {255,140,0};
	color_map["dark_orange"] = dark_orange;

	RGB gold = {255,215,0};
	color_map["gold"] = gold;

//Dawnbringer 16 color palette
	//http://pixeljoint.com/forum/forum_posts.asp?TID=12795

	RGB Dawnbringer00 = {20, 12, 28};
	color_map["Dawnbringer00"] = Dawnbringer00;
	RGB Dawnbringer01 = {68, 36, 52};
	color_map["Dawnbringer01"] = Dawnbringer01;
	RGB Dawnbringer02 = {48, 52, 109};
	color_map["Dawnbringer02"] = Dawnbringer02;
	RGB Dawnbringer03 = {78, 74, 78};
	color_map["Dawnbringer03"] = Dawnbringer03;
	RGB Dawnbringer04 = {133, 76, 48};
	color_map["Dawnbringer04"] = Dawnbringer04;
	RGB Dawnbringer05 = {52, 101, 36};
	color_map["Dawnbringer05"] = Dawnbringer05;
	RGB Dawnbringer06 = {208, 70, 72};
	color_map["Dawnbringer06"] = Dawnbringer06;
	RGB Dawnbringer07 = {117, 113, 97};
	color_map["Dawnbringer07"] = Dawnbringer07;
	RGB Dawnbringer08 = {89, 125, 206};
	color_map["Dawnbringer08"] = Dawnbringer08;
	RGB Dawnbringer09 = {210, 125, 44};
	color_map["Dawnbringer09"] = Dawnbringer09;
	RGB Dawnbringer10 = {133, 149, 161};
	color_map["Dawnbringer10"] = Dawnbringer10;
	RGB Dawnbringer11 = {109, 170, 44};
	color_map["Dawnbringer11"] = Dawnbringer11;
	RGB Dawnbringer12 = {210, 170, 153};
	color_map["Dawnbringer12"] = Dawnbringer12;
	RGB Dawnbringer13 = {109, 194, 202};
	color_map["Dawnbringer13"] = Dawnbringer13;
	RGB Dawnbringer14 = {218, 212, 94};
	color_map["Dawnbringer14"] = Dawnbringer14;
	RGB Dawnbringer15 = {222, 238, 214};
	color_map["Dawnbringer15"] = Dawnbringer15;







	data = NULL;  //declare with an empty block
	};	//call Block::init(int x, int y, int z) to populate it
	~Block(){
		std::cout << "deleting block" << std::endl;
		delete[] data;
	};

	void init(int x, int y, int z);


	RGB get_RGB_for_state(int state){	
			switch(state){
				case 0:
				{
					RGB Dawnbringer00 = {20, 12, 28};
					return Dawnbringer00;
					break;
				}
				case 1:
				{
					RGB Dawnbringer01 = {68, 36, 52};
					return Dawnbringer01;
					break;
				}
				case 2:
				{
					RGB Dawnbringer02 = {48, 52, 109};
					return Dawnbringer02;
					break;
				}
				case 3:
				{
					RGB Dawnbringer03 = {78, 74, 78};
					return Dawnbringer03;
					break;
				}
				case 4:
				{
					RGB Dawnbringer04 = {133, 76, 48};
					return Dawnbringer04;
					break;
				}
				case 5:
				{
					RGB Dawnbringer05 = {52, 101, 36};
					return Dawnbringer05;
					break;
				}
				case 6:
				{
					RGB Dawnbringer06 = {208, 70, 72};
					return Dawnbringer06;
					break;
				}
				case 7:
				{
					RGB Dawnbringer07 = {117, 113, 97};
					return Dawnbringer07;
					break;
				}
				case 8:
				{
					RGB Dawnbringer08 = {89, 125, 206};
					return Dawnbringer08;
					break;
				}
				case 9:
				{
					RGB Dawnbringer09 = {210, 125, 44};
					return Dawnbringer09;
					break;
				}
				case 10:
				{
					RGB Dawnbringer10 = {133, 149, 161};
					return Dawnbringer10;
					break;
				}
				case 11:
				{
					RGB Dawnbringer11 = {109, 170, 44};
					return Dawnbringer11;
					break;
				}
				case 12:
				{
					RGB Dawnbringer12 = {210, 170, 153};
					return Dawnbringer12;
					break;
				}
				case 13:
				{
					RGB Dawnbringer13 = {109, 194, 202};
					return Dawnbringer13;
					break;
				}
				case 14:
				{
					RGB Dawnbringer14 = {218, 212, 94};
					return Dawnbringer14;
					break;
				}
				case 15:
				{
					RGB Dawnbringer15 = {222, 238, 214};
					return Dawnbringer15;
					break;
				}
				default:
				{
					RGB BLACK = {0,0,0};
					return BLACK;
					break;
				}
			}
		}


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

	void set_data_by_3d_index(int x, int y, int z, Vox set);	
	Vox  get_data_by_3d_index(int x, int y, int z);

	Vox  get_data_by_array_index(int index){return data[index];}
	//make sure this can handle negatives - in case we do more 
	//with referencing the cube - for example ambient occlusion
	std::map<std::string, RGB> color_map;


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


	const unsigned char 	 some_random_orange[3] = {255,128, 64};
	const unsigned char	  		some_random_red[3] = { 98, 12, 14};
	const unsigned char		 some_random_purple[3] = { 128, 4,168};

	void draw_point(int x, int y, int z, Vox state);
	void draw_line_segment(vec v1, vec v2, Vox state);
	void draw_triangle(vec v0, vec v1, vec v2, Vox state);
	void draw_sphere(int x, int y, int z, int radius, Vox state);
	void draw_ellipsoid(int x, int y, int z, int xrad, int yrad, int zrad, Vox state);
	void draw_cylinder();
	void draw_blockoid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, Vox state);
	void draw_quadrilateral_hexahedron(vec a, vec b, vec c, vec d, vec e, vec f, vec g, vec h, Vox state);


	RGB get_RGB_for_state(int state){	
			switch(state){
				case 0:
				{
					RGB Dawnbringer00 = {20, 12, 28};
					return Dawnbringer00;
					break;
				}
				case 1:
				{
					RGB Dawnbringer01 = {68, 36, 52};
					return Dawnbringer01;
					break;
				}
				case 2:
				{
					RGB Dawnbringer02 = {48, 52, 109};
					return Dawnbringer02;
					break;
				}
				case 3:
				{
					RGB Dawnbringer03 = {78, 74, 78};
					return Dawnbringer03;
					break;
				}
				case 4:
				{
					RGB Dawnbringer04 = {133, 76, 48};
					return Dawnbringer04;
					break;
				}
				case 5:
				{
					RGB Dawnbringer05 = {52, 101, 36};
					return Dawnbringer05;
					break;
				}
				case 6:
				{
					RGB Dawnbringer06 = {208, 70, 72};
					return Dawnbringer06;
					break;
				}
				case 7:
				{
					RGB Dawnbringer07 = {117, 113, 97};
					return Dawnbringer07;
					break;
				}
				case 8:
				{
					RGB Dawnbringer08 = {89, 125, 206};
					return Dawnbringer08;
					break;
				}
				case 9:
				{
					RGB Dawnbringer09 = {210, 125, 44};
					return Dawnbringer09;
					break;
				}
				case 10:
				{
					RGB Dawnbringer10 = {133, 149, 161};
					return Dawnbringer10;
					break;
				}
				case 11:
				{
					RGB Dawnbringer11 = {109, 170, 44};
					return Dawnbringer11;
					break;
				}
				case 12:
				{
					RGB Dawnbringer12 = {210, 170, 153};
					return Dawnbringer12;
					break;
				}
				case 13:
				{
					RGB Dawnbringer13 = {109, 194, 202};
					return Dawnbringer13;
					break;
				}
				case 14:
				{
					RGB Dawnbringer14 = {218, 212, 94};
					return Dawnbringer14;
					break;
				}
				case 15:
				{
					RGB Dawnbringer15 = {222, 238, 214};
					return Dawnbringer15;
					break;
				}
				default:
				{
					RGB BLACK = {0,0,0};
					return BLACK;
					break;
				}
			}
		}

private:

	Block* Vblock;

	bool planetest(vec plane_point, vec plane_normal, vec test_point);

};