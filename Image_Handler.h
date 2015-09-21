#ifndef IMAGE_HANDLER_GUARD
#define IMAGE_HANDLER_GUARD

#include "std_lib_facilities_3.h"
#include "DImage.h"

using namespace std;


class Image_Handler {
    public:
        Image_Handler(bool);

		void del_image();
		void clear();
		void add(DImage); //implementation details. methods to be implemented in .cpp
		void prev_photo();
        void next_photo();
		void load_photos();
		
		vector<DImage> get_images();
		int get_index();
		
		DImage get_current();

    private:       
		int index;
        vector<DImage> images;
};

#endif 