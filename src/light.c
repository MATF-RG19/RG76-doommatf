#include "light.h"

void light_mode(){
  GLfloat ligh_position[] = {1, 1, 1, 0};
      /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1};

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };

     glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


     GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}