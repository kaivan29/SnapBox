# SnapBox

# A computer application to design and write a C++11/FLTK picture database program with a graphical user interface.  The program starts with a description of what it does and then allows the user to:

1.	Get a picture from a filename.  (The file might have come from a cellphone camera.) The application only accepts file extensions of jpg, gif, jpeg, JPG, GIF, and JPEG.  Allows the user to recover from entering an incorrect type of file, a file that can't be opened, etc.

2.	Get a picture from a URL, using wget.

3.	Add up to 5 tags per picture (Family, Friends, Aggieland, Pets, Vacation, or any combination of these).

4.	Save the picture to disk, and save information to a picture index file.  The picture index file will consist of human-readable text; for example, lines like (family.jpg,Family,Vacation,,,) since there are only two tags on that picture.  The file is read each time the program is run, so that adding pictures is cumulative.

5.	Browse all pictures.  When a picture is displayed, so are its tags.  There are buttons to see the Next or the Previous picture.

6.	Find pictures with any combination of tags.  User can go through Next or the Previous picture with those tags.
