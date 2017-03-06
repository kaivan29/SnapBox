# SnapBox

# A computer application to design and write a C++11/FLTK picture database program with a graphical user interface.  The program starts with a description of what it does and then allows the user to:

1. Get a picture from a filename.  (The file might have come from a cellphone camera.)  You only need to accept file extensions of jpg, gif, jpeg, JPG, GIF, and JPEG (unless you want extra credit—see below).  Allow the user to recover from entering an incorrect type of file, a file that can't be opened, etc.

2.	Get a picture from a URL, using wget as in the homework.  You only need to accept file extensions of jpg, gif, jpeg, JPG, GIF, and JPEG (unless you want extra credit—see below).  Allow the user to recover from entering an incorrect file extension, a URL that can't be downloaded, etc.

3.	Add up to 5 tags per picture (Family, Friends, Aggieland, Pets, Vacation, or any combination of these).

4.	Save the picture to disk, and save information to a picture index file.  The picture index file should consist of human-readable text; for example, lines like
		(reveilleVIII.jpg,Aggieland,Pets,,,)
since there are only two tags on that picture.  This file should be read each time the program is run, so that adding pictures is cumulative.  Hint: See the textbook's code for printing Date objects.

5.	Browse all pictures.  When a picture is displayed, so are its tags.  Provide buttons to see the Next or the Previous picture.

6.	Find pictures with any combination of tags.  Provide buttons to see the Next
      or the Previous picture with those tags.
