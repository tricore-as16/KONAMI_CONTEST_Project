// 標準ライブラリ
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "math.h"
// 追加外部ライブラリ
#include "DxLib.h"
#include "EffekseerForDXLib.h"
// 自作ヘッダー
#include "Common.h"
#include "GemManager.h"
#include "TreasureChest.h"
#include "Calculation.h"
#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Collision.h"
#include "EffectManager.h"
#include "FPSSetting.h"
#include "Room.h"
#include "Gem.h"
// シーン
#include "SceneBase.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "OverScene.h"
// Game.hの上にすべての自作ヘッダーをインクルードする
#include "Game.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
    // DXライブラリの表示方法をウィンドウモードに変更する。
    //ChangeWindowMode(true);     // ウィンドウモード
    ChangeWindowMode(false);    // 全画面モード

    //描画先を裏画面に変更する。
    SetDrawScreen(DX_SCREEN_BACK);

    // フルシーンアンチエイリアスを設定する
    SetFullSceneAntiAliasingMode(4, 2);  // 4x アンチエイリアシングを設定

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        return -1;  // エラーが起きたら直ちに終了
    }

    // 画面モードのセット
    SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT_DEPTH);

    // 描画先グラフィック領域の指定
    SetDrawScreen(DX_SCREEN_BACK);

    // インスタンス化
    EffectManager::CreateInstance();
    Game* game = new Game();

    // エスケープキーが押されるかウインドウが閉じられるまでループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ゲームループ
        game->Update();

        // Windows 特有の面倒な処理をＤＸライブラリにやらせる
        // マイナスの値（エラー値）が返ってきたらループを抜ける
        if (ProcessMessage() < 0)
        {
            break;
        }
        // もしＥＳＣキーが押されていたらループから抜ける
        else if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }
    }

    // Effekseerを終了する。
    Effkseer_End();

    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}
