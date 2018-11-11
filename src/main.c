#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

#define TIMER_RET 0

static int gX = 3;
static int gY = 3;
int timer_active = 1;


/* Dimenzije prozora */
static int window_width, window_height;

/* Callback funkcije */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    /* Kreiranje prozora */
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Grafovi");

    /* Registracija callback funkcija  */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* OpenGL inicijalizacija */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(EXIT_SUCCESS);
        break;
    
    case 'a':
    case 'A':
        gX = -3;
        glutTimerFunc(50,on_timer,TIMER_RET);
        break;
    case 'd':
    case 'D':
        gX = 3;
        glutTimerFunc(50,on_timer,TIMER_RET);
        break;
    case 'w':
    case 'W':
        gY = 3;
        glutTimerFunc(50,on_timer,TIMER_RET);
        break;
    case 's':
    case 'S':
        gY = -3;
        glutTimerFunc(50,on_timer,TIMER_RET);
        break;
    }
    
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera */
    if (value != TIMER_RET)
        return;
    
    printf("Hello ontimer!!\n");
    /* Ponovno iscrtavanje prozora. */
    glutPostRedisplay();
    

}

static void on_reshape(int width, int height)
{
    
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;
    
    
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 30);

    
    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(gX, gY, 6, 0, 0, 0, 0, 1, 0);
    printf("%d\n",gX);
    

    /* Crtamo sferu */
    glPushMatrix();
    glTranslatef(3,0,0);
    glColor3f(0, 0, 1);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    //x-osa
    glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(-10,0,0);
    glVertex3f(10,0,0);
    glEnd();
    
    //y-osa
     glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0,-10,0);
    glVertex3f(0,10,0);
    glEnd();
    
    //z-osa
     glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3f(0,0,-10);
    glVertex3f(0,0,10);
    glEnd();

    glutSwapBuffers();
}
