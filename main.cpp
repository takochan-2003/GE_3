#include"Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "SpriteCommon.h"
#include "Sprite.h"

#include "ImGuiManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winapp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

#pragma region WinApp初期化処理
    winapp_ = new WinApp();
    winapp_->Initialize();

    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winapp_);
    
    input_ = new Input();
    input_->Initialize(winapp_);
  
    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winapp_->GetHwnd(), dxCommon_);

    //スプライトコモン
    SpriteCommon* common = new SpriteCommon();
    common->Initialize(dxCommon_);
    
    //スプライト
    Sprite* sp = new Sprite();
    sp->Initialize(dxCommon_,common);

    // ゲームループ
    while (true) {
       
        if (winapp_->Update() == true) {
            break;
        }
        ImGuiManager::NewFlame();
        imgui->ShowDemo();


        //////多分下からが更新処理
        //入力
        input_->Update();
        sp->Update();

        //更新前処理
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();

        sp->Draw();
       
        //更新後処理
        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();
    }

    delete sp;
    delete common;
    delete imgui;
    delete input_;
    delete dxCommon_;
    winapp_->Finalize();
    delete winapp_;

    return 0;
}
