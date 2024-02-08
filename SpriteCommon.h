#pragma once
#include <string>
#include<wrl.h>
#include<dxcapi.h>
#include"DirectXCommon.h"


//�X�v���C�g���ʕ�
class SpriteCommon {
public:
	//����������
	void Initialize(DirectXCommon* dxCommon);

private:
	static IDxcBlob* CompileShader(
		//Compiler����Shader�t�@�C���ւ̃p�X
		const std::wstring& filePath,
		//Compiler�Ɏg�p����Profile
		const wchar_t* profile,
		//�������Ő����������̂��R��
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

private:
	DirectXCommon* dxCommon_ = nullptr;
};