//g++ machThree.cpp -o OpenGLExample -lglut -lGL -lGLEW -lGLU
//./OpenGLExample

#include<GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4

GLfloat cameraZ=10;
GLfloat rotate=0.0;
GLfloat xRotation=0;
GLfloat yRotation=1.0;
float angle = 0.0, deltaAngle=2.0;
//float day1=0.0, deltaDay1=1.0.0;
float year1=0.0, deltaYear1=1.0;
float year2=0.0, deltaYear2=1.0;
float year3=0.0, deltaYear3=1.0;
float year4=0.0, deltaYear4=1.0;
float red=1.0, blue=1.0, green=1.0;
float width,height;
int specialKey;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short

	// (you cant make a window of zero width).

	if(h == 0)

		h = 1;

	// we're storing these values for latter use in the 

	// mouse motion functions
	width = w;

	height = h;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set the viewport to be the entire window

    glViewport(0, 0, w, h);

	// Set the correct perspective.

	gluPerspective(45,ratio,1,1000);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}

void mySolidSphere(GLfloat radius, int slices, int stacks)
{
glPushMatrix();
glRotatef(90, 1.0, 0.0, 0.0);
glutWireSphere(radius, slices, stacks);
//glutSolidSphere(radius, slices, stacks);
glPopMatrix();
}

//angle describes the camera's rotation relative to the world.
//angle2 describes the rotation of planet 2 and so forth.

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();	

	gluLookAt(	0.0, 0.0, cameraZ,
			0.0, 0.0,  0.0,
			0.0f, 1.0f,  0.0f);
	glPushMatrix();

	glRotatef(angle,xRotation,yRotation,0.0);

	glColor3f(red,green,blue);
	
	mySolidSphere(7.0, 20, 20);

	glPushMatrix();
	
	glRotatef(year1, 0.0, 1.0, 0.0);	

	glTranslatef(10.0, 0.0, 0.0);

	glColor3f(red, green, 1.0);

	mySolidSphere(1.0, 20, 20);
	
	glPushMatrix(); 

	glRotatef(year2, 1.0, 0.0, 0.0);

	glTranslatef(0.0, 10.0, 0.0);

	glColor3f(1.0, green, blue);

	mySolidSphere(1.0, 20, 20);

	glPushMatrix();
	
	glRotatef(year3, 0.0, 0.0, 1.0);
	
	glTranslatef(10.0, 10.0, 0.0);
	
	glColor3f(red, 1.0, blue);
	
	mySolidSphere(1.0, 20, 20);

/*	glPushMatrix();

	glRotatef(year4, -1.0, -1.0, 0.0);

	glTranslatef(-5.0, 10.0, 0.0);

	glColor3f(red, 1.0, 1.0);
*/
	glPopMatrix();
	
	year1+=deltaYear1;

	year2+=deltaYear2;

	year3+=deltaYear3;

	year4+=deltaYear4;
	
//	day1+=deltaDay1;

	glutSwapBuffers();

}

void processMouse(int button, int state, int x, int y) {
        if ((button==4)||(button==5))
        {
        if (state==GLUT_UP)
        return;
        cameraZ=cameraZ+1.0;
        }
        else
        {
        cameraZ=cameraZ-1.0;
        }
      glLoadIdentity();
      glutPostRedisplay();

}

void processMouseActiveMotion(int x, int y) {

	// the ALT key was used in the previous function

	if (specialKey != GLUT_ACTIVE_ALT) {

		// setting red to be relative to the mouse 

		// position inside the window

		if (x < 0)

			red = 0.0;

		else if (x > width)

			red = 1.0;

		else

			red = ((float) x)/height;

		// setting green to be relative to the mouse 

		// position inside the window

		if (y < 0)

			green = 0.0;

		else if (y > width)

			green = 1.0;

		else

			green = ((float) y)/height;

		// removing blue from the color.

		blue = 0.0;

	}
}

void processSpecialKeys(int key, int xx, int yy) {

        float fraction = 0.1f;

        switch (key) {
                case GLUT_KEY_LEFT :
                        angle -= 1.0;
			
			yRotation=1.0;
			
			xRotation=0.0;
                        
			break;
                case GLUT_KEY_RIGHT :
                        angle += 1.0;

			yRotation=1.0;

			xRotation=0.0;;

                        break;
                case GLUT_KEY_UP :
                        angle -= 1.0f;
			
			xRotation=1.0;

			yRotation=0.0;
			
			break;
                case GLUT_KEY_DOWN :
                        angle += 1.0;
			
			xRotation=1.0;	
			
			yRotation=0.0;

			break;
        }

//      glLoadIdentity();
//      glutPostRedisplay();
glutSwapBuffers();
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(100,100);

	glutInitWindowSize(1000,1000);

	glutCreateWindow("machThree");

        glutSpecialFunc(processSpecialKeys);

	glutMouseFunc(processMouse);	

	glutDisplayFunc(renderScene);

	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMotionFunc(processMouseActiveMotion);

	glutMainLoop();
}
