#include "SceneBase.h"
#include "Game.h"
#include "MenuSceneUI.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "OverScene.h"
#include "ClearScene.h"
#include "FPSSetting.h"
#include "EffectManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    : sceneState(SCENE_MENU)
    , previousTime(0)
    , timer(0)
    , nowTimer(0)
    , score(0)
    , keyOn(false)
    , keyRelease(false)
    , prevKeyOn(false)
{
    // 最初のシーンの設定
    nowScene = SceneBase::InitializeBase();
    // 次のシーンの初期化
    nextScene = NULL;
    // FPS
    fpsSetting = new FPSSetting();
    // エフェクト
    effectManager = EffectManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    EffectManager::DeleteInstance();
    delete(nowScene);
    delete(fpsSetting);
}

/// <summary>
/// 実際のゲームループ
/// </summary>
void Game::Update()
{
    // 画面の削除
    ClearDrawScreen();

    // FPS計測処理
    fpsSetting->Update();

    // 現在シーンの更新・描画
    nextScene = nowScene->UpdateScene();
    nowScene->Draw();

    // FPS待機処理
    fpsSetting->SleepForFPS();

    // 描画を反映
    ScreenFlip();

    // Update内で return new 次のScene();された場合
    if (nowScene != nextScene)
    {
        // シーンを切り替える
        ChangeScene();
    }
}

/// <summary>
/// シーンの切り替え
/// </summary>
void Game::ChangeScene()
{
    // 現在のシーンを削除
    delete(nowScene);

    // 現在のシーンを切り替え
    nowScene = nextScene;

    // 初期関数を呼ぶ
    nowScene->Initialize();
    effectManager->Initialize();

    // 次のシーンを初期化
    nextScene = NULL;
}

/// <summary>
/// 初期化
/// </summary>
void Game::Initialize()
{
    // ゲームが始まる前のGetNowCountを取得
    previousTime = GetNowHiPerformanceCount();
    nowTimer = 1;
    score = 0;
}

/// <summary>
/// 入力処理
/// </summary>
void Game::UpdateKeyState()
{
    // キーを離した瞬間をとる
    if (keyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            keyOn = false;
            keyRelease = true;
        }
    }
    else if (prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        keyRelease = false;
        keyOn = true;
    }
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        prevKeyOn = true;
    }
    else
    {
        prevKeyOn = false;
    }
}

/// <summary>
/// 現在制限時間の描画
/// </summary>
void Game::DrawTimer()
{
    // 色保持
    int _color = GetColor(200, 200, 200);

    // 時間を保持する
    timer = (GetNowHiPerformanceCount() - previousTime);		// 現在時間 - 最初の計測時間
    int _nowTimer = (timer % 1000000000) / 1000000;				// 一桁の秒数
    nowTimer = (timer % 1000000000) / 1000000;
    char timerStr[256];
    sprintf_s(timerStr, "TIME: %d / 90", _nowTimer);
    DrawString(850, 0, timerStr, _color, true);
    nowTimer = _nowTimer;

    // 20秒経過ごとに(_nowTimerが０ではないとき。開始直後の時は無視)
    if (_nowTimer % 20 == 0 && _nowTimer != 0)
    {
        char _timeCount[256];
        sprintf_s(_timeCount, "～～～%f秒経過～～～", nowTimer);
        DrawString(250, 400, _timeCount, GetColor(255, 100, 100), true);
    }
}






