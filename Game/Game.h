/**
 * @file   Game.h
 *
 * @brief  ゲーム全体に関するヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// 多重インクルードの防止 =====================================================
#pragma once



// ヘッダファイルの読み込み ===================================================
#include <memory> // スマートポインタ（std::unique_ptr や std::shared_ptr など）を使うために
				  //PlayerState（プレイヤーの状態）を所有・管理するために std::unique_ptr<PlayerState> や std::make_unique を使用しており、その動的メモリ管理を自動化（自動破棄）するために必要な記述です。

#include "GameContext.h"
#include "Game/Boss/TentacleBoss/Tentacle.h"



// クラスの宣言 ===============================================================
class Player;



// クラスの定義 ===============================================================
/**
 * @brief ゲーム
 */
class Game
{
// クラス定数の宣言 -------------------------------------------------
public:
	// システム関連
	static constexpr const wchar_t* TITLE = L"Sample Game";   ///< ゲームタイトル



// データメンバの宣言 -----------------------------------------------
private:

	InputManager m_inputManager;   // 本物（先に宣言する）
	GameContext  m_gameContext;        // m_inputManager への参照を持つ箱

	// プレイヤー（Idleは青、Runは緑、Jumpは黄、Attackは赤）
	std::unique_ptr<Player> m_player;

	// ボスの触手（節の BossPart を持つ）　Tentacleインスタンスを生成
	Tentacle m_tentacle;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();


// 操作
public:
	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float elapsedTime);

	// 描画処理
	void Render();

	// 終了処理
	void Finalize();


// 取得/設定
public:


// 内部実装
private:


};
