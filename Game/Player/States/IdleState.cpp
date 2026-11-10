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
#include "Game/Player/Player.h"
#include "RunState.h"
#include "JumpState.h"
#include "AttackState.h"





 // ===========================================================================
 // IdleState（待機）
 // ===========================================================================
PlayerState* IdleState::Update(Player& player, float elapsedTime)
{
	(void)elapsedTime;

	// 攻撃（Xキー && 攻撃のクールダウンタイムが終わっていれば）
	if (player.IsPressed(PAD_INPUT_2) 
		&&player.CanAttack())
	{
		return player.GetAttackState();
	}

	// ジャンプ（Zキー）
	if (player.IsPressed(PAD_INPUT_1))
	{
		return player.GetJumpState();
	}

	// 左右に入力があれば走る
	if (player.GetMoveDirection() != 0)
	{
		return player.GetRunState();
	}

	return nullptr;
}

unsigned int IdleState::GetBodyColor() const
{
	return GetColor(80, 140, 255);   // 青
}
