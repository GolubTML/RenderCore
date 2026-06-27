#include "RenderCore/rcTypes.hpp"

namespace rc
{
    rc::Mat4 Transform::getModelMatrix() const
    {
        rc::Mat4 model = rc::Mat4(1.0f);
    
        model = rc::Mat4::Translate(model, position);
    
        model = rc::Mat4::RotateX(model, rotation.x);
        model = rc::Mat4::RotateY(model, rotation.y);
        model = rc::Mat4::RotateZ(model, rotation.z);
    
        model = rc::Mat4::Scale(model, scale);
    
        return model;
    }
}