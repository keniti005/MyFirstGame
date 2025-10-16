#include "Transform.h"

Transform::Transform()
{
    position_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    rotate_ = XMFLOAT3(0.0f, 0.0f,0.0f);
    scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);

    matTranslate_ = XMMatrixIdentity();
    matRotate_ = XMMatrixIdentity();
    matScale_ = XMMatrixIdentity();
    pParent_ = nullptr;
}

Transform::~Transform()
{
}

void Transform::Calculation()
{
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    XMMATRIX ax, ay, az;
    ax = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    ay = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    az = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = ax * ay * az;

    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    if (pParent_)
    {
        return matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
    }
    else
    {
        return matTranslate_ * matRotate_ * matScale_;
    }
}

XMMATRIX Transform::GetNomalMatrix()
{
    return matRotate_ * XMMatrixInverse(nullptr,matScale_);
}
