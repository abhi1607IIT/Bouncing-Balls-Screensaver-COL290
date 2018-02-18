#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
using namespace std;
#define pi 3.14159
#define step 0.0005
    /* white ambient light at half intensity (rgba) */
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    /* super bright, full intensity diffuse light. */
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

    /* position of light (x, y, z, (position of light)) */
    GLfloat lightPosition1[] = { 0.0f, 1.0f, -4.0f, 0.0f };
    GLfloat lightPosition2[] = { 0.0f, 1.0f, 4.0f, 0.0f };

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
class ConeObject
{
    GLfloat radius,height;
    GLfloat red,green,blue;
    GLfloat x,y,z;
public:
    ConeObject(GLfloat x)
    {
        radius = x;
        height = x;
    }
    void set_colour(GLfloat r,GLfloat g,GLfloat b)
    {
        red = r;
        green = g;
        blue = b;
    }
    void set_position(GLfloat x1,GLfloat z1)
    {
        x = x1;
        z = z1;
    }
};
class SphereObject
{
    GLfloat radius;
    GLfloat red,green,blue;
    GLfloat x,y,z;
public:
    void set_radius(GLfloat r)
    {
        radius = r;
    }
    void set_colour(GLfloat r,GLfloat g,GLfloat b)
    {
        red = r;
        green = g;
        blue = b;
    }
    void set_position(GLfloat x1,GLfloat y1,GLfloat z1)
    {
        x = x1;
        z = z1;
        y = y1;
    }
    GLfloat get_x()
    {
        return x;
    }
    GLfloat get_y()
    {
        return y;
    }
    GLfloat get_z()
    {
        return z;
    }
    GLfloat get_radius()
    {
        return radius;
    }
    void draw_sphere()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x,y,z);
        glColor3f(red,green,blue);
        //glScalef(1.0,1.0,1.0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);    
    //LightUp(amb_light);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1); // set light position.
        glEnable(GL_LIGHT1);                             // turn light 1 on.

        glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
        glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2); // set light position.
        glEnable(GL_LIGHT2);
        glutSolidSphere(radius,20,20);
                                     // turn light 1 on.
        glEnd();  
    }
};
int count = 3;
GLfloat ballRadius = 0.2f;
GLfloat ballX[3],ballY[3],ballZ[3],xspeed[3],yspeed[3],zspeed[3];
GLfloat ballXMax = 1, ballYMax = 1, ballXMin = -1 ,ballYMin = -1,ballZMax = -8, ballZMin = -12,r[3],zeye = 0;
GLint refreshmillis = 30;
GLfloat normal[3];
bool flag = true;
GLdouble XLeft,XRight,YTop,YBottom,ZFront = -2,ZBack = -20;
pthread_barrier_t barrier,barrier2;
pthread_barrierattr_t attr;
pthread_mutex_t mutex;
int ret = pthread_barrier_init(&barrier,&attr,3);
Ball balls[3];
SphereObject spheres[3];
//ConeObject cone1;
void initGL()
{
    glClearColor(0.0,0.0,0.0,1);
}
GLfloat sdistance(int i,int j)
{
    return((ballX[i]-ballX[j])*(ballX[i]-ballX[j]) + (ballY[i]-ballY[j])*(ballY[i]-ballY[j]) + (ballZ[i]-ballZ[j])*(ballZ[i]-ballZ[j]));
}
void ncap(int i,int j,GLfloat d)
{
    normal[0] = (ballX[i] - ballX[j])/ d;
    normal[1] = (ballY[i] - ballY[j])/ d;
    normal[2] = (ballZ[i] - ballZ[j])/ d;
    //cout<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<endl;
}
GLfloat vdot(int i)
{
    return normal[0]*xspeed[i] + normal[1]*yspeed[i] + normal[2]*zspeed[i];
}
void collide(int i,int j)
{
    while(sdistance(i,j)<ballRadius*ballRadius)
    {
        ballX[i]-=step*xspeed[i];
        ballX[j]-=step*xspeed[j];
        ballY[i]-=step*yspeed[i];
        ballY[j]-=step*yspeed[j];
        ballZ[i]-=step*zspeed[i];
        ballZ[j]-=step*zspeed[j];
    }
    ncap(i,j,sqrt(sdistance(i,j)));
    GLfloat n1 = vdot(i),n2 = vdot(j);
    //cout<<"Done"<<endl;
    xspeed[i] = xspeed[i] + (n2 - n1 )*normal[0]; 
    yspeed[i] =  yspeed[i] + (n2 - n1 )*normal[1];
    zspeed[i] =  zspeed[i] + (n2 - n1 )*normal[2];
    xspeed[j] =  xspeed[j] + (n1 - n2 )*normal[0];
    yspeed[j] =  yspeed[j] + (n1 - n2 )*normal[1];
    zspeed[j] =  zspeed[j] + (n1 - n2 )*normal[2];
   // cout<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<endl<<endl;
}
GLfloat snormal[3];
void s_object_collision(int i,int j)
{
    GLfloat x = spheres[j].get_x();
    GLfloat y = spheres[j].get_y();
    GLfloat z = spheres[j].get_z();
    GLfloat rs = spheres[j].get_radius();
    //cout<<"Oh Yeah"<<endl;
    GLfloat d = sqrt((x - ballX[i])*(x - ballX[i]) + (y - ballY[i])*(y - ballY[i]) + (z - ballZ[i])*(z - ballZ[i]));
    if(d<(rs + r[i]))
    {
        //cout<<"Yeah"<<endl;
        snormal[0] = (x-ballX[i])/d;
        snormal[1] = (y-ballY[i])/d;
        snormal[2] = (z-ballZ[i])/d;
        GLfloat dprod = xspeed[i]*snormal[0] + yspeed[i]*snormal[1] + zspeed[i]*snormal[2];
        xspeed[i] = xspeed[i] - 2*dprod*snormal[0];
        yspeed[i] = yspeed[i] - 2*dprod*snormal[1];
        zspeed[i] = zspeed[i] - 2*dprod*snormal[2];
        while((x - ballX[i])*(x - ballX[i]) + (y - ballY[i])*(y - ballY[i]) + (z - ballZ[i])*(z - ballZ[i])<(rs+r[i])*(rs + r[i]))
        {
            ballX[i] = ballX[i] +step*xspeed[i];
            ballY[i] = ballY[i] +step*yspeed[i];
            ballZ[i] = ballZ[i] +step*zspeed[i];
        }
    }
}
void DrawCube(void)
{

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,0,zeye,0,0,zeye-2,0,400,0);
    glTranslatef(0.0,0.0,0.0);
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
void display()
{	
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    DrawCube();
    for(int j=0;j<3;j++)
    {
        glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	glTranslatef(ballX[j],ballY[j],ballZ[j]);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);    
    //LightUp(amb_light);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1); // set light position.
        glEnable(GL_LIGHT1);                             // turn light 1 on.

        glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
        glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2); // set light position.
        glEnable(GL_LIGHT2);
        glColor3f(0.9, 0.3, 0.2);
        glScalef(1.0,1.0,1.0);
        glutSolidSphere(r[j],20,20);

    	glEnd();
    }
    spheres[0].draw_sphere();
    glLoadIdentity();
    gluLookAt(0,0,zeye,0,0,-20,0,1,0);
    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,YBottom,-4);
    glColor3f(0, 0, 0);
    glScalef(1.0,1.0,1.0);
    glRotatef(270.0,1.0,0,0);
    glutSolidCone(0.4,0.4,100,100);
    glEnd();*/
    glutSwapBuffers();
    if(flag) zeye-=0.05;
    else zeye+=0.05;
    if(zeye<-18)
    {
        flag = false;
    }
    else if(zeye>0)
    {
        flag = true;
    }
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
    gluPerspective(45.0,(GLdouble)width/(GLdouble)height,0,21);
    ballXMin = XLeft + ballRadius;
    ballXMax = XRight - ballRadius;
    ballYMin = YBottom + ballRadius;
    ballYMax = YTop - ballRadius;
    ballZMax = ZFront - ballRadius;
    ballZMin = ZBack + ballRadius; 
    spheres[0].set_position(0,YBottom,-5);
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
        for(int k=0;k<1;k++)
        {
            s_object_collision(i,k);
        }
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        for(int k = i+1;k<3;k++)
        {
            if(sdistance(i,k)<ballRadius*ballRadius)
            {
                collide(i,k);
            }
        }
        pthread_mutex_unlock(&mutex);
        pthread_barrier_wait(&barrier);
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
    balls[0].set_z(-5);
    balls[1].set_x(-0.3);
    balls[1].set_y(0.4);
    balls[1].set_z(-4.9);
    balls[2].set_x(0);
    balls[2].set_y(0.5);
    balls[2].set_z(-6.8);
    balls[0].set_radius(0.2);
    balls[1].set_radius(0.2);
    balls[2].set_radius(0.2);
    balls[0].set_vx(-0.03);
    balls[1].set_vx(0.03);
    balls[2].set_vx(0);
    balls[0].set_vy(-0.04);
    balls[1].set_vy(-0.04);
    balls[2].set_vy(-0.05);
    balls[0].set_vz(0.07);
    balls[1].set_vz(0.02);
    balls[2].set_vz(-0.06);
    //cone1 = new ConeObject(0.2);
    //cone1.set_colour(0.0,0.0,0.0);
    spheres[0].set_radius(0.7);
    spheres[0].set_colour(0.8,0.5,0.7);
    spheres[0].set_position(0,YBottom,-5);
    pthread_create(&id[0],NULL,bball,(void *) j);
    j = 1;
    pthread_create(&id[1],NULL,bball,(void *) j);
    j = 2;
    pthread_create(&id[2],NULL,bball,(void *) j);
    //cone1.set_position(0,-10)
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,Timer,0);
    initGL();
    glutMainLoop();
    pthread_exit(&id[0]);
    pthread_exit(&id[1]);
    return 0;
}   

