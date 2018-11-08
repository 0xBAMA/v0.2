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
using mat = linalg::aliases::double4x4;
using intvec = linalg::aliases::int3;
using veContainer = std::vector<vec>;

//V2 block class

struct Vox {
	unsigned char state;
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

	int get_x_res(){return x_res;}
	int get_y_res(){return y_res;}
	int get_z_res(){return z_res;}

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


	void set_data_by_index(int x, int y, int z, Vox set);	
	Vox  get_data_by_index(int x, int y, int z);


private:


//  ╦═╗┌─┐┌─┐┌─┐┬  ┬ ┬┌┬┐┬┌─┐┌┐┌
//  ╠╦╝├┤ └─┐│ ││  │ │ │ ││ ││││
//  ╩╚═└─┘└─┘└─┘┴─┘└─┘ ┴ ┴└─┘┘└┘


	int x_res; //how many voxels along x axis
	int y_res; //how many voxels along y axis
	int z_res; //how many voxels along z axis

	int num_cells;

	Vox *data;

	int get_index_by_xyz(int x, int y, int z);

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


	//save
	void save_block_to_file(); 
	//save format will be a little different in V2 - the JSON
	//formatted file will have a field for filename, and will 
	//hold information such as dimensions and other pieces of
	//data of that sort. The filename will refer to a PNG
	//image in the same directory.

	//load
	void load_block_from_file();
	//this will need to adapt to the new file storage

private:

	Block* Vblock;

};