#include "DImage.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>


// BELOW ARE METHODS DESINATED FOR THE Image CLASS
string url;
vector<string> tags=vector<string>();
string fn;
string aburl;

//constructor
DImage::DImage(string s, vector<string> t){
    fn=s;
    tags=t;
	aburl=s;
}

string DImage::get_url(){
	return to_string(aburl);
}
//get the tags from the vector and return them as a string, used for writing to file
string DImage::get_tags(){
    string tgs;
    for (int i=0; i<tags.size(); i++){
		if (!(tags[i]=="" || tags[i]==" "))
            tgs.append(tags[i] +" ");
    }
    return tgs;
}
//used for browse_window when displaying the tags associated with photo
string DImage::get_disp_tags(){
	if (tags.size()==0)
		return "There are no tags associated with this photo.";

    string tgs ="Tags for this photo: ";	
    for (int i=0; i<tags.size(); i++){
		if (tags[i].size()>0){
            tgs.append(tags[i] +", ");
		}	
		else{
			tgs.append("");
		}
    }
	// the following 2 if-statements kills any ',' at the end of the list of tags. easier to read.
	// Example, tags: dog, cat, fish, -> dog, cat, fish
	if (tgs.back()==' ')
		tgs.pop_back();
	if (tgs.back()==','){
		tgs.pop_back();
		tgs.append(" ");
	}
	
    return tgs;
}
//add a tag to the vector, checks to make sure it's less than 5.
void DImage::add_tag(string s){
    if (tags.size()<5){
        tags.push_back(s);
    }
    else{
        cout << "Tags is full, " << s << " cannot be added." << endl;
    }

}

void DImage::save_info(){ //save info writes to the image file and saves loc and tags.
    ofstream write("info.txt", ios::app);
    if (!write){
        cout << "couldnt open"<< endl;
    }
    string temp = get_url() + " " + get_tags();
	write << endl << temp;
	write.close();
}


	




