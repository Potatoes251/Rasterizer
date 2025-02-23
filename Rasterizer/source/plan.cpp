#include "plan.h"

LibMath::Vector3 Structures::intersectLinePlane(const LibMath::Vector3& P1, const LibMath::Vector3& P2, const Plane& plane)
{
    LibMath::Vector3 lineDir = P2 - P1; // Direction of the line
    float denom = plane.m_normal.dot(lineDir);

    if (fabs(denom) < 1e-6) {
        throw std::runtime_error("Line is parallel to the plane, no intersection.");
    }

    float t = -(plane.m_normal.dot(P1) + plane.m_distance) / denom;

    LibMath::Vector3 intersection = P1 + (lineDir * t);

    std::cout << "intersection point: x->" << intersection.getX() << " y->" << intersection.getY() << " z->" << intersection.getZ() << '\n';

    return intersection;
}

std::vector<Structures::Vertex> Structures::clipToPlane(const std::vector<Vertex>& polygone, const Plane& plane)
{
    std::vector<Vertex> clippedPolygone;

    for (size_t i = 0; i < polygone.size(); i++)
    {
        // comput the current and the next vertex
        const Vertex& currentVertex = polygone[i];
        const Vertex& nextVertex = polygone[(i + 1) % polygone.size()];

        // signed distance of both verteces to plane

        float currentDistance = signedDistancePointPlane(currentVertex.m_position, plane);
        float nextDistance = signedDistancePointPlane(nextVertex.m_position, plane);

        // both are inside the frustrum
        if (currentDistance > 0  && nextDistance > 0)
        {
            //only add second vertex
            clippedPolygone.push_back(nextVertex);
        }
        // only current is outside
        else if(currentDistance <= 0 && nextDistance > 0)
        {
            LibMath::Vector3 intersectionPoint = intersectLinePlane(currentVertex.m_position, nextVertex.m_position, plane);


            // add intersection point and next vertex
            clippedPolygone.push_back({ intersectionPoint, currentVertex.m_color });
            clippedPolygone.push_back(nextVertex);
        }
        // only next vertex is outside
        else if (currentDistance > 0 && nextDistance <=0)
        {
            LibMath::Vector3 intersectionPoint = intersectLinePlane(currentVertex.m_position, nextVertex.m_position, plane);

            clippedPolygone.push_back({ intersectionPoint, currentVertex.m_color });
        }
        // both outside
    }

    return clippedPolygone;
}

std::vector<Structures::Vertex> Structures::clipToPlanes(const std::vector<Vertex>& polygone)
{
    std::vector<Plane> clipSpacePlanes = {
        // Left plane: x + w >= 0
        Plane{ LibMath::Vector3(1, 0, 0), 1 },
        // Right plane: -x + w >= 0
        Plane{ LibMath::Vector3(-1, 0, 0), 1 },
        // Bottom plane: y + w >= 0
        Plane{ LibMath::Vector3(0, 1, 0), 1 },
        // Top plane: -y + w >= 0
        Plane{ LibMath::Vector3(1, -1, 0), 1 },
        // Near plane: z + w >= 0
        Plane{ LibMath::Vector3(0, 0, 1), 1 },
        // Far plane: -z + w >= 0
        Plane{ LibMath::Vector3(0, 0, -1), 1 }
    };

    std::vector<Structures::Vertex> clippedPolygon = polygone;

    for (const auto& plane : clipSpacePlanes) {
        clippedPolygon = clipToPlane(clippedPolygon, plane);
        if (clippedPolygon.empty()) {
            break; // The polygon is completely outside the frustum
        }
    }

    return clippedPolygon;
}



float Structures::signedDistancePointPlane(const LibMath::Vector3& point, const Plane& plane) 
{
    return (plane.m_normal.dot(point) + plane.m_distance) / plane.m_normal.magnitude();
}