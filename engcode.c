#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

FILE* tablefile;
FILE* wordsfile;

// damn fast engcode encoder
// to use, first run ./preptable < words.txt > words.map

int wordsprinted = 0;
void word(unsigned int n) {
    /* fprintf(stderr,"%x %u\n",n,n); */
    /* if (n > (1<<18)) {fprintf(stderr,"n too large\n");exit(1);}; */
    char buf[20];
    uint32_t begin = 0, pastend;
    int len;
    if (n != 0) {
        if (fseek(tablefile, (n-1)*4, SEEK_SET) == -1) perror("Seek 1st index in map failed");
        if (fread(&begin, 4, 1, tablefile)       != 1) perror("Read 1st index in map failed");
        begin++;
    } else {
        if (fseek(tablefile, 0, SEEK_SET)       == -1) perror("Seek map to beginning failed");
    }
    if (fread(&pastend, 4, 1, tablefile)        == -1) perror("Read 2nd index in map failed");
    len = pastend - begin;
    if (len > 19)       {fprintf(stderr,"Too long strings according to .map file\n"); exit(1);}
    if (fseek(wordsfile, begin, SEEK_SET)       == -1) perror("Seek in words file failed");
    if (fread(&buf, 1, len, wordsfile)         != len) perror("Reading from words file failed");
    if (wordsprinted) {
        if (fwrite(" ", 1, 1, stdout)           != 1) perror("writing ' ' to stdout failed");
    }
    if (fwrite(buf, 1, len, stdout)            != len) perror("writing word to stdout failed");
    wordsprinted++;
}

/* convert 9 bytes to 4 words */
/* bytes 0-------1-------2-------3-------4-------5-------6-------7-------8------- */
/* words 0-----------------1-----------------2-----------------3----------------- */

int main() {
    tablefile = fopen("words.map", "rb"); /* XXX: adjust paths if needed*/
    wordsfile = fopen("words.txt", "rb"); /* map claculated for binary */
    unsigned char buf[9];
    int got = 10;
    while (1) {
        buf[0]=0;buf[1]=0;buf[2]=0;buf[3]=0;buf[4]=0;buf[5]=0;buf[6]=0;buf[7]=0;buf[8]=0;
        got = fread(&buf, 1, 9, stdin);
        if (got < 1) break;
        word( (buf[0]       ) << 10 | buf[1] << 2 | (buf[2] & 0xC0) >> 6 );
        if (got < 3) break;
        word( (buf[2] & 0x3F) << 12 | buf[3] << 4 | (buf[4] & 0xF0) >> 4 );
        if (got < 5) break;
        word( (buf[4] & 0x0F) << 14 | buf[5] << 6 | (buf[6] & 0xFC) >> 2 );
        if (got < 7) break;
        word( (buf[6] & 0x03) << 16 | buf[7] << 8 | (buf[8]       )      );
    }
    if (fwrite("\n", 1, 1, stdout) != 1) perror("writing newline to stdout failed");
    return 0;
}
