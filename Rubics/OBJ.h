#ifndef OBJ__H
#define OBJ__H

#include "Mesh.h"

void writeOBJ(Mesh* mesh, const char* filename);
Mesh* loadOBJ(const char* filename);

#endif