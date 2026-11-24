/**
 * @file   IBossPartObserver.h
 *
 * @brief  ボスの状態変化を部位へ通知する　インターフェースクラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月4日
 */

#pragma once

class IBossPartObserver
{
public:
	virtual ~IBossPartObserver() = default;
	virtual void OnPartBroken(int index) = 0;
};