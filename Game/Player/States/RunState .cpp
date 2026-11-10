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

/// <summary>
/// このStateの切り替わった瞬間に呼ばれる関数
/// </summary>
/// <param name="player">Playerの参照</param>
void RunState::Enter(Player& player)
{
	player.SetVelocityX(0.0f);
}

PlayerState* RunState::Update(Player& player, float elapsedTime)
{

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

	// 攻撃（Xキー && 攻撃のクールダウンタイムが終わっていれば）
	if (player.IsPressed(PAD_INPUT_2)
		&& player.CanAttack())
	{
		return player.GetAttackState();
	}
	return nullptr;
}

unsigned int RunState::GetBodyColor() const
{
	return GetColor(80, 220, 120);   // 緑
}
