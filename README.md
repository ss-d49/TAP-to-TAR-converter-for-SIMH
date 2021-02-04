# mt2tar

This is a utility I have been working on that converts simh unix tap files to tar files. It was inspired by the tar2mt utility for Simh.
There are two scripts. One is  simple reversal of the conversion from tar to tap, and the second if for converting tap files made by simh PDP-11, which contains 8 bytes too many at the begining of the first file block and some unneeded padding at the end of the archive. It seems to extract perfectly now, although it may need further tweaking.
