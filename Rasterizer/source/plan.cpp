#include "plan.h"

LibMath::Vector3 Structures::intersectLinePlane(const LibMath::Vector3& P1, const LibMath::Vector3& P2, const Plane& plane)
{
    LibMath::Vector3 lineDir = P2 - P1; // Direction of the line
    float denom = plane.m_normal.dot(lineDir);

    //if (fabs(denom) < 1e-6) {
    //    throw std::runtime_error("Line is parallel to the plane, no intersection.");
    //}

    float t = -(plane.m_normal.dot(P1) + plane.m_distance) / denom;

    LibMath::Vector3 intersection = P1 + (lineDir * t);

    //std::cout << "intersection point: x->" << intersection.getX() << " y->" << intersection.getY() << " z->" << intersection.getZ() << '\n';

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

        //// Check if the current vertex is inside the plane
        //float currentDot = current.dot(plane.first) + plane.second.m_w;
        //float nextDot = next.dot(plane.first) + plane.second.m_w;

        //if (currentDot >= 0) output.push_back(current); // Inside

        //if (currentDot * nextDot < 0)
        //{ // Intersection
        //    float t = currentDot / (currentDot - nextDot);
        //    output.push_back(current + (next - current) * t);
        //}

        if (currentDistance > 0)
        {
            clippedPolygone.push_back(currentVertex);
        }

        if (currentDistance * nextDistance < 0)
        {
            float t = currentDistance / (currentDistance - nextDistance);
            Vertex intersection;
            intersection.m_position = currentVertex.m_position + (nextVertex.m_position - currentVertex.m_position) * t;
            intersection.m_color = currentVertex.m_color;
            //intersection.m_color = currentVertex.m_color + (nextVertex.m_color - currentVertex.m_color) * t;
            //intersection.m_normal = currentVertex.m_normal + (next.m_normal - current.m_normal) * t;
            /*intersection.m_u = current.m_u + (next.m_u - current.m_u) * t;
            intersection.m_v = current.m_v + (next.m_v - current.m_v) * t;*/

            LibMath::Vector3 intersectionPoint = intersectLinePlane(currentVertex.m_position, nextVertex.m_position, plane);

            clippedPolygone.push_back({ intersectionPoint, currentVertex.m_color });
        }

        //// both are inside the frustrum
        //if (currentDistance > 0  && nextDistance > 0)
        //{
        //    //only add second vertex
        //    clippedPolygone.push_back(nextVertex);
        //}
        //// only current is outside
        //else if(currentDistance <= 0 && nextDistance > 0)
        //{
        //    LibMath::Vector3 intersectionPoint = intersectLinePlane(currentVertex.m_position, nextVertex.m_position, plane);


        //    // add intersection point and next vertex
        //    clippedPolygone.push_back({ intersectionPoint, currentVertex.m_color });
        //    clippedPolygone.push_back(nextVertex);
        //}
        //// only next vertex is outside
        //else if (currentDistance > 0 && nextDistance <=0)
        //{
        //    LibMath::Vector3 intersectionPoint = intersectLinePlane(currentVertex.m_position, nextVertex.m_position, plane);

        //    clippedPolygone.push_back({ intersectionPoint, currentVertex.m_color });
        //}
        //// both outside
    }

    return clippedPolygone;
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
        for (size_t i = 0; i < input.size(); ++i)
        {
            const Vertex& current = input[i];
            const Vertex& next = input[(i + 1) % input.size()];

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
                output.push_back(current);
            }

            // If the current and next vertices are on opposite sides of the plane, compute the intersection
            if ((currentDistance < 0 && nextDistance >= 0) || (currentDistance >= 0 && nextDistance < 0))
            {
                float t = currentDistance / (currentDistance - nextDistance);
                Vertex intersection;
                intersection.m_position = current.m_position + (next.m_position - current.m_position) * t;
                //intersection.m_color = current.m_color;

                intersection.m_color = current.m_color + (next.m_color - current.m_color) * t;
                intersection.m_normal = current.m_normal + (next.m_normal - current.m_normal) * t;
                intersection.m_u = current.m_u + (next.m_u - current.m_u) * t;
                intersection.m_v = current.m_v + (next.m_v - current.m_v) * t;

                output.push_back(intersection);
            }
        }
        input = output;
    }

    // Triangulate the clipped polygon
    std::vector<std::vector<Vertex>> triangles;
    if (input.size() >= 3)
    {
        for (size_t i = 1; i + 1 < input.size(); ++i)
        {
            triangles.push_back({ input[0], input[i], input[i + 1] });
        }
    }

    return triangles;

    //std::vector<Plane> clipSpacePlanes = {
    //    // Left plane: x + w >= 0
    //    Plane{ LibMath::Vector3(1, 0, 0), 1 },
    //    // Right plane: -x + w >= 0
    //    Plane{ LibMath::Vector3(-1, 0, 0), 1 },
    //    // Bottom plane: y + w >= 0
    //    Plane{ LibMath::Vector3(0, 1, 0), 1 },
    //    // Top plane: -y + w >= 0
    //    Plane{ LibMath::Vector3(1, -1, 0), 1 },
    //    // Near plane: z + w >= 0
    //    Plane{ LibMath::Vector3(0, 0, 1), 1 },
    //    // Far plane: -z + w >= 0
    //    Plane{ LibMath::Vector3(0, 0, -1), 1 }
    //};

    //std::vector<Structures::Vertex> clippedPolygon = polygone;

    //for (const auto& plane : clipSpacePlanes) {
    //    clippedPolygon = clipToPlane(clippedPolygon, plane);
    //    if (clippedPolygon.empty()) {
    //        break; // The polygon is completely outside the frustum
    //    }
    //}

    //// Triangulate the clipped polygon
    //std::vector<std::vector<Vertex>> triangles;
    //if (clippedPolygon.size() >= 3)
    //{
    //    for (size_t i = 1; i + 1 < clippedPolygon.size(); ++i)
    //    {
    //        triangles.push_back({ clippedPolygon[0], clippedPolygon[i], clippedPolygon[i + 1] });
    //    }
    //}

    return triangles;
}



float Structures::signedDistancePointPlane(const LibMath::Vector3& point, const Plane& plane) 
{
    return ((plane.m_normal.dot(point) + plane.m_distance) / plane.m_normal.magnitude()) + plane.m_distance;
}