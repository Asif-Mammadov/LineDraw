#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Color.h"
#include "../include/LineStrip.h"
#include "../include/Vector.h"
#include "../include/VertexNode.h"

#define BLUE 0, 0, 255
#define RED 255, 0, 0
#define GREEN 0, 128, 0
#define YELLOW 255, 255, 0
#define C_EDGE_SELECT YELLOW
#define C_VERTEX_SELECT RED

Color C_GLOBAL = {BLUE};
int window_width, window_height;
LineStrip *plot;
Vector mouse;
char MODE = 'c';

//-------------------------------------------------------------
// v : Vector with coordinates to put a cross
// size : size of a cross
// c : Color of a cross
// return value : none
// function draws a color at given vector v(x, y)
static void _drawCross(Vector v, int size, Color c) {
  // Let the current color be red
  glColor3ub(c.r, c.g, c.b);

  // Horizontal line
  glBegin(GL_LINE_STRIP);
  glVertex2i(v.x - size, v.y);
  glVertex2i(v.x + size, v.y);
  glEnd();

  // Vertical line
  glBegin(GL_LINE_STRIP);
  glVertex2i(v.x, v.y - size);
  glVertex2i(v.x, v.y + size);
  glEnd();
}

//-------------------------------------------
// sets global color depending on the MODE
void updateGlobalColor() {
  if (MODE == 'c')
    C_GLOBAL = C_new(BLUE);
  else if (MODE == 'e')
    C_GLOBAL = C_new(GREEN);
}

//------------------------------------------------------------------------
// plots crosses and strips depending on what we are currently working with.
// it's either 1.Edges or 2.Vertexes
// 1. Selected edge is colored in C_EDGE_SELECT, others are colored in C_GLOBAL
// 2. Selected vertex is colored in C_VERTEX_SELECT, others are colored in
// C_GLOBAL
void plotCrosses() {
  VertexNode *p = plot->VHead;
  if (plot->chosen == 'e') {
    while (p != NULL) {
      p->c = C_GLOBAL;
      if (p == plot->VCurrent) {
        _drawCross(p->v, 5, p->c);
        glColor3ub(C_EDGE_SELECT);
        glBegin(GL_LINE_STRIP);
        glVertex2i(p->v.x, p->v.y);
        p = p->next;
        p->c = C_GLOBAL;
        glVertex2i(p->v.x, p->v.y);
        glEnd();
      }
      _drawCross(p->v, 5, p->c);
      glColor3ub(C_GLOBAL.r, C_GLOBAL.g, C_GLOBAL.b);
      glBegin(GL_LINE_STRIP);
      glVertex2i(p->v.x, p->v.y);
      p = p->next;
      if (!p) {
        glEnd();
        break;
      }
      glVertex2i(p->v.x, p->v.y);
      glEnd();
    }
  } else if (plot->chosen == 'v') {
    while (p != NULL) {
      if (p == plot->VCurrent) {
        p->c = C_new(C_VERTEX_SELECT);
      } else {
        p->c = C_GLOBAL;
      }
      _drawCross(p->v, 5, p->c);
      glColor3ub(C_GLOBAL.r, C_GLOBAL.g, C_GLOBAL.b);
      glBegin(GL_LINE_STRIP);
      glVertex2i(p->v.x, p->v.y);
      p = p->next;
      if (!p) {
        glEnd();
        break;
      }
      glVertex2i(p->v.x, p->v.y);
      glEnd();
    }
  }
}

//--------------------------------------------------------------------------
// function updates Global color, plots strips, checks the correctness of modes
void updateGeneral() {
  if (plot->VHead == NULL)
    return;

  // is number of vertexes < 2, change mode to create
  // and work only with vertexes
  if (plot->VertexNum < 2) {
    MODE = 'c';
    plot->chosen = 'v';
  }
  updateGlobalColor();
  plotCrosses();
}

//-------------------------------------------------------------
// The call back function which is called each time that we need
// to draw everything again. All your drawings should be called
// in this function. Initially, we only draw a cross.

static void _display_CB() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0, window_width, window_height, 0, -1, 1);

  glClear(GL_COLOR_BUFFER_BIT);

  // Let the current color be black
  // glColor3ub(0,0,0);

  updateGeneral();
  glFlush();
  glutSwapBuffers();
}

//-------------------------------------------------------------
// The call back function which is called each time that the
// graphical window is resized.

static void _reshape_CB(int largeur, int hauteur) {
  printf("Window resized.\n"); // You can comment this line
  window_width = largeur;
  window_height = hauteur;
  glViewport(0, 0, window_width, window_height);
}

void choose() {
  VertexNode *p = plot->VHead;
  while (p) {
    if (V_PtPtDistance(mouse, p->v) < 6) {
      if (plot->VCurrent)
        plot->VCurrent->c = C_new(BLUE);
      plot->VCurrent = p;
      plot->VCurrent->c = C_new(RED);
      plot->chosen = 'v';
      return;
    }
    p = p->next;
  }
  p = plot->VHead;
  if (p->next) {
    VertexNode *q = p->next;
    while (q) {
      if (V_PtSegmentDistance(mouse, p->v, q->v) < 6) {
        plot->VCurrent = p;
        plot->chosen = 'e';
        return;
      }
      p = q;
      q = q->next;
    }
  }
  return;
}

void _leftButton() {
  if (MODE == 'c') {
    plot->VHead = VN_push(plot->VHead, mouse, C_new(BLUE));
    plot->VertexNum++;
    plot->chosen = 'v';
    if (plot->VCurrent) {
      plot->VCurrent->c = C_new(BLUE);
    }
    plot->VCurrent = plot->VHead;
    plot->VCurrent->c = C_new(RED);
  } else if (MODE == 'e') {
    choose();
  }
}
void _backspace() {
  if (MODE == 'c') {
    plot->VHead = VN_pop(plot->VHead);
    if (plot->VertexNum > 0)
      plot->VertexNum--;
    plot->VCurrent = plot->VHead;
    plot->chosen = 'v';
    if (plot->VCurrent)
      plot->VCurrent->c = C_new(RED);
  } else if (MODE == 'e' && plot->chosen == 'v') {
    VertexNode *p = plot->VCurrent;
    if (p->next) {
      p = p->next;
    } else if (p->prev) {
      p = p->prev;
    } else {
      p = NULL;
    }
    V_show(plot->VCurrent->v, "Current");
    V_show(plot->VHead->v, "Head");
    plot->VHead = VN_remove(plot->VHead, plot->VCurrent);
    plot->VertexNum--;
    if (p != NULL)
      plot->VCurrent = p;
    else
      plot->VCurrent = plot->VHead;
  }
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a mouse button is pressed or released.

static void _mouse_CB(int button, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
      mouse = V_new(x, y);
      _leftButton();
      break;
    case GLUT_RIGHT_BUTTON:
      printf("Right button pressed.\n");
      break;
    case GLUT_MIDDLE_BUTTON:
      printf("Middle button pressed.\n");
      break;
    }
  } else {
    switch (button) {
    case GLUT_LEFT_BUTTON:
      printf("Left button released.\n");
      break;
    case GLUT_RIGHT_BUTTON:
      printf("Right button released.\n");
      break;
    case GLUT_MIDDLE_BUTTON:
      printf("Middle button released.\n");
      break;
    }
  }
  glutPostRedisplay();
}

//-------------------------------------------------------------
// The call back function which is called each time that
// the mouse moves when being clicked.

static void _mouse_move_CB(int x, int y) {
  printf("Mouse position : (%d,%d)\n", x, y);
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a key (corresponding to an ascii code) on the keyboard is pressed.

static void _keyboard_CB(unsigned char key, int x, int y) {
  switch (key) {
  case 27:
    exit(0);
    break; // escape key
  case 8:
    _backspace();
    break; // backspace
  case 13:
    MODE = 'e';
    break; // enter
  case 'n':
    MODE = 'c';
    plot->chosen = 'v';
    plot->VCurrent = plot->VHead;
    break;
  case 'c':
    printf("c pressed.\n");
    break;
  case 'o':
    printf("o pressed.\n");
    break;
  case 'i':
    if (MODE == 'e' && plot->chosen == 'e') {
      plot->VHead = VN_insert(
          plot->VHead, plot->VCurrent,
          V_createMedium(plot->VCurrent->v, plot->VCurrent->next->v), C_GLOBAL);
      plot->chosen = 'v';
      plot->VertexNum++;
      plot->VCurrent = plot->VCurrent->next;
    } else {
      printf("i wont work like that\n");
    }
    break;
    // Feel free to use other keys
  case 'p':
    VN_display(plot->VHead, "Hello");
  default:
    printf("Unknown key : %d %c\n", key, key);
  }
  glutPostRedisplay();
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a special key (arrows, function keys) is pressed.

static void _special_CB(int key, int x, int y) {

  if (plot->chosen == 'v' && MODE == 'e') {
    switch (key) {
    case GLUT_KEY_LEFT:
      plot->VCurrent->v = V_shiftCoordinates(plot->VCurrent->v, -1, 0);
      break;
    case GLUT_KEY_RIGHT:
      plot->VCurrent->v = V_shiftCoordinates(plot->VCurrent->v, 1, 0);
      break;
    case GLUT_KEY_UP:
      plot->VCurrent->v = V_shiftCoordinates(plot->VCurrent->v, 0, -1);
      break;
    case GLUT_KEY_DOWN:
      plot->VCurrent->v = V_shiftCoordinates(plot->VCurrent->v, 0, 1);
      break;
    case GLUT_KEY_F1:
      printf("F1 key.\n");
      break;
    default:
      fprintf(stderr, "Unknown special key.\n");
    }
  }

  glutPostRedisplay();
}

//-------------------------------------------------------------

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("\nUsage : %s <width> <height>\n\n", argv[0]);
    return 1;
  } else {
    plot = LN_new();
    // Reading the command line arguments
    window_width = atoi(argv[1]);
    window_height = atoi(argv[2]);

    int windowPosX = 100, windowPosY = 100;

    // Initializing GLUT (graphic window and events manager)
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutCreateWindow(argv[0]);

    // Initializing OpenGL (drawing tool)
    glViewport(0, 0, window_width, window_height);
    glClearColor(255, 255, 255, 0);

    // Associating callback functions to each type of event
    glutDisplayFunc(_display_CB);
    glutReshapeFunc(_reshape_CB);
    glutKeyboardFunc(_keyboard_CB);
    glutSpecialFunc(_special_CB);
    glutMouseFunc(_mouse_CB);
    glutMotionFunc(_mouse_move_CB);

    // Starting the loop which waits for events.
    glutMainLoop();
  }
}
