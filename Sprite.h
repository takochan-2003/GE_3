#pragma once
#include"DirectXCommon.h"
#include <d3d12.h>
#include<wrl.h>

#include "SpriteCommon.h"

//�X�v���C�g
class Sprite {
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//����������
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);

	void Draw();

private:
	//���_���쐬
	void CreateVertex();
	//�}�e���A�����쐬
	void CreateMaterial();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	//���_���
	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	//�}�e���A�����
	ComPtr<ID3D12Resource> materialResource;
};