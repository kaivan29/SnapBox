/*
	Designed to carry out searches for pictures in the database
*/

#include "Search_window.h"
#include "Fl_Image.h"


using namespace Graph_lib;
//declare methods
void display();
vector<string> find_tag(vector<string> tag);
//vectors to keep track of pointer images/text
vector<Image*> vimgs;
vector<Text*> vtexts;
//------------------------------------------------------------------------------

Search_window::Search_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	//add and attach all of the buttons this window will use.
	next_button(Point(500,60), 100, 40, "Next", cb_next),
    next_pushed(false),
	
	prev_button(Point(100,60), 100, 40, "Previous", cb_prev), 
	prev_pushed(false), 

	ii(false),
		
	t(Point(140,125),"Search pictures using tags in the provided box below."),
	stag1(Point(140,145),70,20,"1."),
	stag2(Point(240,145),70,20,"2."),
	stag3(Point(340,145),70,20,"3."),
	stag4(Point(440,145),70,20,"4."),
	stag5(Point(540,145),70,20,"5."),	
	
	misspell(Point(140,175),470,20,"Info:"),

	clear_button(Point(460,640),100,40,"Clear Search", cb_clear),
	clear_pushed(false),

	search_button(Point(140,640),100,40,"Search", cb_search),
	search_pushed(false),
	
	back_button(Point(260,640),180,40,"Stop Searching", cb_back), 
	back_pushed(false)
	
{
	attach(t);
	attach(stag1);
	attach(stag2);
	attach(stag3);
	attach(stag4);
	attach(stag5);
	attach(next_button);
    attach(prev_button);
	attach(back_button);
	attach(search_button);
	attach(clear_button);
	attach(misspell);
}

//destructor to clear up memory space from pointers
Search_window::~Search_window(){
	for (int i=0; i<vimgs.size(); ++i){
		delete vimgs[i];
	}
	for (int i=0; i<vtexts.size(); ++i){
		delete vtexts[i];
	}
}

//------------------------------------------------------------------------------

bool Search_window::wait_for_button()
// modified event loop:
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
// callbacks for button actions
void Search_window::cb_next(Address, Address pw)
{  
    reference_to<Search_window>(pw).next();    
}

void Search_window::cb_prev(Address, Address pw)
{  
    reference_to<Search_window>(pw).prev();  
}

void Search_window::cb_back(Address, Address pw)
{  
    reference_to<Search_window>(pw).back();  
}

void Search_window::cb_search(Address, Address pw)
{  
    reference_to<Search_window>(pw).search();  
}

void Search_window::cb_clear(Address, Address pw)
{  
    reference_to<Search_window>(pw).clear();  
}

// display an image to the window using pointers
void Search_window::display(){	
	if (vimgs.size() > 0)
		detach(*vimgs[vimgs.size()-1]); 
       if (vtexts.size() > 0)
		detach(*vtexts[vtexts.size()-1]);

	if (ii.get_images().size() > 0){
		
		Image *curr = new Image(Point(140,240), ii.get_current().get_url());
		Image *scaled_image = curr->resize(450, 385); //code from fltk documentation
	
		Text *t = new Text(Point(200,220), ii.get_current().get_disp_tags());
		t->set_font_size(15);
	
		attach(*scaled_image);
		attach(*t);
	
		vimgs.push_back(scaled_image);
		vtexts.push_back(t);
	
		Fl::redraw();
	}
	else{
		Fl::redraw();
	}
	
}



//------------------------------------------------------------------------------
// this method, when the next button is pushed, moves the index forward 1, and wraps around at the end
void Search_window::next()
{
	if (ii.get_images().size()>0){
		ii.next_photo();
		display();
	}
}
// moves the index backwards 1 and wraps around if necessary
void Search_window::prev()
{ 
	if (ii.get_images().size()>0){
		ii.prev_photo();
		display();
	}
}
// cancels the search window
void Search_window::back()
{
    back_pushed = true;
    hide();
}
// refresh the picture index
void Search_window::clear()
{
	ii.clear();
	display();
}
// takes tag input and calls a search method
void Search_window::search()
{
	ii.clear();
	vector<string> tags;
	if (stag1.get_string()!="") tags.push_back(stag1.get_string());
	if (stag2.get_string()!="") tags.push_back(stag2.get_string());
	if (stag3.get_string()!="") tags.push_back(stag3.get_string());
	if (stag4.get_string()!="") tags.push_back(stag4.get_string());
	if (stag5.get_string()!="") tags.push_back(stag5.get_string());
	//loads vector with the tags they searched for
	
	for (int i=0; i<tags.size(); ++i){ //goes through vector, makes sure all the tags are valid
		std::transform(tags[i].begin(), tags[i].end(), tags[i].begin(), ::tolower);
		if(!((tags[i]=="friends")||(tags[i]=="aggieland")||(tags[i]=="family")||(tags[i]=="pets")||(tags[i]=="vacation"))){
			misspell.put("One or more of your tags is either misspelled or incorrect.");
			break;
		}					
	}		
	vector<string> result;
	if (!tags.empty())
		result = find_tag(tags); //search the databsae
		
	
	int found = result.size();
	string out = "The search found " + to_string(found) + " result(s) based on your tags.";
	misspell.put(out.c_str()); //output any info
	
	// load the found images into the image handler
	for (int i=0; i<result.size(); i++){
		string s;
		vector<string> ts;
		string loc;
		s=result[i];		
		stringstream line(s);

		for (int b=0; b<6; b++){
			if (b==0){
				line >> loc; 
				}
			else{
				string temp;
				line >> temp;
				if (!(temp=="" || temp==" ")){
					ts.push_back(temp);
					}
			}
		}
		ii.add(DImage(loc, ts));
	}
	display();

}

//------------------------------------------------------------------------------

//search method
vector<string> find_tag(vector<string> tag)
{
    ifstream index("info.txt");
    vector<string> match_file ; // save matched file info
    string line;
    for(unsigned int i=0 ; i<tag.size() ; i++){
		tag[i] = " " + tag[i] + " ";
		std::transform(tag[i].begin(), tag[i].end(), tag[i].begin(), ::tolower);
	}
        
    if(index.is_open())
    {
        while (getline(index,line)) // read a line from info.txt
        {
            auto flag = 1; // find the tag
            size_t temp;
            for(unsigned int j=0 ; j<tag.size() ; j++)
            {
                temp = line.find(tag[j]);
                if(temp == string::npos)
                    flag = 0;
            }
            if(flag==1)       // if find the tags
                match_file.push_back(line); // save the line to vector
        }
        index.close();
        return match_file;
    }
    else
    {
        cout<< "cannot open info.txt"<<endl;
        return match_file;
    }

}
