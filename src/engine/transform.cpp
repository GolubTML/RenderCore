#include "engine/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace rc
{
    glm::mat4 Transform::getModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f);
    
        model = glm::translate(model, position);
    
        model = glm::rotate(model, rotation.x, {1,0,0});
        model = glm::rotate(model, rotation.y, {0,1,0});
        model = glm::rotate(model, rotation.z, {0,0,1});
    
        model = glm::scale(model, scale);
    
        return model;
    }
}