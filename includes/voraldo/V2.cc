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

	for(int i = 0; i < num_cells; i++){ //initialize arrays

		data[i].mask = false;


		//this makes nice noise, it's from the first iteration.
		int randcheck = rand()%696;
		if(randcheck == 69){
			data[i].state = rand()%256;
		}else{
			data[i].state = 99;
		}
	}
}

Block::~Block(){
	std::cout << "deleting block" << std::endl;
	delete[] data;
}

void Block::set_data_by_3d_index(int x,int y,int z,int set){

	//validate the input - make sure you are in the block
	bool x_valid = x < x_res && x >= 0;
	bool y_valid = y < y_res && y >= 0;
	bool z_valid = z < z_res && z >= 0;

	bool masked = data[get_array_index_by_xyz(x,y,z)].mask;

	//all dimensions valid, do as the user asks
	if(x_valid && y_valid && z_valid && !masked){
		if(set <= 255){
			data[get_array_index_by_xyz(x,y,z)].state = set;
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

	double y_upper = -1.618;

	double y_lower_long = 1.0;
	double y_lower_short = 0.8;

	double x_short = 1.0;
	double x_mid = 1.618;
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
	centers[6] = vec2(400,2803);
	center_x_vecs[6] = vec2(x_long,0);
	center_y_vecs[6] = vec2(0,y_upper);
	center_z_vecs[6] = vec2(-1.0*x_short,0);

	img.draw_point(1501,2503,Voraldo::white); //center #8
	centers[7] = vec2(1501,2803);
	center_x_vecs[7] = vec2(x_mid,0);
	center_y_vecs[7] = vec2(0,y_upper);
	center_z_vecs[7] = vec2(-1.0*x_mid,0);

	img.draw_point(2503,2503,Voraldo::white); //center #9
	centers[8] = vec2(2603,2803);
	center_x_vecs[8] = vec2(x_short,0);
	center_y_vecs[8] = vec2(0,y_upper);
	center_z_vecs[8] = vec2(-1.0*x_long,0);

	int curr_x = 0;
	int curr_y = 0;

	int state = 0;

	Palette_entry c;

	for(int x = 0; x < Vblock->get_x_res(); x++){
		for(int y = 0; y < Vblock->get_y_res(); y++){
			for(int z = 0; z < Vblock->get_z_res(); z++){
				state = Vblock->get_data_by_3d_index(x,y,z).state;
				for(int w = 0; w <= 8; w++){

					curr_x = int(floor(centers[w][0]+x*center_x_vecs[w][0]+y*center_y_vecs[w][0]+z*center_z_vecs[w][0]));
					curr_y = int(floor(centers[w][1]+x*center_x_vecs[w][1]+y*center_y_vecs[w][1]+z*center_z_vecs[w][1]));

					c = get_palette_for_state(state);

					if(c.draw_circle){
						img.draw_circle(curr_x,curr_y,c.radius,c.circle_color,c.circle_alpha);
					}

					if(c.draw_point){
						img.draw_point(curr_x,curr_y,c.point_color);
					}
				}
			}
		}
	}

	img.save_bmp("output.bmp");
}

Palette_entry Voraldo::get_palette_for_state(int state){

	Palette_entry temp;
	temp.point_color = Voraldo::black;
	temp.point_alpha = 0.0;
	temp.draw_point = false;
	temp.circle_color = Voraldo::black;
	temp.radius = 0;
	temp.circle_alpha = 0.0;
	temp.draw_circle = false;

	switch (state){
		case 0: //empty point
			break;
		case 1: //white point
			temp.point_color = Voraldo::white;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 2: //black point
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 3: //dark grey
			temp.point_color = Voraldo::grey_05;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 4:	//middle-dark grey
			temp.point_color = Voraldo::grey_15;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 5:	//middle grey
			temp.point_color = Voraldo::grey_25;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 6: //middle-light grey
			temp.point_color = Voraldo::grey_36;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 7: //light grey
			temp.point_color = Voraldo::grey_47;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 8: //dark red
			temp.point_color = Voraldo::red_05;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 9:	//middle-dark red
			temp.point_color = Voraldo::red_15;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 10://middle red
			temp.point_color = Voraldo::red_25;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::red_25;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 11: //middle-light red
			temp.point_color = Voraldo::red_36;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 12: //light red
			temp.point_color = Voraldo::red_47;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::red_47;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 13: //dark green
			temp.point_color = Voraldo::green_05;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 14:	//middle-dark green
			temp.point_color = Voraldo::green_15;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 15://middle green
			temp.point_color = Voraldo::green_25;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::green_25;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 16: //middle-light green
			temp.point_color = Voraldo::green_36;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 17: //light green
			temp.point_color = Voraldo::green_47;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::green_47;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 18: //dark blue
			temp.point_color = Voraldo::blue_05;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 19: //middle-dark blue
			temp.point_color = Voraldo::blue_15;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 20://middle blue
			temp.point_color = Voraldo::blue_25;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::blue_25;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 21: //middle-light blue
			temp.point_color = Voraldo::blue_36;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			break;
		case 22: //light blue
			temp.point_color = Voraldo::blue_47;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::blue_47;
			temp.radius = 1;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
			break;
		case 23:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.9;
			temp.draw_circle = true;
		case 24:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.7;
			temp.draw_circle = true;
		case 25:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.5;
			temp.draw_circle = true;
		case 26:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.4;
			temp.draw_circle = true;
		case 27:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.3;
			temp.draw_circle = true;
		case 28:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.2;
			temp.draw_circle = true;
		case 29:
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::grey_20;
			temp.radius = 2;
			temp.circle_alpha = 0.1;
			temp.draw_circle = true;
		case 30: //black point with white shroud
			temp.point_color = Voraldo::black;
			temp.point_alpha = 1.0;
			temp.draw_point = true;
			temp.circle_color = Voraldo::white;
			temp.radius = 2;
			temp.circle_alpha = 0.2;
			temp.draw_circle = true;
			break;
		case 69:	//
			break;
		default:
			break;
	}

	return (temp);
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

			//can get away with a 2d array, on account of it being a 2d image
			//with a lot of rows. The format is very compatible with the 1d
			//representation of the block, since it is written out in the
			//same general order as you would read text, left to right and
			//top to bottom.

			int temp_state = int(Vblock->get_data_by_array_index(index).state);
			switch(temp_state){
				case 0:
					img.draw_point(x,y,Voraldo::some_random_orange);
					break;
				case 1:
					img.draw_point(x,y,Voraldo::white);
					break;
				case 17:
					img.draw_point(x,y,Voraldo::some_random_purple);
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

void Voraldo::draw_point(int x, int y, int z, int state){
	Vblock->set_data_by_3d_index(x,y,z,state);
}

void Voraldo::draw_line_segment(int x1, int x2, int y1, int y2, int z1, int z2, int state){
	double xdisp = x2 - x1;
	double ydisp = y2 - y1;
	double zdisp = z2 - z1;

	double length = std::sqrt(xdisp*xdisp + ydisp*ydisp + zdisp*zdisp);

	int num_steps = 2*std::floor(length);

	xdisp = xdisp/num_steps;
	ydisp = ydisp/num_steps;
	zdisp = zdisp/num_steps;

	double current_x = x1;
	double current_y = y1;
	double current_z = z1;

	for(int i = 0; i < num_steps; i++){
		draw_point(current_x,current_y,current_z,state);
		current_x += xdisp;
		current_y += ydisp;
		current_z += zdisp;
	}
}


void Voraldo::draw_triangle(int x0, int y0, int z0, int x1, int y1, int z1, int x2, int y2, int z2, int state){
	//point zero is the origin point

	double disp1x = x0-x1; 
	double disp1y = y0-y1;
	double disp1z = z0-z1;

	double disp2x = x0-x2; 
	double disp2y = y0-y2;
	double disp2z = z0-z2;

	double length1 = std::sqrt(disp1x*disp1x+disp1y*disp1y+disp1z*disp1z);
	double length2 = std::sqrt(disp2x*disp2x+disp2y*disp2y+disp2z*disp2z);

	double length;

	if(length1 > length2){
		length = length1;
	}else{
		length = length2;
	}

	disp1x = disp1x/length;
	disp1y = disp1y/length;
	disp1z = disp1z/length;

	disp2x = disp2x/length;
	disp2y = disp2y/length;
	disp2z = disp2z/length;

	double current_x1 = x1;//start at x1
	double current_y1 = y1;//start at y1
	double current_z1 = z1;//start at z1

	double current_x2 = x2;//start at x2
	double current_y2 = y2;//start at y2
	double current_z2 = z2;//start at z2

	for (int i = 0; i < std::floor(length); ++i){
		draw_line_segment(current_x1,current_y1,current_z1,current_x2,current_y2,current_z2,state);

		current_x1 += disp1x;
		current_y1 += disp1y;
		current_z1 += disp1z;

		current_x2 += disp2x;
		current_y2 += disp2y;
		current_z2 += disp2z;
	}


}

void Voraldo::draw_sphere(int x, int y, int z, int radius, int state){
	for(int i = 0; i < Vblock->get_x_res(); i++){	
		for(int j = 0; j < Vblock->get_y_res(); j++){
			for(int k = 0; k < Vblock->get_z_res(); k++){
				double testx = (i-x)*(i-x);	//apply offsets and square
				double testy = (j-y)*(j-y);
				double testz = (k-z)*(k-z);

				if((testx + testy + testz) < radius*radius){	//pretty self explainatory, equation of sphere
					Vblock->set_data_by_3d_index(i,j,k,state);
				}
			}
		}
	}
}

void Voraldo::draw_ellipsoid(int x, int y, int z, int xrad, int yrad, int zrad, int state){
	for(int i = 0; i < Vblock->get_x_res(); i++){	
		for(int j = 0; j < Vblock->get_y_res(); j++){
			for(int k = 0; k < Vblock->get_z_res(); k++){
				double testx = (i-x)*(i-x);	//apply offsets and square
				double testy = (j-y)*(j-y);
				double testz = (k-z)*(k-z);

				double radx = xrad*xrad;
				double rady = yrad*yrad;
				double radz = zrad*zrad;

				double result = testx/radx + testy/rady + testz/radz;

				if(result <= 1){	//point inside ellipsoid - do we want to be able to invert this?
					//(outside, or on the surface, with >= and ==, respectively)
					Vblock->set_data_by_3d_index(i,j,k,state); 
				}
			}
		}
	}
}

void Voraldo::draw_cylinder(){

}

void Voraldo::draw_blockoid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int state){
	for(int i = 0; i < Vblock->get_x_res(); i++){	
		for(int j = 0; j < Vblock->get_y_res(); j++){
			for(int k = 0; k < Vblock->get_z_res(); k++){

				bool xtest = i <= xmax && i >= xmin;
				bool ytest = i <= ymax && i >= ymin;
				bool ztest = i <= zmax && i >= zmin;

				if(xtest && ytest && ztest){
					Vblock->set_data_by_3d_index(i,j,k,state);
				}
			}
		}
	}
}
