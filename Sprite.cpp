#include "Sprite.h"


#include<DirectXMath.h>

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	//���_���\�[�X�p�̃q�[�v�̐ݒ�
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	//���_���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC vertxResourceDesc{};
	//�o�b�t�@���\�[�X�B�e�N�X�`���̏ꍇ�͂܂��ʂ̐ݒ������
	vertxResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertxResourceDesc.Width = sizeof(XMFLOAT4)*3;
	//�o�b�t�@�̏ꍇ�͂����͂P�ɂ��錈�܂�
	vertxResourceDesc.Height = 1;
	vertxResourceDesc.DepthOrArraySize = 1;
	vertxResourceDesc.MipLevels = 1;
	vertxResourceDesc.SampleDesc.Count = 1;
	//�o�b�t�@�̏ꍇ�͂���ɂ��錈�܂�
	vertxResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result = dxCommon_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertxResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(result));

	
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
