#include "structures.h"

Structures::Mesh* Structures::Mesh::createCube()
{
	Mesh* cubeMesh = new Mesh();

	std::vector<Structures::Vertex> cube;

    static const float coordinates[][3] = {
     { +0.5, +0.5, -0.5}, // Back-top-right
    {-0.5, +0.5, -0.5}, // Back-top-left
    {+0.5, -0.5, -0.5}, // Back-bottom-right
    {-0.5, -0.5, -0.5}, // Back-bottom-left
    {-0.5, -0.5, +0.5}, // Front-bottom-left
    {-0.5, +0.5, -0.5}, // Back-top-left
    {-0.5, +0.5, +0.5}, // Front-top-left
    {+0.5, +0.5, -0.5}, // Back-top-right
    {+0.5, +0.5, +0.5}, // Front-top-right
    {+0.5, -0.5, -0.5}, // Back-bottom-right
    {+0.5, -0.5, +0.5}, // Front-bottom-right
    {-0.5, -0.5, +0.5}, // Front-bottom-left
    {+0.5, +0.5, +0.5}, // Front-top-right
    {-0.5, +0.5, +0.5}, // Front-top-left
    };

	
	return nullptr;
}

Structures::Vertex::Vertex(float x, float y, float z)
{
	m_position = LibMath::Vector3(x, y, z);
}
