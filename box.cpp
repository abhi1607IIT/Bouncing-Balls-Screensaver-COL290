#include <GL/glut.h>
// GLfloat xRotated, yRotated, zRotated;
 GLfloat xleft=-1.0f,xright=1.0f,ytop=1.0f,ybottom=-1.0f,zfront=1.0f,zback=-1.0f;
void init(void)
{
glClearColor(0,0,0,0);
 
}

void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    //glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    //glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
   // glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( xright,ytop,zback);    // Top Right Of The Quad (Top)
    glVertex3f(xleft,ytop,zback);    // Top Left Of The Quad (Top)
    glVertex3f(xleft,ytop,zfront);    // Bottom Left Of The Quad (Top)
    glVertex3f( xright,ytop,zfront);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f(xright,ybottom,zfront);    // Top Right Of The Quad (Bottom)
    glVertex3f(xleft,ybottom,zfront);    // Top Left Of The Quad (Bottom)
    glVertex3f(xleft,ybottom,zback);    // Bottom Left Of The Quad (Bottom)
    glVertex3f(xright,ybottom,zback);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f(xright,ytop,zfront);    // Top Right Of The Quad (Front)
    glVertex3f(xleft,ytop,zfront);    // Top Left Of The Quad (Front)
    glVertex3f(xleft,ybottom,zfront);    // Bottom Left Of The Quad (Front)
    glVertex3f(xright,ybottom,zfront);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f(xright,ybottom,zback);    // Top Right Of The Quad (Back)
    glVertex3f(xleft,ybottom,zback);    // Top Left Of The Quad (Back)
    glVertex3f(xleft,ytop,zback);    // Bottom Left Of The Quad (Back)
    glVertex3f(xright,ytop,zback);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(xleft,ytop,zfront);    // Top Right Of The Quad (Left)
    glVertex3f(xleft,ytop,zback);    // Top Left Of The Quad (Left)
    glVertex3f(xleft,ybottom,zback);    // Bottom Left Of The Quad (Left)
    glVertex3f(xleft,ybottom,zfront);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f(xright,ytop,zback);    // Top Right Of The Quad (Right)
    glVertex3f(xright,ytop,zfront);    // Top Left Of The Quad (Right)
    glVertex3f(xright,ybottom,zfront);    // Bottom Left Of The Quad (Right)
    glVertex3f(xright,ybottom,zback);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
}

/*
void animation(void)
{
 
     yRotated += 0.01;
     xRotated += 0.02;
    DrawCube();
}

*/
void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:45 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(45.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
//Set the function for the animation.
//glutIdleFunc(animation);
glutMainLoop();
return 0;
}