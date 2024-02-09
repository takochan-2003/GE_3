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

	void Initialize(DirectXCommon* dxComoon);

	//画像読み込み
	void LoadTexture(const std::wstring& filePath);
private:
	//読み込んだ画像をGPU(シェーダーに送る)
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private:
	static TextureManager* instance;

	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(TextureManager&) = delete;
	TextureManager& operator=(TextureManager) = delete;

private:
	DirectXCommon* dxCommon_ = nullptr;

	std::vector<TextureData> textureDatas;


};