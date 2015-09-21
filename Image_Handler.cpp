#include "std_lib_facilities_3.h"
#include "Simple_window.h"
#include "Graph.h"
#include "DImage.h"
#include "Image_Handler.h"
#include <iostream>
//In the callback for the buttons next and prev, prev_phot() will be called and then displayed
// in the callback method

vector<DImage> images;
// vector to hold our images

Image_Handler::Image_Handler(bool b){ // b is true if we want it to loadphotos()
	index=0;	
	vector<DImage> images=vector<DImage>();
	if (b)
		load_photos();
}

void Image_Handler::prev_photo(){
	--index;
    if (index < 0){
		index=images.size()-1;
		if (index<0)
			index=0;
	}		
}
// above and below methods to navigate with the vector of images
void Image_Handler::next_photo(){
	++index;
	if (index>=images.size())
		index=0;	
}
// loads the photos from the file "info.txt"
void Image_Handler::load_photos(){
	ifstream input("info.txt");
	if (!input){
		cout << "Error: Could not open file.";		
	}else{
		int loops =0;
 		string s;
		while (!input.eof()){
			if (loops==0){
				++loops;
				getline(input,s);			
				continue;
			}	
			vector<string> ts;
			getline(input,s);
			string loc;
			stringstream line(s);
			for (int i=0; i<6; i++){
				if (i==0){
					line >> loc;
					}
				else{
					string temp;
					line >> temp;
					if (!(temp=="" || temp==" "))
						ts.push_back(temp);
				}
			}
			images.push_back(DImage(loc, ts));
			++loops;
		}
	}
}
		
int Image_Handler::get_index(){
	return index; // get picture index
}

vector<DImage> Image_Handler::get_images(){
	return images; // returns the vector
}

DImage Image_Handler::get_current() {
	return images[get_index()]; //grabs current image
}

void Image_Handler::add(DImage d){
	images.push_back(d); // add a new image to the vector
}

void Image_Handler::clear(){
	images.clear(); // delete all images
}

void Image_Handler::del_image(){
	--index; 
	if (index<0 && images.size()!=0){
		index=images.size()-1;
	}
	else if(images.size()==0){
		index=0;
	}
}

