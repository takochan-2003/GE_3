#pragma once
#include<wrl.h>
#include <string>
#include<dxcapi.h>
#include <d3d12.h>

#include"DirectXCommon.h"

#include<DirectXTex.h>


//スプライト共通部
class SpriteCommon {
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//初期化処理
	void Initialize(DirectXCommon* dxCommon);
	void SpritePreDraw();

	//Getter
	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }

	//画像読み込み
	DirectX::ScratchImage LoadTexture(const std::wstring& filePath);
	//読み込んだ画像をGPU(シェーダーに送る)
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

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

private:
	DirectXCommon* dxCommon_ = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
};