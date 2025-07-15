#include <stdio.h>
#include "cpu.h"

int main() {
    while (1) {
        double usage = calculate_cpu_usage();
        printf("CPU Usage: %.2f%%\n", usage);
    }
    return 0;
}

