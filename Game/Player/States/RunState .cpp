/**
 * @file   RunState.cpp
 *
 * @brief  プレイヤーのRun状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#include "pch.h"
#include "Game/Player/PlayerConstants.h"
#include "RunState.h"
#include "Game/Player/Player.h"
#include "IdleState.h"
#include "JumpState.h"
#include "AttackState.h"


 // ===========================================================================
 // RunState（走り）
 // ===========================================================================
PlayerState* RunState::Update(Player& player, float elapsedTime)
{
	// 攻撃（Xキー）
	if (player.IsPressed(PAD_INPUT_2))
	{
		return player.GetAttackState();
	}

	// ジャンプ（Zキー）
	if (player.IsPressed(PAD_INPUT_1))
	{
		return player.GetJumpState();
	}

	// 入力が無くなったら待機へ
	const int direction = player.GetMoveDirection();
	if (direction == 0)
	{
		return player.GetIdleState();
	}

	// 移動
	player.SetFacingRight(direction > 0);
	player.MoveX(direction * PlayerConstants::MOVE_SPEED * elapsedTime);

	return nullptr;
}

unsigned int RunState::GetBodyColor() const
{
	return GetColor(80, 220, 120);   // 緑
}
