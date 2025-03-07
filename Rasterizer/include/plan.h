#ifndef PLAN_H
#define PLAN_H

#include "LibMath/Vector/Vector3.h"
#include <vector>
#include "vertex.h"

namespace Structures
{
    struct Plane 
    {
                                Plane(const LibMath::Vector3 normal, float distance) : m_normal(normal), m_distance(distance) {};

        LibMath::Vector3        m_normal;                  // Plane normal
        float                   m_distance;               // Distance from the origin
    };

    std::vector<Vertex>                     clipToPlane(const std::vector<Vertex>& polygone, const Plane& plane);

    std::vector<std::vector<Vertex>>        clipToPlanes(Vertex& v1, Vertex& v2, Vertex& v3);

    std::vector<std::vector<Vertex>>        triangulatePolygone(const std::vector<Vertex>& polygone);

    Structures::Vertex                      interpolate(const Structures::Vertex& currentVertex, const Structures::Vertex& nextVertex, const float t);
};



#endif // !PLAN_H