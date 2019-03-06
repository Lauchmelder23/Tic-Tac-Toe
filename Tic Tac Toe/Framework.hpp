#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <random>

#include "Button.hpp"
#include "InputField.hpp"
#include "Field.hpp"
#include "Tile.hpp"
#include "Util.h"

typedef unsigned short uint;

struct Packet
{
	int mouseX, mouseY;
	bool winCondition;
};

class Framework
{
public:
	Framework(uint width, uint height, std::string title);
	~Framework();

	bool Run();

private:
	bool HandleEvents();
	bool Update();
	bool Render();

	void CalculateFrametime();

	bool HostGame();
	bool JoinGame();

	void StartGame();

	void printInfo(int x, int y, char turn);

private:
	sf::RenderWindow* m_window;
	sf::Event m_event;
	sf::Clock m_clock;

	uint m_width;
	uint m_height;
	std::string m_title;

	Button m_host, m_join, m_newGame;
	InputField m_ipField;
	Field m_field;

	sf::IpAddress m_ip;

	GameState m_gameState;
	Role m_role;

	sf::TcpListener listener;
	sf::TcpSocket socket;

	sf::Text turn;
	sf::Text winner;
	sf::Font* font;

	std::default_random_engine engine;
	std::uniform_int_distribution<int> range;

	bool m_packageReceived;
	bool m_connected;
	bool m_myTurn;
	char m_winner;
	char m_mySymbol;
	bool m_ready, m_otherReady;

	long double m_frametime;
};

