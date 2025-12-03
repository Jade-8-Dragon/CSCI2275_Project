#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct point;

struct point {
    int x, int y, int height;
    vector<*path> adj;
    double distance; //temp variable
    bool visited; //temp variable
    point* previous;

    point() {
        height = -1;
        distance = 0;
        visited = false;
        previous = nullptr;
    }
};

struct path;

struct path{
    point* p1;
    point* p2;
    string type;
    double dist;
};

class Graph {
    public:
        Graph(int size);
        ~Graph();
        void createPath(int x1, int y1, int x2, int y2, string type);
        void createPoint(int x, int y, int height);
        void setHeight(int x, int y, int height);
        void flatten(int x, int y);
        void displayMatrix();
        void displayPaths();
        int getBestPath(int x1, int y1, int x2, int y2);

    private:
        point** pointMatrix;
        int size;
        void setUnvisited();
};

#endif