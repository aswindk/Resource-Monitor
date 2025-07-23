#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

const int HISTORY_SIZE = 60;

class UsageGraph {
public:
    UsageGraph();
    void addSample(double value);
    const std::vector<double>& getHistory() const;
    void draw(int start_row, int start_col, int height, int width, const char* title) const;
private:
    std::vector<double> history;
    int nextIndex;
};

#endif // GRAPH_H
