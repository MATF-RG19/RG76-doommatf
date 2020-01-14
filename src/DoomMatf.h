#ifdef _DOOM_H
#define _DOOM_H

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

#endif