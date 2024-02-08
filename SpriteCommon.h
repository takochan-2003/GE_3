#pragma once
#include<dxcapi.h>
#include <string>


//スプライト共通部
class SpriteCommon {
public:
	//初期化処理
	void Initialize();

private:
	static IDxcBlob* CompileShader(
		//CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを３つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);
};