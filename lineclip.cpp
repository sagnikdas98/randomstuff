#include<GL/glut.h>
#define opcode int

float xmin=50, xmax=100, umin=300, umax=400, ymin=50, ymax=100, vmin=300, vmax=400;
enum {top = 0x8, bottom = 0x4, right = 0x2, left = 0x1};
float x1,y1,x2,y2;

opcode generateCode(int x, int y){
	int p = 0;
	if(x < xmin) p |= left;
	if(y < ymin) p |= bottom;
	if(x > xmax) p |= right;
	if(y > ymax) p |= top;
	return p;
}

void sutherland(float prev_x1,float prev_y1,float prev_x2 ,float prev_y2){
	float m;
	opcode p1, p2, p;
	int x, y;
	x1 = prev_x1;
	x2 = prev_x2;
	y1 = prev_y1;
	y2 = prev_y2;

	bool done = false, accept = false;
	p1 = generateCode(x1, y1);
	p2 = generateCode(x2, y2);

	while(!done){
		if((p1 | p2) == 0){
			accept = true;
			done = true;
		}
		else if((p1 & p2) != 0)
			done = true;
		else{
			m = (y2-y1)/(x2-x1);
			p = p1 != 0 ? p1 : p2;
			if((p & left) != 0){
				x = xmin;
				y = y1 + (xmin - x1) * m;
			}
			if((p & right) != 0){
				x = xmax;
				y = y1 + (xmax - x1) * m;
			}
			if((p & top) != 0){
				y = ymax;
				x = x1 + (ymax - y1) / m;
			}
			if((p & bottom) != 0){
				y = ymin;
				x = x1 + (ymin - y1) / m;
			}
			if(p == p1){
				x1 = x;
				y1 = y;
				p1 = generateCode(x1, y1);
			}
			if(p == p2){
				x2 = x;
				y2 = y;
				p2 = generateCode(x2, y2);
			}
		}
	}
	if(accept){
		float sx = (umax - umin) / (xmax - xmin);
		float sy = (vmax - vmin) / (ymax - ymin);
		x1 = sx * x1 + umin - sx * xmin;
		x2 = sx * x2 + umin - sx * xmin;
		y1 = sy * y1 + vmin - sy * ymin;
		y2 = sy * y2 + vmin - sy * ymin;

		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
}

void display(){
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymax);
		glVertex2f(xmax, ymax);
		glVertex2f(xmax, ymin);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(umin, vmin);
		glVertex2f(umin, vmax);
		glVertex2f(umax, vmax);
		glVertex2f(umax, vmin);
	glEnd();

	float prev_x1=0,prev_x2=90,prev_y1=0,prev_y2=90;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(prev_x1, prev_y1);
		glVertex2f(prev_x2, prev_y2);
	glEnd();
	glColor3f(0,0,1);
	sutherland(prev_x1,prev_y1,prev_x2,prev_y2);
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(1200,1200);
	glutCreateWindow("Clip");
	glOrtho(0, 600, 0, 600, -1, 1);
	glutDisplayFunc(display);
	glutMainLoop();
}
