#include <cstdlib>
#include <math.h>
#include <GL/glfw.h>
#include "okglib.h"

void drawSolidParalelepiped (float x, float y, float z, float ax, float ay, float az)
{
    ax = ax/2;
    ay = ay/2;
    az = az/2;

    // Рисуване на стена откъм -X
    glBegin( GL_POLYGON );
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-ax, y-ay, z-az);
        glVertex3f(x-ax, y-ay, z+az);
        glVertex3f(x-ax, y+ay, z+az);
        glVertex3f(x-ax, y+ay, z-az);
    glEnd();

    // Рисуване на стена откъм +X
    glBegin( GL_POLYGON );
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+ax, y-ay, z-az);
        glVertex3f(x+ax, y-ay, z+az);
        glVertex3f(x+ax, y+ay, z+az);
        glVertex3f(x+ax, y+ay, z-az);
    glEnd();

    // Рисуване на стена откъм -Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x-ax, y-ay, z-az);
        glVertex3f(x-ax, y-ay, z+az);
        glVertex3f(x+ax, y-ay, z+az);
        glVertex3f(x+ax, y-ay, z-az);
    glEnd();

    // Рисуване на стена откъм +Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x-ax, y+ay, z-az);
        glVertex3f(x-ax, y+ay, z+az);
        glVertex3f(x+ax, y+ay, z+az);
        glVertex3f(x+ax, y+ay, z-az);
    glEnd();

    // Рисуване на стена откъм -Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x-ax, y-ay, z-az);
        glVertex3f(x-ax, y+ay, z-az);
        glVertex3f(x+ax, y+ay, z-az);
        glVertex3f(x+ax, y-ay, z-az);
    glEnd();

    // Рисуване на стена откъм +Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(x-ax, y-ay, z+az);
        glVertex3f(x-ax, y+ay, z+az);
        glVertex3f(x+ax, y+ay, z+az);
        glVertex3f(x+ax, y-ay, z+az);
    glEnd();
}

void drawPawn(float x, float y, float z)
{
    drawSmoothCone(x, y, z + 0.05, 0.4, 1);
    drawSmoothCylinder(x, y, z, 0.5, 0.1);
    drawSmoothEllipsoid(x, y, z + 0.8, 0.2, 0.2, 0.05);
    drawSmoothEllipsoid(x, y, z + 0.1, 0.45, 0.45, 0.05);
    drawSmoothEllipsoid(x, y, z + 0.1, 0.4, 0.4, 0.1);
    drawSmoothEllipsoid(x, y, z + 0.1, 0.4, 0.4, 0.1);
    drawSmoothSphere(x, y, 1 + z, 0.2);
}

void drawBishop(float x, float y, float z)
{
    drawSmoothCylinder(x, y, z, 0.5, 0.1);
    drawSmoothCylinder(x, y, z, 0.2, 0.5);
    drawSmoothEllipsoid(x, y, z + 0.1, 0.5, 0.5, 0.05);

    drawSmoothEllipsoid(x, y, z + 0.4, 0.5, 0.5, 0.4);
    drawSmoothEllipsoid(x, y, z + 0.425, 0.475, 0.475, 0.425);
    drawSmoothEllipsoid(x, y, z + 0.45, 0.45, 0.45, 0.45);
    drawSmoothEllipsoid(x, y, z + 0.475, 0.425, 0.425, 0.475);
    drawSmoothEllipsoid(x, y, z + 0.5, 0.4, 0.4, 0.5);

    drawSmoothCone(x, y, z + 0.4, 0.5, 1);
    drawSmoothSphere(x, y, 1.5 + z, 0.2);
}

int main()
{
    init();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );

    glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);

    float t = 0;
    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        gluLookAt(10*cos(t),10*sin(t),5+4*sin(t), 0,0,0, 0,0,4 );

        glColor3ub(255, 127, 0);
        drawSolidParalelepiped(0, 0, 0, 9, 9, 0.4);
        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 8; i++)
            {
                if((i+j)%2 == 0)
                    glColor3ub(0, 0, 0);
                else
                    glColor3ub(235, 235, 235);
                drawSolidParalelepiped(-3.5 + i, -3.5 + j, 0.1, 1, 1, 0.4);
            }
        }
        for(int i = 0; i < 8; i++)
        {
            glColor3ub(35, 35, 35);
            drawPawn(-3.5 + i, 2.5, 0.3);

            glColor3ub(235, 235, 235);
            drawPawn(-3.5 + i, -2.5, 0.3);
        }

        //drawBishop(2, 2, 2);

        glColor3f(0, 0, 0);
        drawOxyz();

        glfwSwapBuffers();
    }

    finit();
    return 0;
}

