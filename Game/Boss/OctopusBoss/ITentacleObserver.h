/**
 * @file   ITentacleObserver.h
 *
 * @brief  壊れたことを触手クラスへ通知する　インターフェースクラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月4日
 */

#pragma once

class ITentacleObserver
{
public:
	virtual ~ITentacleObserver() = default;
	virtual void OnSegmentBroken() = 0;

};
