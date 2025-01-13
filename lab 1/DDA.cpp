#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int x0, y0, x1, y1;
    cout << "Enter (x0, y0): ";
    cin >> x0 >> y0;
    cout << "Enter (x1, y1): ";
    cin >> x1 >> y1;
    double dx = x1 - x0;
    double dy = y1 - y0;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);    
    double xincr = dx / steps;
    double yincr = dy / steps;    
    cout << "Rasterizing the line..." << endl;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    double x = x0;
    double y = y0;
    for (int i = 0; i <= steps; ++i) {
        putpixel(round(x), round(y), WHITE); 
        x += xincr; 
        y += yincr; 
    }
    getch(); 
    closegraph(); 
    return 0;
}

