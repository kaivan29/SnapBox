/*
   My_randint_window.cpp
 */

#include "My_randint_window.h"
#include "get_image_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

My_randint_window::My_randint_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    runagain_button(Point(x_max()-435,580),70,20,"Run Again",cb_runagain), //run again butto at the bottom centre of the screen
    next_button(Point(x_max()-70,0), 70, 20, "Quit", cb_next),
    getimage_button(Point(350,130), 70, 20, "Get Image", cb_getimage),
    filename(Point(70,70),400,20,"Filename"),
    url(Point(70,100),400,20,"URL"),
	error(Point(20,150),"Please enter the correct format of image"),
    button_pushed(false)
{
    attach(next_button);
    attach(runagain_button);
    attach(getimage_button);
    attach(filename);
    attach(url);
	error.set_font_size(15);
}

//------------------------------------------------------------------------------
int My_randint_window::check_end(string directory)
{
    string jpg(".jpg"), gif(".gif"), jpeg("jpeg"), JPG(".JPG"), GIF(".GIF"), JPEG("JPEG");
    string::iterator filename_end = directory.end();
    string::iterator jpg_end = jpg.end();
    string::iterator gif_end = gif.end();
    string::iterator jpeg_end = jpeg.end();
    string::iterator JPG_end = JPG.end();
    string::iterator GIF_end = GIF.end();
    string::iterator JPEG_end = JPEG.end();
    for( int i = 0; i < 4; i++ )
	{
		if( *filename_end != *jpg_end &&
            *filename_end != *JPG_end &&
            *filename_end != *gif_end &&
            *filename_end != *GIF_end &&
            *filename_end != *jpeg_end &&
            *filename_end != *JPEG_end  )
        {
		//cout << "Please input correct image format"<<endl; // Need Add throw Error here
		attach(error);
		return 1;
	}
	filename_end--;
	jpg_end--;
	gif_end--;
	jpeg_end--;
	JPG_end--;
	GIF_end--;
	JPEG_end--;
	}
	return 0;
}

//------------------------------------------------------------------------------
bool My_randint_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void My_randint_window::cb_next(Address, Address pw)
// call My_randint_window::next() for the window located at pw
{  
    reference_to<My_randint_window>(pw).next();    
}
 
void My_randint_window::cb_runagain(Address, Address pw)
// call My_randint_window::runagain() for the window located at pw
{
    reference_to<My_randint_window>(pw).runagain();
}

void My_randint_window::cb_getimage(Address, Address pw)
// call My_randint_window::runagain() for the window located at pw
{
    reference_to<My_randint_window>(pw).getimage();
}


//------------------------------------------------------------------------------

void My_randint_window::next()
{
    button_pushed = true;
    exit(0); //To exit when the user presses quit
}

 
//Run Again function
void My_randint_window::getimage()
{
    button_pushed = true;
//	get_image_window w2(Point(100,200),800,600,"Get Image") ;
    string directory = filename.get_string();
	ostringstream ss;
	ss << ' " '<< directory << ' " ';
    string y = url.get_string();
	int a = check_end(directory);
    if( a == 1) //check if the url end with correct format
    { 
		Image x(Point(0,0),ss.str());
		w2.attach(x);
    //   w2.wait_for_button();
	}
 /*   else{
		//error(new Text(Point(20,150),"Please enter the correct format of image"));
	//	error.set_font_size(15);
		attach(error);
		redraw();
	}
	*/

}


 void My_randint_window::runagain()
{
    button_pushed = true;
    exit(0); //To exit when the user presses quit
}
//------------------------------------------------------------------------------
