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
#include "AirState.h"// 基底クラスを継承するので必須

 /**
  * @brief 落下（オレンジ（橙））
  */
class FallState : public AirState
{
public:
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Fall"; }
};


