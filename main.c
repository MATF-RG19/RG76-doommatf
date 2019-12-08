#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "image.h"


static int window_width, window_height;
static void on_display(void);
static void on_reshape();
static void on_keyboard(unsigned char key, int x, int y);
static void specialKey(int key, int x, int y);
static void initialize(void);
double posx=-4.0,posy=2.0,posz=4.0,
lookx=0,looky=1,lookz=0,upx=0,upy=0,upz=-1;

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
     
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
 return 0;   
}
static void on_reshape(int width, int height){
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)width/height, 0, 10);
}
static void initialize(void){
  Image *image;

  glClearColor(0, 0, 0, 0);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x1110);

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
image = image_init(0, 0);

image_read(image, FILENAME0);

glGenTextures(5, names);

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


                 /****/
 image_read(image, FILENAME3);
    
    glBindTexture(GL_TEXTURE_2D, names[3]);
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
  /****/
   image_read(image, FILENAME4);
    
    glBindTexture(GL_TEXTURE_2D, names[4]);
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
 glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}
static void on_keyboard(unsigned char key, int x, int y){
  switch (key)
  {
    case 27:
      exit(0);
      break;
  case 'w':
  posy += 1;
    break;
  case 's':
    posy -= 1;
  case 'a':
    posx -= 1.0;
    break;
  case 'd':
    posx += 1.0;
    break;
  case 'k':
    posz -= 1.0;
    case 'l':
    posy += 1.0;
  }
}
void specialKey(int key, int x, int y){
  switch (key)
  {
  case GLUT_KEY_RIGHT:
    posx +=1;
    break;
    case GLUT_KEY_LEFT:
      posx -= 1;
      break;
    case GLUT_KEY_UP:
      lookz += 1;
    break;
    case GLUT_KEY_DOWN:
      break;
  }
}

/*Funkcija Koja Isrctava Scenu*/
static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
      posx, posy, posz,
      lookx, looky, lookz,
      0, 1, 0
    );
/*koordinatni sistem*/
glEnable(GL_LINE_STIPPLE);
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
    glEnd();
   
  /* crtavanje poda */
  glBindTexture(GL_TEXTURE_2D, names[1]);
    glColor3f(1, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
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
    glBindTexture(GL_TEXTURE_2D, name[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON); 
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
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
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
 glutPostRedisplay();

    glutSwapBuffers(); 
    
}

