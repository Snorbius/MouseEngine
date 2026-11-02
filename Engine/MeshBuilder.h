#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct BuiltMeshData
{
    std::vector<float> vertexData;
    std::vector<int> indices;
};

class MeshBuilder
{
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> indices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> uvs;

    /**
     * Calculate and populate the normals vector based on current vertices/indices. This will overwrite any existing normals.
     */
    void CalculateNormals();

    /**
     * Returns the resulting vertex data by combining all relevant properties. Any empty property will be replaced by a default value.
     * @return The result
     */
    BuiltMeshData BuildMesh();
};
