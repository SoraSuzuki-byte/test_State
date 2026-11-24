/**
 * @file   AirState.h
 *
 * @brief  プレイヤーが空中に居るときのStateの抽象クラスヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月10日
 */
#pragma once
#include "Game/Player/States/PlayerState.h"// 基底クラスを継承するので必須
class Player;

 /**
  * @brief 空中に居るときの抽象クラス
  */
class AirState : public PlayerState
{
public:
	PlayerState* Update(Player& player, float elapsedTime) override;
};


