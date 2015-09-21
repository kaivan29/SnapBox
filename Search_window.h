
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SEARCH_WINDOW_GUARD
#define SEARCH_WINDOW_GUARD 1

#include "GUI.h"   
#include "Graph.h"
#include "Image_Handler.h"
#include "DImage.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Search_window : Graph_lib::Window {
    Search_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop
    ~Search_window();
	
private:
	Button next_button;
    Button prev_button; 
	Button back_button;
	Button search_button;
	Button clear_button;
	
	In_box stag1;
	In_box stag2;
	In_box stag3;
	In_box stag4;
	In_box stag5;
	
	Out_box misspell;
	
	Text t;
	
	Image_Handler ii;
	
	bool next_pushed;
    bool prev_pushed;     // implementation detail
	bool back_pushed;
	bool search_pushed;
	bool clear_pushed;
	
	void display();

    static void cb_next(Address, Address); // callback for next_button
	static void cb_prev(Address, Address);
	static void cb_back(Address, Address);
	static void cb_search(Address, Address);
	static void cb_clear(Address, Address);
	
    void next();            // action to be done when next_button is pressed
	void prev();
	void back();
	void search();
	void clear();

};

//------------------------------------------------------------------------------

#endif // SEARCH_WINDOW_GUARD
