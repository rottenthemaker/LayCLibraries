# LayCLibraries
A command line application designed to speed up the process of C programming and eliminate library definition errors.

# Documentation:
LayCLibraries is an application designed to speed up the process of C programming and eliminate library definition errors. Using it in conjunction with a C source code file allows the user to automatically check for missing library declarations, or not have to worry about finding what library the standard function they are using is in. 
I created this program specifically to help speed up my programming workflow, as I usually took around 30 seconds to a minute finding the source library for a function I knew about in the standard library. This time adds up over a project, and so I created this program to allow for a one and done solution to adding library headers in C source code files.
# Usage:
./layclib (myfile.c) : Runs LayCLib on myfile.c. File must have a .c extension for the program to run correctly. Source file must also be in the same directory as the executable file.
./layclib -h : Displays usage help text, similar to the description above.
# Current Limitations:
LayCLib currently isn’t all encompassing for every library function and macro, but from my limited knowledge of C libraries, looking through .h files, and Wikipedia, I included most if not all major functions and a lot of smaller macros and functions as well. 
LayCLib only currently works on .c files for safety reasons, and it also has no ability to automatically compile the code afterwards, or rename the output file. These features are planned for the next version which will hopefully be released on GitHub
You can technically add support for your own custom libraries, but you need to edit the source code to add checking functionality for your library set. Ability to add custom libraries without editing code is also a planned feature.
# Troubleshooting:
-1 return value: Memory limit has been reached on inputting source file into program. This is usually caused by having more than 4000 characters on one line. Break up your code a bit more if possible.
-2 return value: Malformed input within command line. Make sure you are inputting the command correctly according to the guidelines above.
-3 return value: Error accessing or opening file. This can be related to the input file used on the command line, inability to create the output file in the directory, or a missing library file for the executable itself, making it unable to run. More detailed information is outputted to stdout when this error occurs.
