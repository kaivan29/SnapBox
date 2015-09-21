#include "std_lib_facilities_3.h"
#include "get_image_window.h"
#include "DImage.h"
#include <stdio.h>
#include <ctype.h>

using namespace Graph_lib;

// keeps track of how many images have been added
vector<string> remove_dup(vector<string> tags);
int get_num(); 
int counter = get_num(); 
int ct=0; // for checking tags

//grabs num to check for new file saves
int get_num(){
	ifstream numRead("num.txt");
	if(!numRead)
	{
		cout << "error. no file.";
	}
	else{
		numRead >> counter;
		return counter;
	}
}

//------------------------------------------------------------------------------
// destructor
get_image_window::~get_image_window(){
	ofstream of("num.txt",ios::trunc);
	if (!of){
		cout << "error.";
		}
	else{
		of << counter;
	}
}

//constructor to add all buttons and stuff the window will use
get_image_window::get_image_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
 
    next_button(Point(x_max()-498,500), 180, 40, "Stop Adding", cb_next),
	getimage_button(Point(x_max()-300,500),100,40,"Save",cb_getimage), 
    discard_button(Point(x_max()-620,500), 100, 40, "Discard", cb_discard),

	instruction(Point(150,50),"Enter the filename or the URL of the picture you want to look up for"),
	filename(Point(150,70),450,20,"Image name"),

	tags_instruction(Point (150,200), "Here are the five tags that you can add to your image:"),
	tags_name(Point(150,230), "Aggieland, Family, Friends, Pets, Vacation"),

	info(Point(150,350),450,20,"Info:"),
	t_info(Point(150,400),450,20,"Tags info:"),
	tag1(Point(150,250),70,20,"1."),
	tag2(Point(250,250),70,20,"2."),
	tag3(Point(350,250),70,20,"3."),
	tag4(Point(450,250),70,20,"4."),
	tag5(Point(550,250),70,20,"5."),
    
	button_pushed(false)
{
    attach(next_button);
    attach(getimage_button);
    instruction.set_font_size(15);
    instruction.set_color(Color::black);
	attach(instruction);
	
	tags_instruction.set_font_size(15);
	tags_instruction.set_color(Color::black);
	tags_name.set_font_size(15);
	tags_name.set_color(Color::black);

	attach(tags_instruction);
	attach(tags_name);
	attach(filename);
	attach(tag1);
	attach(tag2);
	attach(tag3);
	attach(tag4);
	attach(tag5);
	attach(info);
	attach(t_info);
    attach(discard_button);
}

//------------------------------------------------------------------------------
//grabs the ending to see if it is a compatible image
int get_image_window::check_end(string directory)
{
    string jpg(".jpg"), gif(".gif"), jpeg("jpeg"), JPG(".JPG"), GIF(".GIF"), JPEG("JPEG"), BMP(".BMP"), bmp(".bmp"), PNG(".PNG"),
	png(".png");
    string::iterator filename_end = directory.end();
    string::iterator jpg_end = jpg.end();
    string::iterator gif_end = gif.end();
    string::iterator jpeg_end = jpeg.end();
    string::iterator JPG_end = JPG.end();
    string::iterator GIF_end = GIF.end();
    string::iterator JPEG_end = JPEG.end();
	string::iterator BMP_end = BMP.end();
	string::iterator bmp_end = bmp.end();
	string::iterator PNG_end = PNG.end();
	string::iterator png_end = png.end();

    for( int i = 0; i < 4; i++ )
	{
		if( *filename_end != *jpg_end &&
            *filename_end != *JPG_end &&
            *filename_end != *gif_end &&
            *filename_end != *GIF_end &&
            *filename_end != *jpeg_end &&
            *filename_end != *JPEG_end &&
			*filename_end != *PNG_end &&
			*filename_end != *png_end &&
			*filename_end != *bmp_end &&
			*filename_end != *BMP_end  )
        {
		return 2;
	}
		filename_end--;
		jpg_end--;
		gif_end--;
		jpeg_end--;
		JPG_end--;
		GIF_end--;
		JPEG_end--;
		BMP_end--;
		bmp_end--;
		PNG_end--;
		png_end--;
	}
	
	if(url(directory) == 1)
	{
		return 1;
	}
	
	else
		return 0;
}

//method belows checks to make sure the URL being entered is valid.
int get_image_window::url(string url)
{
	string head ("http//:");
	string::iterator url_begin=url.begin();
	string::iterator head_begin=head.begin();
	
	int i =0;
	//check if the url begin with http://
	for( int i = 0; i < 4; i++ )
	{
		if( *url_begin != *head_begin )
		{
		 i=0;
		 return 0;
		}
		++url_begin;
		++head_begin;
	}
	return 1;
}

//make sure the filetype is valid.
string get_image_window::get_filetype(string directory)
{
	int cnt = 0;
	string filetype;
	string::iterator filename_ptr = directory.end();
	while(*filename_ptr != '.' && filename_ptr >=directory.begin())
	{
		cnt++;
		filename_ptr--;
	}
	while(cnt>0)
	{
		filetype.push_back(*(++filename_ptr));
		cnt--;
	}
	filetype = "." + filetype; 
	return filetype;
}

//method to check-tags used to make sure tags are valid.
int get_image_window::check_tags(vector <string> temp)
{
	int c = 0;
	if (temp.empty()){
		return 1;
	}
	for(int i=0; i<temp.size(); i++)
	{
		string str = temp[i];
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		/*if(str == "")
			return 1;*/
		if((str=="friends")||(str=="aggieland")||(str=="family")||(str=="pets")||(str=="vacation")){
			c=1;			
		}
		else
			return 0;
	}	
	return c;
}
 

//------------------------------------------------------------------------------
bool get_image_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 0
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
//callbacks for button clicks
void get_image_window::cb_next(Address, Address pw)
{  
    reference_to<get_image_window>(pw).next();    
}
 

void get_image_window::cb_getimage(Address, Address pw)
{
    reference_to<get_image_window>(pw).getimage();
}
 
void get_image_window::cb_discard(Address, Address pw)
{
    reference_to<get_image_window>(pw).discard();
}


//------------------------------------------------------------------------------

void get_image_window::next()
{
    button_pushed = true;
    hide(); //To exit when the user presses quit
}

//long method to save an image when entered
void get_image_window::getimage()
{ 
	button_pushed = true;
	string directory = filename.get_string();
	
	vector <string> tags;
	
	if (tag1.get_string()!=""){ string s = tag1.get_string(); std::transform(s.begin(), s.end(), s.begin(), ::tolower);  tags.push_back(s); }
	if (tag2.get_string()!=""){ string s = tag2.get_string(); std::transform(s.begin(), s.end(), s.begin(), ::tolower);  tags.push_back(s); }
	if (tag3.get_string()!=""){ string s = tag3.get_string(); std::transform(s.begin(), s.end(), s.begin(), ::tolower);  tags.push_back(s); }
	if (tag4.get_string()!=""){ string s = tag4.get_string(); std::transform(s.begin(), s.end(), s.begin(), ::tolower);  tags.push_back(s); }
	if (tag5.get_string()!=""){ string s = tag5.get_string(); std::transform(s.begin(), s.end(), s.begin(), ::tolower);  tags.push_back(s); }
	
	ct = check_tags(tags);
	if(ct!=0)
	{
		string d = "Tags entered by you are in correct format";
		t_info.put(d.c_str());
	
		if(check_end(directory) == 0) //check if the url end with correct format //Call the class and the save the image there
		{
			int check = 100;
			string name = "file" + to_string(counter);
			string file_end = get_filetype(directory);
			check = system(("cp " + directory + " ./" + name + file_end).c_str());		
			if(check!=0)
			{
				string display = "The path of the filename is wrong";
				info.put(display.c_str());
			}
			else
			{
				string display = directory + " was saved as " + name + file_end + " successfully";
				info.put(display.c_str());
				
				++counter;
				tags=remove_dup(tags);
				DImage D((name+file_end).c_str(),tags);
				D.save_info();
			}
		}
		else if( check_end(directory) == 1 )
		{
			string name = "file" + to_string(counter); //name;
			string url_end = get_filetype(directory);
			system(("wget " + directory  + " -O "+ name + url_end).c_str());  //Add the end of the url to maintain the type of the file and save;
			ifstream ifs;
			cout << name+url_end << endl;
			ifs.open(name+url_end);
			ifs.seekg(0, ifs.end);	
			int	size = ifs.tellg();
		
			if( size != 0)
			{
				tags=remove_dup(tags);
				DImage D((name+url_end).c_str(),tags);
				D.save_info();
				
				++counter;
				
				string display = "It was saved as " + name+url_end + " successfully";
				info.put(display.c_str());
			}
			else
			{
				system(("rm " + name + url_end).c_str()); 
				string display = "The path of the URL is wrong";
				info.put(display.c_str());
			}
		}
		else
		{
			string display = "The path of the filename/ URL is wrong";
			info.put(display.c_str());
		}
	}
	else
	{
		string dp = "The file was not saved in the directory";
		info.put(dp.c_str());
		string display = "The tags you entered are either in incorrect format or not from the given list.";
		t_info.put(display.c_str());
	}
	wait_for_button();
}


//reset window
void get_image_window::discard()
{
    button_pushed = true;
	redraw();
}

//remove any duplicate tags
vector<string> get_image_window::remove_dup(vector<string> tags){
	vector<string> new_tags;
	int flag = 0;
	for (int i=0; i<tags.size(); ++i){
		for (int j=0; j<new_tags.size(); ++j){
			if (tags[i]==new_tags[j])
				flag = 1;
		}
		if(flag == 0)
				new_tags.push_back(tags[i]);
		flag = 0;
	}
	return new_tags;
}



