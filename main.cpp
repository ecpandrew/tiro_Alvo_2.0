#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

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

int Alvos::getPosicaoX()
{
  return x;
}

int Alvos::getPosicaoY()
{
  return y;
}
bool Alvos::getStatus()
{
  return status;
}
int Alvos::getTamanho()
{
  return tamanho;
}

//fim dojogo
static bool endgame = false;
GLfloat r, g, b;
//Flexa
float x_PF = 10.0, y_PF = 10.0;

static int global_value = 1;
//velocidade constante;
static float gr = 9.81, v = 5;
//angulo da seta;
static int angulo = -10, angulof;
//ponstos da tragetoria
static float pontos_x[80];
static float pontos_y[80];
static Alvos lista_alvos[5];
bool stateseta = true;

//para reshape
static float px, py;
void init(void);
void initAlvos(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void movimentaSeta(int value);
void trajetoriaSeta();
void desenhaFlexa();
void specialInputDoTeclado(int key, int x, int y);

void desenhaTrajetoria();

Alvos generateAlvos(int x, int y);

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
  // glutTimerFunc(33, movimentaSeta, 1);
  glutSpecialFunc(specialInputDoTeclado);

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
void initAlvos()
{
  Alvos alvo1 = generateAlvos(200, 200, 30, false);
  Alvos alvo2 = generateAlvos(150, 200, 30, false);
  Alvos alvo3 = generateAlvos(80, 100, 30, false);
  Alvos alvo4 = generateAlvos(300, 300, 30, false);

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
    glPolygonMode(GL_BACK, GL_LINE);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2i(alvo.getPosicaoX(), alvo.getPosicaoY());                                         //1
    glVertex2i(alvo.getPosicaoX() + alvo.getTamanho(), alvo.getPosicaoY());                     //2 cima
    glVertex2i(alvo.getPosicaoX() + alvo.getTamanho(), alvo.getPosicaoY() + alvo.getTamanho()); //3
    glVertex2i(alvo.getPosicaoX(), alvo.getPosicaoY() + alvo.getTamanho());                     //4 baixo
    glEnd();
  }
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

  

  desenhaAlvo();

  //tragetoria seta
  if (stateseta)
  {
    desenhaFlexa();
    desenhaTrajetoria();
  }else{
      //Cena da flexa
      double arg = angulo, result;
      // Converting to radian
      arg = (angulo * M_PI) / 180;
      glPushMatrix();
      glTranslatef(10, 10, 0);
      glRotatef(arg, 0, 0, 1);
      glTranslatef(-10, -10, 0);
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2d(pontos_x[global_value], pontos_y[global_value]);           //vertice fixo - origem 10,10
      glVertex2d(pontos_x[global_value] + 30, pontos_y[global_value] + 30); //40,40
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2d(pontos_x[global_value] + 20, pontos_y[global_value] + 10); //30,20
      glVertex2d(pontos_x[global_value] + 30, pontos_y[global_value] + 30); //40,40
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2d(pontos_x[global_value] + 10, pontos_y[global_value] + 20); //20,30
      glVertex2d(pontos_x[global_value] + 30, pontos_y[global_value] + 30); //185,20,0
      glEnd();
      glPopMatrix();
    // nao desenha
    // desenhaTrajetoria();
  }
  glFlush();
  glutSwapBuffers();
}




void desenhaFlexa(){
  //Cena da flexa
  glPushMatrix();
  glTranslatef(10, 10, 0);
  glRotatef(angulo-45, 0, 0, 1);
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
}


void desenhaTrajetoria(){

  glPushMatrix();
  glTranslatef(10, 10, 0);
      glBegin(GL_LINE_STRIP);
      for (int j = 0; j < 80; j++)
      {
      glColor3f(0.0, 0.0, 1.0);
      glVertex2d(pontos_x[j], pontos_y[j]); //20,30
      // printf("ponos x: %f\n", pontos_x[j]);
      // printf("ponos y: %f\n", pontos_y[j]);
      }
      glEnd();
  glPopMatrix();

}

int fim = 0;
void movimentaSeta(int value)
{

  if (!stateseta)
  {
    if(!(value > 70)){

      glutPostRedisplay();
      global_value++;
      glutTimerFunc(33, movimentaSeta, global_value);
    }else{
      global_value = 1;
      stateseta = true;
      glutPostRedisplay();

    }
  }
}

void trajetoriaSeta()
{
  // scanf("oi:  ");
  int nPoint = 80;
  float x, y;

   double arg = angulo, result;
   // Converting to radian
   arg = (angulo * M_PI) / 180;


  float t_total = (2 * v * sin(arg)) / gr;
  float t_ponto = t_total / nPoint;
  float t = 0;
  float x_0 = 0.0, y_0 = 0.0;
  for (int i = 0; i < nPoint; i++)
  {

    //x_PF = 20*(pow(v,2)*sin(2*value))/g;
    //y_PF = 100*(pow(v,2)*pow(sin(value),2))/2*g;
    x = 400 * (x_0 + v * cos(arg) * t);
    y = 400 * (y_0 + v * sin(arg) * t - (g * pow(t, 2)) / 2);

    // printf("x: %f\n", x);
    // printf("y: %f\n", y);

    pontos_x[i] = x;
    pontos_y[i] = y;
    t += t_ponto;
  }

  // Sleep(200);

  // glutPostRedisplay();
  // glutTimerFunc(33, trajetoriaSeta, 1);
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
    if (state == GLUT_DOWN && stateseta == true)
    {
      // angulof = angulo;
      // trajetoriaSeta();
      stateseta = false;
      movimentaSeta(1);

      r = (GLfloat)rand() / (RAND_MAX + 1.0);
      g = (GLfloat)rand() / (RAND_MAX + 1.0);
      b = (GLfloat)rand() / (RAND_MAX + 1.0);
    }
    break;
  }
}


void specialInputDoTeclado(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
      if(!(angulo>=90-45)){
        angulo++;
        trajetoriaSeta();
        glutPostRedisplay();
      }

      
      // glutTimerFunc(33, movimentaSeta, value);

      break;

    case GLUT_KEY_DOWN:
      if(!(angulo<=0-45)){
        angulo--;
        trajetoriaSeta();
        glutPostRedisplay();
      }
      break;
    }
}

