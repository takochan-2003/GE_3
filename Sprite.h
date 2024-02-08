#pragma once
#include"DirectXCommon.h"
#include <d3d12.h>
#include<wrl.h>

#include<DirectXMath.h>

#include "SpriteCommon.h"

//�X�v���C�g
class Sprite {
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	struct Transform {
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT3 translate;
	};

public:
	//����������
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);

	void Draw();

private:
	//���_���쐬
	void CreateVertex();
	//�}�e���A�����쐬
	void CreateMaterial();
	//�s����쐬
	void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	//���_���
	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	//�}�e���A�����
	ComPtr<ID3D12Resource> materialResource;

	//�s����
	ComPtr<ID3D12Resource>wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	//�p�����[�^
	DirectX::XMFLOAT4 color_ = { 1.0f,0.0f,0.0f,1.0f };
	//Scale,Rotate,Translation�B�����ŎO�p�`��ς����
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} };

	//�J����
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};