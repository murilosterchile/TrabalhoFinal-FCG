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

// Intersecção AABB-Plano (Cubo-Plano)
bool checkAABBPlaneCollision(const BoundingBox& a, const glm::vec4& plane) {
    // plane é definido como (normal.x, normal.y, normal.z, distancia)
    glm::vec3 normal(plane.x, plane.y, plane.z);
    float distance = plane.w;

    float r = a.max.x * abs(normal.x) + a.max.y * abs(normal.y) + a.max.z * abs(normal.z);
    float s = glm::dot(normal, a.min) + distance;

    return -r <= s && s <= r;
}

// Intersecção Ponto-Esfera
bool checkPointSphereCollision(const glm::vec3& point, const glm::vec3& sphereCenter, float sphereRadius) {
    float distanceSquared = glm::dot(point - sphereCenter, point - sphereCenter);
    return distanceSquared <= (sphereRadius * sphereRadius);
}


bool checkSphereAABBCollision(const glm::vec3& sphereCenter, float sphereRadius, const BoundingBox& aabb) {
    float x = std::max(aabb.min.x, std::min(sphereCenter.x, aabb.max.x));
    float y = std::max(aabb.min.y, std::min(sphereCenter.y, aabb.max.y));
    float z = std::max(aabb.min.z, std::min(sphereCenter.z, aabb.max.z));

    float distSquared = (x - sphereCenter.x) * (x - sphereCenter.x) +
                        (y - sphereCenter.y) * (y - sphereCenter.y) +
                        (z - sphereCenter.z) * (z - sphereCenter.z);

    return distSquared < (sphereRadius * sphereRadius);
}

glm::vec3 resolveSphereAABBCollision(glm::vec3& spherePosition, glm::vec3 sphereVelocity, float sphereRadius, const BoundingBox& aabb) {
    glm::vec3 closestPoint = glm::clamp(spherePosition, aabb.min, aabb.max);
    glm::vec3 collisionNormal = glm::normalize(spherePosition - closestPoint);
    float distance = glm::distance(spherePosition, closestPoint);
    float overlap = sphereRadius - distance;

    if (overlap > 0) {
         spherePosition += collisionNormal * overlap * 0.5f; // Correção de posição (VERIFIQUE ISSO COM CUIDADO)
        float dotProduct = glm::dot(sphereVelocity, -collisionNormal);
        sphereVelocity = sphereVelocity + (2.0f * dotProduct * collisionNormal) * 0.5f; // Reflexão com amortecimento
    }
    return sphereVelocity;
}


