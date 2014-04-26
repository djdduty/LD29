#include <Resource/Shapes.h>

namespace BearClaw {
VertexList GetSphereVerts(float Radius, int NumRings, int NumSectors)
{
    VertexList Data;
    int Items = 0;
    for(int r = 0; r <= NumRings; r++)
    {
        f32 Theta = r * PI / NumRings;
        f32 SinTheta = sin(Theta);
        f32 CosTheta = cos(Theta);
        for(int s = 0; s <= NumSectors; s++)
        {
            f32 Phi = s * 2 * PI / NumSectors;
            f32 SinPhi = sin(Phi);

            f32 x = cos(Phi) * SinTheta;
            f32 y = CosTheta;
            f32 z = -(SinPhi * SinTheta);

            f32 u = s * (1.0/NumSectors);
            f32 v = r * (1.0/NumRings);

            Data.push_back(Vertex(Vec3(x*Radius,y*Radius,z*Radius), Vec3(x,y,z), Vec2(u,v)));
            Items++;
        }
    }

    return Data;
}

IndexList GetSphereIndices(int NumRings, int NumSectors)
{
    IndexList Indices;
    for(int r = 0; r < NumRings; r++) for(int s = 0; s < NumSectors; s++)
    {
        int first = r* (NumSectors + 1) + s;
        int second = first + NumSectors + 1;
        int third = first+1;

        Indices.push_back(first);
        Indices.push_back(second);
        Indices.push_back(third);

        Indices.push_back(second);
        Indices.push_back(second+1);
        Indices.push_back(third);
    }

    return Indices;
}


}