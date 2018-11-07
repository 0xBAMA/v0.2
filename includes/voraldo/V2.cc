#include "../voraldo/V2.h"

Block::Block(int x,int y,int z){
	x_res = x;
	y_res = y;
	z_res = z;

	num_cells = x_res * y_res * z_res;

	data = new unsigned char[num_cells];
	mask = new bool[num_cells];

	for(int i = 0; i < num_cells; i++){ //initialize arrays with zero values
		data[i] = 0;
		mask[i] = false;
	}
}

void Block::set_data_by_index(int x,int y,int z,int set){

	//validate the input - make sure you are in the block
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	bool masked = mask[get_index_by_xyz(x,y,z)];

	//all dimensions valid, do as the user asks
	if(x_valid && y_valid && z_valid && !masked){
		if(set <= 255){
			data[get_index_by_xyz(x,y,z)] = set;
		}else{
			data[get_index_by_xyz(x,y,z)] = 255;
		}
	}else{
		if(!masked){
			std::cout << std::endl << "Invalid index for set_data_by_index()" << std::endl;
			std::cout << "you used " << std::to_string(x) << " which should be between 0 and ";
			std::cout << std::to_string(x_res) << std::endl;
			std::cout << "you used " << std::to_string(y) << " which should be between 0 and ";
			std::cout << std::to_string(y_res) << std::endl;
			std::cout << "you used " << std::to_string(z) << " which should be between 0 and ";
			std::cout << std::to_string(z_res) << std::endl;
		}else{
			std::cout << "Cell " << std::to_string(x) << " " << std::to_string(y) << " " << std::to_string(z) << " is masked";
		}
	}

	return;
}

int Block::get_data_by_index(int x,int y,int z){

	//validate the input
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	if(x_valid && y_valid && z_valid){
		return(data[get_index_by_xyz(x,y,z)]); //grab the data from the long 1d array
	}else{
		std::cout << std::endl << "Invalid index for get_data_by_index()" << std::endl;
		return(0); //if it is outside, return an empty state
	}
}


//Implementing this as a separate function keeps the logic more intact, I think
int Block::get_index_by_xyz(int x, int y, int z){
	return z*(y_res*x_res) + y*(x_res) + x; //this mapping was figured out on paper, but can be 
}	//described pretty succinctly - the z dimension is like pages, each of dimension x * y, then
	//the y dimension is like rows, each of dimension x, and the x dimension is the location 
	//within the row that has been specified by the z and y coordinates.


Voraldo::Voraldo(int x, int y, int z){
	Vblock = new Block(x,y,z);
}



void Voraldo::save_block_to_file(){
	//produce the JSON file "default.txt"
	nlohmann::json j;
	std::string filename = "default.txt"; 

	j["xdim"] = Vblock->get_x_res();
	j["ydim"] = Vblock->get_y_res();
	j["zdim"] = Vblock->get_z_res();

	j["image_filename"] = "default.png";

	//produce the PNG image, with a default name

	std::fstream f;

	f.open(filename);

	f << j.dump();

	f.close();

}

void Voraldo::load_block_from_file(){
	//load the JSON file, "default.txt"

	//load the PNG image, with a name specified by the JSON file

}