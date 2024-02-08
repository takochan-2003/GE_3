#include"Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "SpriteCommon.h"
#include "Sprite.h"

#include "ImGuiManager.h"

#include<vector>

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
    std::vector<Sprite*> sp;
    for (int i = 0; i < 5; i++) {
        Sprite* temp = new Sprite();
        temp->Initialize(common);
        temp->SetPosition({ (float)i * 1,0 });
        sp.push_back(temp);
    }

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


        //移動
        //DirectX::XMFLOAT2 pos = sp->GetPosition();
        //pos.x += 0.05f;
        //sp->SetPosition(pos);
        ////回転
        //float rot = sp->GetRotation();
        //rot += 0.002f;
        //sp->SetRotation(rot);
        ////色
        //DirectX::XMFLOAT4 color = sp->GetColor();
        //color.x -= 0.01f;
        //if (color.x < 0) {
        //    color.x = 1.0f;
        //}
        //sp->SetColor(color);
        ////サイズ
        //DirectX::XMFLOAT2 size = sp->GetSize();
        //size.y += 0.01f;
        //sp->SetSize(size);

        for (int i = 0; i < 5; i++) {
            sp[i]->Update();
        }

        //更新前処理
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();
        common->SpritePreDraw();

        for (int i = 0; i < 5; i++) {
            sp[i]->Draw();
        }
       
        //更新後処理
        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();
    }
    for (int i = 0; i < 5; i++) {
        delete sp[i];
    }
    delete common;
    delete imgui;
    delete input_;
    delete dxCommon_;
    winapp_->Finalize();
    delete winapp_;

    return 0;
}
