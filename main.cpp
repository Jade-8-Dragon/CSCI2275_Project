#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./program <inputfile> <size>" << endl;
        return 1;
    }

    string filename = argv[1];
    int size = stoi(argv[2]);
    if (size < 1) {
        cout << "Invalid size" << endl;
        return 1;
    }
    Graph map(size);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.rfind("Edges", 0) == 0) break;
        if (line.empty()) continue;

        stringstream ss(line);
        int x, y, h;
        char comma;

        ss >> x >> comma >> y >> comma >> h;
        map.createPoint(x, y, h);
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        int x1, y1, x2, y2;
        string type;
        char comma;

        ss >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2 >> comma >> type;
        map.createPath(x1, y1, x2, y2, type);
    }

    file.close();

    bool active = true;
    int option;

    while (active) {
        cout << "\nSelect an option:\n"
             << "1. Create point\n"
             << "2. Create path\n"
             << "3. Change height\n"
             << "4. Flatten point\n"
             << "5. Flatten all\n"
             << "6. Get shortest path\n"
             << "7. Show graph\n"
             << "8. Show edges\n"
             << "9. Exit program\n";

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        int x, y, x1, y1, x2, y2, height;
        string type;

        switch (option) {
            case 1:
                cout << "Enter x y height: ";
                cin >> x >> y >> height;
                if (x >= size || x < 0 ||y >= size || y < 0 || height < 0) {
                    cout << "Invalid data" << endl;
                    break;
                }
                map.createPoint(x, y, height);
                break;

            case 2:
                cout << "Enter x1 y1 x2 y2 type: ";
                cin >> x1 >> y1 >> x2 >> y2 >> type;
                if (x1 >= size || x1 < 0 || y1 >= size || y1 < 0 || x2 >= size || x2 < 0 || y2 >= size || y2 < 0) {
                    cout << "Invalid data" << endl;
                    break;
                }
                map.createPath(x1, y1, x2, y2, type);
                break;

            case 3:
                cout << "Enter x y newHeight: ";
                cin >> x >> y >> height;
                if (x >= size || x < 0 ||y >= size || y < 0 || height < 0) {
                    cout << "Invalid data" << endl;
                    break;
                }
                map.setHeight(x, y, height);
                break;

            case 4:
                cout << "Enter x y: ";
                cin >> x >> y;
                if (x >= size || x < 0 ||y >= size || y < 0) {
                    cout << "Invalid data" << endl;
                    break;
                }
                map.flatten(x, y);
                break;
                
            case 5:
                cout << "Flattening..." << endl;
                map.flattenAll();
                break;

            case 6:
                cout << "Enter x1 y1 x2 y2: ";
                cin >> x1 >> y1 >> x2 >> y2;
                if (x1 >= size || x1 < 0 || y1 >= size || y1 < 0 || x2 >= size || x2 < 0 || y2 >= size || y2 < 0) {
                    cout << "Invalid data" << endl;
                    break;
                }
                map.getBestPath(x1, y1, x2, y2);
                break;

            case 7:
                map.displayMatrix();
                break;

            case 8:
                map.displayPaths();
                break;

            case 9:
                cout << "Exiting program.\n";
                active = false;
                break;

            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}