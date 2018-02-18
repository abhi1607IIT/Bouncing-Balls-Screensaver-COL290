#include<iostream>
#include <stdio.h>
#include<vector>
#include <string>
#include<GL/glut.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include <cstdlib>

using namespace std;
#define pi 3.14159
#define step 0.0005
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.4f, 0.3f, -5.0f, 0.0f };
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


// Load Bitmaps And Convert To Textures
void LoadGLTextures(string path, int k) { 
    // Load Texture
    Image *image = new Image(path.c_str());
    
    // // allocate space for texture
    // image = (Image *) malloc(sizeof(Image));
    // if (image == NULL) {
    // printf("Error allocating space for image");
    // exit(0);
    // }
    // if (!ImageLoad(path.c_str(), image)) {
    // exit(1);
    // }        
    
    // Create Texture   
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    free(image);
};

class Ball
{
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
    void draw_sphere(GLfloat xeye)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xeye,0,0,xeye,0,-2,0,1,0);
        glTranslatef(x,y,z);
        glColor4f(red,green,blue,1);
        glutSolidSphere(radius,30,30);
        glFlush();
        glEnd();  
    }
};
int count = 5;
GLfloat ballRadius = 0.3f;
GLfloat ballX[10],ballY[5],ballZ[5],xspeed[5],yspeed[5],zspeed[5];
GLfloat ballXMax = 1, ballYMax = 1, ballXMin = -1 ,ballYMin = -1,ballZMax = -8, ballZMin = -12,r[3],xeye = 0,aspect = 1;
GLint refreshmillis = 30;
GLfloat normal[3];
bool flag = true;
GLdouble XLeft,XRight,YTop,YBottom,ZFront = -2,ZBack = -6;
pthread_barrier_t barrier,barrier2;
pthread_barrierattr_t attr;
pthread_mutex_t mutex;
int ret = pthread_barrier_init(&barrier,&attr,5);
Ball balls[5];
SphereObject spheres[12];

void initGL()
{   
    LoadGLTextures("walls2.bmp",0);
 
    glEnable(GL_TEXTURE_2D);

    // This Will Clear The Background Color To Black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);              // Enables Clearing Of The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND); //sachin
    //glDepthFunc(GL_LESS);           // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);        // Enables Depth Testing
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    

    glShadeModel(GL_SMOOTH);
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
    if(d<(rs + ballRadius))
    {
        //cout<<"Yeah"<<endl;
        snormal[0] = (x-ballX[i])/d;
        snormal[1] = (y-ballY[i])/d;
        snormal[2] = (z-ballZ[i])/d;
        GLfloat dprod = xspeed[i]*snormal[0] + yspeed[i]*snormal[1] + zspeed[i]*snormal[2];
        xspeed[i] = xspeed[i] - 2*dprod*snormal[0];
        yspeed[i] = yspeed[i] - 2*dprod*snormal[1];
        zspeed[i] = zspeed[i] - 2*dprod*snormal[2];
        while((x - ballX[i])*(x - ballX[i]) + (y - ballY[i])*(y - ballY[i]) + (z - ballZ[i])*(z - ballZ[i])<(rs+ballRadius)*(rs + ballRadius))
        {
            ballX[i] = ballX[i] +step*xspeed[i];
            ballY[i] = ballY[i] +step*yspeed[i];
            ballZ[i] = ballZ[i] +step*zspeed[i];
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
    for(int j=0;j<5;j++)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xeye,0,0,xeye,0,-2,0,1,0);
        glTranslatef(ballX[j],ballY[j],ballZ[j]);
        glColor4f(0.9, 0.3, 0.2,1);
        glScalef(1.0,1.0,1.0);
        glutSolidSphere(ballRadius,30,30);
        glFlush();
        glEnd();
    }
    for(int j=0;j<8;j++) spheres[j].draw_sphere(xeye);
    glutSwapBuffers();
    if(flag) xeye+=0.01;
    else xeye -=0.01;
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
    ballX[i] = balls[i].get_x();
    ballY[i] = balls[i].get_y();
    ballZ[i] = balls[i].get_z();
    xspeed[i] = balls[i].get_vx();
    yspeed[i] = balls[i].get_vy();
    zspeed[i] = balls[i].get_vz();
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
        for(int k=0;k<8;k++)
        {
            s_object_collision(i,k);
        }
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        for(int k = i+1;k<5;k++)
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
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(windowWidth , windowHeight);
    glutInitWindowPosition(windowPosx,windowPosy);
    glutCreateWindow("Bouncing Ball");
    pthread_t id[5];
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
    balls[3].set_x(0.9);
    balls[3].set_y(0.5);
    balls[3].set_z(-3);
    balls[4].set_x(-0.3);
    balls[3].set_y(-0.2);
    balls[3].set_z(-5.5);
    balls[0].set_vx(-0.03);
    balls[1].set_vx(0.03);
    balls[2].set_vx(0.06);
    balls[3].set_vx(-0.04);
    balls[4].set_vx(0.03);
    balls[0].set_vy(-0.04);
    balls[1].set_vy(-0.04);
    balls[2].set_vy(-0.05);
    balls[3].set_vy(0.03);
    balls[4].set_vy(-0.03);
    balls[0].set_vz(0.07);
    balls[1].set_vz(0.02);
    balls[2].set_vz(-0.06);
    balls[3].set_vz(0.06);
    balls[4].set_vz(-0.02);
    //cone1 = new ConeObject(0.2);
    //cone1.set_colour(0.0,0.0,0.0);
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
    pthread_create(&id[0],NULL,bball,(void *) j);
    j = 1;
    pthread_create(&id[1],NULL,bball,(void *) j);
    j = 2;
    pthread_create(&id[2],NULL,bball,(void *) j);
    j = 3;
    pthread_create(&id[3],NULL,bball,(void *) j);
    j = 4;
    pthread_create(&id[4],NULL,bball,(void *) j);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,Timer,0);
    initGL();
    glutMainLoop();
    pthread_exit(&id[0]);
    pthread_exit(&id[1]);
    return 0;
} 