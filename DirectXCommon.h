#pragma once
#include <Windows.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <d3d12.h>

#include"WinApp.h"
#include <vector>

class DirectXCommon {



public:
	void Initialize(WinApp* winApp);

	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();
	//Getter
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
private:
	//デバイス
	void InitializeDevaice();
	//コマンド
	void CommandInitialize();
	//スワップチェーン
	void SwapChainInitialize();
	//レンダーターゲット
	void RenderTargetInitialize();
	//震度バッファ
	void DepthBufferInitialize();
	//フェンス
	void FenceInitialize();

private:
	WinApp* winApp = nullptr;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	D3D12_RESOURCE_BARRIER barrierDesc{};
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
};