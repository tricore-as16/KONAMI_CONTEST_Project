#pragma once

class Gem;
class EffectManager;

/// <summary>
/// 宝箱クラス
/// </summary>
class TreasureChest final
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TreasureChest();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TreasureChest();

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="initializePosition">初期化座標</param>
    /// <param name="rotationRate">初期化回転率</param>
    void Initialize(VECTOR initializePosition, VECTOR rotationRate);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    // Getter
    const VECTOR& GetPos()const { return pos; }
    const bool GetIsHitGem()const { return isHitGem; }
    const float GetRadius()const { return radius; }
    const float GetWidth()const { return width; }
    const float GetHeight()const { return height; }
    const int GetHitGemType()const { return hitGemType; }

    // Setter
    void SetIsHitGem(const bool set) { isHitGem = set; }
    void SetHitGemType(const int set) { hitGemType = set; }

private:
    // 変数
    EffectManager* effectManager;   // エフェクトマネージャーへのポインタ

    // モデル
    int     modelHanlde;    // モデルハンドル

    // 情報
    VECTOR  pos;            // ポジション
    VECTOR  scale;          // スケール
    float   width;          // 幅
    float   height;         // 高さ

    // フラグ
    bool    isHitGem;       // 宝箱が宝石と接触したか

    // 当たり判定
    float   radius;         // 球型当たり判定用の半径
    int     hitGemType;     // 当たった宝石の種類
};


