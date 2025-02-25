#ifndef PLAN_H
#define PLAN_H

#include "LibMath/Vector/Vector3.h"
#include <vector>
#include "vertex.h"

namespace Structures
{
    struct Plane {
        Plane(const LibMath::Vector3 normal, float distance) : m_normal(normal), m_distance(distance) {};

        LibMath::Vector3 m_normal; // Plane normal (unit vector)
        float m_distance;   // Distance from the origin
    };

    LibMath::Vector3 intersectLinePlane(const LibMath::Vector3& P1, const LibMath::Vector3& P2, const Plane& plane);

    std::vector<Vertex> clipToPlane(const std::vector<Vertex>& polygone, const Plane& plane);

    std::vector<std::vector<Vertex>> clipToPlanes(Vertex& v1, Vertex& v2, Vertex& v3);

    float signedDistancePointPlane(const LibMath::Vector3& point, const Plane& plane);

};



#endif // !PLAN_H

