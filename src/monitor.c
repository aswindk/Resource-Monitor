#include <stdio.h>
#include "cpu.h"
#include "mem.h"

int main() {
    while (1) {
        double usage = calculate_cpu_usage();
        printf("CPU Usage: %.2f%%\n", usage);
         int width_cpu_bar = 50;
            int filled_cpu_bar = (int)(usage/100.0 * width_cpu_bar);
            printf("[");

            for(int i = 0; i < width_cpu_bar; i++){
                if(i < filled_cpu_bar) printf("#");
                else printf("-");

            }

             printf("] %.2f%%\n", usage);

        double mem_usage = get_mem_info();
        printf("Memory Usage: %.2f%%\n", mem_usage);

            int width = 50;
            int filled = (int)(mem_usage/100.0 * width);
            printf("[");

            for(int i = 0; i < width; i++){
                if(i < filled) printf("#");
                else printf("-");

            }

             printf("] %.2f%%\n", mem_usage);

             printf("\n");
           

        
    }
    return 0;
}


