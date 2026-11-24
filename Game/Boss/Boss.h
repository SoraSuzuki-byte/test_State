/**
 * @file   Boss.h
 *
 * @brief  Bossたちの基底クラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月24日
 */

#pragma once
#include "Library/GameMath.h"

class Boss
{
// 公開インターフェース =======================================================
public:
	// 仮想デストラクタ
	virtual ~Boss() = default;

	// 更新処理
	virtual void Update(float elapsedTime) = 0;

	// 描画処理
	virtual void Render() const = 0;

	// プレイヤー等の体との判定
	virtual bool IsCollidingWithCircle(const Vector2D& center, float radius, Vector2D& pushOut) const = 0;

	// いま、触れたらダメージを与える状態か
	virtual bool IsAttacking() const = 0;

	// プレイヤーの攻撃を受ける（当たった部位の個数を返す）
	virtual int TakeDamageByCircle(const Vector2D& center, float radius, int damage, int attackId) = 0;

#pragma region Boss全員の共通の HP
	int GetHp() const { return m_hp; }
	int  GetMaxHp() const { return m_maxHp; }

	// BossのHpが0以下なのか
	bool IsDefeated() const { return m_hp <= 0; }
	// Hpバーの描画
	void RenderHpBar() const;
#pragma endregion

protected:
	// コンストラクタ
	explicit Boss(int maxHp);
	// Hpを減らす
	void ReduceHp(int amount);

private:
	int m_maxHp;
	int m_hp;
};
