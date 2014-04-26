#ifndef SHAPES_H
#define SHAPES_H

#include <Resource/Mesh.h>

namespace BearClaw {
VertexList GetSphereVerts(float Radius, int NumRings, int NumSectors);
IndexList GetSphereIndices(int NumRings, int NumSectors);
}

#endif