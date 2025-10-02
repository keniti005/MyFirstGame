#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8 pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256] = { 0 };
	BYTE arrKeyState[256] = { 0 };
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE mouseState;//マウスの状態
	DIMOUSESTATE prevMouseState;//前回のマウスの状態
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		_memccpy(prevKeyState, keyState, sizeof(keyState), 256);
		pKeyDevice->Acquire();//なくても動作はするが見つからなかったとき再検索するのに必要
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 128)
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 128))
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 128))
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		//mousePosition = XMVectorSet((float)x,(float)y, 0, 0);
		mousePosition = { (float)x,(float)y,0.0f,0.0f };
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}

