/**
 * @file   IdleState.h
 *
 * @brief  プレイヤーのIdle状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#include "pch.h"
#include "IdleState.h"
#include "Player.h"


 // ===========================================================================
 // IdleState（待機）
 // ===========================================================================
std::unique_ptr<PlayerState> IdleState::Update(Player& player, float elapsedTime)
{
	(void)elapsedTime;

	// 攻撃（Xキー）
	if (player.IsPressed(PAD_INPUT_2))
	{
		return std::make_unique<AttackState>();
	}

	// ジャンプ（Zキー）
	if (player.IsPressed(PAD_INPUT_1))
	{
		return std::make_unique<JumpState>();
	}

	// 左右に入力があれば走る
	if (player.GetMoveDirection() != 0)
	{
		return std::make_unique<RunState>();
	}

	return nullptr;
}

unsigned int IdleState::GetBodyColor() const
{
	return GetColor(80, 140, 255);   // 青
}
