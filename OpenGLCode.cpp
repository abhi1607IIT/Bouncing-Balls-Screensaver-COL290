#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;
#define pi 3.14159

GLfloat ballRadius = 0.1f;
double ballX[2] = {0.3f,-0.3f};
double ballY[2] = {0.0f,0.0f};
GLfloat ballXMax = 1, ballYMax = 1, ballXMin = -1 ,ballYMin = -1;
GLfloat xspeed[2] = {0.01f,-0.01f};
GLfloat yspeed[2] = {0.01f,0.01f};
GLint refreshmillis = 30;
GLdouble XLeft,XRight,YTop,YBottom;
pthread_barrier_t barrier;
pthread_barrierattr_t attr;
pthread_mutex_t mutex;
int ret = pthread_barrier_init(&barrier,&attr,2);
void initGL()
{
    glClearColor(0.0,0.0,0.0,1);
}
void display()
{	
    glClear(GL_COLOR_BUFFER_BIT);
    for(int j=0;j<2;j++)
    {
    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	//glTranslatef(ballX[j],ballY[j],0.0f);
    	glBegin(GL_TRIANGLE_FAN);
    	glColor3f(0.0f,1.0f,0.0f);
    	glVertex2f(ballX[j],ballY[j]);
    	GLint numSegments =  60;
    	GLfloat angle;
    	for(int i =0;i<=numSegments;i++)
    	{
        	angle = i * 2.0f * pi / numSegments;
        	glVertex2f(ballX[j]+cos(angle)*ballRadius,ballY[j]+sin(angle) * ballRadius); 
    	}
       // cout<<ballX[j]<<" "<<ballY[j]<<endl;
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
    gluOrtho2D(XLeft,XRight,YBottom,YTop);
    ballXMin = XLeft + ballRadius;
    ballXMax = XRight - ballRadius;
    ballYMin = YBottom + ballRadius;
    ballYMax = YTop - ballRadius;
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
	cout<<i<<endl;
	while(true)
	{	ballX[i]+=xspeed[i];
    	ballY[i]+=yspeed[i];
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
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        for(int k = i+1;k<2;k++)
        {
            if(abs(ballX[i]-ballX[k])<2*ballRadius)
            {
                //usleep(1000000);
                //cout<<xspeed[i]<<" "<<xspeed[k]<<endl;
                GLfloat l = xspeed[i];
                xspeed[i] = xspeed[k];
                xspeed[k] = l;
               /* while(abs(ballX[i]-ballX[k])<2*ballRadius)
                {
                    if(ballX[i]<ballX[k])
                    {
                        ballX[i]-=0.001f;
                        ballX[k]+=0.001f;
                    }
                    else
                    {
                        ballX[i]+=0.0001f;
                        ballX[i]-=0.0001f;
                    }
                }*/
                //cout<<xspeed[i]<<" "<<xspeed[k]<<" "<<l<<endl;
                //cout<<ballX[i]<<" "<<ballX[poiu]<<"Here the change happens"<<endl;
                /*j = (ballX[i]+ballX[poiu])/2;
                ballX[i] = j - ballRadius;
                ballX[poiu] = j + ballRadius;*/
            }
            //cout<<i<<endl;
            //pthread_barrier_destroy(&barrier);
            //cout<<"It unlocked"<<endl;
        }
        pthread_mutex_unlock(&mutex);
        usleep(10000);
    }
    
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth , windowHeight);
    glutInitWindowPosition(windowPosx,windowPosy);
    glutCreateWindow("Bouncing Ball");
    pthread_t id[2];
    int j = 0;
    pthread_create(&id[0],NULL,bball,(void *) j);
    j = 1;
    //xspeed = -xspeed;
    pthread_create(&id[1],NULL,bball,(void *) j);
    //j = 2;
    //pthread_create(&id,NULL,bball,(void *) j);
    //cout<<j<<endl;
    //cout<<ballX[0]<<" "<<ballX[1]<<" "<<ballY[0]<<" "<<ballY[1]<<endl;
    //cout<<ballXMax<<" "<<ballYMax<<endl;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,Timer,0);
    initGL();
    glutMainLoop();
    pthread_exit(&id[0]);
    pthread_exit(&id[1]);
    return 0;
}   