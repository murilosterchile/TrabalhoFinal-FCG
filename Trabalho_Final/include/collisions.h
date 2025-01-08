#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#ifndef COLISIONS_H_INCLUDED
#define COLISIONS_H_INCLUDED

#include <glm/glm.hpp>


struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
};

bool checkSphereAABBCollision(const glm::vec3& sphereCenter, float sphereRadius, const BoundingBox& aabb);
glm::vec3 resolveSphereAABBCollision(const glm::vec3& sphereCenter, glm::vec3 sphereVelocity, float sphereRadius, const BoundingBox& aabb);


bool checkAABBCollision(const BoundingBox& a, const BoundingBox& b);
glm::vec3 resolveAABBCollision(const BoundingBox& a, const BoundingBox& b, glm::vec3 currentPosition);
bool checkAABBPlaneCollision(const BoundingBox& a, const glm::vec4& plane);
bool checkPointSphereCollision(const glm::vec3& point, const glm::vec3& sphereCenter, float sphereRadius);
glm::vec3 resolveSphereAABBCollision(glm::vec3& spherePosition, glm::vec3 sphereVelocity, float sphereRadius, const BoundingBox& aabb);


#endif // COLISIONS_H_INCLUDED


#endif // COLLISIONS_H_INCLUDED
