# mt2tar

This is a utility I have been working on that converts simh unix tap files to tar files. It was inspired by the tar2mt utility for Simh.
There are two scripts. One is  simple reversal of the conversion from tar to tap, and the second if for converting tap files made by simh PDP-11, which contains 8 bytes too many at the begining of the first file block and some unneeded padding at the end of the archive. It seems to extract perfectly now, although it may need further tweaking.

NOTE:

I have been made aware that this tool does not work for all tap files. After some testing I have found that it is possible that not all versions of simh, even running the same OS produce the tap files that are compatible with each other. To add to this, I have found that this tool does not work for tap files containing more than a certain number of files. I am working on the issue and hope to fix it in due course.
