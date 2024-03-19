Directory information:

ArtWork - The original artwork.  The approiate version from "Black and White" or "Color" should be copied into the main "ArtWork" directory for snipper to work.
DrawStuff - A VB app that creates the bitmaps that contain the location of each letter, as well as the bitmap for the "keys"
Install - Batch file and ini files to create the installation cab file
KeyStrokeCEReg - Simple executable that makes the proper registry entries
KeyTest - VB App used to test the initial placement of keys.  Parts of it are used by other VB apps
Snipper - VB App that takes the art works and splits it up into smaller peices to save some space.  Again, the proper artwork should be copied from the Color or Black And White directory before it's run.

Root (KeyStrokCE)

This contains the source for the DLL KeyStrokeCE.  It should be pointed out you'll need to copy the correct BMPs from the Color and BW directories under Snipper and DrawStuff before compiling.