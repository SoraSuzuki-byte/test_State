/**
 * @file   OctopusBoss.h
 *
 * @brief タコ型ボスのクラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月24日
 */

#pragma once
#include "Game/Boss/Boss.h"
#include "ITentacleObserver.h"
#include <vector>
#include <memory>
class Tentacle;

class OctopusBoss : public Boss, public ITentacleObserver
{
private:
	// 最大HP
	static constexpr int MAX_HP = 250;
	// 1部位壊れるごとに減るHP量
	static constexpr int DAMAGE_PER_SEGMENT = 5;

	// 持っている触手のリスト
	std::vector<std::unique_ptr<Tentacle>> m_tentacles;

public:
	// コンストラクタ / デストラクタ
	OctopusBoss();
	~OctopusBoss() override;

	// Boss からのオーバーライド
	void Update(float elapsedTime) override;
	void Render() const override;
	bool IsCollidingWithCircle(const Vector2D& center, float radius, Vector2D& pushOut) const override;
	bool IsAttacking() const override;
	int TakeDamageByCircle(const Vector2D& center, float radius, int damage, int attackId) override;

	// ITentacleObserver からのオーバーライド（部位が1つ壊れたときに呼ばれる）
	void OnSegmentBroken() override;
};

