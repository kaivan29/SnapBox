//My_randint_window.h
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GET_IMAGE_WINDOW_GUARD
#define GET_IMAGE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
//get_image_window class
struct get_image_window : Graph_lib::Window {
    get_image_window(Point xy, int w, int h, const string& title );
	~get_image_window();
	
    bool wait_for_button(); // simple event loop

private:
    Button next_button;     // the "next" button
    Button getimage_button;
    Button discard_button;     // the "next" button
	
    In_box filename;
	In_box tag1;
	In_box tag2;
	In_box tag3;
	In_box tag4;
	In_box tag5;
	
	Out_box t_info;
	Out_box info;

    Text instruction;
	Text tags_instruction;
	Text tags_name;
	
	vector<string> remove_dup(vector<string> tags);
	
	bool button_pushed;     // implementation detail

    static void cb_next(Address, Address); 
    static void cb_getimage(Address, Address);
    static void cb_discard(Address, Address); 

    
    int check_end(string); // To check the end of the filename or the URL of image entered by user
	int url(string); //To check the url of the image entered by user
	string get_filetype(string);
	int check_tags(vector <string>);
	
    void next();          //actions to be done when corresponding buttons are pressed
    void getimage();
    void discard();	  
};

//------------------------------------------------------------------------------

#endif 
