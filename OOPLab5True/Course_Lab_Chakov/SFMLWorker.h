#pragma once
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class SFMLWorker
{
private:
	sf::RenderWindow* window;

	void manageEvent(sf::Event event);

public:
	SFMLWorker();

	void work();
};