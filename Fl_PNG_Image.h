/* \file
Fl_PNG_Image class . */

#ifndef Fl_PNG_Image_H
#define Fl_PNG_Image_H
#  include "Fl_Image.h"

class FL_EXPORT Fl_PNG_Image : public Fl_RGB_Image {

public:

Fl_PNG_Image(const char* filename);
Fl_PNG_Image (const char *name_png, const unsigned char *buffer, int datasize);
private:
void load_png_(const char *name_png, const unsigned char *buffer_png, int datasize);
};

#endif

//
 // End of "$Id: Fl_PNG_Image.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//