# CSCI2275_Project
Our project aims to accurately map a 3D environment which is made up of a 2d coordinate system extended to 3D by giving each coordinate point a height. In order to not have the environment’s upward facing surface be made of cubes, we implemented a path system that allows each coordinate point to have different shapes of path between the surrounding points. This allows us to have different traversal distances (as if a person is moving between coordinate points) between points. We used this to model the shortest path between different points given that different shapes may force the person to move along some paths slower than others despite the shorter distance in the xy-plane.


We primarily used a graph with a 2D Array implementation. Each “point” on the graph called “pointMatrix” has a coordinate position corresponding to its position in the matrix, a height, some temp variables, and a vector of “path”s leading to adjacent points. Each path has its own endpoints, path type, and distance.


The graph allows us to easily store each point’s paths so that we can traverse through the whole matrix using Dijkstra’s to find the shortest path between points. Additionally, each edge calculates its own length based on the path type and the crow’s flight distance between the two points.


# Documentation
Constructor:

    Graph(int size);
Destructor:

    ~Graph();
Mutator functions:

    void createPath(int x1, int y1, int x2, int y2, const string& type);
    void createPoint(int x, int y, int height);
    void setHeight(int x, int y, int height);
    void flatten(int x, int y);
    void flattenAll();
Getter functions:
    
    void displayMatrix() const;
    void displayPaths() const;
    void getBestPath(int x1, int y1, int x2, int y2); // prints path and distance
