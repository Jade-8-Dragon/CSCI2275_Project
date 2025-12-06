#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <limits>

using namespace std;

struct point;
struct path;

struct point {
    int x = 0;
    int y = 0;
    int height;
    vector<path*> adj;
    double distance; // temp variable for algorithms
    bool visited;    // temp variable
    point* previous;

    point() {
        height = -1;
        distance = numeric_limits<double>::infinity();
        visited = false;
        previous = nullptr;
    }
};

struct path {
    point* p1;
    point* p2;
    string type;
    double dist;
};

class Graph {
public:
    Graph(int size);
    ~Graph();

    void createPath(int x1, int y1, int x2, int y2, const string& type);
    void createPoint(int x, int y, int height);
    void setHeight(int x, int y, int height);
    void flatten(int x, int y);
    void flattenAll();
    void displayMatrix() const;
    void displayPaths() const;
    void getBestPath(int x1, int y1, int x2, int y2); // prints path and distance

private:
    point** pointMatrix = nullptr;
    int size = 0;
    vector<path*> edges; // track allocated edges to delete exactly once

    void setUnvisited();
};

#endif // GRAPH_H