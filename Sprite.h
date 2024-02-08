#pragma once
#include"DirectXCommon.h"
#include <d3d12.h>
#include<wrl.h>

#include<DirectXMath.h>

#include "SpriteCommon.h"

//スプライト
class Sprite {
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//初期化処理
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);

	void Draw();

private:
	//頂点情報作成
	void CreateVertex();
	//マテリアル情報作成
	void CreateMaterial();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	//頂点情報
	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	//マテリアル情報
	ComPtr<ID3D12Resource> materialResource;

	//パラメータ
	DirectX::XMFLOAT4 color_ = { 1.0f,0.0f,0.0f,1.0f };
};