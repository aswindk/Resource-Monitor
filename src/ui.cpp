#include <ncurses.h>
#include <thread>
#include <chrono>

extern "C" {
#include "cpu.h"
#include "mem.h"
}

#include "graph.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(0);
    start_color();

    UsageGraph cpuGraph;
    UsageGraph memGraph;

    int height = 10;
    int width = 60;
    int cpu_start_row = 3;
    int cpu_start_col = 5;
    int mem_start_row = cpu_start_row + height + 4;
    int mem_start_col = 5;

    bool running = true;
    while (running) {
        double cpu_usage = calculate_cpu_usage();
        double mem_usage = get_mem_info();

        cpuGraph.addSample(cpu_usage);
        memGraph.addSample(mem_usage);

        clear();

        mvprintw(0, 5, "Terminal Resource Monitor  (press 'q' to quit)");

        cpuGraph.draw(cpu_start_row, cpu_start_col, height, width, "CPU Usage (%)");
        memGraph.draw(mem_start_row, mem_start_col, height, width, "Memory Usage (%)");

        refresh();

        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    endwin();
    return 0;
}
