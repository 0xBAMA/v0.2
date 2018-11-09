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
		data[i].state = std::rand()%255;
		data[i].mask = false;
	}
}

Block::~Block(){
	std::cout << "deleting block" << std::endl;
	delete[] data;
}

void Block::set_data_by_3d_index(int x,int y,int z,Vox set){

	//validate the input - make sure you are in the block
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	bool masked = data[get_array_index_by_xyz(x,y,z)].mask;

	//all dimensions valid, do as the user asks
	if(x_valid && y_valid && z_valid && !masked){
		if(set.state <= 255){
			data[get_array_index_by_xyz(x,y,z)].state = set.state;
		}else{
			data[get_array_index_by_xyz(x,y,z)].state = 255;
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

Vox Block::get_data_by_3d_index(int x,int y,int z){

	//validate the input
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	if(x_valid && y_valid && z_valid){
		return(data[get_array_index_by_xyz(x,y,z)]); //grab the data from the long 1d array
	}else{
		std::cout << std::endl << "Invalid index for get_data_by_3d_index()" << std::endl;

		Vox temp = {0,false};

		return(temp); //if it is outside, return an empty state 
	}
}


//Implementing this as a separate function keeps the logic more intact, I think
int Block::get_array_index_by_xyz(int x, int y, int z){
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

void Voraldo::display(){

	double y_upper = -2.28;

	double y_lower_long = 1.0;
	double y_lower_short = 0.8;

	double x_short = 1.0;
	double x_mid = 1.73;
	double x_long = 2.26;

	using namespace cimg_library;

	CImg<unsigned char> img(3005,3005,1,3,0);

//vertical dividers
	img.draw_line(1001,0,1001,3004,Voraldo::grey_20);
	img.draw_line(2003,0,2003,3004,Voraldo::grey_20);

//horizontal dividers
	img.draw_line(0,1001,3004,1001,Voraldo::grey_20);
	img.draw_line(0,2003,3004,2003,Voraldo::grey_20);

//centers

	vec2 centers[9];
	vec2 center_x_vecs[9];
	vec2 center_y_vecs[9];
	vec2 center_z_vecs[9];

	//first row
	img.draw_point( 500, 500,Voraldo::white); //center #1
	centers[0] = vec2(400,700);
	center_x_vecs[0] = vec2(x_long,0);
	center_y_vecs[0] = vec2(0,y_upper);
	center_z_vecs[0] = vec2(-1.0*x_short,y_lower_long);

	img.draw_point(1501, 500,Voraldo::white); //center #2
	centers[1] = vec2(1501,500);
	center_x_vecs[1] = vec2(-1.0*x_mid,y_lower_long);
	center_y_vecs[1] = vec2(0,y_upper);
	center_z_vecs[1] = vec2(x_mid,y_lower_long);

	img.draw_point(2503, 500,Voraldo::white); //center #3
	centers[2] = vec2(2603,700);
	center_x_vecs[2] = vec2(x_short,y_lower_long);
	center_y_vecs[2] = vec2(0,y_upper);
	center_z_vecs[2] = vec2(-1.0*x_long,0);

	//second row
	img.draw_point( 500,1501,Voraldo::white); //center #4
	centers[3] = vec2(400,1701);
	center_x_vecs[3] = vec2(x_long,0);
	center_y_vecs[3] = vec2(0,y_upper);
	center_z_vecs[3] = vec2(-1.0*x_short,y_lower_short);

	img.draw_point(1501,1501,Voraldo::white); //center #5
	centers[4] = vec2(1501,1576);
	center_x_vecs[4] = vec2(x_mid,y_lower_short);
	center_y_vecs[4] = vec2(0,y_upper);
	center_z_vecs[4] = vec2(-1.0*x_mid,y_lower_short);

	img.draw_point(2503,1501,Voraldo::white); //center #6
	centers[5] = vec2(2603,1701);
	center_x_vecs[5] = vec2(x_short,y_lower_short);
	center_y_vecs[5] = vec2(0,y_upper);
	center_z_vecs[5] = vec2(-1.0*x_long,0);

	//third row
	img.draw_point( 500,2503,Voraldo::white); //center #7
	centers[6] = vec2(400,2903);
	center_x_vecs[6] = vec2(x_long,0);
	center_y_vecs[6] = vec2(0,y_upper);
	center_z_vecs[6] = vec2(-1.0*x_short,0);

	img.draw_point(1501,2503,Voraldo::white); //center #8
	centers[7] = vec2(1501,2903);
	center_x_vecs[7] = vec2(x_mid,0);
	center_y_vecs[7] = vec2(0,y_upper);
	center_z_vecs[7] = vec2(-1.0*x_mid,0);

	img.draw_point(2503,2503,Voraldo::white); //center #9
	centers[8] = vec2(2603,2903);
	center_x_vecs[8] = vec2(x_short,0);
	center_y_vecs[8] = vec2(0,y_upper);
	center_z_vecs[8] = vec2(-1.0*x_long,0);

	int curr_x = 0;
	int curr_y = 0;

	int state = 0;

	for(int x = 0; x < Vblock->get_x_res(); x++){
		for(int y = 0; y < Vblock->get_y_res(); y++){
			for(int z = 0; z < Vblock->get_z_res(); z++){
				state = Vblock->get_data_by_3d_index(x,y,z).state;
				for(int w = 0; w <= 8; w++){

					curr_x = int(floor(centers[w][0]+x*center_x_vecs[w][0]+y*center_y_vecs[w][0]+z*center_z_vecs[w][0]));
					curr_y = int(floor(centers[w][1]+x*center_x_vecs[w][1]+y*center_y_vecs[w][1]+z*center_z_vecs[w][1]));

					switch(state){
						case 0:
							img.draw_point(curr_x,curr_y,Voraldo::black);
							break;
						case 1:
							img.draw_point(curr_x,curr_y,Voraldo::grey_03);
							break;
						case 2:
							img.draw_point(curr_x,curr_y,Voraldo::grey_07);
							break;
						case 3:
							img.draw_point(curr_x,curr_y,Voraldo::grey_18);
							break;
						case 4:
							img.draw_point(curr_x,curr_y,Voraldo::grey_26);
							break;
						case 5:
							img.draw_point(curr_x,curr_y,Voraldo::grey_32);
							break;
						case 6:
							img.draw_point(curr_x,curr_y,Voraldo::grey_40);
							break;
						case 7:
							img.draw_point(curr_x,curr_y,Voraldo::grey_45);
							break;
						case 8:
							img.draw_point(curr_x,curr_y,Voraldo::grey_50);
							break;
						case 9:
							img.draw_point(curr_x,curr_y,Voraldo::white);
							break;
						default:
							break;
					}
				}
			}
		}
	}

	img.save_bmp("output.bmp");
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

	using namespace cimg_library;

	int imagex = Vblock->get_x_res();
	int imagey = Vblock->get_y_res()*Vblock->get_z_res();

	CImg<unsigned char> img(imagex,imagey,1,3,128);  
	//declare image with one color per pixel, one channel. 
	//full of 128 values, the dimensions are x = x-res, y = y-res*z-res

	const unsigned char color[] = { 255,128, 64};
	img.draw_point(50,50,color);

	int index = 0;

	for (int y = 0; y < imagey; y++){
		for (int x = 0; x < imagex; x++){
			int temp_state = int(Vblock->get_data_by_array_index(index).state);
			switch(temp_state){
				case 0:
					img.draw_point(x,y,Voraldo::some_random_orange);
					break;
				case 1:
					img.draw_point(x,y,Voraldo::white);
					break;
				default:
					break;
			}

			index++;
		}
	}

	img.save_bmp("example.bmp");

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