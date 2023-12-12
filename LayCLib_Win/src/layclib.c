#include <stdio.h>
#include <string.h>

int nextLib(FILE *f, char * fileName) { //closes file pointer and then opens a new file in the same filepointer
    fclose(f);
    f = fopen(fileName, "r");
    if (f == NULL) return -1; //check for file opening errors
    return 0;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("ERROR: Incorrect usage, refer to 'layclib -h' for help with usage.\n"); //check for command misuage
        return -2;
    }
    if (strcmp(argv[1],"-h") == 0) {
        printf("Usage:\n layclib myfile.c | Executes layclib on myfile.c (must be in same directory as executable)\n layclib -h | Displays this help text.\n"); //help message
        return 0;
    }
    if (!strstr(argv[1],".c")) {
        printf("ERROR: Input file must be in .c format (ex: hello.c)\n");
        return -2;
    }
    FILE *wp, *rp, *libp; //write pointer, read pointer, library txt pointer
    char c, input[4096], lib[100];
    char *test;
    int cnt = 1, memcnt = 0, err = 0;
    int assert = 0, complex = 0, ctype = 0, errno = 0, fenv = 0, flt = 0, inttypes = 0, limits = 0, locale = 0, math = 0, setjmp = 0, signal = 0, stdalign = 0, stdarg = 0, stdatomic = 0, stdbool = 0, stddef = 0, stdint = 0, stdio = 0,  stdlib = 0, stdnoreturn = 0, string = 0, threads = 0, time = 0, wchar = 0, wctype = 0;
    rp = fopen(argv[1], "r");
    wp = fopen(strcat(argv[1],"_layclib_added.c"), "w");
    libp = fopen("data/stdio_lib.txt", "r");
    if (rp == NULL) {
        printf("ERROR: File specified does not exist or is not readable.\n"); //check for file opening errors
        return -3;
    } else if (wp == NULL) {
        printf("ERROR: Cannot write to new file.\n"); //check for file opening errors
        return -3;
    } else if (libp == NULL) {
        printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n"); //check for file opening errors
        return -3;
    }
    while ((c = fgetc(rp)) != EOF) { //check for new lines
        memcnt++;
        if (memcnt == 4095) {
            printf("ERROR: Memory limit has been reached, break up your lines a bit more! (too many characters in one line [4096])\n"); //check for memory overflow in input array
            return -1;
        }
        if (c == '\n') {
            cnt++;
            memcnt = 0;
        }
    }
    rewind(rp);
    for (int i = 0; i <= cnt; i++) { //search for library functions
        fscanf(rp, "%[^\n]\n", input);
        err = nextLib(libp, "data/assert_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if (assert == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <assert.h>") == 0) assert = 1;
            if (assert == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <assert.h>\n");
                assert = 1;
            }
        }
        err = nextLib(libp, "data/stdio_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdio == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdio.h>") == 0) stdio = 1;
            if (stdio == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdio.h>\n");
                stdio = 1;
            }
        }
        err = nextLib(libp, "data/complex_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(complex == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <complex.h>") == 0) complex = 1;
            if (complex == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <complex.h>\n");
                complex = 1;
            }
        }
        err = nextLib(libp, "data/ctype_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(ctype == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <ctype.h>") == 0) ctype = 1;
            if (ctype == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <ctype.h>\n");
                ctype = 1;
            }
        }
        err = nextLib(libp, "data/errno_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(errno == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <errno.h>") == 0) errno = 1;
            if (errno == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <errno.h>\n");
                errno = 1;
            }
        }
        err = nextLib(libp, "data/fenv_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(fenv == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <fenv.h>") == 0) fenv = 1;
            if (fenv == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <fenv.h>\n");
                fenv = 1;
            }
        }
        err = nextLib(libp, "data/flt_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(flt == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <float.h>") == 0) flt = 1;
            if (flt == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <float.h>\n");
                flt = 1;
            }
        }
        err = nextLib(libp, "data/inttypes_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(inttypes == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <inttypes.h>") == 0) inttypes = 1;
            if (inttypes == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <inttypes.h>\n");
                inttypes = 1;
            }
        }
        err = nextLib(libp, "data/limits_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(limits == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <limits.h>") == 0) limits = 1;
            if (limits == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <limits.h>\n");
                limits = 1;
            }
        }
        err = nextLib(libp, "data/locale_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(locale == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <locale.h>") == 0) locale = 1;
            if (locale == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <locale.h>\n");
                locale = 1;
            }
        }
        err = nextLib(libp, "data/math_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(math == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <math.h>") == 0) math = 1;
            if (math == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <math.h>\n");
                math = 1;
            }
        }
        err = nextLib(libp, "data/setjmp_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(setjmp == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <setjmp.h>") == 0) setjmp = 1;
            if (setjmp == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <setjmp.h>\n");
                setjmp = 1;
            }
        }
        err = nextLib(libp, "data/signal_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(signal == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <signal.h>") == 0) signal = 1;
            if (signal == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <signal.h>\n");
                signal = 1;
            }
        }
        err = nextLib(libp, "data/stdalign_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdalign == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdalign.h>") == 0) stdalign = 1;
            if (stdalign == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdalign.h>\n");
                stdalign = 1;
            }
        }
        err = nextLib(libp, "data/stdarg_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdarg == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdarg.h>") == 0) stdarg = 1;
            if (stdarg == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdarg.h>\n");
                stdarg = 1;
            }
        }
        err = nextLib(libp, "data/stdatomic_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdatomic == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdatomic.h>") == 0) stdatomic = 1;
            if (stdatomic == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdatomic.h>\n");
                stdatomic = 1;
            }
        }
        err = nextLib(libp, "data/stdbool_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdbool == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdbool.h>") == 0) stdbool = 1;
            if (stdbool == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdbool.h>\n");
                stdbool = 1;
            }
        }
        err = nextLib(libp, "data/stddef_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stddef == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stddef.h>") == 0) stddef = 1;
            if (stddef == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stddef.h>\n");
                stddef = 1;
            }
        }
        err = nextLib(libp, "data/stdint_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdint == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdint.h>") == 0) stdint = 1;
            if (stdint == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdint.h>\n");
                stdint = 1;
            }
        }
        err = nextLib(libp, "data/stdlib_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdlib == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdlib.h>") == 0) stdlib = 1;
            if (stdlib == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdlib.h>\n");
                stdlib = 1;
            }
        }
        err = nextLib(libp, "data/stdnoreturn_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(stdnoreturn == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <stdnoreturn.h>") == 0) stdnoreturn = 1;
            if (stdnoreturn == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <stdnoreturn.h>\n");
                stdnoreturn = 1;
            }
        }
        err = nextLib(libp, "data/string_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(string == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <string.h>") == 0) string = 1;
            if (string == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <string.h>\n");
                string = 1;
            }
        }
        err = nextLib(libp, "data/threads_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(threads == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <threads.h>") == 0) threads = 1;
            if (threads == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <threads.h>\n");
                threads = 1;
            }
        }
        err = nextLib(libp, "data/time_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(time == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <time.h>") == 0) time = 1;
            if (time == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <time.h>\n");
                time = 1;
            }
        }
        err = nextLib(libp, "data/wchar_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(wchar == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <wchar.h>") == 0) wchar = 1;
            if (wchar == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <wchar.h>\n");
                wchar = 1;
            }
        }
        err = nextLib(libp, "data/wctype_lib.txt");
        if (err == -1) {
            printf("ERROR: Cannot read library files, check if *_lib.txt files are missing, corrupted, unreadable, or not in the right folder relative to the executable. Maybe reinstall layclib?\n");
            return -3;
        }
        while(fgets(lib, 100, libp) != NULL) {
            if(wctype == 1) break;
            test = strchr(lib, '\n'); //remove \n character from fgets output
            if (test) *test = '\0';
            if (strcmp(input, "#include <wctype.h>") == 0) wctype = 1;
            if (wctype == 0 && strstr(input, lib)) { //if line has lib funct, add it to wp
                fprintf(wp, "#include <wctype.h>\n");
                wctype = 1;
            }  
        }
        rewind(libp);
    }
    
    if (assert == 1 || complex == 1 || ctype == 1 || errno == 1 || fenv == 1 || flt == 1 || inttypes == 1 || limits == 1 || locale == 1 || math == 1 || setjmp == 1 || signal == 1 || stdalign == 1 || stdarg == 1 || stdatomic == 1 || stdbool == 1 || stddef == 1  || stdint == 1 || stdio == 1 || stdlib == 1 || stdnoreturn == 1 || string == 1 || threads == 1 || time == 1 || wchar == 1 || wctype == 1) {
        fprintf(wp, "//* ^These library calls were generated by LayCLibraries^ */\n\n");
    }
    
    //copy and paste old file contents to new file
    rewind(rp);
    fprintf(wp, "\n");
    while ((c = fgetc(rp)) != EOF) {
        fprintf(wp, "%c", c);
    }
    
    //close all files
    fclose(libp);
    fclose(wp);
    fclose(rp);
    return 0;
}


/* usage:
./layclib myfile.c
flags: -h (help)
reutnr values: 0 = all good
-1 = memory limit reached
-2 = incorrect usage
-3 = file error*/