#pragma once
#include"DirectXCommon.h"
#include<string>
#include"DirectXTex.h"

class TextureManager {
private:
	//テクスチャ一枚分のデータ
	struct TextureData {
		std::wstring filePath;
		DirectX::TexMetadata metaData;
		Microsoft::WRL::ComPtr<ID3D12Resource>resource;
		D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU;
		D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU;
	};
public:
	//シングルトン
	static TextureManager* GetInstance();
	void Finalize();

	void Initialize();

private:
	static TextureManager* instance;

	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(TextureManager&) = delete;
	TextureManager& operator=(TextureManager) = delete;

private:
	std::vector<TextureData> textureDatas;


};