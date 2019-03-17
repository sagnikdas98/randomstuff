
#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>

using namespace std;

GLfloat xRotated, yRotated, zRotated;
void init(void)
{
glClearColor(0,0,0,1);
 
}

void DrawCube(void)
{

     

    glMatrixMode(GL_MODELVIEW);
  
    glClear(GL_COLOR_BUFFER_BIT);

   glLoadIdentity();
   
      glTranslatef(0.0,0.0,-5);
    glRotatef(zRotated,1.0,0.0,0.0);
    glRotatef(zRotated,0.0,1.0,0.0);
    
    glRotatef(zRotated,0.0,0.0,1.0);
    glPointSize(1);
  glBegin(GL_POINTS);       
       

    
    for(float  i = -1.0; i< 1.0; i+=0.02 )
    for(float  j = -1.0; j<= 1.0; j+=0.02 )
    for(float  k = -1.0; k<= 1.0; k+=0.02 ){
     // glColor3f(i,j,k);
    glVertex3f(i, j, k); 
    }   
    

  glEnd();            
glFlush();
}


void animation(void)
{
 
     yRotated += 0.01;
     xRotated += 0.01;
     zRotated += 0.02;
    DrawCube();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();

    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
   
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowPosition(100, 100);
glutInitWindowSize(500,500);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
//Set the function for the animation.
glutIdleFunc(animation);
glutMainLoop();
return 0;
}
