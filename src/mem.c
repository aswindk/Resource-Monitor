#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

double get_mem_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char line[256];
    long memTotal = 0, memAvailable = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemTotal: %ld kB", &memTotal) == 1) continue;
        if (sscanf(line, "MemAvailable: %ld kB", &memAvailable) == 1) continue;
    }
    fclose(fp);

    long used = memTotal - memAvailable;
    double used_percent = (double)used / memTotal * 100.0;

    return used_percent;
}
