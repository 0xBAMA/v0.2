#include "../voraldo/V2.h"

Block::Block(){
	data = NULL;  //declare with an empty block
}	//call Block::init(int x, int y, int z) to populate it


void Block::init(int x, int y, int z){

	if(data != NULL){
		delete[] data;
	}

	x_res = x;
	y_res = y;
	z_res = z;

	num_cells = x_res * y_res * z_res;

	data = new Vox[num_cells];

	for(int i = 0; i < num_cells; i++){ //initialize arrays with zero values
		data[i].state = 0;
		data[i].mask = false;
	}
}

Block::~Block(){
	std::cout << "deleting block" << std::endl;
	delete[] data;
}

void Block::set_data_by_index(int x,int y,int z,Vox set){

	//validate the input - make sure you are in the block
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	bool masked = data[get_index_by_xyz(x,y,z)].mask;

	//all dimensions valid, do as the user asks
	if(x_valid && y_valid && z_valid && !masked){
		if(set.state <= 255){
			data[get_index_by_xyz(x,y,z)].state = set.state;
		}else{
			data[get_index_by_xyz(x,y,z)].state = 255;
		}
	}else{
		if(!masked){
			std::cout << std::endl << "Invalid index for set_data_by_index()" << std::endl;

			std::cout << "you used " << std::to_string(x) << " for x which should be between 0 and ";
			std::cout << std::to_string(x_res) << std::endl;

			std::cout << "you used " << std::to_string(y) << " for y which should be between 0 and ";
			std::cout << std::to_string(y_res) << std::endl;

			std::cout << "you used " << std::to_string(z) << " for z which should be between 0 and ";
			std::cout << std::to_string(z_res) << std::endl;
		}else{
			std::cout << "Cell " 
				<< std::to_string(x) << " " 
				<< std::to_string(y) << " " 
				<< std::to_string(z) << " is masked";
		}
	}

	return;
}

Vox Block::get_data_by_index(int x,int y,int z){

	//validate the input
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	if(x_valid && y_valid && z_valid){
		return(data[get_index_by_xyz(x,y,z)]); //grab the data from the long 1d array
	}else{
		std::cout << std::endl << "Invalid index for get_data_by_index()" << std::endl;

		Vox temp = {0,false};

		return(temp); //if it is outside, return an empty state 
	}
}


//Implementing this as a separate function keeps the logic more intact, I think
int Block::get_index_by_xyz(int x, int y, int z){
	return z*(y_res*x_res) + y*(x_res) + x; //this mapping was figured out on paper, but can be 
}	//described pretty succinctly - the z dimension is like pages, each of dimension x * y, then
	//the y dimension is like rows, each of dimension x, and the x dimension is the location 
	//within the row that has been specified by the z and y coordinates.


Voraldo::Voraldo(){

}

Voraldo::Voraldo(int x, int y, int z){
	Vblock = new Block;
	Vblock->init(x,y,z);
}


Voraldo::~Voraldo(){
	std::cout << "deleting voraldo object" << std::endl; 
	delete Vblock;
}



void Voraldo::save_block_to_file(){
	//produce the JSON file "default.txt"
	nlohmann::json j;
	std::string filename = "save/default.txt"; 

	j["xdim"] = Vblock->get_x_res();
	j["ydim"] = Vblock->get_y_res();
	j["zdim"] = Vblock->get_z_res();

	j["image_filename"] = "save/default.png";

	std::fstream f;

	f.open(filename);

	f << j.dump();

	f.close();

	//produce the PNG image, with a default name
	//this doesn't actually happen right now.

	//eventually we need to figure out how this
	//is going to be structured. 

}

void Voraldo::load_block_from_file(){

	//this needs to delete any existing data and make new data from the file





	//load the JSON file, "default.txt"

	//code to load file into block
	//check dimensions first and then load it all in
	int tempx = 0;
	int tempy = 0;  //variables for incoming json values
	int tempz = 0;

	std::string filename = "save/default.txt";

	nlohmann::json j; //declare json object
	std::fstream f;	  //declare fstream object

	f.open(filename); //open the user's file

	f >> j;			  //read in all the content of that file

	tempx = j.value("xdim",0);
	tempy = j.value("ydim",0); //take some specific values from the json input file
	tempz = j.value("zdim",0);	
	//the formatting is j.value("key name", "default value if key not found")



	//load the PNG image, with a name specified by the JSON file
	//this doesn't actually happen right now.

}