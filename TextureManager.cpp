#include "TextureManager.h"

#include"BufferResource.h"

TextureManager* TextureManager::instance= nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new TextureManager;
	}
	return instance;
}

void TextureManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

void TextureManager::Initialize(DirectXCommon* dxComoon)
{
	dxCommon_ = dxComoon;
	textureDatas.reserve(DirectXCommon::kMaxSRVCount);
}

void TextureManager::LoadTexture(const std::wstring& filePath)
{
	///テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	//std::wstring filePathW = ConvertString(filePath);
	HRESULT result = DirectX::LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(result));

	DirectX::ScratchImage mipImages{};
	result = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(result));

	//テクスチャデータを追加
	textureDatas.resize(textureDatas.size() + 1);
	//追加した画像データの編集
	TextureData& data = textureDatas.back();

	data.filePath = filePath;
	data.metaData = mipImages.GetMetadata();
	data.resource = CreateTextureResource(dxCommon_->GetDevice(), data.metaData);
	UploadTextureData(data.resource.Get(), mipImages);

	//画像が保存されているメモリ
	uint32_t srvIndex = static_cast<uint32_t>(textureDatas.size() - 1);
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = dxCommon_->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = dxCommon_->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	handleCPU.ptr += dxCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * srvIndex;
	handleGPU.ptr += dxCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * srvIndex;

	data.srvHandleCPU = handleCPU;
	data.srvHandleGPU = handleGPU;

	//ShaderResourceView作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = data.metaData.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = UINT(data.metaData.mipLevels);

	//読み込んだ情報をsrvDesc(枠)とHandle(位置)を使って保存する
	dxCommon_->GetDevice()->CreateShaderResourceView(data.resource.Get(), &srvDesc, data.srvHandleCPU);
}

void TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	//Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	//全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
		//MipMapLevelを指定して各Imageを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		//Textureに転送
		HRESULT result = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,//全領域へコピー
			img->pixels,//元データアドレス
			UINT(img->rowPitch),//1ラインサイズ
			UINT(img->slicePitch)//１枚サイズ
		);
		assert(SUCCEEDED(result));
	}
}
