#include <iostream>
#include <graphics.h>

using namespace std;

// Define the clipping window boundaries
float xmin, ymin, xmax, ymax;

// Liang-Barsky Algorithm function
bool liangBarsky(float x1, float y1, float x2, float y2, float &newX1, float &newY1, float &newX2, float &newY2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float p[4], q[4];
    float t1 = 0.0, t2 = 1.0;

    p[0] = -dx; q[0] = x1 - xmin;  // Left boundary
    p[1] = dx;  q[1] = xmax - x1;  // Right boundary
    p[2] = -dy; q[2] = y1 - ymin;  // Bottom boundary
    p[3] = dy;  q[3] = ymax - y1;  // Top boundary

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) return false; // Parallel and outside the window

        float t = q[i] / p[i];

        if (p[i] < 0) {
            t1 = max(t1, t); // Entering boundary
        } else if (p[i] > 0) {
            t2 = min(t2, t); // Exiting boundary
        }
    }

    if (t1 > t2) return false; // Line is completely outside

    // Compute new clipped coordinates
    newX1 = x1 + t1 * dx;
    newY1 = y1 + t1 * dy;
    newX2 = x1 + t2 * dx;
    newY2 = y1 + t2 * dy;

    return true; // Line is visible
}

// Function to draw the clipping window
void drawClippingWindow() {
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
}

int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Get clipping window coordinates
    cout << "Enter clipping window coordinates (xmin ymin xmax ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    // Get line coordinates
    float x1, y1, x2, y2;
    cout << "Enter line coordinates (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw clipping window
    drawClippingWindow();

    // Draw original line in WHITE
    setcolor(WHITE);
    line(x1, y1, x2, y2);

    cout << "\nOriginal line drawn. Press any key to clip...";
    getch(); // Wait for user input before clipping
    cleardevice(); // Clear screen before drawing clipped line

    // Draw clipping window again
    drawClippingWindow();

    float newX1, newY1, newX2, newY2;
    if (liangBarsky(x1, y1, x2, y2, newX1, newY1, newX2, newY2)) {
        // Draw the clipped line in WHITE
        setcolor(WHITE);
        line(newX1, newY1, newX2, newY2);
        cout << "\nClipped Line Coordinates: (" << newX1 << ", " << newY1 << ") to (" << newX2 << ", " << newY2 << ")\n";
    } else {
        cout << "\nLine is completely outside the clipping window.\n";
    }

    getch();  // Wait for user input before closing graphics window
    closegraph();

    return 0;
}

