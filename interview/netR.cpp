#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <stack>
using namespace std;

void compile_time() {
	#define A 1
	
	#if A+1 == 2
	std::cout<<"A+1==2"<<std::endl;
	#endif

	char *str="abc";
	const int B = 1;
	#if B == 1
	std::cout<<"B+1==2"<<std::endl;
	#endif

}

void drawLine(float x1, float y1, float x2, float y2) {
	printf("(%f,%f)\t(%f,%f)\n",x1,y1,x2,y2);
}

void draw(double angle, double x, double y, double len) {
	if(len < 10)
		return;
	double x1 = x+len*cos(angle);
	double y1 = y+len*sin(angle);
	double angle1 = angle - 1;

	drawLine(x,y,x1,y1);
	draw(angle1,x1,y1,len*0.75);

	double x2 = x-len*cos(angle);
	double y2 = y-len*sin(angle);
	double angle2 = angle + 1;
	drawLine(x,y,x2,y2);
	draw(angle2,x2,y2,len*0.75);
}

void draw_no_reduce(double angle, double x, double y, double len) {
	stack<double> s;
	//s.push(angle),s.push(x),s.push(y),s.push(len);
	while(!s.empty() || len >= 10) {
		if(len >= 10) {
			double x1 = x + len*cos(angle);
			double y1 = y + len*sin(angle);
			double angle1 = angle - 1;
			drawLine(x,y,x1,y1);
			s.push(angle),s.push(x),s.push(y),s.push(len);
			angle = angle1;
			x = x1;
			y = y1;
			len = len*0.75;
		} else {
			len = s.top(); s.pop();
			y = s.top(); s.pop();
			x = s.top(); s.pop();
			angle = s.top(); s.pop();

			double x2 = x - len*cos(angle);
			double y2 = y - len*sin(angle);
			double angle2 = angle + 1;
			drawLine(x,y,x2,y2);
			angle = angle2;
			x = x2;
			y = y2;
			len = len *0.75;
		}
	}
}
	

int main() {

	double angle = 3;
	double x = 1;
	double y = 3;
	double len = 20;
	draw(angle, x, y, len);
	printf("-------------------------------------------\n");
	draw_no_reduce(angle, x, y, len);
	return 0;
}
