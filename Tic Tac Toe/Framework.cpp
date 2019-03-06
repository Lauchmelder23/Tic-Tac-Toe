#include "Framework.hpp"

#include <iostream>
#include <Windows.h>

Framework::Framework(uint width, uint height, std::string title)
{
	font = new sf::Font();
	font->loadFromFile("C:/Windows/Fonts/lucon.ttf");

	turn.setFont(*font);
	turn.setString("Opponent's Turn");
	turn.setCharacterSize(18);
	turn.setPosition(10, 10);
	turn.setFillColor(sf::Color::White);

	winner.setFont(*font);
	winner.setString("Placeholder");
	winner.setCharacterSize(140);
	winner.setStyle(sf::Text::Style::Bold);
	winner.setPosition(100, 100);
	winner.setFillColor(sf::Color(10, 255, 10));

	m_width = width;
	m_height = height;
	m_title = title;

	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
	m_window->setFramerateLimit(120);

	m_event = sf::Event();
	m_clock = sf::Clock();

	m_frametime = -1.0;

	m_gameState = MAIN_MENU;
	m_role = UNKNOWN;

	m_host = Button("Host Game", 200, 200);
	m_join = Button("Join Game", 200, 450);
	m_newGame = Button("New Game", 200, 450);

	m_ipField = InputField();

	m_field = Field();

	m_winner = ' ';

	m_ip = "";

	m_connected = false;
	m_packageReceived = false;
	m_myTurn = false;
	m_mySymbol = 'o';
	m_ready = true;
	m_otherReady = true;

	listener.setBlocking(false);

	engine = std::default_random_engine{ static_cast<long unsigned int>(time(0)) };
	range = std::uniform_int_distribution<int>(0, 1);

	m_clock.restart();

}

Framework::~Framework()
{
	delete m_window;
	m_window = nullptr;
}

bool Framework::Run()
{
	if (m_window == nullptr)
	{
		std::cerr << "Framework was not initialized." << std::endl;
		return false;
	}

	while (m_window->isOpen())
	{
		if (!HandleEvents())
			return false;

		if (!Update())
			return false;

		if (!Render())
			return false;
	}

	return true;
}


void Framework::StartGame()
{
	m_gameState = IN_GAME;

	// If host, determine who begins. 
	// if client, wait for host to call who begins

	// If it is host's turn -> Let Host make turn, send client turn result
	// If it is client's turn -> Let client make turn, send host turn result
}


bool Framework::HostGame()
{
	if (!m_connected)
	{
		m_role = HOST;

		sf::Font font;
		font.loadFromFile("C:/Windows/Fonts/lucon.ttf");

		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::White);
		text.setString("Waiting for connection...");
		text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
		text.setPosition(sf::Vector2f(400, 400));

		sf::Text ip;
		ip.setFont(font);
		ip.setCharacterSize(24);
		ip.setFillColor(sf::Color::White);
		ip.setString("Your IP: " + m_ip.getPublicAddress().toString());
		ip.setOrigin(ip.getLocalBounds().left + ip.getLocalBounds().width / 2, ip.getLocalBounds().top + ip.getLocalBounds().height / 2);
		ip.setPosition(sf::Vector2f(400, 550));

		m_window->draw(text);
		m_window->draw(ip);

		

		if (listener.accept(socket) == sf::Socket::Done)
		{
			m_connected = true;
			m_gameState = READY;
			socket.setBlocking(false);
		}
		
		return true;
		
	}
	else
	{
		if (m_gameState == READY)
		{
			int starter = range(engine);
			std::cout << starter << std::endl;
			/*LPCWSTR who = L"Nobody";
			if (starter == true)
			{
				who = L"Opponent";
			}
			if (starter != true)
			{
				who = L"My turn";
			}*/

			// MessageBox(NULL, who, L"Host", MB_OK);

			sf::Packet data;
			data << starter;
			if (socket.send(data) == sf::Socket::Done)
			{
				m_gameState = IN_GAME;

				if (starter == 0) {
					m_myTurn = true;
					m_mySymbol = 'x';
					turn.setString("Your Turn");
				}
				else
				{
					m_myTurn = false;
					m_mySymbol = 'o';
					turn.setString("Opponent's Turn");
				}
			}
		}

		if (m_gameState == IN_GAME)
		{
			// If not my turn, wait for package
			sf::Packet data;
			if (socket.receive(data) == sf::Socket::Done)
			{
				m_myTurn = true;
				turn.setString("Your Turn");

				int mouseX, mouseY;
				int symb;

				data >> mouseX >> mouseY >> symb;

				m_field.Click(mouseX, mouseY, (char)symb);

				printInfo(mouseX, mouseY, (char)symb);
			}
		}

		if (m_gameState == GAME_OVER)
		{
			sf::Packet data;
			if (socket.receive(data) == sf::Socket::Done)
			{
				m_otherReady = true;
			}
		}
	}

	return true;
}

void Framework::printInfo(int x, int y, char turn)
{
	// std::cout << turn << " set piece at (" << x << ", " << y << ")" << std::endl;
}


bool Framework::JoinGame()
{
	if (!m_connected)
	{
		m_role = CLIENT;

		if (socket.connect(m_ip, 30000, sf::Time(sf::seconds(3))) != sf::Socket::Done)
		{
			std::cerr << "Could not connect to " << m_ip << ":30000. Is the IP correct and port 30000 open on the host's PC?" << std::endl;
			return false;
		}

		socket.setBlocking(false);

		m_connected = true;
		m_gameState = READY;
		return true;
	}
	else
	{
		if (m_gameState == READY)
		{
			m_winner = ' ';
			// Wait for Host to send data about who starts
			sf::Packet data;
			if (socket.receive(data) == sf::Socket::Done)
			{
				m_gameState = IN_GAME;
				int starter;
				data >> starter;
				//LPCWSTR who = (starter) ? L"Me" : L"Other";
				//MessageBox(NULL, who, L"Client", MB_OK);

				std::cout << starter << std::endl;

				if (starter == true)
				{
					m_myTurn = true;
					m_mySymbol = 'x';
					turn.setString("Your Turn");
				}
				else
				{
					m_myTurn = false;
					m_mySymbol = 'o';
					turn.setString("Opponent's Turn");
				}
			}
		}

		if (m_gameState == IN_GAME)
		{
			// If not my turn, wait for package
			sf::Packet data;
			if (socket.receive(data) == sf::Socket::Done)
			{
				m_myTurn = true;
				turn.setString("Your Turn");

				int mouseX, mouseY;
				int symb;

				data >> mouseX >> mouseY >> symb;

				m_field.Click(mouseX, mouseY, (char)symb);

				printInfo(mouseX, mouseY, (char)symb);
			}
		}

		if (m_gameState == GAME_OVER)
		{
			sf::Packet data;
			if (socket.receive(data) == sf::Socket::Done)
			{
				m_gameState = READY;
				m_field = Field();
				m_newGame.enable();
			}
		}
	}

	return true;
}


bool Framework::HandleEvents()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;

		case sf::Event::MouseButtonReleased:
		{
			if (m_gameState == MAIN_MENU)
			{
				if (m_host.isClicked(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y))
				{
					m_gameState = CONNECTING;
					m_role = HOST;

					if (listener.listen(30000) != sf::Socket::Done)
					{
						std::cerr << "Could not listen for incoming requests at port 30000" << std::endl;
						return false;
					}
				}

				if (m_join.isClicked(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y))
				{
					m_gameState = JOIN_GAME;
				}
			}


			if (m_gameState == IN_GAME && m_myTurn)
			{
				if (!m_field.Click(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y, m_mySymbol))
					break;

				m_myTurn = false;
				turn.setString("Opponent's Turn");

				sf::Packet data;
				data << sf::Mouse::getPosition(*m_window).x << sf::Mouse::getPosition(*m_window).y << m_mySymbol;
				socket.send(data);
			}


			if (m_gameState == GAME_OVER)
			{
				if (m_newGame.isClicked(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y))
				{
					if (m_role == HOST) {
						m_ready = true;
						m_newGame.disable();
					}

					if (m_role == CLIENT)
					{
						m_newGame.disable();

						sf::Packet data;
						data << true;
						if (socket.send(data) == sf::Socket::Done)
							break;
					}
				}

			}
		} break;

		case sf::Event::KeyPressed:
		{
			if (m_gameState == JOIN_GAME)
			{
				if (m_event.key.code == sf::Keyboard::Return) {
					m_ip = sf::IpAddress(m_ipField.Enter());
					m_role = CLIENT;
					m_gameState = CONNECTING;
				}
				
				if (m_event.key.code == sf::Keyboard::BackSpace)
					m_ipField.Backspace();

				if (m_event.key.code == sf::Keyboard::Period)
					m_ipField.Type('.');

				for (int key = sf::Keyboard::Num0; key <= sf::Keyboard::Num9; key++)
				{
					if(m_event.key.code == key)
						m_ipField.Type(key + 22);
				}
			}
		} break;

		default:
			break;
		}
	}

	return true;
}


bool Framework::Update()
{
	m_window->clear(sf::Color::Black);
	CalculateFrametime();

	int FPS = floor(1 / m_frametime);
	m_window->setTitle(m_title + " | " + std::to_string(FPS) + " FPS");

	int mouseX = sf::Mouse::getPosition(*m_window).x;
	int mouseY = sf::Mouse::getPosition(*m_window).y;

	if (m_gameState == MAIN_MENU)
	{
		m_host.Update(mouseX, mouseY);
		m_join.Update(mouseX, mouseY);
	}

	if (m_gameState == IN_GAME || m_gameState == READY || m_gameState == GAME_OVER || m_gameState == CONNECTING)
	{
		if (m_role == HOST)
			HostGame();

		if (m_role == CLIENT)
			JoinGame();


	}

	if (m_gameState == GAME_OVER)
	{
		m_myTurn = false;

		if (m_winner == m_mySymbol) {
			winner.setString("You won!");
			winner.setOrigin(winner.getLocalBounds().left + winner.getLocalBounds().width / 2, winner.getLocalBounds().top + winner.getLocalBounds().height / 2);
			winner.setPosition(m_window->getSize().x / 2, m_window->getSize().y / 4);
		}

		if (m_winner != m_mySymbol) {
			if (m_winner == 't')
			{
				winner.setString("Tie!");
				winner.setOrigin(winner.getLocalBounds().left + winner.getLocalBounds().width / 2, winner.getLocalBounds().top + winner.getLocalBounds().height / 2);
				winner.setPosition(m_window->getSize().x / 2, m_window->getSize().y / 4);
			}
			else {
				winner.setString("You lost!");
				winner.setOrigin(winner.getLocalBounds().left + winner.getLocalBounds().width / 2, winner.getLocalBounds().top + winner.getLocalBounds().height / 2);
				winner.setPosition(m_window->getSize().x / 2, m_window->getSize().y / 4);
			}
			
		}


		m_newGame.Update(mouseX, mouseY);

		if (m_ready && m_otherReady)
		{
			m_gameState = READY;
			m_ready = false;
			m_otherReady = false;

			m_field = Field();

			m_newGame.enable();

			sf::Packet data;
			data << true;
			socket.send(data) == sf::Socket::Done;
		}

		// std::cout << "Host: " << m_ready << std::endl << "Client: " << m_otherReady << std::endl << std::endl;

	}

	if (m_gameState != GAME_OVER)
	{
		m_winner = m_field.Update();

		if (m_winner != ' ') {
			m_gameState = GAME_OVER;
			m_ready = false;
			m_otherReady = false;
		}
	}


	return true;
}


bool Framework::Render()
{

	if (m_gameState == MAIN_MENU)
	{
		m_host.Render(*m_window);
		m_join.Render(*m_window);
	}

	if (m_gameState == JOIN_GAME)
	{
		m_ipField.Render(*m_window);
	}

	if (m_gameState == IN_GAME || m_gameState == GAME_OVER)
	{
		m_field.Render(*m_window);
		m_window->draw(turn);
	}

	if (m_gameState == GAME_OVER)
	{
		m_window->draw(winner);
		m_newGame.Render(*m_window);
	}

	m_window->display();
	return true;
}

void Framework::CalculateFrametime()
{
	m_frametime = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();
}