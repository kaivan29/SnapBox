#include "std_lib_facilities_3.h"
// #include "randint.h"
#include "My_randint_window.h" //Including the My_randint_window.h, which has a Run Again button and a quit button
#include "Graph.h"
// #include "Simple_window.h"

int main()
try{
     while(true)
    {
	if(H112 != 201206L)error("Error: incorrect std_lib_facilities_3.h version ",
		  	   H112);
//	Simple_window win1(Point(100,200),800,600,"MENU" ); //A window with the name Initials
	My_randint_window win1(Point(100,200),800,600,"Random Digit" ) ; //A window with the name Initials

	vector <int> v(10,0);

	Text t(Point(1,50),"Enter the filename or the URL of the picture you want to look up for");
//	Text t1(Point(50,50),"COUNT");

	t.set_font_size(15);
//	t1.set_font_size(15);

        t.set_color(Color::black);
//      t1.set_color(Color::black);
	win1.attach(t);
//	win1.attach(t1);

	win1.wait_for_button(); //Giving the control to the display engine

    }
return 0;
}

catch (exception& e)
{
	cerr << "\n error :" << e.what() << " \n";
	keep_window_open();
	return 1;
}
	
catch (...)
{
	cerr << " Unknown Exception \n ";
	keep_window_open();
	return 2;
}

