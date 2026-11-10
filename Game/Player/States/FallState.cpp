/**
 * @file   FallState.cpp
 *
 * @brief  プレイヤーのFall状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月10日
 */
#include "pch.h"
#include "FallState.h"



 // ===========================================================================
 // FallState（落下）
 // ===========================================================================

unsigned int FallState::GetBodyColor() const
{
	return GetColor(255, 140, 0);   // オレンジ（橙）
}

