#include "SpriteCommon.h"
#include<cassert>
#include <d3d12.h>

#pragma comment(lib,"dxcompiler.lib")

using namespace Microsoft::WRL;

void SpriteCommon::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result{};
	dxCommon_ = dxCommon;

	//DXC������
	ComPtr<IDxcUtils> dxcUtils;
	ComPtr<IDxcCompiler3> dxcCompiler;
	ComPtr<IDxcIncludeHandler> includeHandler;

	result = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
	assert(SUCCEEDED(result));
	result = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	assert(SUCCEEDED(result));

	result = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(result));

	//RootSignature�쐬
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//�V���A���C�Y���ăo�C�i���ɂ���
	ComPtr<ID3DBlob> signatureBlob;
	ComPtr<ID3DBlob> errorBlob;
	result = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(result)) {
		assert(SUCCEEDED(result));
	}
	//�o�C�i�������ɍ쐬
	ComPtr<ID3D12RootSignature> rootSignature;
	result = dxCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));

}

IDxcBlob* SpriteCommon::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)
{
	//hlsl�t�@�C����ǂ�
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT result = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	//�ǂ߂Ȃ�������~�߂�
	assert(SUCCEEDED(result));

	//�ǂݍ��񂾃t�@�C���̓��e��ݒ肷��
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;//YTF8�̕����R�[�h�ł��邱�Ƃ�ʒm

	LPCWSTR arguments[] = {
		filePath.c_str(),//�R���p�C���Ώۂ�hlsl�t�@�C����
		L"-E",L"main",//�G���g���[�|�C���g�̎w��B��{�I��main�ȊO�ɂ͂��Ȃ�
		L"-T",profile,//ShaderProfile�̐ݒ�
		L"-Zi",L"-Qembed_debug",//�f�o�b�O�p�̏��𖄂ߍ���
		L"-Od",//�œK�����O���Ă���
		L"-Zpr",//���������C�A�E�g�͍s�D��
	};
	//���ۂɂ��R���p�C������
	IDxcResult* shaderResult = nullptr;
	result = dxcCompiler->Compile(
		&shaderSourceBuffer,//�ǂݍ��񂾃t�@�C��
		arguments,//�R���p�C���I�v�V����
		_countof(arguments),//�R���p�C���I�v�V�����̐�
		includeHandler,//include���܂܂ꂽ���X
		IID_PPV_ARGS(&shaderResult)//�R���p�C������
	);
	//�R���p�C���G���[�ł͂Ȃ�dxc���N���ł��Ȃ��قǒv���I�ȏ�
	assert(SUCCEEDED(result));

	//�x���E�G���[���o�Ă��烍�O�ɏo���Ď~�߂�
	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		//�x���E�G���[�_���[�b�^�C
		assert(false);
	}

	//�R���p�C�����ʂ�����s�p�̃o�C�i���������擾
	IDxcBlob* shaderBlob = nullptr;
	result = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(result));
	//�����g��Ȃ����\�[�X�����
	shaderSource->Release();
	shaderSource->Release();
	//���s�p�̃o�C�i����ԋp
	return shaderBlob;
}
