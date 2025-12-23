#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
	//transform_.position_.y -= transform_.scale_.y / 2.0f;
	hModel_ = Model::Load("Cube.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
	XMFLOAT3 mousePosFront;
	XMStoreFloat3(&mousePosFront, Input::GetMousePosition());
	mousePosFront.z = 0.0f;

	XMFLOAT3 mousePosBack;
	XMStoreFloat3(&mousePosBack, Input::GetMousePosition());
	mousePosBack.z = 1.0f;


}

void Stage::Draw()
{
	//for (int i = 0; i < XSIZE; i++)
	//{
	//	for (int j = 0; j < ZSIZE; j++)
	//	{
	//		transform_.position_.x = transform_.scale_.x * i;
	//		transform_.position_.z = transform_.scale_.z * j;
	//		Model::SetTransform(hModel_, transform_);
	//		Model::Draw(hModel_);
	//	}
	//}

	Transform t;
	t.position_.x = 5;
	t.position_.y = 0;
	t.position_.z = 5;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	RayCastData data{
		{ 0.0f, 0.0f, 5.0f },
		{ 0.0f,-1.0f, 0.0f },
		false,
		0.0f
	};

	Model::RayCast(hModel_, data);

	if (data.isHit)
	{
		int a = 0;
		a++;
	}

	//Transform t;
	//t.position_.x = 5;
	//t.position_.y = 0;
	//t.position_.z = 5;
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
	//RayCastData data{
	//	{ 0.0f, 0.0f, 5.0f, 0.0f },
	//	{ 0.0f,-1.0f, 0.0f, 0.0f },
	//	false,
	//	0.0f
	//};
	//
	//Model::RayCast(hModel_, data);
	//
	//if (data.isHit)
	//{
	//	int a = 0;
	//	a++;
	//}

	//Model::SetTransform(hModel_, transform_);
}

void Stage::Release()
{
	Model::Release();
}

BOOL Stage::localProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: //コントロールの操作
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hWnd, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hWnd, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL Stage::menuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{//名前:IDC_COMBO1
	switch (message) 
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hWnd, IDC_RADIO1), BM_SETCHECK, BST_CHECKED,0);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"草地");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"砂地");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"水場");
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO1:
			mode_ = 0;//上げる
			return TRUE;
		case IDC_RADIO2:
			mode_ = 1;//下げる
			return TRUE;
		case IDC_RADIO3:
			mode_ = 2;//種類変更
			return TRUE;
		case IDC_COMBO1:
			select_ = (int)SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
