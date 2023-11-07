#pragma once
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include<wrl.h>
#include"WinApp.h"



//����
class Input
{
 public:

	 void Initialize(WinApp* winApp);

	 void Update();
	 //�C�ӂ̃{�^����������Ă���
	 bool PushKey(BYTE keyNumber);
	 //�C�ӂ̃{�^���������ꂽ�u��
	 bool TriggerKey(BYTE keyNumber);
	 //�C�ӂ̃{�^���������ꂽ�u��

 private:
	 WinApp* winApp_ = nullptr;

	 Microsoft::WRL::ComPtr<IDirectInputDevice8>keyboard;
	 Microsoft::WRL::ComPtr<IDirectInput8> directInput;
	 BYTE key[256] = {};
	 //�O��̑S�L�[�̏��
	 BYTE keyPre[256] = {};
};