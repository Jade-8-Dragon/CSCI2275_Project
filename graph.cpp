#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;


Graph::Graph(int size) {
    this.size = size;
    pointMatrix = new point*[size];
    for (int i = 0; i < size; i++) {
        pointMatrix[i] = new point[size];
        for (int j = 0; j; size; j++) {
            pointMatrix[i][j].x = i;
            pointMatrix[i][j].y = j;
        }
    }
}

void Graph::createPoint(int x, int y, int height){
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "That position is out of range. Please try another position.\n";
        return;
    }
    if (pointMatrix[x][y].height >= 0) {
        cout << "There is already a point here. Please try another position.\n";
        return;
    }
    pointMatrix[x][y].height = height;
}

void Graph::createPath(int x1, int y1, int x2, int y2, string type){
    p1 = pointMatrix[x1][y1];
    p2 = pointMatrix[x2][y2];
    if (x1 >= size || y1 >= size || x1 < 0 || y1 < 0 || x2 >= size || y2 >= size || x2 < 0 || y2 < 0) {
        cout << "Those positions are out of range. Please try new positions.\n";
        return;
    }
    if (p1.height < 0 || p2.height < 0) {
        cout << "These points haven't been initialized. Please try new positions or initialize these ones.\n";
        return;
    }

    path* p = new path {&p1, &p2, type, 0.0};

    switch (type) {
        case "wall":
            p.dist = 1.0 + abs(p1.height - p2.height);
            break;
        case "diagonal":
            p.dist = 1.0 + sqrt(1.0 + (p1.height - p2.height) * (p1.height - p2.height));
            break;
        case "arc":
            p.dist = 0.5 * 3.14159 * (abs(p1.height - p2.height) + 1); //FINISH LATER
            break;
        case "par":
            p.dist = 0.5 * 3.14159 * (abs(p1.height - p2.height) + 1); //FINISH LATER
            break;
        default:
            break;
    }

    p1.adj.push_back(p);
    p2.adj.push_back(p);
}

void Graph::setHeight(int x, int y, int height) {
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "That position is out of range. Please try another position.\n";
        return;
    }
    pointMatrix[x][y].height = height;
}

void Graph::flatten(int x, int y) {
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "That position is out of range. Please try another position.\n";
        return;
    }
    pointMatrix[x][y].height = height;
}

void Graph::displayMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << pointMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::displayPaths() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vector<path*> paths = vertices[i]->adj;
            cout << "Point (" << i << ", " << j << ") --> ";
            for (int k = 0; k < paths.size(); k++) {
                if (paths[k]->p1.x == i && paths[k]->p1.y == j) {
                    cout << "(" << paths[k]->p2.x << ", " << paths[k]->p2.y << ") ";
                } else {
                    cout << "(" << paths[k]->p1.x << ", " << paths[k]->p1.y << ") ";
                }
            }
        }
        cout << endl;
    }
}

void Graph::setUnvisited() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pointMatrix[i][j].visited = false;
            pointMatrix[i][j].distance = 0;
            pointMatrix[i][j].previous = nullptr;
        }
    }
}

void Graph::getBestPath(int x1, int y1, int x2, int y2) {
    point* start = pointMatrix[x1][y1];
    point* end = pointMatrix[x2][y2];

    queue<point*> tqueue;
    tqueue.push(start);
    start->visited = true;

    while (!tqueue.empty()) {
        vector<path*> paths = tqueue.front()->adj;
        vector<point*> points;
        vector<int> distances;
        int n = tqueue.front()->distance;
        point* curr = tqueue.front();
        tqueue.pop();

        for (size_t i = 0; i < paths.size(); i++) {
            if (curr == paths[i]->p1) {
                points.push_back(paths[i]->p2);
            } else {
                points.push_back(paths[i]->p1);
            }
            distances.push_back(paths[i]->dist);
        }

        for (size_t i = 0; i < points.size(); i++) {
            if (points[i] == end) {
                cout << "The shortest Path is: ";
                string temp = "(" + x2 + ", " + y2 + ")";
                while (curr != nullptr) {
                    temp = "(" + curr->x + ", " + curr->y + ") -> " + temp;
                    curr = curr->previous;
                }

                cout << temp << "\nThe shortest path's distance is: " << n + distances[i] << endl;
                return;
            }
            if (!points[i]->visited) {
                tqueue.push(edges[i].v);
                points[i]->visited = true;
                points[i]->distance = n + distances[i];
                edges[i]->previous = curr;
            }
        }

        setUnvisited();
    }

    cout << "There is no path between the start and destination.";
}