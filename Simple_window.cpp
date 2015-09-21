/*
	Simple window. Designed as the mainframe to AggieSnap.

*/
#include "Simple_window.h"
#include "Browse_window.h"
#include "get_image_window.h"
#include "Search_window.h"


using namespace Graph_lib;

//------------------------------------------------------------------------------
//instantiate window
Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	
	add_button(Point(100,240), 180, 40, "Add an Image", cb_add),
    add_pushed(false),
	
	browse_button(Point(100,320),180,40,"Browse Images", cb_browse), 
	browse_pushed(false),   
	
	search_button(Point(100,400),180,40,"Search Images by Tag", cb_search), 
	search_pushed(false),
	
	logo_img(Point(85,20),"logo.jpeg")
	
{
	//attach
	attach(add_button);
    attach(browse_button);
	attach(search_button);
	attach(logo_img);
	
}



//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
//event loop to handle actions and buttons pressed
{
    show();
    browse_pushed = false;
	
#if 0
    // Simpler handler
    while (!browse_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return browse_pushed;
}

//------------------------------------------------------------------------------
// callbacks below for the button actions
void Simple_window::cb_browse(Address, Address pw)
{  
    reference_to<Simple_window>(pw).browse();    
}

void Simple_window::cb_add(Address, Address pw)
{  
    reference_to<Simple_window>(pw).add();  

}

void Simple_window::cb_search(Address, Address pw)
{  
    reference_to<Simple_window>(pw).search();  

}



//------------------------------------------------------------------------------
// bring up the new windows
void Simple_window::browse()
{
	Browse_window w2(Point(90,100),700,800,"Browse Images");
	w2.wait_for_button();
}

void Simple_window::add()
{
    get_image_window w3(Point(90,100),800,600,"Add Image");
    w3.wait_for_button();
}

void Simple_window::search()
{
    Search_window w4(Point(90,100),700,700,"Search Images");
    w4.wait_for_button();
}

//------------------------------------------------------------------------------
