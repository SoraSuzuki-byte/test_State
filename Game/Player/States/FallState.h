/**
 * @file   FallState.h
 *
 * @brief  プレイヤーのFall状態のヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月10日
 */
#pragma once
#include "Game/Player/PlayerState.h"// 基底クラスを継承するので必須
class Player;

 /**
  * @brief 落下（オレンジ（橙））
  */
class FallState : public PlayerState
{
public:
	PlayerState* Update(Player& player, float elapsedTime) override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Fall"; }
};


