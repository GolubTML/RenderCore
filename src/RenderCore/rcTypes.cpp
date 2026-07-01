#include "RenderCore/rcTypes.hpp"

namespace rc
{
    Mat4 Transform::getModelMatrix() const
    {
        Mat4 model = Mat4(1.0f);
        
        model = Mat4::Scale(model, scale);
    
        model = Mat4::Translate(model, position);
        
        model = model * rotation.ToMatrix(); 
    
        return model;
    }
}