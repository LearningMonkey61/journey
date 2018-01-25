/*
 *  drawf2.c
 *
 *  draw subimage of F
 *
 *  set up subrect origin with glPixelStore:
 *    _x0 : GL_UNPACK_SKIP_PIXELS
 *    _y0 : GL_UNPACK_SKIP_ROWS
 *
 *  And width and height in glDrawPixel.
 *
 *  Note that GL_UNPACK_ROW_LENGTH is 0 by default, it use width passed from
 *  glDrawPixel as row length. You should set GL_UNPACK_ROW_LENGTH to it's
 *  actural row length if you  don't plan to use exact image width in
 *  glDrawPixels, otherwise, you image will be messed up.
 *
 *  for 3d images, use GL_UNPACK_SKIP_IMAGES to skip layers. You might also need
 *  to set GL_UNPACK_IMAGE_HEIGHT to it's actural height if only want to use a
 *  subrect in each layer, see texture3d for example.
 *
 *  If color_map is enabled with rgb color, let's assume red map is size of n,
 *  than after map, r = map[round(r*(n-1))].
 *
 *  If you use pixel buffer, you will get GL_INVALID_OPERATION if you draw call
 *  access exceed buffer size.
 *
 */

#include "glad/glad.h"
#include <GL/freeglut.h>
#include <stdlib.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include "common.h"

GLuint pubo;
GLubyte image[12 * 16 * 3];

// subrect of image
GLuint _x0 = 0, _y0 = 0, width = 16, height = 12;
GLdouble redScale = 1.0, redBias = 0.0;

// clang-format off

// bitmap mask of f

 //     * * * * * * * * * * 0 0 0 0 0 0 
 //     * * * * * * * * * * 0 0 0 0 0 0 
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * * * * * * * 0 0 0 0 0 0 0 0 
 //     * * * * * * * * 0 0 0 0 0 0 0 0 
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 //     * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 
//bit mask of f, this is only used to create f image
GLubyte bitmask[24] = {
  0xc0, 0x00,   //bottom
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0x00,
  0xff, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0xc0,
  0xff, 0xc0    //top
};

GLfloat redMap[]= { 1, 0 }; // 0 to 1 , 1 to 0
GLfloat greenMap[]= { 1, 0 };
GLfloat blueMap[]= { 1, 0 };
// clang-format on

void createImage() {
  GLubyte* k = image;
  for (int i = 0; i < 24; ++i) {
    // loop bytes
    GLubyte b = bitmask[i];
    for (int j = 7; j >= 0; j--) {
      // loop bits
      GLubyte c = b & (0x01 << j) ? 0xff : 0x3f;
      *k++ = c;
      *k++ = c;
      *k++ = c;
    }
  }
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  createImage();

  glGenBuffers(1, &pubo);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pubo);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(image), image, GL_STATIC_DRAW);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2i(200, 200);
  glPixelZoom(10, 10);

  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pubo);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

  glColor3f(1.0f, 1.0f, 1.0f);
  glWindowPos2i(10, 480);
  char info[512];

  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  sprintf(info,
    "qQ : _x0 : %u\n"
    "wW : _y0 : %u\n"
    "eE : width : %u\n"
    "rR : height : %u\n"
    "uU : red scale : %3.2f\n"
    "iI : red bias : %3.2f\n"
    "o : toggle color map\n",
    _x0, _y0, width, height, redScale, redBias);

  glutBitmapString(GLUT_BITMAP_9_BY_15, (const GLubyte*)info);

  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
    case 'q':
      if (_x0 < 15) {
        _x0 += 1;
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, _x0);
        glutPostRedisplay();
      }
      break;
    case 'Q':
      if (_x0 > 0) {
        _x0 -= 1;
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, _x0);
        glutPostRedisplay();
      }
      break;
    case 'w':
      if (_y0 < 12) {
        _y0 += 1;
        glPixelStorei(GL_UNPACK_SKIP_ROWS, _y0);
        glutPostRedisplay();
      }
      break;
    case 'W':
      if (_y0 > 0) {
        _y0 -= 1;
        glPixelStorei(GL_UNPACK_SKIP_ROWS, _y0);
        glutPostRedisplay();
      }
      break;
    case 'e':
      if (width < 16) {
        width += 1;
        /*glPixelStorei(GL_UNPACK_ROW_LENGTH, width);*/
        glutPostRedisplay();
      }
      break;
    case 'E':
      if (width > 0) {
        width -= 1;
        /*glPixelStorei(GL_UNPACK_ROW_LENGTH, width);*/
        glutPostRedisplay();
      }
      break;
    case 'r':
      if (height < 12) {
        height += 1;
        glutPostRedisplay();
      }
      break;
    case 'R':
      if (height > 0) {
        height -= 1;
        glutPostRedisplay();
      }
      break;
    case 'u':
      redScale += 0.1;
      glPixelTransferf(GL_RED_SCALE, redScale);
      glutPostRedisplay();
      break;
    case 'U':
      if (redScale >= 0.1) {
        redScale -= 0.1;
        glPixelTransferf(GL_RED_SCALE, redScale);
        glutPostRedisplay();
      }
      break;
    case 'i':
      redBias += 0.1;
      glPixelTransferf(GL_RED_BIAS, redBias);
      glutPostRedisplay();
      break;
    case 'I':
      if (redBias >= 0.1) {
        redBias -= 0.1;
        glPixelTransferf(GL_RED_BIAS, redBias);
        glutPostRedisplay();
      }
      break;
    case 'o': {
      GLboolean b;
      glGetBooleanv(GL_MAP_COLOR, &b);

      glPixelTransferi(GL_MAP_COLOR, !b);
      if (!b) {
        glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 2, redMap);
        glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 2, greenMap);
        glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 2, blueMap);
      }
      glutPostRedisplay();

    } break;
  }
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  loadGL();
  init();
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}