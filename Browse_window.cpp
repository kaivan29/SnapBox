/*
	Window to browse through images and possibly edit their tags or delete them.
*/

#include "Browse_window.h"
#include "Fl_Image.h"


using namespace Graph_lib;

void display();
vector<string> remove_dup(vector<string> tags);

//keep track of pointers images/text
vector<Image*> vimg;
vector<Text*> vtext;
//------------------------------------------------------------------------------

Browse_window::Browse_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	// constructor that attaches all of the necessary buttons/stuff for the window to run
	next_button(Point(500,40), 100, 40, "Next", cb_next),
    next_pushed(false),
	
	prev_button(Point(100,40), 100, 40, "Previous", cb_prev), 
	prev_pushed(false),  

	edit_button(Point(260,630),180,20,"Edit Tags", cb_edit),
	edit_pushed(false),

	save_button(Point(590,700),70,20,"Save",cb_save),
	save_pushed(false),
	
	info(Point(100,720),450,20,"Info:"),

	tag1(Point(100,690),70,20,"1."),
	tag2(Point(200,690),70,20,"2."),
	tag3(Point(300,690),70,20,"3."),
	tag4(Point(400,690),70,20,"4."),
	tag5(Point(500,690),70,20,"5."),
	instruction(Point(100,680), "Choose new tags from Aggieland, Family, Friends, Pets, or Vacation."),
	
	del_button(Point(480,755),100,40, "Delete Photo", cb_del),
	del_pushed(false),

    i(true),
	
	back_button(Point(260,755),180,40,"Stop Browsing", cb_back), 
	back_pushed(false)
	
{
	attach(next_button);
    attach(prev_button);
	attach(back_button);
	attach(del_button);
	attach(edit_button);
	display();
}

//destructor to prevent memory leaks
Browse_window::~Browse_window(){
	for (int i=0; i<vimg.size(); ++i){
		delete vimg[i];
	}
	for (int i=0; i<vtext.size(); ++i){
		delete vtext[i];
	}
}



//------------------------------------------------------------------------------

bool Browse_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when browse_pushed becomes true
// this allows graphics without control inversion
{
    show();
    back_pushed = false;
	
#if 0
    // Simpler handler
    while (!back_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return back_pushed;
}

//------------------------------------------------------------------------------
// callbacks to handle button clicking
void Browse_window::cb_next(Address, Address pw)
{  
    reference_to<Browse_window>(pw).next();    
}

void Browse_window::cb_prev(Address, Address pw)
{  
    reference_to<Browse_window>(pw).prev();  
 	
}

void Browse_window::cb_back(Address, Address pw)
{  
    reference_to<Browse_window>(pw).back();  
}

void Browse_window::cb_del(Address, Address pw)
{  
    reference_to<Browse_window>(pw).del();  	
}

void Browse_window::cb_edit(Address, Address pw)
{  
    reference_to<Browse_window>(pw).edit();  	
}

void Browse_window::cb_save(Address, Address pw)
{  
    reference_to<Browse_window>(pw).save();  	
}

//display the images using pointers
void Browse_window::display(){	
	if (vimg.size() > 0)
		detach(*vimg[vimg.size()-1]); 
    if (vtext.size() > 0)
		detach(*vtext[vtext.size()-1]);


	if (i.get_images().size()>0){
		Image *curr = new Image(Point(100,100), i.get_current().get_url());
		Image *scaled_image = curr->resize(500, 485); //code from fltk documentation
	
		Text *t = new Text(Point(210,615), i.get_current().get_disp_tags());
		t->set_font_size(15);
	
		attach(*scaled_image);
		attach(*t);
	
		vimg.push_back(scaled_image);
		vtext.push_back(t);

	}
	Fl::redraw();
}



//------------------------------------------------------------------------------

void Browse_window::next()
{
    i.next_photo(); //go to next photo
    display();
}

void Browse_window::prev()
{ 
    i.prev_photo(); //go to prev photo
    display();
}

void Browse_window::back()
{
    back_pushed = true; //cancel out, and go back to the main menu
    hide();
}

void Browse_window::del()
{  //del() method to delete an image *EXTRA CREDIT*
	if (i.get_images().size() > 0){
		if (i.get_images().size()==1){
			edit();
		}
		
		string filename = i.get_current().get_url();
		ifstream filein("info.txt"); //File to read from
		ofstream fileout("temp.txt"); //Temporary file
		if(!filein || !fileout)
		{
			cout << "Error opening files!" << endl;
		}
		string line;
		while(getline(filein,line))
		{	
			 size_t tmp = line.find(filename);
			 if( tmp == string::npos && !line.empty())
				fileout << endl << line;
		}
		system("rm info.txt"); //remove old info.txt
		system(("rm " + filename).c_str());//remove image file 
		system("mv temp.txt info.txt"); // rename the temp.txt => info.txt
		filein.close();
		fileout.close();
		i.clear();       
		i.load_photos();
		i.del_image();
		display();   
	}else{}
}

void Browse_window::edit()
{ //edit method to edit tags, *EXTRA CREDIT*
	if (i.get_images().size()>0){
		edit_pushed=!edit_pushed; // toggle on/off
	
		if (edit_pushed){
			attach(tag1);
			attach(tag2);
			attach(tag3);
			attach(tag4);
			attach(tag5);
			attach(instruction);
			attach(save_button);
			attach(info);
		}
		else if (!edit_pushed){
			detach(tag1);
			detach(tag2);
			detach(tag3);
			detach(tag4);
			detach(tag5);
			detach(instruction);
			detach(save_button);
			detach(info);
		}
		Fl::redraw();
	}
	else{} //no images so do not show an edit option
	//toggle system above that shows or hides depending on whether they are trying to hide or show.
}

void Browse_window::save()
{
	//make sure that the new tags are valid
	
	if (check_tags() && i.get_images().size()>0){
		string filename = i.get_current().get_url();
		vector<string> t = {tag1.get_string(), tag2.get_string(), tag3.get_string(), tag4.get_string(),
			tag5.get_string()};		
		for (int j=0; j<t.size(); ++j){
			std::transform(t[j].begin(), t[j].end(), t[j].begin(), ::tolower);
		}
		t = remove_dup(t);
		
		string tags;
		for (int i=0; i<t.size(); ++i)
			tags.append(t[i] + " ");
		
		ifstream filein("info.txt"); //File to read from
		ofstream fileout("temp.txt"); //Temporary file
		if(!filein || !fileout)
		{
			cout << "Error opening files!" << endl;
		}

		string line;
		while(getline(filein,line))
		{
			size_t tmp = line.find(filename);
			if( tmp != string::npos){
				std::transform(tags.begin(), tags.end(), tags.begin(), ::tolower);
				line = filename + " " + tags;	
			}
			if (!line.empty()){ // check to see if line is blank, if it is, skip it, otherwise write
				fileout << endl << line;
			}
			else{}//nothing
				
		}
		system("rm info.txt");
		system("mv temp.txt info.txt");

		edit();
		filein.close();
		fileout.close();
		i.clear();       
		i.load_photos();
		display(); 
		info.put("New tags saved.");
	}
	else{ 
		info.put("Tags were not valid. The requested change was not saved."); // bad change
	}
}

//check_tags() to make sure the tags are valid. Blank boxes are allowed inbetween tags.
bool Browse_window::check_tags()
{
	vector<string> tags;
	if (tag1.get_string()!="") tags.push_back(tag1.get_string());
	if (tag2.get_string()!="") tags.push_back(tag2.get_string());
	if (tag3.get_string()!="") tags.push_back(tag3.get_string());
	if (tag4.get_string()!="") tags.push_back(tag4.get_string());
	if (tag5.get_string()!="") tags.push_back(tag5.get_string());
	
	int c = 0;
	for(int i=0; i<tags.size(); i++)
	{
		string str = tags[i];
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		if(str == "")
			break;
		else if((str=="friends")||(str=="aggieland")||(str=="family")||(str=="pets")||(str=="vacation")){
			c=1;
			//make sure the tags are acceptable
		}
		else
			return 0; //if unacceptable found, return error immediately.
	}	
	return c;
}

vector<string> Browse_window::remove_dup(vector<string> tags){
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
//------------------------------------------------------------------------------
