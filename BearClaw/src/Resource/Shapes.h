#ifndef SHAPES_H
#define SHAPES_H

#include <Resource/Mesh.h>

namespace BearClaw {
VertexList GetSphereVerts(float Radius, int NumRings, int NumSectors);
IndexList GetSphereIndices(int NumRings, int NumSectors);
VertexList GetRectangularPrismVerts(f32 width, f32 height, f32 depth);
IndexList GetRectangularPrismIndices();
}

#endif