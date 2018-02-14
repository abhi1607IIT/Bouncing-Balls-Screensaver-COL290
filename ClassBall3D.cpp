#include<math.h>
#include <GL/glut.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
using namespace std;
#define pi 3.14159

class Ball{
	GLfloat  radius;
	GLfloat XCenter,YCentre,ZCentre;
	GLfloat XTranSpeed,YTranSpeed,ZTranSpeed;
	GLfloat XRotBall,YRotBall,ZRotBall;
	GLfloat XRotSpeed,YRotSpeed,ZRotSpeed;
public:
	Ball(){
		radius=0.1f;
		XCenter=(rand()/(RAND_MAX/1.5f)) - 0.75;
		YCentre=(rand()/(RAND_MAX/1.5f)) - 0.75;
		ZCentre=(rand()/(RAND_MAX/1.5f)) - 0.9;
		XRotBall=(rand()/(RAND_MAX/20.0f));
		YRotBall=(rand()/(RAND_MAX/20.0f));
		ZRotBall=(rand()/(RAND_MAX/20.0f));
		XTranSpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
		YTranSpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
		ZTranSpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
		XRotSpeed=(rand()/(RAND_MAX/2.0f))+1.0;
		YRotSpeed=(rand()/(RAND_MAX/2.0f))+1.0;
		ZRotSpeed=(rand()/(RAND_MAX/2.0f))+1.0;
	}

	GLfloat GetRadius(){
		return r;
	}
	GLfloat GetXCentre(){
		return XCenter;
	}
	void SetXCentre(GLfloat var){
		XCenter=var;
	}
	GLfloat GetYCentre(){
		return YCentre;
	}
	void SetYCentre(GLfloat var){
		YCenter=var;
	}
	GLfloat GetZCentre(){
		return ZCentre;
	}
	void SetXCentre(GLfloat var){
		XCenter=var;
	}
	GLfloat GetXTranSpeed(){
		return XTranSpeed;
	}
	void SetXTranSpeed(GLfloat var){
		XTranSpeed=var;
	}
	GLfloat GetYTranSpeed(){
		return YTranSpeed;
	}
	void SetYTranSpeed(GLfloat var){
		YTranSpeed=var;
	}
	GLfloat GetZTranSpeed(){
		return ZTranSpeed;
	}
	void SetZTranSpeed(GLfloat var){
		ZTranSpeed=var;
	}
	GLfloat GetXRotSpeed(){
		return XRotSpeed;
	}
	void SetXRotSpeed(GLfloat var){
		XRotSpeed=var;
	}
	GLfloat GetYRotSpeed(){
		return YRotSpeed;
	}
	void SetYRotSpeed(GLfloat var){
		YRotSpeed=var;
	}
	GLfloat GetZRotSpeed(){
		return ZRotSpeed;
	}
	void SetZRotSpeed(GLfloat var){
		ZRotSpeed=var;
	}
	GLfloat GetXRotBall(){
		return XRotBall;
	}
	void SetXRotBall(GLfloat var){
		XRotBall=var;
	}
	GLfloat GetYRotBall(){
		return YRotBall;
	}
	void SetYRotBall(GLfloat var){
		YRotBall=var;
	}
	GLfloat GetZRotBall(){
		return ZRotBall;
	}
	void SetXRotBall(GLfloat var){
		XRotBall=var;
	}
};