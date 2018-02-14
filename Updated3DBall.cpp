#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
using namespace std;
#define pi 3.14159
#define step 0.005
class Ball
{
    GLfloat ballRadius;
    GLfloat ballX;
    GLfloat ballY;
    GLfloat ballZ;
    GLfloat vx,vy,vz;
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
public:
    GLfloat set_r(GLfloat red)
    {
        r = red;
    }
    GLfloat set_b(GLfloat blue)
    {
        b = blue;
    }
    GLfloat set_g(GLfloat green)
    {
        g = green;
    }
    GLfloat get_x()
    {
        return ballX;
    }
    GLfloat get_y()
    {
        return ballY;
    }
    GLfloat get_z()
    {
        return ballZ;
    }
    GLfloat get_vx()
    {
        return vx;
    }
    GLfloat get_vy()
    {
        return vy;
    }
    GLfloat get_vz()
    {
        return vz;
    }
    GLfloat set_x(GLfloat xd)
    {
        ballX = xd;
    }
    GLfloat set_y(GLfloat yd)
    {
        ballY = yd;
    }
    GLfloat set_z(GLfloat zd)
    {
        ballZ = zd;
    }
    GLfloat set_vx(GLfloat xv)
    {
        vx = xv;
    }
    GLfloat set_vy(GLfloat yv)
    {
        vy = yv;
    }
    GLfloat set_vz(GLfloat zv)
    {
        vz = zv;
    }
    GLfloat set_radius(GLfloat r)
    {
        ballRadius = r;
    }
    GLfloat get_radius()
    {
        return ballRadius;
    }
};
int count = 3;
GLfloat ballRadius = 0.1f;
GLfloat ballX[3],ballY[3],ballZ[3],xspeed[3],yspeed[3],zspeed[3];
GLfloat ballXMax = 1, ballYMax = 1, ballXMin = -1 ,ballYMin = -1,ballZMax = -3, ballZMin = -5,r[3];
GLint refreshmillis = 30;
GLfloat normal[3];
GLdouble XLeft,XRight,YTop,YBottom,ZFront = 0,ZBack = -4;
pthread_barrier_t barrier,barrier2;
pthread_barrierattr_t attr;
pthread_mutex_t mutex;
int ret = pthread_barrier_init(&barrier,&attr,3);
int ret2 = pthread_barrier_init(&barrier2,&attr,3);
Ball balls[3];
void initGL()
{
    glClearColor(0.0,0.0,0.0,1);
}
GLfloat sdistance(int i,int j)
{
    return((ballX[i]-ballX[j])*(ballX[i]-ballX[j]) + (ballY[i]-ballY[j])*(ballY[i]-ballY[j]) + (ballZ[i]-ballZ[j])*(ballZ[i]-ballZ[j]));
}
void ncap(int i,int j)
{
    normal[0] = (ballX[i] - ballX[j])/ sqrt(sdistance(i,j));
    normal[1] = (ballY[i] - ballY[j])/ sqrt(sdistance(i,j));
    normal[2] = (ballZ[i] - ballZ[j])/ sqrt(sdistance(i,j));
}
GLfloat vdot(int i)
{
    return normal[0]*xspeed[i] + normal[1]*yspeed[i] + normal[2]*xspeed[2];
}
void collide(int i,int j)
{
    ncap(i,j);
    GLfloat n1 = vdot(i),n2 = vdot(j);
    //cout<<"Done"<<endl;
    xspeed[i] = xspeed[i] + (n2 - n1 )*normal[0];
    yspeed[i] =  yspeed[i] + (n2 - n1 )*normal[1];
    zspeed[i] =  zspeed[i] + (n2 - n1 )*normal[2];
    xspeed[j] =  xspeed[j] + (n1 - n2 )*normal[0];
    yspeed[j] =  yspeed[j] + (n1 - n2 )*normal[1];
    zspeed[j] =  zspeed[j] + (n1 - n2 )*normal[2];
    while(sdistance(i,j)<=(r[i]+r[j])*(r[i]+r[j]))
    {
        ballX[i]+=step*xspeed[i];
        ballX[j]+=step*xspeed[j];
        ballY[i]+=step*yspeed[i];
        ballY[j]+=step*yspeed[j];
        ballZ[i]+=step*zspeed[i];
        ballY[j]+=step*zspeed[j];
    }
}

void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,0.0);
    //glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    //glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
   // glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( XRight,YTop,ZBack);    // Top Right Of The Quad (Top)
    glVertex3f(XLeft,YTop,ZBack);    // Top Left Of The Quad (Top)
    glVertex3f(XLeft,YTop,ZFront);    // Bottom Left Of The Quad (Top)
    glVertex3f( XRight,YTop,ZFront);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f(XRight,YBottom,ZFront);    // Top Right Of The Quad (Bottom)
    glVertex3f(XLeft,YBottom,ZFront);    // Top Left Of The Quad (Bottom)
    glVertex3f(XLeft,YBottom,ZBack);    // Bottom Left Of The Quad (Bottom)
    glVertex3f(XRight,YBottom,ZBack);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f(XRight,YTop,ZFront);    // Top Right Of The Quad (Front)
    glVertex3f(XLeft,YTop,ZFront);    // Top Left Of The Quad (Front)
    glVertex3f(XLeft,YBottom,ZFront);    // Bottom Left Of The Quad (Front)
    glVertex3f(XRight,YBottom,ZFront);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f(XRight,YBottom,ZBack);    // Top Right Of The Quad (Back)
    glVertex3f(XLeft,YBottom,ZBack);    // Top Left Of The Quad (Back)
    glVertex3f(XLeft,YTop,ZBack);    // Bottom Left Of The Quad (Back)
    glVertex3f(XRight,YTop,ZBack);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(XLeft,YTop,ZFront);    // Top Right Of The Quad (Left)
    glVertex3f(XLeft,YTop,ZBack);    // Top Left Of The Quad (Left)
    glVertex3f(XLeft,YBottom,ZBack);    // Bottom Left Of The Quad (Left)
    glVertex3f(XLeft,YBottom,ZFront);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f(XRight,YTop,ZBack);    // Top Right Of The Quad (Right)
    glVertex3f(XRight,YTop,ZFront);    // Top Left Of The Quad (Right)
    glVertex3f(XRight,YBottom,ZFront);    // Bottom Left Of The Quad (Right)
    glVertex3f(XRight,YBottom,ZBack);    // Bottom Right Of The Quad (Right)
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
void reshapebox(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:45 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(45.0,(GLdouble)x/(GLdouble)y,0,5.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}
void display()
{	
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    DrawCube();
    for(int j=0;j<3;j++)
    {
        glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	glTranslatef(ballX[j],ballY[j],ballZ[j]);
        glColor3f(0.9, 0.3, 0.2);
        glScalef(1.0,1.0,1.0);
        glutSolidSphere(r[j],20,20);
    	glEnd();
    }
    glutSwapBuffers();
}
void reshape(GLsizei width,GLsizei height)
{
    if(height==0) height = 1;
    GLfloat aspect = (GLfloat)width/(GLfloat) height;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width>height)
    {
        XLeft = -1.0 * aspect;
        XRight = 1.0 * aspect;
        YBottom = -1.0;
        YTop = 1.0;

    }
    else
    {
        XLeft = -1.0;
        XRight = 1.0;
        YBottom = -1.0 / aspect;
        YTop = 1.0 / aspect;
    }
    //gluOrtho2D(XLeft,XRight,YBottom,YTop);
    gluPerspective(39.0,(GLdouble)width/(GLdouble)height,1,5);
    ballXMin = XLeft + ballRadius;
    ballXMax = XRight - ballRadius;
    ballYMin = YBottom + ballRadius;
    ballYMax = YTop - ballRadius;
    ballZMax; 
}

void Timer(GLint value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshmillis,Timer,0);
}

GLint windowWidth = 640;
GLint windowHeight = 480;
GLint windowPosx = 300;
GLint windowPosy = 300;

void *bball(void* j)
{
	int i = (long long int) j;
    ballX[i] = balls[i].get_x();
    ballY[i] = balls[i].get_y();
    ballZ[i] = balls[i].get_z();
    xspeed[i] = balls[i].get_vx();
    yspeed[i] = balls[i].get_vy();
    zspeed[i] = balls[i].get_vz();
    r[i] = balls[i].get_radius();
	while(true)
	{	
        ballX[i]+=xspeed[i];
    	ballY[i]+=yspeed[i];
        ballZ[i]+=zspeed[i];
    	if(ballX[i]>ballXMax)
    	{
        	ballX[i] = ballXMax;
        	xspeed[i] = -xspeed[i];
    	}
    	else if(ballX[i]<ballXMin)
    	{
        	ballX[i] = ballXMin;
        	xspeed[i] = -xspeed[i];
    	}
    	if(ballY[i]>ballYMax)
    	{
        	ballY[i] = ballYMax;
        	yspeed[i] = -yspeed[i];
    	}
    	else if(ballY[i]<ballYMin)
    	{
        	ballY[i] = ballYMin;
        	yspeed[i] = -yspeed[i];
    	}
        if(ballZ[i]>ballZMax)
        {
            ballZ[i] = ballZMax;
            zspeed[i] = -zspeed[i];
        }
        else if(ballZ[i]<ballZMin)
        {
            ballZ[i] = ballZMin;
            zspeed[i] = -zspeed[i];
        }
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        for(int k = i+1;k<3;k++)
        {
            if(sdistance(i,k)<=(r[i]+r[k])*(r[i]+r[k]))
            {
                collide(i,k);
                //cout<<"Yeah"<<endl;
            }
        }
        pthread_mutex_unlock(&mutex);
        pthread_barrier_wait(&barrier2);
        usleep(20000);
    }
    
}
int main(int argc,char** argv)
{
    time_t seconds;
    time(&seconds);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth , windowHeight);
    glutInitWindowPosition(windowPosx,windowPosy);
    glutCreateWindow("Bouncing Ball");
    pthread_t id[2];
    int j = 0;
    balls[0].set_x(0.3);
    balls[0].set_y(0.4);
    balls[0].set_z(0.9);
    balls[1].set_x(-0.3);
    balls[1].set_y(0.4);
    balls[1].set_z(0.4);
    balls[2].set_x(0);
    balls[2].set_y(0.5);
    balls[2].set_z(0.2);
    balls[0].set_radius(0.2);
    balls[1].set_radius(0.2);
    balls[2].set_radius(0.2);
    balls[0].set_vx(-0.03);
    balls[1].set_vx(0.03);
    balls[2].set_vx(0);
    balls[0].set_vy(-0.04);
    balls[1].set_vy(-0.04);
    balls[2].set_vy(-0.05);
    balls[0].set_vz(0.08);
    balls[1].set_vz(-0.02);
    balls[2].set_vz(0.04);
    pthread_create(&id[0],NULL,bball,(void *) j);
    j = 1;
    pthread_create(&id[1],NULL,bball,(void *) j);
    j = 2;
    pthread_create(&id[1],NULL,bball,(void *) j);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,Timer,0);
    initGL();
    glutMainLoop();
    pthread_exit(&id[0]);
    pthread_exit(&id[1]);
    return 0;
}   
