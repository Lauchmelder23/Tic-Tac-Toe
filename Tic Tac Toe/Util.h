#pragma once

enum GameState
{
	MAIN_MENU,
	READY,
	IN_GAME,
	GAME_OVER,
	HOST_GAME,
	JOIN_GAME,
	CONNECTING
};

enum Role
{
	UNKNOWN,
	HOST,
	CLIENT
};