/**
 * @file   PartDamagedState.h
 *
 * @brief  ボスのPartDamagedStateのヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月11日
 */

#pragma once
#include "Game/Boss/BossPartState.h"
 // クラスの宣言 ===============================================================
class BossPart;

// クラスの定義 ===============================================================

//OnDamaged は「次の状態」を返す。状態が変わらないときは nullptr を返す。

 /**
  * @brief HPが半分以下（黄）
  */
class PartDamagedState : public BossPartState
{
public:
	BossPartState* OnDamaged(BossPart& bossPart) override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Damaged"; }

};
