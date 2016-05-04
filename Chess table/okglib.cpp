#include <cstdlib>
#include <math.h>
#include <GL/glfw.h>
#include "okglib.h"

#define M_PI 3.141592

float random(float a, float b)
{
    return (rand()/(float)RAND_MAX)*(b-a)+a;
}

float irandom(int a, int b)
{
    return rand()%(b-a+1)+a;
}

float grad(float rad)
{
    return rad*M_PI/180.0;
}

bool running()
{
    return( !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED) );
}

void init()
{
    int width, height;

    glfwInit();
    if( !glfwOpenWindow( 1280, 720, 0, 0, 0, 0, 8, 0, GLFW_WINDOW ) ) return;

    glfwGetWindowSize( &width, &height );
    height = height > 0 ? height : 1;

    glViewport( 0, 0, width, height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.0f, -10.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f );
}

void finit()
{
    glfwTerminate();
}

void drawCube (float x,float y,float z,float a)
{
    a = a/2;
    glBegin( GL_LINE_LOOP );
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);

        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    glBegin( GL_LINE_LOOP );
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z+a);

        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    glBegin( GL_LINES );
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y+a, z-a);

        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);

        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y+a, z+a);

        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();
}

void drawSolidCube (float x,float y,float z,float a)
{
    a = a/2;

    // Рисуване на стена откъм -X
    glBegin( GL_POLYGON );
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x-a, y+a, z-a);
    glEnd();

    // Рисуване на стена откъм +X
    glBegin( GL_POLYGON );
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x+a, y-a, z-a);
        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    // Рисуване на стена откъм -Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x+a, y-a, z+a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    // Рисуване на стена откъм +Y
    glBegin( GL_POLYGON );
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y+a, z-a);
    glEnd();

    // Рисуване на стена откъм -Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x-a, y-a, z-a);
        glVertex3f(x-a, y+a, z-a);
        glVertex3f(x+a, y+a, z-a);
        glVertex3f(x+a, y-a, z-a);
    glEnd();

    // Рисуване на стена откъм +Z
    glBegin( GL_POLYGON );
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(x-a, y-a, z+a);
        glVertex3f(x-a, y+a, z+a);
        glVertex3f(x+a, y+a, z+a);
        glVertex3f(x+a, y-a, z+a);
    glEnd();
}

void drawOxyz()
{
    // Рисуване на лъчите
    glBegin( GL_LINES );
        // OX
        glVertex3f( 0.0, 0.0, 0.0 );
        glVertex3f( 5.0, 0.0, 0.0 );
        // OY
        glVertex3f( 0.0, 5.0, 0.0 );
        glVertex3f( 0.0, 0.0, 0.0 );
        // OZ
        glVertex3f( 0.0, 0.0, 5.0 );
        glVertex3f( 0.0, 0.0, 0.0 );
    glEnd();

    // Рисуване на стрелките
    glBegin( GL_TRIANGLES );
        // OX
        glVertex3f( 5.0, 0.0, 0.0 );
        glVertex3f( 4.5, 0.2, 0.0 );
        glVertex3f( 4.5,-0.2, 0.0 );
        // OY
        glVertex3f( 0.0, 5.0, 0.0 );
        glVertex3f( 0.2, 4.5, 0.0 );
        glVertex3f(-0.2, 4.5, 0.0 );
        // OZ
        glVertex3f( 0.0,  0.0,  5.0 );
        glVertex3f(+0.14,-0.14, 4.5 );
        glVertex3f(-0.14,+0.14, 4.5 );
    glEnd();
}

OKG_POINT point( float x, float y, float z)
{
    OKG_POINT p;
    p.x = x;
    p.y = y;
    p.z = z;
    return( p );
}

float distance( OKG_POINT a, OKG_POINT b)
{
    float dx = a.x-b.x;
    float dy = a.y-b.y;
    float dz = a.z-b.z;
    return( sqrt(dx*dx+dy*dy+dz*dz) );
}

void drawCircleXY( float x, float y, float z, float r )
{
    int n = 64;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    glBegin( GL_LINE_LOOP );
    for( int i=0; i<n; i++)
    {
        glVertex3f( x+r*cos(alpha), y+r*sin(alpha), z );
        alpha += dalpha;
    }
    glEnd();
}

void drawCircleXZ( float x, float y, float z, float r )
{
    int n = 64;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    glBegin( GL_LINE_LOOP );
    for( int i=0; i<n; i++)
    {
        glVertex3f( x+r*cos(alpha), y, z+r*sin(alpha) );
        alpha += dalpha;
    }
    glEnd();
}

void drawCircleYZ( float x, float y, float z, float r )
{
    int n = 64;
    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    glBegin( GL_LINE_LOOP );
    for( int i=0; i<n; i++)
    {
        glVertex3f( x, y+r*cos(alpha), z+r*sin(alpha) );
        alpha += dalpha;
    }
    glEnd();
}

void drawCylinder ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // Рисуване на околна стена
        glBegin( GL_LINE_LOOP );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        // Рисуване на парче от долната основа
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        // Рисуване на парче от горната основа
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        alpha += dalpha;
    }
}

void drawCone ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // Рисуване на околна стена
        glBegin( GL_LINE_LOOP );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x,     y,     z+h );
        glEnd();

        // Рисуване на парче от основата
        glBegin( GL_LINE_LOOP );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();
        alpha += dalpha;
    }
}

void drawSolidCylinder ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // Рисуване на околна стена
        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha+dalpha/2), sin(alpha+dalpha/2), 0 );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
        glEnd();

        // Рисуване на парче от долната основа
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        // Рисуване на парче от горната основа
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        alpha += dalpha;
    }
}

void drawSolidCone ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);
        float nx = cos(alpha+dalpha/2)*cosbeta;
        float ny = sin(alpha+dalpha/2)*cosbeta;
        float nz = sinbeta;

        // Рисуване на околна стена
        glBegin( GL_POLYGON );
            glNormal3f( nx, ny, nz );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x,     y,     z+h );
        glEnd();

        // Рисуване на парче от основата
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();
        alpha += dalpha;
    }
}

OKG_POINT spherical( float alpha, float beta, float r )
{
    OKG_POINT p;
    p.x = r*cos(alpha)*cos(beta);
    p.y = r*sin(alpha)*cos(beta);
    p.z = r*sin(beta);
    return p;
}

void drawSphere( float x, float y, float z, float r )
{
    int na = 32;
    int nb = 16;

    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            glBegin( GL_LINE_LOOP );

            OKG_POINT a = spherical(alpha,beta,r);
            OKG_POINT b = spherical(alpha+dalpha,beta,r);
            OKG_POINT c = spherical(alpha+dalpha,beta-dbeta,r);
            OKG_POINT d = spherical(alpha,beta-dbeta,r);

            glVertex3f(x+a.x,y+a.y,z+a.z);
            glVertex3f(x+b.x,y+b.y,z+b.z);
            glVertex3f(x+c.x,y+c.y,z+c.z);
            glVertex3f(x+d.x,y+d.y,z+d.z);
            glEnd( );
        }
    }
}

void drawSolidSphere( float x, float y, float z, float r )
{
    int na = 32;
    int nb = 16;

    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            glBegin( GL_POLYGON );

            OKG_POINT a = spherical(alpha,beta,r);
            OKG_POINT b = spherical(alpha+dalpha,beta,r);
            OKG_POINT c = spherical(alpha+dalpha,beta-dbeta,r);
            OKG_POINT d = spherical(alpha,beta-dbeta,r);

            OKG_POINT n = spherical(alpha+dalpha/2,beta-dbeta/2,0.8);
            glNormal3f(n.x,n.y,n.z);

            glVertex3f(x+a.x,y+a.y,z+a.z);
            glVertex3f(x+b.x,y+b.y,z+b.z);
            glVertex3f(x+c.x,y+c.y,z+c.z);
            glVertex3f(x+d.x,y+d.y,z+d.z);
            glEnd( );
        }
    }
}

void drawSmoothCylinder ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        // Рисуване на околна стена
        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha), sin(alpha), 0 );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx1, y+dy1, z );
            glNormal3f( cos(alpha+dalpha), sin(alpha+dalpha), 0 );
            glVertex3f( x+dx2, y+dy2, z );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        // Рисуване на парче от долната основа
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        // Рисуване на парче от горната основа
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, 1 );
            glVertex3f( x,     y,     z+h );
            glVertex3f( x+dx1, y+dy1, z+h );
            glVertex3f( x+dx2, y+dy2, z+h );
        glEnd();

        alpha += dalpha;
    }
}


void drawSmoothCone ( float x, float y, float z, float r, float h )
{
    int n = 32;

    float alpha = 0.0;
    float dalpha = 2*M_PI/n;

    for( int i=0; i<n; i++)
    {
        float dx1 = r*cos(alpha);
        float dy1 = r*sin(alpha);

        float dx2 = r*cos(alpha+dalpha);
        float dy2 = r*sin(alpha+dalpha);

        float cosbeta = h/sqrt(h*h+r*r);
        float sinbeta = r/sqrt(h*h+r*r);

        // Рисуване на околна стена
        glBegin( GL_POLYGON );
            glNormal3f( cos(alpha)*cosbeta, sin(alpha)*cosbeta, sinbeta );
            glVertex3f( x+dx1, y+dy1, z );

            glNormal3f( cos(alpha+dalpha)*cosbeta, sin(alpha+dalpha)*cosbeta, sinbeta );
            glVertex3f( x+dx2, y+dy2, z );

            glNormal3f( 2*cos(alpha+dalpha/2)*cosbeta, 2*sin(alpha+dalpha/2)*cosbeta, 2*sinbeta );
            glVertex3f( x,     y,     z+h );
        glEnd();

        // Рисуване на парче от основата
        glBegin( GL_POLYGON );
            glNormal3f( 0, 0, -1 );
            glVertex3f( x,     y,     z );
            glVertex3f( x+dx1, y+dy1, z );
            glVertex3f( x+dx2, y+dy2, z );
        glEnd();

        alpha += dalpha;
    }
}

void drawSmoothSphere( float x, float y, float z, float r )
{
    int na = 48;
    int nb = 24;

    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            OKG_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+r*p.x,y+r*p.y,z+r*p.z);

            glEnd( );
        }
    }
}

void drawSmoothEllipsoid( float x, float y, float z, float rx, float ry, float rz )
{
    int na = 48;
    int nb = 24;

    float alpha;
    float dalpha = 2.0*M_PI/na;
    float beta;
    float dbeta = 1.0*M_PI/nb;

    beta = M_PI/2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = 0;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            OKG_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            glEnd( );
        }
    }
}

void drawSmoothEllipsoidPatch(
        float x, float y, float z,     // координати
        float rx, float ry, float rz,  // размери
        float a1, float a2,            // хоризонтален диапазон
        float b1, float b2             // вертикален диапазон
    )
{
    int na = 32;
    int nb = 16;

    float alpha;
    float dalpha = (a2-a1)/na;
    float beta;
    float dbeta = (b2-b1)/nb;

    beta = b2;
    for( int j=0; j<nb; j++, beta-=dbeta)
    {
        alpha = a1;
        for( int i=0; i<na; i++, alpha+=dalpha)
        {
            OKG_POINT p;
            glBegin( GL_POLYGON );

            p = spherical(alpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha+dalpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            p = spherical(alpha,beta-dbeta,1);
            glNormal3f(p.x,p.y,p.z);
            glVertex3f(x+rx*p.x,y+ry*p.y,z+rz*p.z);

            glEnd( );
        }
    }
}

