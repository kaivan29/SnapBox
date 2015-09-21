//My_randint_window.h
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef MY_RANDINT_WINDOW_GUARD
#define MY_RANDINT_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
//My_randint_window class
struct My_randint_window : Graph_lib::Window {
    My_randint_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

private:
    Button runagain_button; //the "run again" button
    Button next_button;     // the "next" button
    Button getimage_button;
    In_box filename;
    In_box url;
	Text error;
    bool button_pushed;     // implementation detail

    static void cb_next(Address, Address); // callback for next_button
    static void cb_runagain(Address, Address); //callback for runagain_button
    static void cb_getimage(Address, Address);
    
    int check_end(string);

    void next();            // action to be done when next_button is pressed
    void runagain();	   //action to be done when runagain_button is presses
    void getimage();
};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
