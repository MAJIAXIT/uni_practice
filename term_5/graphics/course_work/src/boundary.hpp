#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include <glm/glm.hpp>

namespace Boundary {
    // Global variables for terrain dimensions
    inline float terrainWidth = 50.0f;  // Default, can be updated
    inline float terrainDepth = 50.0f;  // Default, can be updated
    
    // Function to check if position is out of bounds
    inline bool isOutOfBounds(const glm::vec3& position) {
        float terrainMinX = -terrainWidth / 2.0f;
        float terrainMaxX = terrainWidth / 2.0f;
        float terrainMinZ = -terrainDepth / 2.0f;
        float terrainMaxZ = terrainDepth / 2.0f;
        
        return (position.x < terrainMinX || position.x > terrainMaxX ||
                position.z < terrainMinZ || position.z > terrainMaxZ);
    }
    
    // Function to update terrain dimensions
    inline void setTerrainDimensions(float width, float depth) {
        terrainWidth = width;
        terrainDepth = depth;
    }
}

#endif // BOUNDARY_HPP