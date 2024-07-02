#include "DxLib.h"
#include "Gem.h"
#include "TreasureChest.h"
#include "EffectManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TreasureChest::TreasureChest()
    : modelHanlde       (-1)
    , width             (5)
    , height            (5)
    , isHitGem          (false)
    , radius            (0)
    , hitGemType        (0)
{
    effectManager = EffectManager::GetInstance();
    modelHanlde = MV1LoadModel("data/model/TreasureChest/treasureChestOld.mv1");
    pos = VGet(5, 1, -5);
    scale = VGet(0.012f, 0.012f, 0.012f);
    radius = 3.0f;
    // スケールの設定
    MV1SetScale(modelHanlde, scale);
}

/// <summary>
/// デストラクタ
/// </summary>
TreasureChest::~TreasureChest()
{
    // モデルハンドルの削除
    MV1DeleteModel(modelHanlde);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="initializePosition">初期化座標</param>
/// <param name="rotationRate">初期化回転率</param>
void TreasureChest::Initialize(VECTOR initializePosition,VECTOR rotationRate)
{
    pos = initializePosition;
    // モデルの回転(違和感ない位置に修正)
    MV1SetRotationXYZ(modelHanlde, rotationRate);
}

/// <summary>
/// 更新
/// </summary>
void TreasureChest::Update()
{
    // 宝石と接触したらエフェクト再生
    if (isHitGem)
    {
        effectManager->PlayGemGetEffect(pos);
    }

    // 3Dモデルの座標設定
    MV1SetPosition(modelHanlde, pos);
}

/// <summary>
/// 描画
/// </summary>
void TreasureChest::Draw()
{
    // 3Dモデルの描画
    MV1DrawModel(modelHanlde);
}


