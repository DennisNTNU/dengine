#pragma once

/* 
 *
 * @param n Latitudinal subdivisions
 * @param m Longitudinal subdivisions
 * @param r Radius of sphere geometry
 */
void initVAOSphere(unsigned int * vaoID, unsigned int * indexCount, unsigned char n, unsigned char m, float r);

void initVAOSphereNoNormals(unsigned int * vaoID, unsigned int * indexCount, unsigned char n, unsigned char m, float r);

void initVAOSphere_MinimalVertexCount(unsigned int * vaoID, unsigned int * indexCount, unsigned char n, unsigned char m, float r);