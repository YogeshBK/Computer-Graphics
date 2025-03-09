#include <iostream>
#include <cstdlib>
#include <graphics.h> // Include graphics library

using namespace std;

// Structure to store a point
struct Point {
    float x, y;
};

// Define the clipping window boundaries
Point window[4];
float xminp, yminp, xmaxp, ymaxp;

// Function to check if a point is inside a given boundary
bool isInside(Point p, int edge) {
    switch (edge) {
        case 0: return (p.x >= xminp);  // Left boundary
        case 1: return (p.x <= xmaxp);  // Right boundary
        case 2: return (p.y >= yminp);  // Bottom boundary
        case 3: return (p.y <= ymaxp);  // Top boundary
    }
    return false;
}

// Function to calculate intersection of a line with a boundary
Point getIntersection(Point p1, Point p2, int edge) {
    Point intersection;
    float m = (p2.x - p1.x != 0) ? (p2.y - p1.y) / (p2.x - p1.x) : 0.0f; // Ensure float division

    switch (edge) {
        case 0: // Left boundary
            intersection.x = xminp;
            intersection.y = p1.y + m * (xminp - p1.x);
            break;
        case 1: // Right boundary
            intersection.x = xmaxp;
            intersection.y = p1.y + m * (xmaxp - p1.x);
            break;
        case 2: // Bottom boundary
            if (p2.y - p1.y != 0)
                intersection.x = p1.x + (p2.x - p1.x) * (yminp - p1.y) / (p2.y - p1.y);
            intersection.y = yminp;
            break;
        case 3: // Top boundary
            if (p2.y - p1.y != 0)
                intersection.x = p1.x + (p2.x - p1.x) * (ymaxp - p1.y) / (p2.y - p1.y);
            intersection.y = ymaxp;
            break;
    }
    return intersection;
}

// Function to clip the polygon using Sutherland-Hodgman algorithm
void clipPolygon(Point polygon[], int &n, int edge) {
    Point newPolygon[20]; // Array to store the new clipped polygon (Max 20 points)
    int newN = 0;

    for (int i = 0; i < n; i++) {
        Point current = polygon[i];
        Point next = polygon[(i + 1) % n];

        bool currentInside = isInside(current, edge);
        bool nextInside = isInside(next, edge);

        if (currentInside && nextInside) {
            newPolygon[newN++] = next;
        } else if (currentInside && !nextInside) {
            newPolygon[newN++] = getIntersection(current, next, edge);
        } else if (!currentInside && nextInside) {
            newPolygon[newN++] = getIntersection(current, next, edge);
            newPolygon[newN++] = next;
        }
    }

    n = newN;
    for (int i = 0; i < n; i++) {
        polygon[i] = newPolygon[i];
    }
}

// Function to draw a polygon
void drawPolygon(Point polygon[], int n) {
    setcolor(WHITE);
    for (int i = 0; i < n; i++) {
        int x1 = polygon[i].x, y1 = polygon[i].y;
        int x2 = polygon[(i + 1) % n].x, y2 = polygon[(i + 1) % n].y;
        line(x1, y1, x2, y2);
    }
}

int main() {
    int n;
    cout << "Enter number of vertices in polygon: ";
    cin >> n;

    Point polygon[20]; // Max 20 points
    cout << "Enter polygon coordinates (x, y):\n";
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    cout << "Enter clipping window coordinates bottom-left (x, y ): ";
    cin >> xminp >> yminp ;
cout << "Enter clipping window coordinates  top-right (x, y): ";
cin>>xmaxp >> ymaxp;
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Draw the original polygon in WHITE
    drawPolygon(polygon, n);

    // Draw clipping window in WHITE
    setcolor(WHITE);
    rectangle(xminp, yminp, xmaxp, ymaxp);

    cout << "\nOriginal polygon drawn. Press any key to clip...";
    getch();
    cleardevice(); // Clear screen before drawing clipped polygon

    // Draw clipping window again
    setcolor(WHITE);
    rectangle(xminp, yminp, xmaxp, ymaxp);

    // Clip against all four edges
    for (int edge = 0; edge < 4; edge++) {
        clipPolygon(polygon, n, edge);
    }

    // Draw the final clipped polygon in WHITE
    drawPolygon(polygon, n);

    cout << "\nClipped Polygon vertices:\n";
    for (int i = 0; i < n; i++) {
        cout << "(" << polygon[i].x << ", " << polygon[i].y << ")\n";
    }

    getch();  // Wait for user input before closing graphics window
    closegraph(); // Close graphics mode

    return 0;
}

