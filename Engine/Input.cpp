#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8 pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256] = { 0 };
	BYTE arrKeyState[256] = { 0 };
	//マウスインプット
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

		//マウスデバイス初期化
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		_memccpy(prevKeyState, keyState, sizeof(keyState), 256);
		for (int i = 0;i < 256;i++)
		{
			prevKeyState[i] = keyState[i];
		}
		pKeyDevice->Acquire();//なくても動作はするが見つからなかったとき再検索するのに必要
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		//マウスの状態を保存
		pMouseDevice->Acquire();
		_memccpy(&prevMouseState, &mouseState, sizeof(mouseState), 256);
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
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

	bool IsMouseButton(int btnCode)
	{
		if (mouseState.rgbButtons[btnCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int btnCode)
	{
		if (!IsMouseButton(btnCode) && (prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int btnCode)
	{
		if (IsMouseButton(btnCode) && !(prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}

