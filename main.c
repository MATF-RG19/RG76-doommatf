#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "image.h"
#include "main.h"
#include "light.h"
#include "axis.h"

#define FILENAME0 "wall.bmp"
#define FILENAME1 "floor.bmp"
#define FILENAME2 "sky.bmp"

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
void draw_throne();
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
    glutFullScreen();           

   
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(on_mouse_motion);
    initialize();//Teksture


    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
   
    glutMainLoop();
 return 0;   
}
static void on_reshape(int width, int height){
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)width/height, 0.1, 100);
}
static void initialize(void){
  Image *image;

  glClearColor(0, 0, 0, 0);

  glEnable(GL_DEPTH_TEST);


  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
image = image_init(0, 0);

image_read(image, FILENAME0);

glGenTextures(4, names);

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
      //kretanjem pomocu w i s su namestena ogranicenja kako ne bi prolazili kroz zidove
    case 'w':

      if (((x + lx*fraction)+lx) <= -7.9 || ((x + lx*fraction)+lx) >= 7.9 )
          break;

        if (((z+lz*fraction)  + lz) <= -7.9 || ((z+lz*fraction)  + lz) >= 7.9)
          break;
      x += lx*fraction;
      z += lz*fraction;
    break;
    case 's':
     
        if (((x + lx*fraction)+lx) <=  -7.9 || ((x + lx*fraction)+lx) >= 7.9)
          break;

        if (((z+lz*fraction)  + lz) <= -7.9 || ((z+lz*fraction)  + lz) >= 7.9)
          break;     
      x -= lx*fraction;
      z -= lz*fraction;
      break;
    case 'g':
    lookx += 1;
    break;
    //Pritiskom enter demon pocinje da se krece
     case 13:
          if(!animation_ongoing){
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          }
          else if(animation_ongoing)
            animation_ongoing = 0;
          break;
  }
  glutPostRedisplay();
}

//kretanje pomocu strelica nisu namestena ogranicenja za zidove, u slucaju da se negde igrac 
//zaglavi ovo je nacin kako da se odglavi
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
  //cursor se ne prikazuje na ekranu kada je u prozoru
  glutSetCursor(GLUT_CURSOR_NONE);
  
  float angleY = 0;
  float angleX = 0;
  angleY += x;
  angleX += y;
  angle = angleY;
  if(angleY > 360/sensitivity){
    angleY -= 360/sensitivity;
      angle = angleY;

    }
  if(angleY < -360/sensitivity){
    angleY += 360/sensitivity;
      angle = angleY;

    }
  if(angleX > 89/sensitivity){
    angleX = 89/sensitivity;
      angle = angleX;

    }
  if(angleX < -89/sensitivity){
    angleX = -89/sensitivity;
      angle = angleX;

  } 
  lx = cos(pi/180.0f*angleX*sensitivity)*sin(pi/180.0f*angleY*sensitivity);
  ly = -sin(pi/180.0f*angleX*sensitivity);
  lz = -cos(pi/180.0f*angleX*sensitivity)*cos(pi/180.0f*angleY*sensitivity);    
  
  glutPostRedisplay();
}
void draw_throne(){      
  glPushMatrix();
  glColor3f(0, 0, 0);
  glScalef(0.7, 1, 0.5);
  glutSolidCube(2);
  glPopMatrix();

  glColor3f(212, 175, 0);
  glPushMatrix();
  glTranslatef(0.55, 1, 0.1);
  glScalef(0.1, 0.1, 0.4);
  glutSolidCube(3);
  glPopMatrix();


  glPushMatrix();
  glTranslatef(-0.55, 1, 0.1);
  glScalef(0.1, 0.1, 0.4);
  glutSolidCube(3);
  glPopMatrix();


  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(0, 1, -0.4);
  glScalef(1, 1.8, 0.2);
  glutSolidCube(1);
  glPopMatrix();
}

void draw_dagger(){
    glPushMatrix();

   glTranslatef(x+lx, 0.6, z+lz + 0.6);//translacija koja pomera mac u skladu sa kamerom
   glRotatef(-angle, 0, ly, 0);
   printf("%lf %lf\n", x, z);

   glScalef(0.7, 0.7, 0.7);
   glScalef(0.2, 0.2, 0.2);
    //glTranslatef(1, 4.0f, 23.6);
    glRotatef(90, 1, 0, 0);
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(0.5, 4, 30, 30);
    glPopMatrix();
  
    double clipping[] = {0, 1, 0, 0};
    glColor3f(0, 0, 0);
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

    glPopMatrix();



}
void draw_demon(){
   // glScalef(5, 5, 5);
    glRotatef(animation_parameter, 0, 1, 0);
   glTranslatef(-4, 0, 0);

    
   //rogovi
   glColor3f(0, 0, 0);
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
    glColor3f(1, 0, 0);
    //glava
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
    
    //telo
    glPushMatrix();
    glTranslatef(0, 0.9, 0);
    glScalef(0.6, 0.7, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.37, 1.1, 0);
    glRotatef(30*cos(8*pi*animation_parameter/180), 1, 0, 0);
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.34, 1.1, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/180), 1, 0, 0);
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.1, 0.4, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/180), 1, 0, 0);
    glScalef(0.3, 0.9, 0.3);
    glutSolidCube(0.6);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-0.1, 0.4, 0);
    glRotatef(30*cos(8*pi*animation_parameter/180), 1, 0, 0);
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
    //namestanje svetlosti
    light_mode();


/*koordinatni sistem
  iscrtavan je po potrebi
 drawAxis();
 */
   
  /* crtanje poda */
  glBindTexture(GL_TEXTURE_2D, names[1]);
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
  glBindTexture(GL_TEXTURE_2D, 0);//gasenje tekstura, fatalna greska, mukom pronadjena//

//crtanje oruzja
glPushMatrix();
 draw_dagger();
glPopMatrix();

 //crtanje neprijatelja
 glPushMatrix();
 draw_demon();
 glPopMatrix();

//crtanje trona
glPushMatrix();
draw_throne();
glPopMatrix();

    glutSwapBuffers(); 
    
}

