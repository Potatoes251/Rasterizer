#include "plan.h"

std::vector<Structures::Vertex> Structures::clipToPlane(const std::vector<Vertex>& polygone, const Plane& plane)
{
    std::vector<Vertex> clippedTringle;

    for (size_t i = 0; i < polygone.size(); ++i)
    {
        const Vertex& current = polygone[i];
        const Vertex& next = polygone[(i + 1) % polygone.size()];

        // Compute signed distance from the current and next vertices to the plane
        float currentDistance = (plane.m_normal.getX() * current.m_position.getX()) +
            (plane.m_normal.getY() * current.m_position.getY()) +
            (plane.m_normal.getZ() * current.m_position.getZ()) +
            plane.m_distance;
        float nextDistance = (plane.m_normal.getX() * next.m_position.getX()) +
            (plane.m_normal.getY() * next.m_position.getY()) +
            (plane.m_normal.getZ() * next.m_position.getZ()) +
            plane.m_distance;

        // If the current vertex is inside the plane, add it to the output
        if (currentDistance >= 0)
        {
            clippedTringle.push_back(current);
        }

        // If the current and next vertices are on opposite sides of the plane, compute the intersection
        if ((currentDistance < 0 && nextDistance >= 0) || (currentDistance >= 0 && nextDistance < 0))
        {
            float t = currentDistance / (currentDistance - nextDistance);

            Vertex intersection = interpolate(current, next, t);
            
            clippedTringle.push_back(intersection);
        }
    }
    return clippedTringle;
}

std::vector<std::vector<Structures::Vertex>> Structures::clipToPlanes(Vertex& v1, Vertex& v2, Vertex& v3)
{

    // Convert vertices to clip space
    std::vector<Vertex> input = { v1, v2, v3};
    std::vector<Vertex> output;

    std::vector<Plane> planes = {
        // Left plane: x + w >= 0
        Plane{ LibMath::Vector3(1, 0, 0), 1 },
        // Right plane: -x + w >= 0
        Plane{ LibMath::Vector3(-1, 0, 0), 1 },
        // Bottom plane: y + w >= 0
        Plane{ LibMath::Vector3(0, 1, 0), 1 },
        // Top plane: -y + w >= 0
        Plane{ LibMath::Vector3(0, -1, 0), 1},
        // Near plane: z + w >= 0
        Plane{ LibMath::Vector3(0, 0, 1), 1 },
        // Far plane: -z + w >= 0
        Plane{ LibMath::Vector3(0, 0, -1), 1 }
    };

    for (const auto& plane : planes)
    {
        output.clear();
        output = clipToPlane(input, plane);
        
        input = output;
    }

    // Triangulate the clipped polygon
    std::vector<std::vector<Vertex>> triangles = triangulatePolygone(input);

    return triangles;
}

std::vector<std::vector<Structures::Vertex>> Structures::triangulatePolygone(const std::vector<Vertex>& polygone)
{
    // Triangulate using fan methode
    std::vector<std::vector<Vertex>> triangles;
    if (polygone.size() >= 3)
    {
        for (size_t i = 1; i + 1 < polygone.size(); ++i)
        {
            triangles.push_back({ polygone[0], polygone[i], polygone[i + 1] });
        }
    }
    return triangles;
}

Structures::Vertex Structures::interpolate(const Structures::Vertex& currentVertex, const Structures::Vertex& nextVertex, const float t)
{
    Vertex intersection;

    intersection.m_position = currentVertex.m_position + (nextVertex.m_position - currentVertex.m_position) * t;
    intersection.m_color = currentVertex.m_color + (nextVertex.m_color - currentVertex.m_color) * t;
    intersection.m_normal = currentVertex.m_normal + (nextVertex.m_normal - currentVertex.m_normal) * t;
    intersection.m_u = currentVertex.m_u + (nextVertex.m_u - currentVertex.m_u) * t;
    intersection.m_v = currentVertex.m_v + (nextVertex.m_v - currentVertex.m_v) * t;

    return intersection;
}
