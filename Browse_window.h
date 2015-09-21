
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef BROWSE_WINDOW_GUARD
#define BROWSE_WINDOW_GUARD 1

#include "GUI.h"   
#include "Graph.h"
#include "DImage.h"
#include "Image_Handler.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Browse_window : Graph_lib::Window {
    Browse_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop
    ~Browse_window();
	
private:
	Button next_button;
    Button prev_button; 
	Button back_button;
	Button del_button;
	Button edit_button;
	
	Image_Handler i;
	
	bool next_pushed;
    bool prev_pushed;     // implementation detail
	bool back_pushed;
	bool del_pushed;
	bool edit_pushed;
	bool save_pushed;

	//edit tags option
	Text instruction;
	In_box tag1;
	In_box tag2;
	In_box tag3;
	In_box tag4;
	In_box tag5;
	Button save_button;
	
	
	Out_box info;
	
	void display();
	vector<string> remove_dup(vector<string>);
	
    static void cb_next(Address, Address); // callback for next_button
	static void cb_prev(Address, Address);
	static void cb_back(Address, Address);
	static void cb_del(Address, Address);
	static void cb_edit(Address, Address);
	static void cb_save(Address, Address);
	
    void next();            // action to be done when next_button is pressed
	void prev();
	void back();
	void del();
	void edit();
	void save();
	
	bool check_tags();

};

//------------------------------------------------------------------------------

#endif // Browse_window_GUARD
