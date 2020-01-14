#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "image.h"
#include "light.h"
#include "axis.h"
#include "DoomMatf.h"


#define FILENAME0 "wall.bmp"
#define FILENAME1 "floor.bmp"
#define FILENAME2 "sky.bmp"

#define pi 3.14159265358979323846
#define TIMER_INTERVAL 20
#define TIMER_ID 0
static GLuint names[4];


int window_width, window_height;
//fukncija za sva glavna iscrtavanja
static void on_display(void);
static void on_reshape();
//za interakciju sa programom uz pomoc tastature
static void on_keyboard(unsigned char key, int x, int y);
//za kretanje strelicama
static void specialKey(int key, int x, int y);
//teksture
static void initialize(void);
//rotiranje kamere misem
static void on_mouse_motion(int x, int y);
//timer funkcija
static void on_timer(int id);
//funkcija za klik
static void on_mouse(int button, int state, int x, int y);
void draw_demon();
void draw_throne();
//angle za rotaciju kamere
float angle = 0.0;
//parametri za poziciju i za tacku u sta kamera gleda
float lx = 0.0f;
float lz = -1.0f;
float ly = 0;
float x = 0.0f, z=5.0f;
//promenljiva koja regulise brzinu misa
double sensitivity = 0.4;
//animacioni parametri za pomeranje nogu demona
float animation_parameter = 0;
int animation_ongoing = 0;
//za animaciju napada
int attack = 0;
//za odnos rotacije daggera
float dagger_angle = 62;
//promenljive koje vred. dobijaju rand-om za generisanje demona
float randomX;
float randomZ;

int main(int argc, char **argv)
{
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(900, 900);
    glutInitWindowPosition(300, 300);           
    glutCreateWindow("DoomMatf");     
    
    glutKeyboardFunc(on_keyboard);
    glutMouseFunc(on_mouse);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(on_mouse_motion);
    initialize();//Teksture
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
   
   //Pojavljivanje prvog demona
        srand(time(NULL));

        randomX = rand()%15 - 8;
        randomZ = rand()%15 - 8;
      
    //++++++++++++++++++
   
    glutMainLoop();
 return 0;   
}
static void on_reshape(int width, int height){
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)width/height, 0.1, 100);
}
//teskture
static void initialize(void){
  Image *image;

  glClearColor(0, 0, 0, 0);

  glEnable(GL_DEPTH_TEST);


  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
image = image_init(0, 0);

image_read(image, FILENAME0);

glGenTextures(3, names);

//prva tekstura
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

  image_read(image, FILENAME1);
    
    //druga tekstura
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


  //treca tekstura
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

  //provera da li je pritisnut levi klik koji oznacava napad, pa provera da li smo pogodili demona
  //ako jesmo pravimo nove koordinate za sledeceg demona
  if(attack == 1){
    if(randomX + 0.8 >= x + lx && randomX - 0.8 <= x + lx
            && randomZ + 0.8 >= z + lz && randomZ - 0.8 <= z + lz){
          randomX = rand()%15 - 8;
          randomZ = rand()%15 - 8;
      }
      //za animaciju napada daggerom 
      usleep(100000);
      attack = 0;

  }
    //parametar koji se koristi za pomeranje ruku i nogu demona
    animation_parameter += 0.5f;

    //dok god traje animacija poziva se timer_funkcija
    if(animation_ongoing)
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

      glutPostRedisplay();
}
static void on_keyboard(unsigned char key, int xx, int yy){
  float fraction = 0.1f;
  switch (key)
  {
    case 27://dugme esc za gasenje programa
    exit(0);
    break;
  case 'd':
    //postavljena su ogranicenja za dagger_angle kako bi se dagger uvek rotirao normalno
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
    //Start
     case 13:
          if(!animation_ongoing){
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          }
          else if(animation_ongoing)
            animation_ongoing = 0;
          break;

      //pritiskom f prozor postaje fullscreen
      case 'f':
            glutFullScreen();           
            break;
      //smanjuje se prozor
      case 'm':
        glutReshapeWindow(900, 900);
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
  //levim klikom je napad
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    attack = 1;
  }
  glutPostRedisplay();
  
}
static void on_mouse_motion(int x, int y){//kretanje kamere pomocu misa
  //cursor se ne prikazuje na ekranu kada je u prozoru
  glutSetCursor(GLUT_CURSOR_NONE);
  
  float angle_y = 0;
  float angle_x = 0;
  //pozicije cursora na ekranu
  angle_y += x;
  angle_x += y;

  if(angle_y > 360/sensitivity){
      angle_y -= 360/sensitivity;
    }
  if(angle_y < -360/sensitivity){
      angle_y += 360/sensitivity;
    }
  if(angle_x > 89/sensitivity){
      angle_x = 89/sensitivity;
    }
  if(angle_x < -89/sensitivity){
      angle_x = -89/sensitivity;
    }

   //uglovi se prebacuju u radijane kao sferne koordinate
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

  //animacija napada
   if(attack == 1){
     glTranslatef(lx/2, 0, lz/2);
   }
        //translacija koja pomera mac
        glTranslatef(x + lx, 0.6, z + lz);
        //rotiranje maca
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
   
  //spawnuju se demoni
  glTranslatef(randomX, 0, randomZ);
  
  glScalef(0.7, 1, 0.5);
    //Demonovi rogovi
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
    //Demonova Glava
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
    
    //Demonov Torso
    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(0, 0.9, 0);
    glScalef(0.6, 0.7, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(1, 0, 0);
    //Demonove ruke
    glPushMatrix();
    glTranslatef(0.37, 1.1, 0);
    glRotatef(30*cos(8*pi*animation_parameter/180), 1, 0, 0);//za animaciju kretanja ruke
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.34, 1.1, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/180), 1, 0, 0);//za animaciju kretanja ruke
    glScalef(0.2, 0.6, 0.2);
    glutSolidCube(0.6);
    glPopMatrix();
    

    //Demonove Noge
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.1, 0.4, 0);
    glRotatef(-30*cos(8*pi*animation_parameter/180), 1, 0, 0);//za animaciju kretanja ruke
    glScalef(0.3, 0.9, 0.3);
    glutSolidCube(0.6);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-0.1, 0.4, 0);
    glRotatef(30*cos(8*pi*animation_parameter/180), 1, 0, 0);//za animaciju kretanja ruke
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


//crtanje demona 
 glPushMatrix();
 draw_demon();
 glPopMatrix();

//crtanje noza
glPushMatrix();
 draw_dagger();
glPopMatrix();

 
 
    glutSwapBuffers(); 
    
}

