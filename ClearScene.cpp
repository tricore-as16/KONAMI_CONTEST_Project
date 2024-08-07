﻿#include "ClearSceneUI.h"
#include "ClearScene.h"
#include "TitleScene.h"
#include "SceneBase.h"
#include "TreasureChest.h"
#include "Camera.h"
#include "Collision.h"
#include "SkyDome.h"
#include "Gem.h"
#include "GemManager.h"
#include "Player.h"
#include "GameScene.h"
#include "BoatWithChest.h"
#include "sea.h"
#include "Player.h"
#include "EffectManager.h"
#include "SoundManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ClearScene::ClearScene(int _score, int _highScore)
    : fireWorksEffectCount      (0)
{
    score           = _score;
    highScore       = _highScore;
    clearSceneUI    = new ClearSceneUI();
    treasureChest   = new TreasureChest();
    gemManager      = new GemManager();
    camera          = new Camera();
    skyDome         = new SkyDome();
    boatWithChest   = new BoatWithChest();
    sea             = new Sea();
    player          = new Player();
    effectManager   = EffectManager::GetInstance();
    soundManager    = SoundManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
ClearScene::~ClearScene()
{
    delete(clearSceneUI);
    delete(treasureChest);
    delete(gemManager);
    delete(camera);
    delete(skyDome);
    delete(boatWithChest);
    delete(sea);
    delete(player);
}

/// <summary>
/// 初期化
/// </summary>
void ClearScene::Initialize()
{
    treasureChest->Initialize(TREASURE_CHEST_INITIALIZE_POSITION,
                              TREASURE_CHEST_INITIALIZE_ROTATION_RATE);
    gemManager->Initialize();
    boatWithChest->Initialize(BOAT_WITH_CHEST_INITIALIZE_POSITION);
    player->Initialize(PLAYER_INITILIZE_POSITION,
                       PLAYER_INITILIZE_ROTATION_RATE,
                       Player::ANIMATION_TYPE::DELIGHTED,
                       PLAYER_INITILIZE_SCALE);
}

/// <summary>
/// 更新
/// </summary>
void ClearScene::Update()
{
    treasureChest->Update();    // 宝箱
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns></returns>
SceneBase* ClearScene::UpdateScene()
{
    // フェードイン指示
    if (clearSceneUI->GetFadeState() == SceneUIBase::FADE_NONE)
    {
        clearSceneUI->SetFadeState(SceneUIBase::FADE_IN_UI_PLAYING);
    }
    if (clearSceneUI->GetFadeState() == SceneUIBase::FADE_IN_UI_PLAYING)
    {
        clearSceneUI->StartFadeInUI();
    }

    // 更新処理
    camera->Update();           // カメラ
    treasureChest->Update();    // 宝箱
    skyDome->Update();          // スカイドーム
    boatWithChest->Update();    // 宝箱を乗せる船
    sea->UpdateClearScene();    // 海
    player->UpdateClearScene(); // プレイヤー
    effectManager->Update();    // エフェクトマネージャー
    UpdateSound();              // サウンド更新
    UpdateEffect();             // エフェクト更新
    UpdateEffekseer3D();        // エフェクシア更新

    // スペースキーが押されたらフェードアウトしてメニューへ
    if (CheckHitKey(KEY_INPUT_SPACE) == 1 || GetJoypadInputState(DX_INPUT_KEY_PAD1))
    {
        isFadeOutStart = true;
        clearSceneUI->SetFadeState(SceneUIBase::FADE_OUT_SCREEN_PLAYING);
    }
    if (isFadeOutStart && clearSceneUI->GetFadeState() == SceneUIBase::FADE_OUT_SCREEN_PLAYING)
    {
        clearSceneUI->StartFadeOutScreen();
    }
    if (isFadeOutStart && clearSceneUI->GetFadeState() == SceneUIBase::FADE_OUT_SCREEN_END)
    {
        // メニューシーンへ移行
        return new TitleScene(highScore);
    }

    return this;
}

/// <summary>
/// サウンドの更新
/// </summary>
void ClearScene::UpdateSound()
{
    // BGM再生
    soundManager->PlaySoundListBGM(SoundManager::CLEAR_SCENE_BGM);

    // 効果音再生
    // 花火
    soundManager->PlaySoundListBGM(SoundManager::FIRE_WORKS_BGM);
    // 入力音
    if (CheckHitKey(KEY_INPUT_SPACE) == 1 || GetJoypadInputState(DX_INPUT_KEY_PAD1))
    {
        // プッシュ音再生
        soundManager->PlaySoundListSE(SoundManager::PUSH_SE);
    }
}

/// <summary>
/// エフェクトの更新
/// </summary>
void ClearScene::UpdateEffect()
{
    // 花火のエフェクト再生
    if (fireWorksEffectCount % FIRE_WORKS_EFFECT_PLAY_CYCLE == 0)
    {
        effectManager->PlayFireWorksEffect(FIRE_WORKS_EFFECT_PLAY_POSITION);
    }
    fireWorksEffectCount++;
}

/// <summary>
/// 描画
/// </summary>
void ClearScene::Draw()
{
    // オブジェクト描画
    treasureChest->Draw();      // 宝箱
    skyDome->Draw();            // スカイドーム
    boatWithChest->Draw();      // 宝石を乗せる船
    sea->Draw();                // 海
    player->DrawClearScene();   // プレイヤー
    DrawEffekseer3D();          // 3Dエフェクト描画

    // UI描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void ClearScene::DrawUI()
{
    clearSceneUI->Draw(score, highScore);
}
