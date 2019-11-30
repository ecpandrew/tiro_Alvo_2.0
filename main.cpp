#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Classe dos alvos
class Alvos
{

public:
  void setPosicaoX(int x);
  void setPosicaoY(int y);
  void setStatus(bool s);
  int getPosicaoX();
  int getPosicaoY();
  bool getStatus();
  int getTamanho();
  void setTamanho(int t);

private:
  int x;
  int y;
  int tamanho;
  bool status;
};

void Alvos::setPosicaoX(int pos)
{

  x = pos;
}
void Alvos::setPosicaoY(int pos)
{
  y = pos;
}
void Alvos::setStatus(bool s)
{
  status = s;
}
void Alvos::setTamanho(int t)
{

  tamanho = t;
}
int Alvos::getTamanho()
{

  return tamanho;
}

bool Alvos::getStatus()
{
  return status;
}
int Alvos::getPosicaoX()
{
  return x;
}

int Alvos::getPosicaoY()
{
  return y;
}

//fim dojogo
static bool endgame = false;
GLfloat r, g, b;
//Flexa
float x_PF = 10.0, y_PF = 10.0;
//velocidade constante;
static float gr = 9.81, v = 2;
//angulo da seta;
static int angulo = -10, angulof;
//ponstos da tragetoria
static float pontos_sx[20];
static float pontos_y[20];
static Alvos lista_alvos[5];

//para reshape
static float px, py;
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void movimentaSeta(int value);
void movimentaAlvo(int value);
void movimentaSetaAlvo(int value);
Alvos generateAlvos(int x, int y, int tamanho, bool status);
void initAlvos();

void desenhaAlvo();

void initAlvos()
{
  Alvos alvo1 = generateAlvos(200, 200, 30, false);
  Alvos alvo2 = generateAlvos(150, 200, 30, false);
  Alvos alvo3 = generateAlvos(80, 100, 30, false);
  Alvos alvo4 = generateAlvos(300, 40, 30, false);

  lista_alvos[0] = alvo1;
  lista_alvos[1] = alvo2;
  lista_alvos[2] = alvo3;
  lista_alvos[3] = alvo4;
}

void desenhaAlvo()
{
  for (int i = 0; i <= 3; i++)
  {
    Alvos alvo = lista_alvos[i];

    glColor3i(0, 1, 0);
    glRecti(alvo.getPosicaoX(), alvo.getPosicaoY(), alvo.getPosicaoX() + alvo.getTamanho(), alvo.getPosicaoY() + alvo.getTamanho());
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tiro ao Alvo");
  init();

  initAlvos();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutTimerFunc(33, movimentaSeta, 1);
  //glutIdleFunc(movimentaSeta);
  glutMainLoop();
  return 0;
}
void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(0, 500, 0, 500, 0, 1);
  r = 0;
  g = 1;
  b = 0;
}

Alvos generateAlvos(int x, int y, int tamanho, bool status)
{
  Alvos auxalvo;
  auxalvo.setPosicaoX(x);
  auxalvo.setPosicaoY(y);
  auxalvo.setStatus(status);
  auxalvo.setTamanho(tamanho);
  return auxalvo;
}

void display(void)
{
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_POLYGON_STIPPLE);

  //jogo
  glPolygonMode(GL_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2i(10, 490);  //1
  glVertex2i(380, 490); //2 cima
  glVertex2i(380, 10);  //3
  glVertex2i(10, 10);   //4 baixo
  glEnd();

  //placar
  glPolygonMode(GL_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2i(390, 410); //1
  glVertex2i(490, 410); //2 cima
  glVertex2i(490, 300); //3
  glVertex2i(390, 300); //4 baixo
  glEnd();

  //Cena da flexa
  glPushMatrix();
  glTranslatef(10, 10, 0);
  glRotatef(angulo, 0, 0, 1);
  glTranslatef(-10, -10, 0);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2d(x_PF, y_PF);           //vertice fixo - origem 10,10
  glVertex2d(x_PF + 30, y_PF + 30); //40,40
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2d(x_PF + 20, y_PF + 10); //30,20
  glVertex2d(x_PF + 30, x_PF + 30); //40,40
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2d(x_PF + 10, y_PF + 20); //20,30
  glVertex2d(x_PF + 30, x_PF + 30); //185,20,0
  glEnd();
  glPopMatrix();

  desenhaAlvo();

  glFlush();
  glutSwapBuffers();
}
int fim = 0;
void movimentaSeta(int value)
{

  if (angulo < 40)
  {
    angulo++;
  }

  else
  {
    angulo = -10;
  }

  glutPostRedisplay();
  glutTimerFunc(33, movimentaSeta, 1);
}
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
    break;
  }
}

void reshape(int w, int h)
{
  if (h == 0)
  {
    h = 1;
  }
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  float m = (float)w;
  float n = (float)h;
  py = n / 500.0;
  px = m / 500.0;
}

void mouse(int button, int state, int x, int y)
{
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
    {
      angulof = angulo;
      r = (GLfloat)rand() / (RAND_MAX + 1.0);
      g = (GLfloat)rand() / (RAND_MAX + 1.0);
      b = (GLfloat)rand() / (RAND_MAX + 1.0);
    }
    break;
  }
}
