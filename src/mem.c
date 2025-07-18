#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

void get_mem_info(){
    unsigned long long *mdata;

    FILE *fp = fopen("/proc/meminfo","r");
    if(!fp){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer),fp);  
    fclose(fp);

    char memdata[]

    
}


