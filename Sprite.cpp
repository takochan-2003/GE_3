#include "Sprite.h"

#include<DirectXMath.h>

#include"BufferResource.h"

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	//VertexResource
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4) * 3);

	
	//���\�[�X�̐擪�̃A�h���X����g��
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//�g�p���郊�\�[�X�̃T�C�Y�͒��_�R���̃T�C�Y
	vertexBufferView.SizeInBytes = sizeof(DirectX::XMFLOAT4) * 3;
	//1���_������̃T�C�Y
	vertexBufferView.StrideInBytes = sizeof(DirectX::XMFLOAT4);
}

void Sprite::Draw()
{

	//���_���\�[�X�Ƀf�[�^����������
	XMFLOAT4* vertexData = nullptr;
	//�������ނ��߂̃A�h���X���擾
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//����
	vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//��
	vertexData[1] = { +0.0f,+0.5f,0.0f,1.0f };
	//�E��
	vertexData[2] = { +0.5f,-0.5f,0.0f,1.0f };

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());

	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);

	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}
