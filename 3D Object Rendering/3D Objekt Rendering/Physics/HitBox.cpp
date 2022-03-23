#include "HitBox.h"

HitBox::HitBox(XMFLOAT4 dimensions)
{
    this->dimensions = dimensions; 
}

bool HitBox::PointIsInBox(XMFLOAT3 point)
{
    return point.x > dimensions.x && point.x < dimensions.y && point.z > dimensions.z && point.z < dimensions.w;
}
