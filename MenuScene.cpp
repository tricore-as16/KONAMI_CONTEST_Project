﻿#include "SceneBase.h"
#include "MenuSceneUI.h"
#include "MenuScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
MenuScene::MenuScene()
{
    menuSceneUI = new MenuSceneUI();
}

/// <summary>
/// デストラクタ
/// </summary>
MenuScene::~MenuScene()
{
    delete(menuSceneUI);
}

/// <summary>
/// 初期化
/// </summary>
void MenuScene::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void MenuScene::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void MenuScene::Draw()
{

}

/// <summary>
/// UIの描画
/// </summary>
void MenuScene::DrawUI()
{
    // メニューシーンUIの描画
    menuSceneUI->Draw();
}
