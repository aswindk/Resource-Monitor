/*
Example :cpu  9066 1151 14958 635196 3652 0 3613 0 0 0

FIELD_INDEX		VALUE		MEANING
1				9066		user — time spent in user mode
2				1151		nice — user mode with nice priority
3				14958		system — kernel mode
4				635196		idle — idle time
5				3652		iowait — waiting for I/O
6				0			irq — servicing interrupts
7				3613		softirq — servicing softirqs
8–10			0 0 0		steal, guest, guest_nice — virtualization (not always used) 

*/


#include <stdio.h> // Includes standard I/O library functions like fopen, fgets, sscanf, and printf 
#include <stdlib.h> //Includes functions like exit() and standard constants like EXIT_FAILURE
#include <unistd.h> //Provides access to system calls and functions like sleep()
#include "cpu.h"

void get_cpu_times(unsigned long long *idle, unsigned long long *total){
    FILE *fp = fopen("/proc/stat","r");
    if (!fp){
        perror("fopen");
        exit(EXIT_FAILURE);  
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer),fp); //Reads the first line that starts with CPU....
    //Reads one line from the file into buffer
    fclose(fp);

    char cpu_label[5];
    unsigned long long user, nice, system, idle_time, iowait, irq, softirq, steal;

    sscanf(buffer, "%s %llu %llu %llu %llu %llu %llu %llu %llu",
           cpu_label, &user, &nice, &system, &idle_time, &iowait, &irq, &softirq, &steal);


    *idle = idle_time + iowait; // Sum of idle and iowait gives total time the CPU was not actively doing useful work.
    *total = user + nice + system + *idle + irq + softirq + steal;
    //Total time includes all the measured times. This is used as the denominator to calculate percentage usage.
}

double calculate_cpu_usage() {
    unsigned long long idle1, total1, idle2, total2;
    get_cpu_times(&idle1, &total1);
    sleep(1);
    get_cpu_times(&idle2, &total2);

    double delta_total = total2 - total1;
    double delta_idle  = idle2 - idle1;

    //Calculates how much time passed in total and how much of that time was idle.
    //These deltas represent the activity during the 1-second window.

    if (delta_total == 0) return 0.0;
    return 100.0 * (delta_total - delta_idle) / delta_total;
}
