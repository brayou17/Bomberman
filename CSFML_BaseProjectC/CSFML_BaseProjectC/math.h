#pragma once
#include "tools.h"

#define EPSILON (float)1e-6
#define MAX (a,b) a >= b ? a : b
#define MIN (a,b) a <= b ? a : b
#define DEG2RAD 0.01745329
#define RAD2DEG 57.295779
#define PI 3.141592
#define LERP(a, b, t) (b-a) * t +a
#define MAX(a,b) a >= b ? a : b
#define MIN(a,b) a <= b ? a : b
#define SIGN(nbr) nbr >= 0.f ? 1.f : -1.f

/// <summary>
/// Create a vector between 2 given float vectors
/// </summary>
/// <param name="a">the start vector</param>
/// <param name="b">the end vector</param>
/// <returns>the vector going from a to b</returns>
sfVector2f createVectorWithVectorf(sfVector2f a, sfVector2f b);

/// <summary>
/// Create a vector between 2 given int vectors
/// </summary>
/// <param name="a">the start vector</param>
/// <param name="b">the end vector</param>
/// <returns>the vector going from a to b</returns>
sfVector2i createVectorWithVectori(sfVector2i a, sfVector2i b);

/// <summary>
/// add 2 float vectors together
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the adition between those 2 vectors</returns>
sfVector2f addVectorsrf(sfVector2f a, sfVector2f b);

/// <summary>
/// add 2 int vectors together
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the adition between those 2 vectors</returns>
sfVector2i addVectorsri(sfVector2i a, sfVector2i b);

/// <summary>
/// add 2 float vectors together and put the result in the first vector
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
void addVectorsf(sfVector2f* a, sfVector2f b);

/// <summary>
/// add 2 int vectors together and put the result in the first vector
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
void addVectorsi(sfVector2i* a, sfVector2i b);

/// <summary>
/// substract 2 float vectors together
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the substraction between those 2 vectors</returns>
sfVector2f substractVectorsrf(sfVector2f a, sfVector2f b);

/// <summary>
/// substract 2 int vectors together
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the substraction between those 2 vectors</returns>
sfVector2i substractVectorsri(sfVector2i a, sfVector2i b);

/// <summary>
/// substract 2 float vectors together and store the result in the first vector
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the substraction between those 2 vectors</returns>
void substractVectorsf(sfVector2f* a, sfVector2f b);

/// <summary>
/// substract 2 int vectors together and store the result in the first vector
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the substraction between those 2 vectors</returns>
void substractVectorsi(sfVector2i* a, sfVector2i b);

/// <summary>
/// calculate the dot product of 2 float vectors
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the dot product</returns>
float dotProductf(sfVector2f a, sfVector2f b);

/// <summary>
/// calculate the dot product of 2 int vectors
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the dot product</returns>
int dotProducti(sfVector2i a, sfVector2i b);

/// <summary>
/// get the magnitude of a float vector
/// </summary>
/// <param name="a">the vector</param>
/// <returns>the magnitude of a</returns>
float getMagnitudef(sfVector2f a);

/// <summary>
/// get the magnitude of a int vector
/// </summary>
/// <param name="a">the vector</param>
/// <returns>the magnitude of a</returns>
int getMagnitudei(sfVector2i a);

/// <summary>
/// get the squared magnitude of a float vector
/// </summary>
/// <param name="a">the vector</param>
/// <returns>the squared magnitude of a</returns>
float getSqrMagnitudef(sfVector2f a);

/// <summary>
/// get the squared magnitude of a float vector
/// </summary>
/// <param name="a">the vector</param>
/// <returns>the squared magnitude of a</returns>
int getSqrMagnitudei(sfVector2i a);

float getSqrMagnitudeBetween2Vectorsf(sfVector2f _a, sfVector2f _b);
float getMagnitudeBetween2Vectorsf(sfVector2f _a, sfVector2f _b);


/// <summary>
/// normalize a float vector
/// </summary>
/// <param name="a">the vector to normalize</param>
/// <returns>the normalized vector</returns>
sfVector2f normalizef(sfVector2f a);

sfVector2f getNormBetween2Vectorsf(sfVector2f _a, sfVector2f _b);

/// <summary>
/// Multiply a float vector by a float number and store the result in the vector
/// </summary>
/// <param name="a">The vector</param>
/// <param name="m">The number to multiply the vector by</param>
void multiplyVectorsf(sfVector2f* a, float m);

/// <summary>
/// Multiply a int vector by a int number and store the result in the vector
/// </summary>
/// <param name="a">The vector</param>
/// <param name="m">The number to multiply the vector by</param>
void multiplyVectorsi(sfVector2i* a, int m);

/// <summary>
/// Multiply a float vector by a float number
/// </summary>
/// <param name="a">The vector</param>
/// <param name="m">The number to multiply the vector by</param>
/// <returns>the multiplied vector</returns>
sfVector2f multiplyVectorsrf(sfVector2f a, float m);

/// <summary>
/// Multiply a int vector by a int number
/// </summary>
/// <param name="a">The vector</param>
/// <param name="m">The number to multiply the vector by</param>
/// <returns>the multiplied vector</returns>
sfVector2i multiplyVectorsri(sfVector2i a, int m);

/// <summary>
/// check if 2 vectors are equal to eachother
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>sftrue if they are equals, sffalse if otherwise</returns>
sfBool equals(sfVector2f a, sfVector2f b);

/// <summary>
/// check if an object is in the fov of another object
/// </summary>
/// <param name="targetObject">the pos of the object targeted</param>
/// <param name="lookingObject">the pos of the looking object</param>
/// <param name="forwardE">the forward of the looking object</param>
/// <param name="angle">the angle of the fov used for the size of it</param>
/// <param name="dist">the max dist of the fov</param>
/// <returns>true if the looking object is in fov false if otherwise</returns>
sfBool isInFOV(sfVector2f targetObject, sfVector2f lookingObject, sfVector2f forwardE, float angle, float dist);

/// <summary>
/// calculate a position with an angle and a distance
/// </summary>
/// <param name="a">the initial pos</param>
/// <param name="r">the distance</param>
/// <param name="teta">the angle</param>
/// <returns>the new pos</returns>
sfVector2f polarCoord(sfVector2f a, float r, float teta);

/// <summary>
/// display the fov
/// </summary>
/// <param name="FOV">a vertex array</param>
/// <param name="teta">the angle of the fov</param>
/// <param name="rad">the radius of the fov</param>
/// <param name="pos">the pos of the looking object</param>
/// <param name="forward">the forward of the looking object</param>
void makeFOV(sfVertexArray* FOV, float teta, float rad, sfVector2f pos, sfVector2f forward);

/// <summary>
/// give you half of a vector
/// </summary>
/// <param name="a">the initial vector</param>
/// <returns>half of a</returns>
sfVector2f getHalflVectorsrf(sfVector2f a);

/// <summary>
/// get the angle between 2 vectors
/// </summary>
/// <param name="a">the first vector</param>
/// <param name="b">the 2nd vector</param>
/// <returns>the angle between those 2 vectors in radiant</returns>
float getAngleBetweenVectors(sfVector2f a, sfVector2f b);

/// <summary>
/// create a float vector
/// </summary>
/// <param name="_x">the x pos</param>
/// <param name="_y">the y pos</param>
/// <returns>the vector</returns>
sfVector2f vector2f(float _x, float _y);

sfVector2f pointSegmentDistance(sfVector2f _circleCenter, sfVector2f _point1, sfVector2f _point2, float* _sqrDist);

sfVector2f getCustomPoint(sfVector2f circleMiddle, float angle, float dist, int pointToGet);
sfVector2f getfWorldMousePos(sfRenderWindow* _window);
sfVector2f getfMousePos(sfRenderWindow* _window);