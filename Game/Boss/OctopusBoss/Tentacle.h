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
#include "Game/Boss/IBossPartObserver.h"
#include "Game/Boss/BossPart.h"
class ITentacleObserver;

class Tentacle : public IBossPartObserver
{
private:
	// 部位の数
	static constexpr int SEGMENT_COUNT   = 12;

	// 部位（関部位）と部位の間の長さ
	static constexpr float SEGMENT_LENGTH = 30.0f;

	// 根元の半径
	static constexpr float BASE_RADIUS   = 27.0f;

	// 部位1つあたりの最大HP
	static constexpr int PART_MAX_HP = 100;

	// 曲がり具合
	static constexpr float BEND      = 0.02f;

	// 振れ幅
	static constexpr float AMPLITUDE = 0.18f;

	// 速さ
	static constexpr float SPEED     = 1.2f;

	// 位相のずれ
	static constexpr float PHASE     = 0.26f;

	// 崩壊が次の部位へ進むまでの時間（秒）
	static constexpr float COLLAPSE_INTERVAL = 0.15f;

	// 触手全体が届く最大の距離（これより遠いプレイヤーは、部位を調べなくてよい）
	static constexpr float REACH = SEGMENT_COUNT * SEGMENT_LENGTH + BASE_RADIUS;

	// 攻撃と待機を切り替える間隔（秒）
	static constexpr float ATTACK_MODE_INTERVAL = 2.0f;

	// 付け根の座標
	Vector2D m_root;

	// 部位（位置・半径・HP・状態を持つ）
	std::vector<std::unique_ptr<BossPart>> m_parts;
	
	// 経過時間
	float m_time{};

	// 次に壊す部位の番号（-1 なら崩壊していない）
	int m_collapseIndex{ -1 };

	// 次の部位を壊すまでの残り時間
	float m_collapseTimer{};

	// 攻撃中であるか
	bool m_isAttacking{};

	// 攻撃モードに切り替えるタイマー
	float m_attackModeTimer{ ATTACK_MODE_INTERVAL };

	// 部位が壊れたことを通知する先
	ITentacleObserver* m_observer{ nullptr };

public:
	// コンストラクタ / デストラクタ
	Tentacle(const Vector2D& root);
	~Tentacle();
	
	// 部位が Tentacle の this を覚えるので、コピーおよびムーブを禁止する
	Tentacle(const Tentacle&) = delete;
	Tentacle& operator=(const Tentacle&) = delete;
	Tentacle(Tentacle&&) = delete;
	Tentacle& operator=(Tentacle&&) = delete;

	// 更新 / 描画
	void Update(float elapsedTime);
	void Render() const;


	// プレイヤーの攻撃を受ける（当たった部位の個数を返す）
	int TakeDamageByCircle(const Vector2D& center, float radius, int damage, int attackId);

	// index 番目の部位にダメージを与える
	void TakeDamage(int index, int damage);

	// 部位が壊れた時に呼ばれる (Observer)
	void OnPartBroken(int index) override;

	/// <summary>
	/// 攻撃中のフラグを取得
	/// </summary>
	/// <returns>攻撃中かどうか</returns>
	bool IsAttacking() const { return m_isAttacking; }

	/// <summary>
	/// 円（プレイヤ等）と触手の各部位との当たり判定を行い、押し戻しベクトルを計算する
	/// </summary>
	/// <param name="center">円の中心座標</param>
	/// <param name="radius">円の半径</param>
	/// <param name="pushOut">円を押し出すベクトル</param>
	/// <returns>いずれかの部位と重なっているか</returns>
	bool IsCollidingWithCircle(const Vector2D& center, float radius, Vector2D& pushOut) const;
	
	/// <summary>
	/// 通知先（ボス）を登録する
	/// </summary>
	/// <param name="observer">通知先のオブザーバー</param>
	void SetObserver(ITentacleObserver* observer) { m_observer = observer; }


private:
	// 崩壊（壊れた部位より 先端側を、1部位ずつ壊していく）を、進める
	void UpdateCollapse(float elapsedTime);
	

private:
};

