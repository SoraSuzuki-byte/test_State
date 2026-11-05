/*
    @file   GameContext.h
    @brief  ゲームコンテキストクラス（構造体）
    @author 鈴木蒼良
    @date   2026年10月21日
*/
#pragma once
#include "Game/Manager/InputManager.h"
//#include "Game/Class/Manager/GhManager.h"
//#include"Game/Class/Manager/SoundManager.h"






struct GameContext
{
    // インプットマネージャー
    InputManager& inputManager;
    //// グラフィックマネージャー
    //GhManager& ghManager;
    //// サウンドマネージャー
    //SoundManager& soundManager;
};
