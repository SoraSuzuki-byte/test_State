/**
 * @file   PartBrokenState.h
 *
 * @brief  ボスのPartBrokenStateのヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月11日
 */

#pragma once
#include "Game/Boss/States/BossPartState.h"
 // クラスの宣言 ===============================================================
class BossPart;

// クラスの定義 ===============================================================

//OnDamaged は「次の状態」を返す。状態が変わらないときは nullptr を返す。

/**
 * @brief HPが0（灰色）
 */
class PartBrokenState : public BossPartState
{
public:
	BossPartState* OnDamaged(BossPart& bossPart) override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Broken"; }

	void Enter(BossPart& bossPart) override;// この状態に遷移したときの初期化処理を行なう
};