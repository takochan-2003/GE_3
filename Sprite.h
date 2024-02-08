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

	struct VertexData {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcoord;
	};

public:
	//����������
	void Initialize(SpriteCommon* common);

	void Update();

	void Draw();

private:
	//���_���쐬
	void CreateVertex();
	//�C���f�b�N�X���쐬
	void CreateIndex();
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

	//�C���f�b�N�X
	ComPtr<ID3D12Resource>indexResource;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	//�}�e���A�����
	ComPtr<ID3D12Resource> materialResource;

	//�s����
	ComPtr<ID3D12Resource>wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	//�摜�̕ۑ���̃A�h���X
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	//�p�����[�^
	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	//Scale,Rotate,Translation�B�����ŎO�p�`��ς����
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} };

	//�J����
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};