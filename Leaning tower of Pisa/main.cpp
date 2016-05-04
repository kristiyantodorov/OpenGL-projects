
// Problem S09 E01
//
// Тази програма рисува координатната система
// и паралелепипед 2х2х1 с център на основата
// точката (0,0,0). Допишете drawUnitCylinder()
// така, че да рисува единичен цилиндър:
//    - център на долната основа (0,0,0)
//    - радиус 1
//    - височина 1
// Ако е правилно нарисуван единичния цилиндър,
// той би се вписал точно в паралелепипеда.
// Опитайте се да "оптимизирате" изчисленията,
// за да са колкото се може по-малко.

#include <cstdlib>
#include <math.h>
#include <time.h>
#include <GL/glfw.h>
#include "okglib.h"


void drawUnitCylinder ( )
{
    // Рисуване на единичен цилиндър
    // с колкото се може по-малко сметки
    float alpha = 0;
    int n = 32;
    float step = 2 * M_PI / n;
    glNormal3f(0, 0, -1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
        for(int i = 0; i <= n; i++)
        {
            glVertex3f(sin(alpha), cos(alpha), 0);
            alpha += step;
        }
    glEnd();

    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 1);
        for(int i = 0; i <= n; i++)
        {
            glVertex3f(sin(alpha), cos(alpha), 1);
            alpha += step;
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= n; i++)
        {
            glNormal3f(sin(alpha), cos(alpha), 0);
            glVertex3f(sin(alpha), cos(alpha), 1);
            glVertex3f(sin(alpha), cos(alpha), 0);
            alpha += step;
        }
    glEnd();
}

void drawFloor()
{
    glColor3ub(150,150,150);

        glPushMatrix();
            glTranslatef(0, 0, 5);
            glScalef (5, 5, 0.3);
            drawUnitCylinder();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, 0);
            glScalef (3.5, 3.5, 5);
            drawUnitCylinder();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, 0);
            glScalef (5, 5, 0.7);
            drawUnitCylinder();
        glPopMatrix();
        for(int i = 0; i < 20; i++)
        {
            glPushMatrix();
                glRotatef(18 * i, 0, 0, 1);
                glTranslatef(0, 4.2, 0.1);
                glScalef (0.4, 0.4, 5);
                drawUnitCylinder();
            glPopMatrix();
        }
}

void drawTower()
{
    for(int i = 0; i < 6; i++)
    {
        glPushMatrix();
            glTranslatef(0, 0, i * 5);
            drawFloor();
        glPopMatrix();
    }

    glPushMatrix();
        glTranslatef(0, 0, 30);
        glScalef(0.7, 0.7, 0.7);
        drawFloor();
    glPopMatrix();
}

int main()
{
    init();

    glClearColor( 0.0f, 0.0f, 0.9f, 0.0f );
    glEnable( GL_DEPTH_TEST );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );

    glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);


    float t = 0;

    srand(time(NULL));
    na = 24;
    nb = 12;

    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );
        t=t+0.003;
        glLoadIdentity();
        gluLookAt(45*cos(t),45*sin(t),0, 0,0,15, 0,0,1 );

        glBegin(GL_QUADS);
            glColor3ub(0, 200, 0);
            glVertex3f(100, 100, 0);
            glVertex3f(100, -100, 0);
            glVertex3f(-100, -100, 0);
            glVertex3f(-100, 100, 0);
        glEnd();

        glEnable( GL_LIGHTING );

        glPushMatrix();
            glRotatef(10, 1, 0, 0);
            drawTower();
        glPopMatrix();

        glDisable( GL_LIGHTING );

        glfwSwapBuffers();
    }

    finit();
    return 0;
}

