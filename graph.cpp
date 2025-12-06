#include "graph.hpp"

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std;

Graph::Graph(int size) : size(size) {
    if (size <= 0) {
        pointMatrix = nullptr;
        return;
    }

    pointMatrix = new point*[size];
    for (int i = 0; i < size; i++) {
        pointMatrix[i] = new point[size];
        for (int j = 0; j < size; j++) {
            pointMatrix[i][j].x = i;
            pointMatrix[i][j].y = j;
            pointMatrix[i][j].distance = numeric_limits<double>::infinity();
            pointMatrix[i][j].visited = false;
            pointMatrix[i][j].previous = nullptr;
        }
    }
}

void Graph::createPoint(int x, int y, int height) {
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "Invalid point" << endl;
        return;
    }
    if (pointMatrix[x][y].height != -1) {
        cout << "Point already exists here. Flatten or choose a different point" << endl;
        return;
    }

    pointMatrix[x][y].height = height;
}

void Graph::createPath(int x1, int y1, int x2, int y2, const string& type) {
    if (x1 >= size || y1 >= size || x1 < 0 || y1 < 0 ||
        x2 >= size || y2 >= size || x2 < 0 || y2 < 0) {
            cout << "Invalid point(s)" << endl;
            return;
        }

    point& p1 = pointMatrix[x1][y1];
    point& p2 = pointMatrix[x2][y2];

    if (p1.height < 0 || p2.height < 0) {
        cout << "Invalid point(s)" << endl;
        return;
    }
    path* p = new path{ &p1, &p2, type, 0.0 };

    if (type == "wall")
        p->dist = 1.0 + abs(p1.height - p2.height);
    else if (type == "diagonal")
        p->dist = 1.0 + sqrt(1.0 + pow(static_cast<double>(p1.height - p2.height), 2));
    else if (type == "arc")
        p->dist = 0.5 * 3.1415926 * (abs(p1.height - p2.height) + 1);
    else {
        cout << "Invalid path type" << endl;
        delete p;
        return;
    }
    p1.adj.push_back(p);
    p2.adj.push_back(p);

    edges.push_back(p);
}

void Graph::setHeight(int x, int y, int height) {
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "Invalid point" << endl;
        return;
    }
    if (height < 0) {
        cout << "Invalid height" << endl;
        return;
    }
    pointMatrix[x][y].height = height;
}

void Graph::flatten(int x, int y) {
    if (x >= size || y >= size || x < 0 || y < 0) {
        cout << "Invalid point" << endl;
        return;
    }
    pointMatrix[x][y].height = 0;
}

void Graph::flattenAll() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pointMatrix[i][j].height = 0;
}

void Graph::displayMatrix() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(3) << pointMatrix[j][i].height << " ";
        }
        cout << "\n";
    }
}

void Graph::displayPaths() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            const vector<path*>& paths = pointMatrix[i][j].adj;

            cout << "Point (" << i << ", " << j << ") --> ";

            for (path* p : paths) {
                if (p->p1 == &pointMatrix[i][j]) {
                    cout << "(" << p->p2->x << ", " << p->p2->y << ")[" << p->type << ":" << p->dist << "] ";
                } else {
                    cout << "(" << p->p1->x << ", " << p->p1->y << ")[" << p->type << ":" << p->dist << "] ";
                }
            }
            cout << "\n";
        }
    }
}

void Graph::setUnvisited() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pointMatrix[i][j].visited = false;
            pointMatrix[i][j].distance = numeric_limits<double>::infinity();
            pointMatrix[i][j].previous = nullptr;
        }
    }
}

void Graph::getBestPath(int x1, int y1, int x2, int y2) {
    if (!pointMatrix) {
        cout << "Graph is empty.\n";
        return;
    }
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 ||
        x1 >= size || y1 >= size || x2 >= size || y2 >= size) {
        cout << "Invalid point(s)" << endl;
        return;
    }

    point* start = &pointMatrix[x1][y1];
    point* goal  = &pointMatrix[x2][y2];

    if (start->height < 0 || goal->height < 0) {
        cout << "Start or goal point is not initialized (height < 0).\n";
        return;
    }

    setUnvisited();

    using PQItem = pair<double, point*>;
    priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;

    start->distance = 0.0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [dist, curr] = pq.top();
        pq.pop();

        if (dist > curr->distance) continue;

        if (curr == goal) break;

        for (path* e : curr->adj) {
            point* next = (e->p1 == curr ? e->p2 : e->p1);
            double nd = curr->distance + e->dist;
            if (nd < next->distance) {
                next->distance = nd;
                next->previous = curr;
                pq.push({nd, next});
            }
        }
    }

    cout << goal->distance << endl;
    if (isfinite(goal->distance)) {
        vector<string> pathStr;
        point* p = goal;
        while (p != nullptr) {
            pathStr.push_back("(" + to_string(p->x) + "," + to_string(p->y) + ")");
            p = p->previous;
        }

        cout << "Shortest path: ";
        for (int i = static_cast<int>(pathStr.size()) - 1; i >= 0; --i) {
            cout << pathStr[i];
            if (i > 0) cout << " -> ";
        }
        cout << "\nDistance: " << goal->distance << "\n";
    } else {
        cout << "No path found.\n";
    }

    setUnvisited();
}

Graph::~Graph() {
    // delete unique edges
    for (path* p : edges)
        delete p;
    edges.clear();

    // delete matrix rows
    if (pointMatrix) {
        for (int i = 0; i < size; i++) {
            delete[] pointMatrix[i];
        }
        delete[] pointMatrix;
        pointMatrix = nullptr;
    }
}
