#include "graph.h"
#include <ncurses.h>
#include <algorithm>
#include <cstring>

UsageGraph::UsageGraph()
    : history(HISTORY_SIZE, 0.0), nextIndex(0) {}

void UsageGraph::addSample(double value) {
    history[nextIndex] = value;
    nextIndex = (nextIndex + 1) % HISTORY_SIZE;
}

const std::vector<double>& UsageGraph::getHistory() const {
    return history;
}

void UsageGraph::draw(int start_row, int start_col, int height, int width, const char* title) const {
    // Clear the graph area
    for (int i = 0; i < height; ++i) {
        move(start_row + i, start_col);
        for (int j = 0; j < width; ++j) {
            addch(' ');
        }
    }

    int title_len = strlen(title);
    if (title_len < width) {
        mvprintw(start_row - 1, start_col + (width - title_len)/2, "%s", title);
    }

    const double max_value = 100.0;
    int idx = nextIndex;

    for (int x = 0; x < width && x < HISTORY_SIZE; ++x) {
        int hist_idx = (idx + x) % HISTORY_SIZE;
        double value = history[hist_idx];
        int bar_height = static_cast<int>(value / max_value * height);
        if (bar_height > height) bar_height = height;

        for (int y = 0; y < bar_height; ++y) {
            mvaddch(start_row + height - 1 - y, start_col + x, '|');
        }
    }
    
    // Draw y-axis separator
    for (int y = 0; y < height; ++y) {
        mvaddch(start_row + y, start_col - 1, ':');
    }
}
