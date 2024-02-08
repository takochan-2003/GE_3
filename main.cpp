#include"Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winapp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

#pragma region WinApp初期化処理
    winapp_ = new WinApp();
    winapp_->Initialize();

    input_ = new Input();
    input_->Initialize(winapp_);
  
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winapp_);

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

        //入力
        input_->Update();

        //更新前処理
        dxCommon_->PreDraw();

        sp->Draw();
       
        //更新後処理
        dxCommon_->PostDraw();
       

    }

    delete sp;
    delete common;
    delete input_;
    delete dxCommon_;
    winapp_->Finalize();
    delete winapp_;

    return 0;
}
