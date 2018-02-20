#include <GL/glut.h>
#include <iostream>
#include <random>
using namespace std;

GLfloat ballRadius = 0.18f;
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
    void makeBall()
    {
        count++;
        ballX.push_back(lrand(generator));
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
            glColor4f(0.9,0.9,0.9,1);
        }
        else glColor4f(r[j],g[j],b[j],1); 
        glutSolidSphere(ballRadius,30,30);
        
        glDisable(GL_LIGHT0);
        glFlush();
        glEnd();
    }
};