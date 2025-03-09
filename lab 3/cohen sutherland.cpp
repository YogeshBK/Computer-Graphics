#include <iostream>
#include <graphics.h>

using namespace std;

// Region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Clipping Window Boundaries
int xmin, ymin, xmax, ymax;

// Function to find the region code of a point (x, y)
int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    if (y > ymax) code |= TOP;
    return code;
}

// Cohen-Sutherland clipping algorithm
void cohenSutherlandClip(int x0, int y0, int x1, int y1) {
    int code0 = computeCode(x0, y0);
    int code1 = computeCode(x1, y1);
    bool accept = false;

    while (true) {
        if ((code0 == 0) && (code1 == 0)) {
            accept = true;
            break;
        } else if (code0 & code1) {
            break;
        } else {
            int codeOut;
            int x, y;

            if (code0 != 0)
                codeOut = code0;
            else
                codeOut = code1;

            if (codeOut & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (codeOut == code0) {
                x0 = x;
                y0 = y;
                code0 = computeCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
        }
    }

    if (accept) {
        line(x0, y0, x1, y1);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    cout << "Enter clipping window coordinates (xmin, ymin, xmax, ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    int number;
    cout << "Enter the number of lines: ";
    cin >> number;

    int lines[number][4];
    for (int i = 0; i < number; i++) {
        cout << "Enter line coordinates (x0, y0, x1, y1) for line " << i + 1 << ": ";
        cin >> lines[i][0] >> lines[i][1] >> lines[i][2] >> lines[i][3];
    }

    // Draw clipping window
    rectangle(xmin, ymin, xmax, ymax);

    // Draw original lines
    for (int i = 0; i < number; i++) {
        line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }

    cout << "Press any key to perform clipping...";
    getch();
    cleardevice();

    // Draw clipping window again
    rectangle(xmin, ymin, xmax, ymax);

    // Perform clipping
    for (int i = 0; i < number; i++) {
        cohenSutherlandClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }

    getch();
    closegraph();
    return 0;
}
