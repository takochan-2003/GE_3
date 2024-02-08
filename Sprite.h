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

	//���_���
	struct VertexData {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcoord;
	};

	//�}�e���A��
	struct MaterialData {
		DirectX::XMFLOAT4 color;
		DirectX::XMMATRIX uvTransform;
	};

public:
	//����������
	void Initialize(SpriteCommon* common);

	void Update();

	void Draw();

	//Getter/Setter
	DirectX::XMFLOAT2 GetPosition() { return position; }
	float GetRotation() { return rotation; }
	DirectX::XMFLOAT4 GetColor() { return color_; }
	DirectX::XMFLOAT2 GetSize() { return size; }

	void SetPosition(DirectX::XMFLOAT2 pos) { position = pos; }
	void SetRotation(float rot) { rotation = rot; }
	void SetColor(DirectX::XMFLOAT4 color) { color_ = color; }
	void SetSize(DirectX::XMFLOAT2 size) { this->size = size; }

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
	VertexData* vertexData = nullptr;

	//�C���f�b�N�X
	ComPtr<ID3D12Resource>indexResource;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	//�}�e���A�����
	ComPtr<ID3D12Resource> materialResource;
	MaterialData* materialData = nullptr;

	//�s����
	ComPtr<ID3D12Resource>wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	//�摜�̕ۑ���̃A�h���X
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	//�p�����[�^
	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	//UV���W
	Transform uvTransform = { {1,1,1},{0,0,0},{0,0,0} };

	//���@ Scale,Rotate,Translationj�B�����ŎO�p�`��ς����
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} };
	DirectX::XMFLOAT2 position = { 0,0};
	float rotation = 0;
	DirectX::XMFLOAT2 size = { 1,1 };

	//�J����
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};