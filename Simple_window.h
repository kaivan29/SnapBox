
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Simple_window : Graph_lib::Window {
    Simple_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

private:
	Button add_button;
    Button browse_button; 
    Button search_button;
	Image logo_img;
	
	bool search_pushed;
    bool browse_pushed;     // implementation detail
	bool add_pushed;

    static void cb_browse(Address, Address); // callback for next_button
	static void cb_add(Address, Address);
	static void cb_search(Address, Address);
	
    void browse();            // action to be done when next_button is pressed
	void add();
	void search();

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
