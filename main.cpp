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
    DirectXCommon* dxCommon = nullptr;

#pragma region WinApp初期化処理
    winapp_ = new WinApp();
    winapp_->Initialize();

    input_ = new Input();
    input_->Initialize(winapp_);
  
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winapp_);

    //スプライトコモン
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize();
    
    //スプライト
    Sprite* sprite = new Sprite();
    sprite->Initialize();

    // ゲームループ
    while (true) {
       
        if (winapp_->Update() == true) {
            break;
        }

        //入力
        input_->Update();

        //更新前処理
        dxCommon->PreDraw();
       
        //更新後処理
        dxCommon->PostDraw();
       

    }

    delete sprite;
    delete spriteCommon;
    delete input_;
    delete dxCommon;
    winapp_->Finalize();
    delete winapp_;

    return 0;
}
