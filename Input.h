#pragma once
#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include<wrl.h>
#include"WinApp.h"



//入力
class Input
{
 public:

	 void Initialize(WinApp* winApp);

	 void Update();
	 //任意のボタンが押されている
	 bool PushKey(BYTE keyNumber);
	 //任意のボタンが押された瞬間
	 bool TriggerKey(BYTE keyNumber);
	 //任意のボタンが離された瞬間

 private:
	 WinApp* winApp_ = nullptr;

	 Microsoft::WRL::ComPtr<IDirectInputDevice8>keyboard;
	 Microsoft::WRL::ComPtr<IDirectInput8> directInput;
	 BYTE key[256] = {};
	 //前回の全キーの状態
	 BYTE keyPre[256] = {};
};