#pragma once

#include <d3d11.h>
#include<windows.h>
#include<assert.h>

//�����J
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE
{
	SHADER_3D,//3D�p�V�F�[�_�[
	SHADER_2D,//2D�p�V�F�[�_�[
	SHADER_MAX//�V�F�[�_�[�̍ő吔
};

namespace Direct3D
{
	extern ID3D11Device* pDevice;		                    //�f�o�C�X
	extern ID3D11DeviceContext* pContext;		            //�f�o�C�X�R���e�L�X�g
	#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
	#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);//�V�F�[�_�[�Z�b�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
}