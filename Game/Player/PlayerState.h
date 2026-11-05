/**
 * @file   PlayerState.h
 *
 * @brief  プレイヤーの状態（Stateパターン）に関するヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// 多重インクルードの防止 =====================================================
#pragma once
#include <memory>


// クラスの宣言 ===============================================================
class Player;



// クラスの定義 ===============================================================
/**
 * @brief プレイヤーの状態（基底クラス）
 *
 * Update は「次の状態」を返す。状態が変わらないときは nullptr を返す。
 */
class PlayerState
{
// メンバ関数の宣言 -------------------------------------------------
public:
	// デストラクタ
	virtual ~PlayerState() = default;

	// 状態に入った時の処理
	virtual void Enter(Player& player)
	{
		UNREFERENCED_PARAMETER(player);
	} // UNREFERENCED_PARAMETER(player); を書く理由 → player を使用しない場合に、未使用引数の警告が出ないようにするため。

	// 更新処理（遷移先の状態を返す。遷移しないなら nullptr）
	virtual std::unique_ptr<PlayerState> Update(Player& player, float elapsedTime) = 0;

	// 状態から出る時の処理
	virtual void Exit(Player& player) { UNREFERENCED_PARAMETER(player); }

	// 状態固有の追加描画
	virtual void RenderEffect(const Player& player) const { UNREFERENCED_PARAMETER(player); }

	// 本体の色を取得
	virtual unsigned int GetBodyColor() const = 0;

	// 状態名を取得（デバッグ表示用）
	virtual const wchar_t* GetName() const = 0;
};












/**
 * @brief 攻撃（赤）
 */
class AttackState : public PlayerState
{
private:
	float m_timer = 0.0f;   ///< 攻撃の残り時間（この状態だけが持つデータ）

public:
	void Enter(Player& player) override;
	std::unique_ptr<PlayerState> Update(Player& player, float elapsedTime) override;
	void RenderEffect(const Player& player) const override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Attack"; }
};
