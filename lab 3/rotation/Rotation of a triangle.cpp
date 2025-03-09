#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

#define PI 3.14159265

class TwoDTransform {
public:
    TwoDTransform() {}

    // Function to draw a triangle
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
        setcolor(color);
        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x1, y1);
    }

    // Function to rotate a point about a pivot
    void rotatePoint(int x, int y, int pivotX, int pivotY, float angle, int &xNew, int &yNew) {
        float rad = angle * (PI / 180.0);  // Convert degrees to radians

        xNew = pivotX + (x - pivotX) * cos(rad) - (y - pivotY) * sin(rad);
        yNew = pivotY + (x - pivotX) * sin(rad) + (y - pivotY) * cos(rad);
    }

    // Function to rotate a triangle around an arbitrary point
    void rotateTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int pivotX, int pivotY, float angle) {
        // Draw original triangle in WHITE
        drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        cout << "Original Triangle Coordinates: (" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ") (" << x3 << ", " << y3 << ")\n";
        
        // Wait for user to press a key
        cout << "Press any key to rotate the triangle..." << endl;
        getch();
        cleardevice();

        // Compute new rotated coordinates
        int x1New, y1New, x2New, y2New, x3New, y3New;
        rotatePoint(x1, y1, pivotX, pivotY, angle, x1New, y1New);
        rotatePoint(x2, y2, pivotX, pivotY, angle, x2New, y2New);
        rotatePoint(x3, y3, pivotX, pivotY, angle, x3New, y3New);

        // Draw rotated triangle in WHITE
        drawTriangle(x1New, y1New, x2New, y2New, x3New, y3New, WHITE);
        cout<<endl<<"Rotated Traingle(counter clockwise): 45 degree"<<endl;
        cout << "Rotated Triangle Coordinates: (" << x1New << ", " << y1New << ") (" << x2New << ", " << y2New << ") (" << x3New << ", " << y3New << ")\n";
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    TwoDTransform transform;

    // Given triangle points
    int x1 = 100, y1 = 150;
    int x2 = 150, y2 = 100;
    int x3 = 50, y3 = 100;

    // Pivot point for rotation
    int pivotX = 100, pivotY = 100;

    // Rotation angle (Counterclockwise)
    float angle = 45.0;

    // Perform rotation
    transform.rotateTriangle(x1, y1, x2, y2, x3, y3, pivotX, pivotY, angle);

    getch();
    closegraph();
    return 0;
}

