/**
 * @file   AttackState.h
 *
 * @brief  プレイヤーのAttack状態のヘッダーファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#pragma once
#include "Game/Player/PlayerState.h"// 基底クラスを継承するので必須
class Player;

 /**
  * @brief 攻撃（赤）
  */
class AttackState : public PlayerState
{
private:
	float m_timer = 0.0f;   ///< 攻撃の残り時間（この状態だけが持つデータ）

public:
	void Enter(Player& player) override;
	PlayerState* Update(Player& player, float elapsedTime) override;
	void RenderEffect(const Player& player) const override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Attack"; }
};

