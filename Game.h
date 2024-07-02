#pragma once
#include "SceneBase.h"

class MenuScene;
class GameScene;
class ClearScene;
class OverScene;
class FPSSetting;
class EffectManager;

/// <summary>
/// シーンマネージャー
/// </summary>
class Game
{
public:
    /// <summary>
    /// シーンの進行状態
    /// </summary>
    enum SceneState
    {
        SCENE_MENU,     // メニュー
        SCENE_GAME,     // ゲーム
        SCENE_CLEAR,    // クリア
        SCENE_OVER      // オーバー
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Game();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Game();

    /// <summary>
    /// 実際のゲームループ
    /// </summary>
    void Update();

    /// <summary>
    /// シーンの切り替え
    /// </summary>
    void ChangeScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 入力処理
    /// </summary>
    void UpdateKeyState();

    /// <summary>
    /// 現在制限時間の描画
    /// </summary>
    void DrawTimer();

private:

    // 実行用シーン
    SceneBase* nowScene;            // 現在のシーン
    SceneBase* nextScene;           // 次のシーン

    // FPS処理
    FPSSetting* fpsSetting;         // FPS更新

    // エフェクト
    EffectManager* effectManager;   //エフェクト

    // ステート
    int     sceneState;             // 現在のシーン

    // 時間
    int     previousTime;           // ゲームループが始まる前の時間
    int     timer;                  // ゲーム時間
    float   nowTimer;               // 現在の制限時間

    // スコア
    int     score;                  // スコア

    // キー入力
    bool    keyOn;                  // キー入力されているか
    bool    keyRelease;             // キー入力が離れたか
    bool    prevKeyOn;              // 前フレームでキー入力があったか
};





