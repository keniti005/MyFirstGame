#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		pKeyDevice->Acquire();//‚È‚­‚Ä‚à“®ì‚Í‚·‚é‚ªŒ©‚Â‚©‚ç‚È‚©‚Á‚½‚Æ‚«ÄŒŸõ‚·‚é‚Ì‚É•K—v
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] && DIK_ESCAPE)
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

