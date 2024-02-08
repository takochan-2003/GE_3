#include "Sprite.h"


#include<DirectXMath.h>

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	//頂点リソースの設定
	D3D12_RESOURCE_DESC vertxResourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	vertxResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertxResourceDesc.Width = sizeof(XMFLOAT4)*3;
	//バッファの場合はこれらは１にする決まり
	vertxResourceDesc.Height = 1;
	vertxResourceDesc.DepthOrArraySize = 1;
	vertxResourceDesc.MipLevels = 1;
	vertxResourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	vertxResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result = dxCommon_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertxResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(result));

	
	//リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点３つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(DirectX::XMFLOAT4) * 3;
	//1頂点あたりのサイズ
	vertexBufferView.StrideInBytes = sizeof(DirectX::XMFLOAT4);
}

void Sprite::Draw()
{
	//頂点リソースにデータを書き込む
	XMFLOAT4* vertexData = nullptr;
	//書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//上
	vertexData[1] = { +0.0f,+0.5f,0.0f,1.0f };
	//右下
	vertexData[2] = { +0.5f,-0.5f,0.0f,1.0f };

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());

	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);

	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}
