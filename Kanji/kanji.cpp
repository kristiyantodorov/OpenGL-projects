#include <cstdlib>
#include <iostream>
#include <GL/glfw.h>
#include <cmath>

bool running()
{
    return( !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED ) );
}

void init()
{
    int width, height;

    glfwInit();
    if( !glfwOpenWindow( 1600, 900, 0, 0, 0, 0, 8, 0, GLFW_WINDOW ) ) return;

    glfwGetWindowSize( &width, &height );
    height = height > 0 ? height : 1;

    glViewport( 0, 0, width, height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.0f, -6.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f );
}

void finit()
{
    glfwTerminate();
}

void drawSector(float x, float y, float z, float r, float alpha_start, float alpha_end, float width, float offset)
{
    int n = 64;
    float step = 2*M_PI/n;
    float alpha = alpha_start;

    glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(0, -1, 0);
        glVertex3f(x + r*cos(alpha), y - offset, z + r*sin(alpha));
        glVertex3f(x + (r+width)*cos(alpha), y - offset, z + (r+width)*sin(alpha));
        while(alpha < alpha_end)
        {
            glVertex3f(x + r*cos(alpha), y - offset, z + r*sin(alpha));
            glVertex3f(x + (r+width)*cos(alpha), y - offset, z + (r+width)*sin(alpha));
            alpha += step;
        }
        glVertex3f(x + r*cos(alpha_end), y - offset, z + r*sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), y - offset, z + (r+width)*sin(alpha_end));
    glEnd();

    alpha = alpha_start;
    glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(0, +1, 0);
        glVertex3f(x + r*cos(alpha), -y + offset, z + r*sin(alpha));
        glVertex3f(x + (r+width)*cos(alpha), -y + offset, z + (r+width)*sin(alpha));
        while(alpha < alpha_end)
        {
            glVertex3f(x + r*cos(alpha), -y + offset, z + r*sin(alpha));
            glVertex3f(x + (r+width)*cos(alpha), -y + offset, z + (r+width)*sin(alpha));
            alpha += step;
        }
        glVertex3f(x + r*cos(alpha_end), -y + offset, z + r*sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), -y + offset, z + (r+width)*sin(alpha_end));
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(sin(alpha_start), 0, -cos(alpha_start));
        glVertex3f(x + r*cos(alpha_start), y - offset, z + r*sin(alpha_start));
        glVertex3f(x + r*cos(alpha_start), y + offset, z + r*sin(alpha_start));
        glVertex3f(x + (r+width)*cos(alpha_start), y + offset, z + (r+width)*sin(alpha_start));
        glVertex3f(x + (r+width)*cos(alpha_start), y - offset, z + (r+width)*sin(alpha_start));
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-sin(alpha_end), 0, cos(alpha_end));
        glVertex3f(x + r*cos(alpha_end), y - offset, z + r*sin(alpha_end));
        glVertex3f(x + r*cos(alpha_end), y + offset, z + r*sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), y + offset, z + (r+width)*sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), y - offset, z + (r+width)*sin(alpha_end));
    glEnd();

    alpha = alpha_start;
    glBegin(GL_QUAD_STRIP);
        while(alpha < alpha_end)
        {
            glNormal3f(-cos(alpha), 0, -sin(alpha));
            glVertex3f(x + r*cos(alpha), y - offset, z + r*sin(alpha));
            glVertex3f(x + r*cos(alpha), y + offset, z + r*sin(alpha));
            alpha += step;
        }
        glNormal3f(-cos(alpha_end), 0, -sin(alpha_end));
        glVertex3f(x + r*cos(alpha_end), y - offset, z + r*sin(alpha_end));
        glVertex3f(x + r*cos(alpha_end), y + offset, z + r*sin(alpha_end));
    glEnd();

    alpha = alpha_start;
    glBegin(GL_QUAD_STRIP);
        while(alpha < alpha_end)
        {
            glNormal3f(cos(alpha), 0, sin(alpha));
            glVertex3f(x + (r+width)*cos(alpha), y - offset, z + (r+width)*sin(alpha));
            glVertex3f(x + (r+width)*cos(alpha), y + offset, z + (r+width)*sin(alpha));
            alpha += step;
        }
        glNormal3f(cos(alpha_end), 0, sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), y - offset, z + (r+width)*sin(alpha_end));
        glVertex3f(x + (r+width)*cos(alpha_end), y + offset, z + (r+width)*sin(alpha_end));
    glEnd();

}

void drawBlock (float x, float y, float z, float width, float lenght)
{
    glBegin( GL_POLYGON );
        glNormal3f(0, -1, 0);
        glVertex3f(x - width, y - 0.5, z - lenght);
        glVertex3f(x - width, y - 0.5, z + lenght);

        glVertex3f(x + width, y - 0.5, z + lenght);
        glVertex3f(x + width, y - 0.5, z - lenght);
    glEnd();
    glBegin( GL_POLYGON );
        glNormal3f(0, 1, 0);
        glVertex3f(x - width, y + 0.5, z - lenght);
        glVertex3f(x - width, y + 0.5, z + lenght);

        glVertex3f(x + width, y + 0.5, z + lenght);
        glVertex3f(x + width, y + 0.5, z - lenght);
    glEnd();
    glBegin( GL_POLYGON );
        glNormal3f(0, 0, +1);
        glVertex3f(x - width, y + 0.5, z + lenght);
        glVertex3f(x + width, y + 0.5, z + lenght);

        glVertex3f(x + width, y - 0.5, z + lenght);
        glVertex3f(x - width, y - 0.5, z + lenght);
    glEnd();
    glBegin( GL_POLYGON );
        glNormal3f(0, 0, -1);
        glVertex3f(x - width, y + 0.5, z - lenght);
        glVertex3f(x + width, y + 0.5, z - lenght);

        glVertex3f(x + width, y - 0.5, z - lenght);
        glVertex3f(x - width, y - 0.5, z - lenght);
    glEnd();
    glBegin( GL_POLYGON );
        glNormal3f(+1, 0, 0);
        glVertex3f(x + width, y + 0.5, z + lenght);
        glVertex3f(x + width, y - 0.5, z + lenght);

        glVertex3f(x + width, y - 0.5, z - lenght);
        glVertex3f(x + width, y + 0.5, z - lenght);
    glEnd();
    glBegin( GL_POLYGON );
        glNormal3f(-1, 0, 0);
        glVertex3f(x - width, y + 0.5, z + lenght);
        glVertex3f(x - width, y - 0.5, z + lenght);

        glVertex3f(x - width, y - 0.5, z - lenght);
        glVertex3f(x - width, y + 0.5, z - lenght);
    glEnd();

}

int main()
{
    init();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_DEPTH_TEST );

    glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0, 0.7, 0.0);

    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );
        glRotatef( 0.1, 0.0, 0.5, 1.0);

        drawBlock(-1, 0.0, 0.3, 0.15, 2.3);
        drawBlock(-1.05, 0.0, 1.3, 1.0, 0.15);
        drawBlock(1.6, 0.0, 1.5, 1.6, 0.15);

        drawBlock(1.6, 0.0, 0.9, 1, 0.15);
        drawBlock(1.6, 0.0, 0.1, 1, 0.15);
        drawBlock(0.75, 0.0, 0.5, 0.15, 0.25);
        drawBlock(2.45, 0.0, 0.5, 0.15, 0.25);

        drawBlock(1.6, 0.0, -0.4, 1.6, 0.15);
        drawBlock(0.15, 0.0, -1.30, 0.15, 0.75);
        drawBlock(3.05, 0.0, -1.05, 0.15, 0.55);
        drawBlock(2.5, 0.0, -1.85, 0.3, 0.15);

        drawBlock(1.6, 0.0, -0.9, 0.5, 0.15);
        drawBlock(1.6, 0.0, -1.4, 0.5, 0.15);
        drawBlock(1.25, 0.0, -1.15, 0.15, 0.1);
        drawBlock(1.95, 0.0, -1.15, 0.15, 0.1);

        drawSector(-4.15, 0.0, 1.0, 3.0, -M_PI/4, 0.0, 0.3, 0.5);
        drawSector(-2.3, 0.0, -2.5, 3.0, M_PI/4, M_PI/3, 0.3, 0.5);
        drawSector(0.25, 0.0, 8.3, 6.0, -M_PI/2, -4.5*M_PI/12, 0.3, 0.5);
        drawSector(-1.75, 0.0, 3.0, 3.0, -4*M_PI/13, -M_PI/13, 0.3, 0.5);
        drawSector(5.0, 0.0, 3.0, 3.0, -11*M_PI/13, -9*M_PI/13, 0.3, 0.5);
        drawSector(2.8, 0.0, -1.6, 0.1, -M_PI/2, 0, 0.3, 0.5);
        glfwSwapBuffers();
    }

    finit();
    return 0;
}
