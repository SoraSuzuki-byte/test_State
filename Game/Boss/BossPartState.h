/**
 * @file   BossPartState.h
 *
 * @brief  ボスの状態（Stateパターン）に関するヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月21日
 */

#pragma once
#include <memory>
 // クラスの宣言 ===============================================================
class BossPart;

// クラスの定義 ===============================================================
/**
 * @brief ボスの部位の状態（基底クラス）
 *
 * OnDamaged は「次の状態」を返す。状態が変わらないときは nullptr を返す。
 */
class BossPartState
{
public:
	// デストラクタ
	virtual ~BossPartState() = default; // virtualを付けると、子クラスのデストラクタから順番に呼ばれるようになるらしい...

	// 状態に入った時の処理
	virtual void Enter(BossPart& bossPart) { UNREFERENCED_PARAMETER(bossPart); } // UNREFERENCED_PARAMETER(bossPart); を書く理由 → bossPart を使用しない場合に、未使用引数の警告が出ないようにするため。

	// ダメージを受けた後に呼ぶ。遷移先を返し、遷移しないなら nullptr
	virtual std::unique_ptr<BossPartState> OnDamaged(BossPart& bossPart) = 0;
	// 状態から出る時の処理
	virtual void Exit(BossPart& bossPart) { UNREFERENCED_PARAMETER(bossPart); }

	// 状態固有の追加描画
	virtual void RenderEffect(const BossPart& bossPart) const { UNREFERENCED_PARAMETER(bossPart); }

	// 本体の色を取得
	virtual unsigned int GetBodyColor() const = 0;

	// 状態名を取得（デバッグ表示用）
	virtual const wchar_t* GetName() const = 0;
};





