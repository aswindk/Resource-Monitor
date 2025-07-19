#include <stdio.h>
#include "cpu.h"
#include "mem.h"

int main() {
    while (1) {
        double usage = calculate_cpu_usage();
        printf("CPU Usage: %.2f%%\n", usage);
        double mem_usage = get_mem_info();
        printf("Memory Usage: %.2f%%\n", mem_usage);
    }
    return 0;
}


