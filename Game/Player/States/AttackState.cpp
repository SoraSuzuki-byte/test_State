/**
 * @file   AttackState.cpp
 *
 * @brief  プレイヤーのAttack状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#include "pch.h"
#include "Game/Player/PlayerConstants.h"
#include "AttackState.h"
#include "Game/Player/Player.h"
#include "IdleState.h"

 // ===========================================================================
 // AttackState（攻撃）
 // ===========================================================================

/// <summary>
/// このStateの切り替わった瞬間に呼ばれる関数
/// </summary>
/// <param name="player">Playerの参照</param>
void AttackState::Enter(Player& player)
{
	UNREFERENCED_PARAMETER(player);
	m_timer = PlayerConstants::ATTACK_TIME;
}




/// <summary>
/// このStateの更新
/// </summary>
/// <param name="player">Playerの参照</param>
/// <param name="elapsedTime">経過時間</param>
/// <returns>次に切り替わるState</returns>
PlayerState* AttackState::Update(Player& player, float elapsedTime)
{
	// 重力を適応
	player.ApplyGravityAndLand(elapsedTime);

	// 着地していれば
	if (player.IsGrounded())
	{
		player.SetVelocityX(0.0f);
	}

	// 持続時間が終わったら待機へ
	m_timer -= elapsedTime;
	if (m_timer <= 0.0f)
	{
		if (player.IsGrounded())
		{
			return player.GetIdleState();
		}
		return player.GetFallState();
	}

	return nullptr;
}




/// <summary>
/// 描画
/// </summary>
/// <param name="player">Playerの参照</param>
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




/// <summary>
/// 色を取得する
/// </summary>
/// <returns>取得される色</returns>
unsigned int AttackState::GetBodyColor() const
{
	return GetColor(255, 90, 90);   // 赤
}



/// <summary>
/// 別のStateに切り替わる瞬間に 呼ばれる関数
/// </summary>
/// <param name="player">Playerの参照</param>
void AttackState::Exit(Player& player)
{
	//攻撃用クールダウンタイムの開始
	player.StartAttackCooldown();
}

