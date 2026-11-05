/*
	@file   Tentacle.h
	@brief  触手クラスのヘッダーファイル
	@author 鈴木蒼良
	@date   2026年11月4日
*/
#pragma once
#include "Library/GameMath.h"
#include <vector>
#include <cmath>
#include "IBossPartObserver.h"
#include "BossPart.h"

class Tentacle : public IBossPartObserver
{
private:
	// 節の数
	static constexpr int SEGMENT_COUNT   = 12;

	// 節（関節）と節の間の長さ
	static constexpr float SEGMENT_LENGTH = 30.0f;

	// 根元の半径
	static constexpr float BASE_RADIUS   = 27.0f;

	// 節1つあたりの最大HP
	static constexpr int PART_MAX_HP = 100;

	// 曲がり具合
	static constexpr float BEND      = 0.02f;

	// 振れ幅
	static constexpr float AMPLITUDE = 0.18f;

	// 速さ
	static constexpr float SPEED     = 1.2f;

	// 位相のずれ
	static constexpr float PHASE     = 0.26f;

	// 崩壊が次の節へ進むまでの時間（秒）
	static constexpr float COLLAPSE_INTERVAL = 0.15f;


	// 付け根の座標
	Vector2D m_root;

	// 節（位置・半径・HP・状態を持つ）
	std::vector<BossPart> m_parts;
	
	// 経過時間
	float m_time{};

	// 次に壊す節の番号（-1 なら崩壊していない）
	int m_collapseIndex{ -1 };

	// 次の節を壊すまでの残り時間
	float m_collapseTimer{};


public:
	// コンストラクタ / デストラクタ
	Tentacle(const Vector2D& root);
	~Tentacle();
	
	// 節が Tentacle の this を覚えるので、コピーおよびムーブを禁止する
	Tentacle(const Tentacle&) = delete;
	Tentacle& operator=(const Tentacle&) = delete;
	Tentacle(Tentacle&&) = delete;
	Tentacle& operator=(Tentacle&&) = delete;

	// 更新 / 描画
	void Update(float elapsedTime);
	void Render() const;

	// index 番目の節にダメージを与える
	void TakeDamage(int index, int damage);

	// 節が壊れた時に呼ばれる (Observer)
	void OnPartBroken(int index) override;

private:
	// 崩壊（壊れた節より 先端側を、1節ずつ壊していく）を、進める
	void UpdateCollapse(float elapsedTime);
	

private:
};

