#include<iostream>
#include <stdio.h>
#include<vector>
#include <string>
#include<GL/glut.h>
#include<random>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include <cstdlib>
using namespace std;
#define pi 3.14159
#define step 0.0001
#define delta 0.005
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
const GLfloat light_ambient2[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_ambient3[] = {0.2f, 0.5f, 0.6f, 0.0f}
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 2.0f, 0.0f };
const GLfloat light_position2[]= { 0.0f,-4.0f, 0.0f, 0.0f};
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
GLuint texture;




struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    Image(const char *filename);    
    void SetSizeX(unsigned long i){sizeX = i;}
    unsigned long GetSizeX(unsigned long i){return sizeX;}
    unsigned long GetSizeY(unsigned long i){return sizeY;}
    void SetSizeY(unsigned long i){sizeY = i;}
};

Image:: Image(const char *filename) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
    printf("File Not Found : %s\n",filename);
    exit(0);
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename);
    exit(0);
    }
    sizeX = 64;
    printf("Width of %s: %lu\n", filename, sizeX);
    
    // read the height 
    if ((i = fread(&sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename);
    exit(0);
    }
    sizeY = 48;
    printf("Height of %s: %lu\n", filename, sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = sizeX * sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename);
    exit(0);
    }
    if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    exit(0);
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename);
    exit(0);
    }
    if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    exit(0);
    }
    
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    data = (char *) malloc(size);
    if (data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    exit(0);   
    }

    if ((i = fread(data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    exit(0);
    }
    

    // we're done.
} 
<<<<<<< HEAD
GLfloat ballRadius = 0.2f;
void LoadGLTextures(string path, int k) 
{ 
=======
GLfloat ballRadius = 0.18f;

// Load Bitmaps And Convert To Textures
void LoadGLTextures(string path, int k) { 
    // Load Texture
>>>>>>> 65bc1899bf4843a67c10e8bc2fb7f08299554403
    Image *image = new Image(path.c_str());
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    free(image);
}
uniform_real_distribution <float> lrand(-1.0,1.0);
default_random_engine generator;
int bselected = -1;
class Balls
{
    GLint count ;
    vector<GLfloat> ballX;
    vector<GLfloat> ballY;
    vector<GLfloat> ballZ;
    vector<GLfloat> vx,vy,vz;
    vector<GLfloat> r;
    vector<GLfloat> g;
    vector<GLfloat> b;
public:
    Balls()
    {
        count = 0;
    }
    void makeBall(GLfloat xeye)
    {
        count++;
        ballX.push_back(xeye + lrand(generator));
        ballY.push_back(lrand(generator));
        ballZ.push_back(-4 + 2 * lrand(generator));
        vx.push_back(lrand(generator)/20);
        vy.push_back(lrand(generator)/20);
        vz.push_back(lrand(generator)/20);
        r.push_back(0.5 + 2*lrand(generator)/5);
        b.push_back(0.5 + 2*lrand(generator)/5);
        g.push_back(0.5 + 2*lrand(generator)/5);
    }
    GLfloat get_x(GLint i)
    {
        return ballX[i];
    }
    GLfloat get_y(GLint i)
    {
        return ballY[i];
    }
    GLfloat get_z(GLint i)
    {
        return ballZ[i];
    }
    GLfloat get_vx(GLint i)
    {
        return vx[i];
    }
    GLfloat get_vy(GLint i)
    {
        return vy[i];
    }
    GLfloat get_vz(GLint i)
    {
        return vz[i];
    }
    void set_x(GLint i,GLfloat xp)
    {
        ballX[i] = xp;
    }
    void set_y(GLint i,GLfloat yp)
    {
        ballY[i] = yp;
    }
    void set_z(GLint i,GLfloat zp)
    {
        ballZ[i] = zp;
    }
    void set_vx(GLint i,GLfloat xv)
    {
        vx[i] = xv;
    }
    void set_vy(GLint i,GLfloat yv)
    {
        vy[i] = yv;
    }
    void set_vz(GLint i,GLfloat zv)
    {
        vz[i] = zv;
    }
    GLfloat get_r(GLint i)
    {
        return r[i];
    }
    GLfloat get_g(GLint i)
    {
        return g[i];
    }
    GLfloat get_b(GLint i)
    {
        return b[i];
    }
    GLint get_count()
    {
        return count;
    }
    void DrawBall(int j,GLfloat xeye)
    {
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glLoadIdentity();
        gluLookAt(xeye,0,0,xeye,0,-2,0,400,0);
        glTranslatef(ballX[j],ballY[j],ballZ[j]);
        if(j==bselected)
        {
            glColor4f(1.0,1.0,1.0,1);
        }
        else glColor4f(r[j],g[j],b[j],1); 
        glutSolidSphere(ballRadius,30,30);
        
        glDisable(GL_LIGHT0);
        glFlush();
        glEnd();
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
    void draw_sphere(GLfloat xeye)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xeye,0,0,xeye,0,-2,0,1,0);
        glTranslatef(x,y,z);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient3);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glColor4f(red,green,blue,1);
        glutSolidSphere(radius,30,30);
        glFlush();
        glDisable(GL_LIGHT0);
        glEnd();  
    }
};
Balls Ball;
int count ;
GLfloat ballXMax = 1, ballYMax = 1, ballXMin = -1 ,ballYMin = -1,ballZMax = -8, ballZMin = -12,xeye = 0,aspect = 1,vxmax = 0.1,vymax = 0.1,vzmax = 0.1;
GLint refreshmillis = 30;
GLfloat normal[3];
bool flag = true,play = true;
GLdouble XLeft,XRight,YTop,YBottom,ZFront = -2,ZBack = -6;
pthread_barrier_t barrier,barrier2;
pthread_mutex_t mutex;
pthread_barrierattr_t attr;
SphereObject spheres[12];

void initGL()
{   
    LoadGLTextures("walls2.bmp",0);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);              
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); 
    glShadeModel(GL_SMOOTH);
}
GLfloat sdistance(int i,int j)
{
    return((Ball.get_x(i)-Ball.get_x(j))*(Ball.get_x(i)-Ball.get_x(j)) + (Ball.get_y(i)-Ball.get_y(j))*(Ball.get_y(i)-Ball.get_y(j)) + (Ball.get_z(i)-Ball.get_z(j))*(Ball.get_z(i)-Ball.get_z(j)));
}
void ncap(int i,int j,GLfloat d)
{
    normal[0] = (Ball.get_x(i) - Ball.get_x(j))/ d;
    normal[1] = (Ball.get_y(i) - Ball.get_y(j))/ d;
    normal[2] = (Ball.get_z(i) - Ball.get_z(j))/ d;
    //cout<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<endl;
}
GLfloat vdot(int i)
{
    return normal[0]*Ball.get_vx(i) + normal[1]*Ball.get_vy(i) + normal[2]*Ball.get_vz(i);
}
void collide(int i,int j)
{
    while(sdistance(i,j)<ballRadius*ballRadius)
    {
        Ball.set_x(i,Ball.get_x(i)-step*Ball.get_vx(i));
        Ball.set_x(j,Ball.get_x(j)-step*Ball.get_vx(j));
        Ball.set_y(i,Ball.get_y(i)-step*Ball.get_vy(i));
        Ball.set_y(j,Ball.get_y(j)-step*Ball.get_vy(j));
        Ball.set_z(i,Ball.get_z(i)-step*Ball.get_vz(i));
        Ball.set_z(j,Ball.get_z(j)-step*Ball.get_vz(j));
    }
    ncap(i,j,sqrt(sdistance(i,j)));
    GLfloat n1 = vdot(i),n2 = vdot(j);
    Ball.set_vx(i,Ball.get_vx(i) + (n2 - n1 )*normal[0]);
    Ball.set_vy(i,Ball.get_vy(i) + (n2 - n1 )*normal[1]);
    Ball.set_vz(i,Ball.get_vz(i) + (n2 - n1 )*normal[2]);
    Ball.set_vx(j,Ball.get_vx(j) + (n1 - n2 )*normal[0]);
    Ball.set_vy(j,Ball.get_vy(j) + (n1 - n2 )*normal[1]);
    Ball.set_vz(j,Ball.get_vz(j) + (n1 - n2 )*normal[2]);
}
GLfloat snormal[3];
void s_object_collision(int i,int j)
{
    GLfloat x = spheres[j].get_x();
    GLfloat y = spheres[j].get_y();
    GLfloat z = spheres[j].get_z();
    GLfloat rs = spheres[j].get_radius();
    //cout<<"Oh Yeah"<<endl;
    GLfloat d = sqrt((x - Ball.get_x(i))*(x - Ball.get_x(i)) + (y - Ball.get_y(i))*(y - Ball.get_y(i)) + (z - Ball.get_z(i))*(z - Ball.get_z(i)));
    if(d<(rs + ballRadius))
    {
        //cout<<"Yeah"<<endl;
        snormal[0] = (x-Ball.get_x(i))/d;
        snormal[1] = (y-Ball.get_y(i))/d;
        snormal[2] = (z-Ball.get_z(i))/d;
        GLfloat dprod = Ball.get_vx(i)*snormal[0] + Ball.get_vy(i)*snormal[1] + Ball.get_vz(i)*snormal[2];
        Ball.set_vx(i,Ball.get_vx(i) - 2*dprod*snormal[0]);
        Ball.set_vy(i,Ball.get_vy(i) - 2*dprod*snormal[1]);
        Ball.set_vz(i,Ball.get_vz(i) - 2*dprod*snormal[2]);
        while((x - Ball.get_x(i))*(x - Ball.get_x(i)) + (y - Ball.get_y(i))*(y - Ball.get_y(i)) + (z - Ball.get_z(i))*(z - Ball.get_z(i))<(rs+ballRadius)*(rs + ballRadius))
        {
            Ball.set_x(i,Ball.get_x(i) +step*Ball.get_vx(i));
            Ball.set_y(i,Ball.get_y(i) +step*Ball.get_vy(i));
            Ball.set_z(i,Ball.get_z(i) +step*Ball.get_vz(i));
        }
    }
}
void DrawCube(void)
{
    //glDisable(GL_DEPTH_TEST);                   //sachin
    glBlendFunc(GL_SRC_ALPHA,GL_ONE); //sachin                   // Set The Blending Function For Translucency        
    glBindTexture(GL_TEXTURE_2D, texture); 
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xeye,0,0,xeye,0,-2,0,400,0);
    glTranslatef(0.0,0.0,0.0);
    glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient2);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position2);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor4f(0.0f,1.0f,0.0f,1);    // Color Blue
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( XRight,YTop,ZBack);    // Top Right Of The Quad (Top)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(XLeft,YTop,ZBack);    // Top Left Of The Quad (Top)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(XLeft,YTop,ZFront);    // Bottom Left Of The Quad (Top)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( XRight,YTop,ZFront);    // Bottom Right Of The Quad (Top)
    glColor4f(1.0f,0.5f,0.0f,1);    // Color Orange
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(XRight,YBottom,ZFront);    // Top Right Of The Quad (Bottom)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(XLeft,YBottom,ZFront);    // Top Left Of The Quad (Bottom)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(XLeft,YBottom,ZBack);    // Bottom Left Of The Quad (Bottom)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(XRight,YBottom,ZBack);    // Bottom Right Of The Quad (Bottom)
    glColor4f(1.0f,1.0f,0.0f,1);    // Color Yellow
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(XRight,YBottom,ZBack);    // Top Right Of The Quad (Back)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(XLeft,YBottom,ZBack);    // Top Left Of The Quad (Back)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(XLeft,YTop,ZBack);    // Bottom Left Of The Quad (Back)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(XRight,YTop,ZBack);    // Bottom Right Of The Quad (Back)
    glColor4f(0.0f,0.0f,1.0f,1);    // Color Blue
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(XLeft,YTop,ZFront);    // Top Right Of The Quad (Left)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(XLeft,YTop,ZBack);    // Top Left Of The Quad (Left)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(XLeft,YBottom,ZBack);    // Bottom Left Of The Quad (Left)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(XLeft,YBottom,ZFront);    // Bottom Right Of The Quad (Left)
    glColor4f(1.0f,0.0f,1.0f,1);    // Color Violet
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(XRight,YTop,ZBack);    // Top Right Of The Quad (Right)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(XRight,YTop,ZFront);    // Top Left Of The Quad (Right)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(XRight,YBottom,ZFront);    // Bottom Left Of The Quad (Right)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(XRight,YBottom,ZBack);    // Bottom Right Of The Quad (Right)
    glDisable(GL_LIGHT0);
  glEnd();            // End Drawing The Cube
  
//glFlush();
  
}
void display()
{   
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDepthRange(0.0f, 1.0f);
    if(aspect>1)
    {
        XLeft = -1.0 * aspect + xeye;
        XRight = 1.0 * aspect + xeye;
    }
    else
    {
        XLeft = -1.0 + xeye;
        XRight = 1.0 + xeye;
    }
    ballXMin = XLeft + ballRadius;
    ballXMax = XRight - ballRadius;
    DrawCube();
    glDisable(GL_TEXTURE_2D);
    for(int j=0;j<count;j++)
    {
        Ball.DrawBall(j,xeye);
    }
    for(int j=0;j<8;j++) spheres[j].draw_sphere(xeye);
    glutSwapBuffers();
    if(play)
    {
        if(flag) xeye+=0.01;
        else xeye -=0.01;
    }
    if(xeye<0)
    {
        flag = true;
    }
    else if(xeye>10)
    {
        flag = false;
    }
}
void reshape(GLsizei width,GLsizei height)
{
    if(height==0) height = 1;
    aspect = (GLfloat)width/(GLfloat) height;

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
    gluPerspective(45.0,(GLdouble)width/(GLdouble)height,1,8);
    ballXMin = XLeft + ballRadius;
    ballXMax = XRight - ballRadius;
    ballYMin = YBottom + ballRadius;
    ballYMax = YTop - ballRadius;
    ballZMax = ZFront - ballRadius;
    ballZMin = ZBack + ballRadius; 
    spheres[0].set_position(1,YBottom,-4);
    spheres[1].set_position(2.3,YBottom,-4.8);
    spheres[2].set_position(2.6,YBottom,-6);
    spheres[3].set_position(3.7,YBottom,-3);
    spheres[4].set_position(5.6,YBottom,-5.5);
    spheres[5].set_position(6.2,YBottom,-4.7);
    spheres[6].set_position(8,YBottom,-4.2);
    spheres[7].set_position(8.9,YBottom,-5);
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
    while(true)
    {   
        if(play)
        {
            Ball.set_x(i,Ball.get_x(i)+Ball.get_vx(i));
            Ball.set_y(i,Ball.get_y(i)+Ball.get_vy(i));
            Ball.set_z(i,Ball.get_z(i)+Ball.get_vz(i));
        }
        if(Ball.get_x(i)>ballXMax)
        {
            Ball.set_x(i,ballXMax) ;
            Ball.set_vx(i,-1*Ball.get_vx(i));
        }
        else if(Ball.get_x(i)<ballXMin)
        {
            Ball.set_x(i,ballXMin);
            Ball.set_vx(i,-1*Ball.get_vx(i));
        }
        if(Ball.get_y(i)>ballYMax)
        {
            Ball.set_y(i,ballYMax);
            Ball.set_vy(i,-1*Ball.get_vy(i));
        }
        else if(Ball.get_y(i)<ballYMin)
        {
            Ball.set_y(i,ballYMin);
            Ball.set_vy(i,-1*Ball.get_vy(i));
        }
        if(Ball.get_z(i)>ballZMax)
        {
            Ball.set_z(i,ballZMax);
            Ball.set_vz(i,-1*Ball.get_vz(i));
        }
        else if(Ball.get_z(i)<ballZMin)
        {
            Ball.set_z(i,ballZMin);
            Ball.set_vz(i,-Ball.get_vz(i));
        }
        for(int k=0;k<8;k++)
        {
            s_object_collision(i,k);
        }
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        for(int k = i+1;k<count;k++)
        {
            if(sdistance(i,k)<ballRadius*ballRadius)
            {
                collide(i,k);
            }
        }
        pthread_mutex_unlock(&mutex);
        //pthread_barrier_wait(&barrier);
        usleep(20000);
    }
    
}
void specialKeys( int key, int x, int y ) 
{
    if (key == GLUT_KEY_RIGHT)
    {
        if(bselected<0) return;
        else
        {
            if(Ball.get_vx(bselected)<0&&Ball.get_vx(bselected)>-vxmax)
            {
                Ball.set_vx(bselected,Ball.get_vx(bselected)-delta);
            }
            else if(Ball.get_vx(bselected)>0&&Ball.get_vx(bselected)<vxmax)
            {
                Ball.set_vx(bselected,Ball.get_vx(bselected)+delta);
            }
            if(Ball.get_vy(bselected)<0&&Ball.get_vy(bselected)>-vymax)
            {
                Ball.set_vy(bselected,Ball.get_vy(bselected)-delta);
            }
            else if(Ball.get_vy(bselected)>0&&Ball.get_vy(bselected)<vymax)
            {
                Ball.set_vy(bselected,Ball.get_vy(bselected)+delta);
            }
            if(Ball.get_vz(bselected)<0&&Ball.get_vz(bselected)>-vzmax)
            {
                Ball.set_vz(bselected,Ball.get_vz(bselected)-delta);
            }
            else if(Ball.get_vz(bselected)>0&&Ball.get_vz(bselected)<vzmax)
            {
                Ball.set_vz(bselected,Ball.get_vz(bselected)+delta);
            }
        }
    }
    else if (key == GLUT_KEY_LEFT)
    { 
        if(bselected<0) return;
        else
        {
            if(Ball.get_vx(bselected)<0&&Ball.get_vx(bselected)>-vxmax)
            {
                Ball.set_vx(bselected,Ball.get_vx(bselected)+delta);
            }
            else if(Ball.get_vx(bselected)>0&&Ball.get_vx(bselected)<vxmax)
            {
                Ball.set_vx(bselected,Ball.get_vx(bselected)-delta);
            }
            if(Ball.get_vy(bselected)<0&&Ball.get_vy(bselected)>-vymax)
            {
                Ball.set_vy(bselected,Ball.get_vy(bselected)+delta);
            }
            else if(Ball.get_vy(bselected)>0&&Ball.get_vy(bselected)<vymax)
            {
                Ball.set_vy(bselected,Ball.get_vy(bselected)-delta);
            }
            if(Ball.get_vz(bselected)<0&&Ball.get_vz(bselected)>-vzmax)
            {
                Ball.set_vz(bselected,Ball.get_vz(bselected)+delta);
            }
            else if(Ball.get_vz(bselected)>0&&Ball.get_vz(bselected)<vzmax)
            {
                Ball.set_vz(bselected,Ball.get_vz(bselected)-delta);
            }
        }
    }
    else if(key== GLUT_KEY_UP)
    {
        bselected++;
        if(bselected == count) bselected = 0;
       usleep(1000);
   }
    else if(key== GLUT_KEY_DOWN)
    {
        bselected--;
        if(bselected <0) bselected = count - 1;
        usleep(1000);
    }
 

  glutPostRedisplay();
 
}
int ret;
pthread_t id;
void normalKeys(unsigned char key, int x, int y) {
    if (key == ' ')
    {
        play = !play;
        usleep(1000);
    }
    if(key=='?'){
        bselected=-1;
    } 
    /*else if(key=='+')
    {
        //pthread_barrier_destroy(&barrier);
        count++;
        ret = pthread_barrier_init(&barrier,&attr,count);
        Ball.makeBall(xeye);
        cout<<Ball.get_vx(count-1)<<endl;
        pthread_create(&id,NULL,bball,(void *) count-1);
    }*/
}
int main(int argc,char** argv)
{
    time_t seconds;
    time(&seconds);
    glutInit(&argc,argv);
    count = 10;
    if(count%2==0)
    {
        ret = pthread_barrier_init(&barrier,&attr,count);
        ret = pthread_barrier_init(&barrier,&attr,count-1);
    }
    else
    {
        ret = pthread_barrier_init(&barrier,&attr,count-1);
        ret = pthread_barrier_init(&barrier,&attr,count);
    }
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(windowWidth , windowHeight);
    glutInitWindowPosition(windowPosx,windowPosy);
    glutCreateWindow("Bouncing Ball");
<<<<<<< HEAD
    for(int i=0;i<count;i++)
    {
        Ball.makeBall(xeye);
        pthread_create(&id,NULL,bball,(void *) i);
    }
    for(int i=0;i<10;i++)
=======
    pthread_t id[count];
    int j = 0;
    for(int i=0;i<5;i++)
>>>>>>> 65bc1899bf4843a67c10e8bc2fb7f08299554403
    {
        cout<<lrand(generator)<<endl;
    }
    spheres[0].set_radius(0.4);
    spheres[0].set_colour(0.8,0.5,0.7);
    spheres[0].set_position(1,YBottom,-4);
    spheres[1].set_radius(0.3);
    spheres[1].set_colour(0.4,0.2,0.8);
    spheres[1].set_position(2.3,YBottom,-4.8);
    spheres[2].set_radius(0.268);
    spheres[2].set_colour(0.6,0.1,0.9);
    spheres[2].set_position(2.6,YBottom,-6);
    spheres[3].set_radius(0.5);
    spheres[3].set_colour(0.2,0.7,0.5);
    spheres[3].set_position(3.7,YBottom,-3);
    spheres[4].set_radius(0.7);
    spheres[4].set_colour(0.1,0.7,0.7);
    spheres[4].set_position(5.6,YBottom,-5.5);
    spheres[5].set_radius(0.35);
    spheres[5].set_colour(0.8,0.7,0.3);
    spheres[5].set_position(6.2,YBottom,-4.7);
    spheres[6].set_radius(0.6);
    spheres[6].set_colour(0.2,0.1,0.3);
    spheres[6].set_position(8,YBottom,-4.2);
    spheres[7].set_radius(0.5);
    spheres[7].set_colour(0.3,0.9,0.5);
    spheres[7].set_position(8.9,YBottom,-5);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,Timer,0);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normalKeys);
    initGL();
    glutMainLoop();
    pthread_exit(&id);
    return 0;
} 