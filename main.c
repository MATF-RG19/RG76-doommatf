#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>

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
static void on_mouse(int button, int state, int x, int y);
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
int attack = 0;
float dagger_angle = 62;

float randomX;
float randomZ;
int Killed = 0;

/*void print(int x, int y)
{
//set the position of the text in the window using the x and y coordinates
glRasterPos2f(20,20);
//get the length of the string to display
char string[] = {'S', 'c', 'o', 'r', 'e'};
int len = (int) strlen("Score:");

//loop to display character by character
for (int i = 0; i < len; i++) 
{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}

}*/
int main(int argc, char **argv)
{
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 300);           
    glutCreateWindow("DoomMatf");     
    glutFullScreen();           

   
    glutKeyboardFunc(on_keyboard);
    glutMouseFunc(on_mouse);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(on_mouse_motion);
    initialize();//Teksture
    //print(0,0);
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
    if(dagger_angle < 57)
        dagger_angle += 0.06;
      else 
        dagger_angle -= 0.06;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case 'a':
      angle -= 0.06f;
      if(dagger_angle < 57)
        dagger_angle += 0.06;
      else 
        dagger_angle -= 0.06;

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
          if(!Killed)
            Killed = 1;
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
    if(dagger_angle < 57)
        dagger_angle += 0.06;
      else 
        dagger_angle -= 0.06;

    break;
    case GLUT_KEY_LEFT:
      angle -= 0.06f;
      lx = sin(angle);
      lz = -cos(angle);
      if(dagger_angle < 57)
        dagger_angle += 0.06;
      else 
        dagger_angle -= 0.06;

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

static void on_mouse(int button, int state, int x, int y){
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    attack = 1;
  glutPostRedisplay();
  }
}
static void on_mouse_motion(int x, int y){
  //cursor se ne prikazuje na ekranu kada je u prozoru
  glutSetCursor(GLUT_CURSOR_NONE);
  
  float angle_y = 0;
  float angle_x = 0;
  angle_y += x;
  angle_x += y;

  if(angle_y > 360.0*1/sensitivity){
      angle_y -= 360.0*1/sensitivity;
    }
  if(angle_y < -360.0*1/sensitivity){
      angle_y += 360.0*1/sensitivity;
    }
  if(angle_x > 89.0*1/sensitivity){
      angle_x = 89.0*1/sensitivity;
    }
  if(angle_x < -89.0*1/sensitivity){
      angle_x = -89.0*1/sensitivity;
    }
  lx = cos(pi/180.0f*angle_x*sensitivity)*sin(pi/180.0f*angle_y*sensitivity);
  ly = -sin(pi/180.0f*angle_x*sensitivity);
  lz = -cos(pi/180.0f*angle_x*sensitivity)*cos(pi/180.0f*angle_y*sensitivity);    
  
  glutPostRedisplay();
}
void draw_throne(){     
  //sediste 
  glPushMatrix();
  glColor3f(0, 0, 0);
  glScalef(0.7, 1, 0.5);
  glutSolidCube(2);
  glPopMatrix();
  //rukohvat
  glColor3f(212, 175, 0);
  glPushMatrix();
  glTranslatef(0.55, 1.1, 0.1);
  glScalef(0.1, 0.1, 0.4);
  glutSolidCube(3);
  glPopMatrix();

  //rukohvat
  glPushMatrix();
  glTranslatef(-0.55, 1.1, 0.1);
  glScalef(0.1, 0.1, 0.4);
  glutSolidCube(3);
  glPopMatrix();

  //naslon
  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(0, 1, -0.3);
  glScalef(1, 2, 0.2);
  glutSolidCube(1);
  glPopMatrix();
}

void draw_dagger(){
    glPushMatrix();

   //glTranslatef(x+lx, 0.6, z+lz/2 + 0.4);//translacija koja pomera mac u skladu sa kamerom
   if(attack == 1){
     glTranslatef(lx/2, 0, lz/2);
     
    //glTranslatef(0, 0.9, 0);
    //glScalef(0.6, 0.7, 0.3);
     printf("%lf %lf\n x y z", x + lx/2, z + lz/2);
     printf("%lf %lf\n", randomX, randomZ);

      if((abs(x + lx/2)) - abs(randomX) <= 0.6){
     // z + lz/2 <= randomZ + 0.3 && z + lz/2 >= randomZ - 0.3){
        Killed = 1;
        printf("HIT\n");
      }
     attack = 0;
     
   }
     /*  x, 1.0f, z,
      x+lx, 1.0f + ly, z+lz,
      0, 1, 0*/

        glTranslatef(x + lx, 0.6, z + lz);
        glRotatef(-angle*dagger_angle, 0, 1, 0);
    glPushMatrix();    
    
    glRotatef(90, 1, 0, 0);

   glScalef(0.7, 0.7, 0.7);
   glScalef(0.2, 0.2, 0.2);
  
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

   glPopMatrix();


}
void draw_demon(){
   // glScalef(5, 5, 5);
    //glRotatef(animation_parameter, 0, 1, 0);

  srand(time(NULL));

 glScalef(0.7, 1, 0.5);
  glutSolidCube(2);
  //spawnuju se demoni
  if(Killed){
  randomX = rand()%15 - 8;
  randomZ = rand()%15 - 8;
  if(randomX >= 0.7 || randomX <= -0.7){
  glTranslatef(randomX, 0, randomZ);
  Killed = 0;
  }
  }
  else{
      glTranslatef(randomX, 0, randomZ);

  }
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

//crtanje trona
glPushMatrix();
draw_throne();
glPopMatrix();

 //crtanje neprijatelja
 
 glPushMatrix();
 draw_demon();
 glPopMatrix();
 

//crtanje noza
glPushMatrix();
 draw_dagger();
glPopMatrix();

    glutSwapBuffers(); 
    
}

