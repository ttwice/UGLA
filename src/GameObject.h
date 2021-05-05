#ifndef GAMEOBJECT_H
#include <Constants.h>
#include <SFML/Window.hpp>
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject(float x, float y, sf::RectangleShape sprite);

	void update(float dt);
	void render(sf::RenderWindow& window);
	sf::Vector2f cornerAsSFMLCoords();
	sf::Vector2f centerAsSFMLCoords();

	sf::Vector2f size, position, velocity;
	sf::RectangleShape sprite;
};

#endif