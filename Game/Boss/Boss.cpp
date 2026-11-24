/**
 * @file   Boss.cpp
 *
 * @brief  Bossたちの基底クラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月24日
 */

#include "pch.h"
#include "Boss.h"

/// <summary>
/// BossのHpバーの描画
/// </summary>
void Boss::RenderHpBar() const
{
	// 最大HPが0以下のときは何もしない（0除算でゲームが落ちないように）
	if (m_maxHp <= 0) return;

	// HPバーの位置とサイズ
	constexpr int BAR_X = 240;
	constexpr int BAR_Y = 30;
	constexpr int BAR_WIDTH = 800;
	constexpr int BAR_HEIGHT = 24;

	// 背景（暗いグレー）
	DrawBox(BAR_X, BAR_Y, BAR_X + BAR_WIDTH, BAR_Y + BAR_HEIGHT, GetColor(40, 40, 40), TRUE);

	// 現在のHPバー（赤色）
	const float hpRatio = static_cast<float>(m_hp) / static_cast<float>(m_maxHp);
	const int currentWidth = static_cast<int>(BAR_WIDTH * hpRatio);
	DrawBox(BAR_X, BAR_Y, BAR_X + currentWidth, BAR_Y + BAR_HEIGHT, GetColor(220, 40, 40), TRUE);

	// 外枠（白色）
	DrawBox(BAR_X, BAR_Y, BAR_X + BAR_WIDTH, BAR_Y + BAR_HEIGHT, GetColor(255, 255, 255), FALSE);
}





/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="maxHp">Bossの最大Hp</param>
Boss::Boss(int maxHp)
	: m_maxHp{ maxHp }
	, m_hp   { maxHp }
{
}





/// <summary>
/// Hpを減らす
/// </summary>
/// <param name="amount">減らす量</param>
void Boss::ReduceHp(int amount)
{
	m_hp -= amount;

	// 0未満にならないように
	if (m_hp < 0) m_hp = 0;
}
