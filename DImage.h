#ifndef DIMAGE_GUARD
#define DIMAGE_GUARD

#include <iostream>
#include "std_lib_facilities_3.h"

using namespace std;

class DImage{
    public:
        DImage(string , vector<string>  ); // if true, image is a url, else, file


        string get_url();
        string get_tags();
		string get_disp_tags(); //to be implemented
		string getaburl();

        void add_tag(string s);
        void save_info();

    private:
        string aburl;
        string url;
        string fn;       //private access only

        vector<string> tags;
};


#endif
