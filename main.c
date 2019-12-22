#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "image.h"
#include "main.h"

#define FILENAME0 "wall.bmp"
#define FILENAME1 "floor.bmp"
#define FILENAME2 "sky.bmp"
#define FILENAME3 "well.bmp"

#define pi 3.14159265358979323846
#define TIMER_INTERVAL 20
#define TIMER_ID 0
static GLuint names[4];

static int window_width, window_height;
static void on_display(void);
static void on_reshape();
static void on_keyboard(unsigned char key, int x, int y);
static void specialKey(int key, int x, int y);
static void initialize(void);
static void on_mouse_motion(int x, int y);
static void on_timer(int id);
void draw_demon();
void draw_well();
float angle = 0.0;
float lx = 0.0f;
float lz = -1.0f;
float ly = 0;
float x = 0.0f, z=5.0f;
double posx= 8,posy= 1,posz=7,
lookx=0,looky=0,lookz=0,upx=0,upy=0,upz=-1;
double sensitivity = 0.4;
float animation_parameter = 0;
int animation_ongoing = 0;

int main(int argc, char **argv)
{
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1200, 1200);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("DoomMatf");
   
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(on_mouse_motion);
    initialize();//Teksture

     glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_position[] = {-1, 3, 2, 1};
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
     
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST | GL_COLOR_MATERIAL);
   
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

 glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}
static void on_timer(int id){
  if(id != TIMER_ID)
    return;

    animation_parameter += 0.5f;

    if(animation_ongoing)
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

      glutPostRedisplay();
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
    case 'g':
    lookx += 1;
    printf("%lf\n", lookx);
    break;
    //Pritiskom enter demon pocinje da se krece
     case 13:
          if(!animation_ongoing){
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          }
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
void draw_well(){      
  glBindTexture(GL_TEXTURE_2D, names[3]);
  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  GLUquadric *quad;
  quad = gluNewQuadric();
  gluCylinder(quad, 1, 0.6, 0.8, 30, 30);
  glPopMatrix();
}

void draw_dagger(){
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(1, 4.0f, 23.6);
    glRotatef(90, 1, 0, 0);
    glPushMatrix();
       glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glutSolidCone(0.5, 4, 30, 30);
    glPopMatrix();
  
    double clipping[] = {0, 1, 0, 0};
    
    GLfloat ambient1[] = {0.3,0.3,0.3,0};
    GLfloat diffuse1[] = {0.7,0,0,0};
    GLfloat specular1[] = {0.6,0.6,0.6,0};
    GLfloat shininess1 = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
    glClipPlane(GL_CLIP_PLANE0, clipping);
    glEnable(GL_CLIP_PLANE0);
    glScalef(0.6, 4, 0.6);
    glutSolidCube(1);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef(2, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

}
void draw_demon(){
   // glScalef(5, 5, 5);
    glRotatef(animation_parameter, 0, 1, 0);
   glTranslatef(-4, 0, 0);

    
   //rogovi
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-0.08, 0, 1.6);
    glutSolidCone(0.05, 0.2, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0.08, 0, 1.6);
    glutSolidCone(0.05, 0.2, 30, 30);
    glPopMatrix();

    //glava
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
    
    //telo
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0, 0.9, 0);
    glScalef(0.6, 0.7, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.37, 1.1, 0);
    glRotatef(30*cos(8*pi*animation_parameter/240), 1, 0, 0);
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.34, 1.1, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/240), 1, 0, 0);
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    
    glColor3f(0,0,1);
    glPushMatrix();
    glTranslatef(0.1, 0.4, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/240), 1, 0, 0);
    glScalef(0.3, 0.9, 0.3);
    glutSolidCube(0.6);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-0.1, 0.4, 0);
    glRotatef(30*cos(8*pi*animation_parameter/240), 1, 0, 0);
    glScalef(0.3, 0.9, 0.3);
    glutSolidCube(0.6);
    glPopMatrix();
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

    //light_mode();

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

//crtanje oruzja
glPushMatrix();
 draw_dagger();
glPopMatrix();

 //crtanje neprijatelja
 glPushMatrix();
 draw_demon();
 glPopMatrix();

glPushMatrix();
draw_well();
glPopMatrix();
    glutSwapBuffers(); 
    
}

