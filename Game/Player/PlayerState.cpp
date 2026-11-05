/**
 * @file   PlayerState.cpp
 *
 * @brief  プレイヤーの状態（Stateパターン）に関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// ヘッダファイルの読み込み ===================================================
#include "PlayerState.h"

#include "Game/Screen.h"
#include "Player.h"
#include "PlayerConstants.h"
#include "Game/Player/States/IdleState.h"
#include "Game/Player/States/RunState.h"




// 定数の定義 =================================================================
namespace
{
}



// ===========================================================================
// AttackState（攻撃）
// ===========================================================================
void AttackState::Enter(Player& player)
{
	UNREFERENCED_PARAMETER(player);
	m_timer = PlayerConstants::ATTACK_TIME;
}

std::unique_ptr<PlayerState> AttackState::Update(Player& player, float elapsedTime)
{
	UNREFERENCED_PARAMETER(player);

	// 持続時間が終わったら待機へ
	m_timer -= elapsedTime;
	if (m_timer <= 0.0f)
	{
		return std::make_unique<IdleState>();
	}

	return nullptr;
}

void AttackState::RenderEffect(const Player& player) const
{
	// 攻撃判定の見た目（向いている方向に箱を出す）
	const int attackW = 30;
	const int attackH = 20;

	const int top = static_cast<int>(player.GetY() - PlayerConstants::HEIGHT) + 15;

	int left = static_cast<int>(player.GetX()) - attackW;   // 左向きのときの位置
	if (player.IsFacingRight())
	{
		left = static_cast<int>(player.GetX() + PlayerConstants::WIDTH);   // 右向きのときの位置
	}

	DrawBox(left, top, left + attackW, top + attackH, GetColor(255, 180, 180), TRUE);
}

unsigned int AttackState::GetBodyColor() const
{
	return GetColor(255, 90, 90);   // 赤
}
