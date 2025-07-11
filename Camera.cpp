#include "Camera.h"

//�ϐ�
XMVECTOR position_;	//�J�����̈ʒu�i���_�j
XMVECTOR target_;	//����ʒu�i�œ_�j
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

void Camera::SetPosition(XMVECTOR position)
{
}

void Camera::SetTarget(XMVECTOR target)
{
}

XMMATRIX Camera::GetViewMatrix()
{
    return viewMatrix_;
}

XMMATRIX Camera::GetProjectionMatrix()
{
    return projMatrix_;
}
