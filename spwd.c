#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>

char* currentPath(short* len);
short terminalWidth();
bool isHelp(char* arg);
void printShort(short* plen, char* path, short deltaLen);

int main(int argc, char *argv[]) {
    short alen = 0, plen = 0;  //Init len vars
    char* cpath = currentPath(&plen);  //Get current path and its lenght

    if (argc > 1) {
        if (!isHelp(argv[1])) alen = atoi(argv[1]);  //Get aviable len (if exists)
        else return 0;
    } else alen = terminalWidth();  //Set the terminal widht if it is not a help exec

    /* check for the ability to write the path in the available len */
    if (plen <= alen) printf(cpath);  //Print default path
    else printShort(&plen, cpath, plen - alen);  //Print short path

    return 0;
}

char* currentPath(short* len) {
    char* buffer = getenv("PWD");  //Get current path
    for (*len = 0; buffer[*len] != '\0'; (*len)++) { }  //Get path len
    return buffer;
}

short terminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

bool strcomp(char* str1, char* str2) {
    for (short i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
        if (str1[i] != str2[i]) return false;
    return true;
}

bool isHelp(char* arg) {
    if (!strcomp(arg, "-h") && !strcomp(arg, "--help")) return false;
    printf("Usage:\n    spwd <max width>\nExample:\n    spwd 123");
    return true;
}

/* Get all titles' lenght */
short* titleLenghts(char* path, short* size) {
    short* buffer = (short*)malloc(512 * sizeof(short));
    for (short i = 0, slcounter = 0, counter = 0, clen = 0; path[i] != '\0'; i++) {
        if (path[i] == '/') {
            slcounter++;
            if (slcounter > 3) (counter)++;
            *size = counter + 1;
            buffer[counter] = clen;
            clen = 0;
            continue;
        }
        clen++;
    }
    buffer = realloc(buffer, *size);
    return buffer;
}

bool* excludeTitles(short size, short* lens, short delta) {
    bool* buffer = (bool*)malloc(size * sizeof(bool));

    short first = 0, last = 0;
    for (short i = 0, max = 0; i < size; i++) {
        for (short j = i, csum = 0; j < size; j++) {
            csum += lens[j];
            if (csum > max && csum <= delta) {
                max = csum;
                first = i;
                last = j;
            }
        }
    }

    for (int i = first; i <= last; i++) buffer[i] = true;
    return buffer;
}

void printShort(short* plen, char* path, short deltaLen) {
    deltaLen += 5;  //Special for "..." symbols
    short tlsize; short* tlens = titleLenghts(path, &tlsize);
    if (tlsize <= 1) {
        printf(path);
        return;
    }

    bool* excludes = excludeTitles(tlsize, tlens, deltaLen);
    bool placeholdered = false;

    for (short i = 0, slcounter = 0; path[i] != '\0'; i++) {
        if (path[i] == '/') slcounter++;
        if (excludes[slcounter - 2]) {
            if (!placeholdered) {
                printf("/...");  //Print placeholder
                placeholdered = true;
            }
            continue;
        }
        putchar(path[i]);
    }
}
