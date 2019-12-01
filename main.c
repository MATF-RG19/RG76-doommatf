#include <stdlib.h>
#include <GL/glut.h>

static int window_width, window_height;
static void on_display(void);
static void on_reshape();
static void on_keyboard(char key, int x, int y);
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glClearColor(0.75, 0.75, 0.75, 0);

    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
 return 0;   
}
static void on_reshape(int width, int height){
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)width/height, 10, 10);
}


//Funkcija Koja Isrctava Scenu
static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(-10, 10.0, 10.0, 0);
    
    
    
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 1);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

     glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.3);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.8);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();
    

  glFlush();
  glutSwapBuffers();
}

