#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	Tile(int posX, int posY);
	~Tile();

	virtual void Render(sf::RenderWindow& target);
	virtual char what() { return ' '; }
	bool isClicked(int mouseX, int mouseY);

	bool isActive() { return active; }

	sf::Vector2f getPosition() { return position; }

private:
	bool active;

	sf::RectangleShape frame;

protected:
	sf::Vector2f position;
	sf::Vector2f size;
};



class Cross : public Tile
{
public:
	Cross();
	Cross(int posX, int posY);

	void Render(sf::RenderWindow& target) override;
	char what() { return 'x'; }

private:
	sf::RectangleShape lines[2];
};


class Circle : public Tile
{
public:
	Circle();
	Circle(int posX, int posY);

	void Render(sf::RenderWindow& target) override;
	char what() { return 'o'; }

private:
	sf::CircleShape cir;
};