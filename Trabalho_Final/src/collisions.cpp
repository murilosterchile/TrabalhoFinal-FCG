#include "collisions.h"
#include <glm/glm.hpp>
#include <algorithm>
#include <cmath>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>



// Intersecção AABB-AABB (Cubo-Cubo)
bool checkAABBCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
           (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
           (a.min.z <= b.max.z && a.max.z >= b.min.z);
}

// Resolução de colisão AABB-AABB (empurra o objeto 'a' para fora da colisão)
glm::vec3 resolveAABBCollision(const BoundingBox& a, const BoundingBox& b, glm::vec3 currentPosition) {
    glm::vec3 overlap;
    overlap.x = std::min(a.max.x, b.max.x) - std::max(a.min.x, b.min.x);
    overlap.y = std::min(a.max.y, b.max.y) - std::max(a.min.y, b.min.y);
    overlap.z = std::min(a.max.z, b.max.z) - std::max(a.min.z, b.min.z);

    if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0) {
        // Encontra o eixo com a menor sobreposição
        float minOverlap = std::min({overlap.x, overlap.y, overlap.z});

        if (minOverlap == overlap.x) {
            if (currentPosition.x > b.min.x) {
                currentPosition.x += overlap.x;
            } else {
                currentPosition.x -= overlap.x;
            }
        } else if (minOverlap == overlap.y) {
            if (currentPosition.y > b.min.y) {
                currentPosition.y += overlap.y;
            } else {
                currentPosition.y -= overlap.y;
            }
        } else {
            if (currentPosition.z > b.min.z) {
                currentPosition.z += overlap.z;
            } else {
                currentPosition.z -= overlap.z;
            }
        }
    }
    return currentPosition;
}


bool checkCollisionWithMonster(const glm::vec3& spherePosition, float sphereRadius, const glm::vec3& monsterPosition) {
     float distSquared = (monsterPosition.x - spherePosition.x) * (monsterPosition.x - spherePosition.x) +
                        (monsterPosition.y - spherePosition.y) * (monsterPosition.y - spherePosition.y) +
                        (monsterPosition.z - spherePosition.z) * (monsterPosition.z - spherePosition.z);

    return distSquared <= (sphereRadius * sphereRadius) + sphereRadius ;}

bool checkCollisionWithBunnies(const glm::vec3& spherePosition, float sphereRadius, const std::vector<Bunny>& bunnies) {
    for (const auto& bunny : bunnies) {
        float distSquared = (bunny.position.x - spherePosition.x  ) * (bunny.position.x - spherePosition.x ) +
                            (bunny.position.y - spherePosition.y ) * (bunny.position.y - spherePosition.y ) +
                            (bunny.position.z - spherePosition.z ) * (bunny.position.z - spherePosition.z );

        if (distSquared <= (sphereRadius * sphereRadius)) {
            return false;
        }
    }
    return true;
}




