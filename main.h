#ifdef _DOOM_H
#define _DOOM_H

#define FILENAME0 "tree.bmp"
#define FILENAME1 "grass.bmp"
#define FILENAME2 "sky.bmp"

static GLuint names[3];
static int window_width, window_height;


static void on_display(void);
static void on_reshape();
static void on_keyboard(unsigned char key, int x, int y);
static void specialKey(int key, int x, int y);
static void initialize(void);

double posx=-4.0,posy=2.0,posz=4.0,
lookx=0,looky=1,lookz=0,upx=0,upy=0,upz=-1;
#endif