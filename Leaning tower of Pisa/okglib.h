#ifndef OKGLIB_H_INCLUDED
#define OKGLIB_H_INCLUDED

struct OKG_POINT
{
    float x;
    float y;
    float z;
} ;

extern int na;
extern int nb;

bool running();
void init();
void finit();
float random(float a, float b);
float irandom(int a, int b);
OKG_POINT spherical( float alpha, float beta, float r );
float grad(float rad);

// Рисуване на координатна система
void drawOxyz();

// Рисуване на окръжности
void drawCircleXY( float x, float y, float z, float r );
void drawCircleYZ( float x, float y, float z, float r );
void drawCircleXZ( float x, float y, float z, float r );
void drawSolidCircleXY( float x, float y, float z, float r );;

// Рисуване на куб
void drawCube( float x, float y, float z, float a );
void drawSolidCube ( float x, float y, float z, float a );
void drawSolidParalelogram (float x,float y,float z,float ax,float ay,float az);

// Рисуване на цилиндър
void drawCylinder( float x, float y, float z, float r, float h );
void drawSolidCylinder( float x, float y, float z, float r, float h );
void drawSmoothCylinder ( float x, float y, float z, float r, float h );

// Рисуване на конус
void drawCone( float x, float y, float z, float r, float h );
void drawSolidCone ( float x, float y, float z, float r, float h );
void drawSmoothCone ( float x, float y, float z, float r, float h );

// Рисуване на сфера
void drawSphere( float x, float y, float z, float r );
void drawSolidSphere( float x, float y, float z, float r );
void drawSmoothSphere( float x, float y, float z, float r );

// Рисуване на елипсоид
void drawSmoothEllipsoid( float x, float y, float z, float rx, float ry, float rz );
void drawSmoothEllipsoidPatch( float x, float y, float z, float rx, float ry, float rz, float a1, float a2, float b1, float b2 );

#endif // OKGLIB_H_INCLUDED
