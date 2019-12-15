#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "image.h"
#include "main.h"
#include "light.h"

#define FILENAME0 "tree.bmp"
#define FILENAME1 "grass.bmp"
#define FILENAME2 "sky.bmp"

#define pi 3.14159265358979323846
static GLuint names[3];

static int window_width, window_height;
static void on_display(void);
static void on_reshape();
static void on_keyboard(unsigned char key, int x, int y);
static void specialKey(int key, int x, int y);
static void initialize(void);
static void on_mouse_motion(int x, int y);
float angle = 0.0;
float lx = 0.0f;
float lz = -1.0f;
float ly = 0;
float x = 0.0f, z=5.0f;
double posx= 8,posy= 1,posz=7,
lookx=0,looky=0,lookz=0,upx=0,upy=0,upz=-1;
double sensitivity = 0.4;

int main(int argc, char **argv)
{
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("DoomMatf");
 
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(on_mouse_motion);
    initialize();
     
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
 return 0;   
}
static void on_reshape(int width, int height){
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)width/height, 0.1, 100);
  //glFrustum(-1, 1, -1, 1, 1, 10);
}
static void initialize(void){
  Image *image;

  glClearColor(0, 0, 0, 0);

  glEnable(GL_DEPTH_TEST);


  glEnable(GL_NORMALIZE);
  //glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
image = image_init(0, 0);

image_read(image, FILENAME0);

glGenTextures(3, names);

 glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  /******/

  image_read(image, FILENAME1);
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels); 


  /*****/

   image_read(image, FILENAME2);
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);  

 glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}
static void on_keyboard(unsigned char key, int xx, int yy){
  float fraction = 0.1f;
 // x+lx, 1.0f, z+lz,
  switch (key)
  {
    case 27:
    exit(0);
    break;
  case 'd':
    angle += 0.06f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case 'a':
      angle -= 0.06f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case 'w':

      if (((x + lx*fraction)+lx) <= -7.9 || ((x + lx*fraction)+lx) >= 7.9 )
          break;

        if (((z+lz*fraction)  + lz) <= -7.9 || ((z+lz*fraction)  + lz) >= 7.9)
          break;
      x += lx*fraction;
      z += lz*fraction;
      printf("%lf %lf %lf\n", angle, lx, lz);
    break;
    case 's':
     
        if (((x + lx*fraction)+lx) <=  -7.9 || ((x + lx*fraction)+lx) >= 7.9)
          break;

        if (((z+lz*fraction)  + lz) <= -7.9 || ((z+lz*fraction)  + lz) >= 7.9)
          break;
       //printf("%lf %lf %lf\n", angle, lx, lz);
     
      x -= lx*fraction;
      z -= lz*fraction;
      break;
  }
  glutPostRedisplay();
}
void specialKey(int key, int xx, int yy){
  float fraction = 0.1f;
  switch (key)
  {
  case GLUT_KEY_RIGHT:
    angle += 0.06f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_LEFT:
      angle -= 0.06f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case GLUT_KEY_UP:
      x += lx*fraction;
      z += lz*fraction;
    break;
    case GLUT_KEY_DOWN:
      x -= lx*fraction;
      z -= lz*fraction;
      break;
  }
  glutPostRedisplay();
  
}
static void on_mouse_motion(int x, int y){
  glutSetCursor(GLUT_CURSOR_NONE);
  
  float angleY = 0;
  float angleX = 0;
  angleY += x;
  angleX += y;

  if(angleY > 360.0*1/sensitivity){
    angleY -= 360.0*1/sensitivity;
    }
  if(angleY < -360.0*1/sensitivity){
    angleY += 360.0*1/sensitivity;
    }
  if(angleX > 89.0*1/sensitivity){
    angleX = 89.0*1/sensitivity;
    }
  if(angleX < -89.0*1/sensitivity){
    angleX = -89.0*1/sensitivity;
  } 
  lx = cos(pi/180.0f*angleX*sensitivity)*sin(pi/180.0f*angleY*sensitivity);
  ly = -sin(pi/180.0f*angleX*sensitivity);
  lz = -cos(pi/180.0f*angleX*sensitivity)*cos(pi/180.0f*angleY*sensitivity);    
  glutPostRedisplay();
}

/*Funkcija Koja Isrctava Scenu*/
static void on_display(void){
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
      x, 1.0f, z,
      x+lx, 1.0f + ly, z+lz,
      0, 1, 0
    );

    light_mode();

/*koordinatni sistem*/
  /*glEnable(GL_LINE_STIPPLE);
  glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(-5, 0, 0);
        glVertex3f(20, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, -5, 0);
        glVertex3f(0, 20, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -5);
        glVertex3f(0, 0, 20);
    glEnd();*/
   
  /* crtanje poda */
  glBindTexture(GL_TEXTURE_2D, names[1]);
    glColor3f(1, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(9, 0, 9);
        glTexCoord2f(1, 0);
        glVertex3f(9, 0, -9);
        glTexCoord2f(1, 1);
        glVertex3f(-9, 0, -9);
        glTexCoord2f(0, 1);
        glVertex3f(-9, 0, 9);
    glEnd();

    /* crtanje levog zida */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON); 
        
        
        
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-9, 0, 9);
        glTexCoord2f(1, 0);
        glVertex3f(-9, 0, -9);
        glTexCoord2f(1, 1);
        glVertex3f(-9, 5, -9);
        glTexCoord2f(0, 1);
        glVertex3f(-9, 5, 9);
    glEnd();
    
    /*crtanje zadnjeg zida */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0);
        glVertex3f(-9, 0, -9);
        glTexCoord2f(1, 0);
        glVertex3f(9, 0, -9);
        glTexCoord2f(1, 1);      
        glVertex3f(9, 5, -9);
        glTexCoord2f(0, 1);        
        glVertex3f(-9, 5, -9);
    glEnd();
      

     /* crtanje desnog zida */
    
    glColor3f(0.3, 0.4, 0.6);
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(9, 0, -9);
        glTexCoord2f(0, 1);
        glVertex3f(9, 5, -9);
        glTexCoord2f(1, 1);
        glVertex3f(9, 5, 9);
        glTexCoord2f(1, 0);
        glVertex3f(9, 0, 9);
    glEnd(); 

    /* crtanje prednjeg zida */
    
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0);
        glVertex3f(-9, 0, 9);
        glTexCoord2f(1, 0);
        glVertex3f(9, 0, 9);
        glTexCoord2f(1, 1);
        glVertex3f(9, 5, 9);
        glTexCoord2f(0, 1);
        glVertex3f(-9, 5, 9);
    glEnd();
    
    /* crtanje plafona */
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glNormal3f(0, -9, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-9, 5, 9);
        glTexCoord2f(1, 0);
        glVertex3f(9, 5, 9);
        glTexCoord2f(1, 1);
        glVertex3f(9, 5, -9);
        glTexCoord2f(0, 1);
        glVertex3f(-9, 5, -9);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
 //glutPostRedisplay();

    glutSwapBuffers(); 
    
}

