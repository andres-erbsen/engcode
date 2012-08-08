#include <stdio.h>
#include <stdint.h>
#define BUFSIZE 32*1024

char buf[BUFSIZE+1];
int main(){
    int i, got;
    uint32_t pos = 0, t;
    while ( (got = fread(buf, 1, BUFSIZE, stdin)) > 0 ) {
        for (i = 0; i < got; i++) if (buf[i] == '\n') {
            t = pos + i;
            /* fprintf(stderr,"%d\n",t); */
            fwrite(&t, 4, 1, stdout);            
        }
        pos += got;
    }
    return 0;
}
