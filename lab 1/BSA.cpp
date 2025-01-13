#include<graphics.h>
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int x0,y0,x1,y1;
	cout<<"enter x0:"<<endl;
	cin>>x0;
	cout<<"enter x1:"<<endl;
	cin>>x1;
	cout<<"enter y0:"<<endl;
	cin>>y0;
	cout<<"enter y1:"<<endl;
	cin>>y1;
	int gd = DETECT, gm;
    initgraph(&gd, &gm,"C:\\TC\\BGI");
	int dx=abs(x1-x0);
	int dy=abs(y1-y0);
	int pk=2*dy-dx;
	
	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy); 
	int x=x0,y=y0;
	for(int i=0;i<steps;++i){
		if(pk<0){
			putpixel(x+1,y,WHITE);
			pk=pk+2*dy;
		}
		else if(pk>=0){
			putpixel(x+1,y+1,WHITE);
			pk=pk+2*dy-dx;
		}
	}
	
	reutrn 0;
}

