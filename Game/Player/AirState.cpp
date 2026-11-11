/**
 * @file   AirState.cpp
 *
 * @brief  プレイヤーが空中に居るときのStateの抽象クラスのソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月10日
 */
#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Player/PlayerConstants.h"
#include "Game/Player/States/FallState.h"
#include "Game/Player/States/IdleState.h"
#include "Game/Player/States/RunState.h"



 // ===========================================================================
 // AirState（空中に居るときの抽象クラス）
 // ===========================================================================




/// <summary>
/// 更新
/// </summary>
/// <param name="player">Playerの参照</param>
/// <param name="elapsedTime">経過時間</param>
/// <returns>切り替わるState</returns>
PlayerState* AirState::Update(Player& player, float elapsedTime)
{
	// 空中でも左右に動ける
	const int direction = player.GetMoveDirection();

	// X軸方向の速度 = 入力方向 × 速さ
	const float velocityX = (direction) * (PlayerConstants::MOVE_SPEED);

	// X軸方向の速度をセット
	player.SetVelocityX(velocityX);

	// もし移動の向きがあれば
	if (direction != 0)
	{
		player.SetFacingRight(direction > 0);

		// ここに、ジャンプ時の移動速度の追加　書くのかも？？
		//player.MoveX(velocityX * elapsedTime);
	}

	// 着地していれば
	if (player.IsGrounded())
	{
		if (direction != 0)
		{
			return player.GetRunState();
		}
		return player.GetIdleState();
	}


	// 攻撃（Xキー && 攻撃のクールダウンタイムが終わっていれば）
	if (player.IsPressed(PAD_INPUT_2)
		&& player.CanAttack())
	{
		return player.GetAttackState();
	}

	return nullptr;
}