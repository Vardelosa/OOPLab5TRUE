#include "SFMLWorker.h"
#include "SFMLShape.h"

SFMLWorker::SFMLWorker()
{
	sf::ContextSettings settings;

	settings.antialiasingLevel = 10;


	window = new sf::RenderWindow(sf::VideoMode(800, 800), "Chakov_Vladimir", sf::Style::Close, settings);
}

void SFMLWorker::work()
{
	window->clear(sf::Color::Black);

	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			// Close program
			if (event.type == sf::Event::Closed)
			{
				window->close();

				return;
			}

			manageEvent(event);
		}

		window->clear(sf::Color::Black);

		std::vector<PropertiesOfFigure*> figures = Controller::getState().getFigures();

		std::vector<sf::Shape*> shapes;

		for (auto& figure : figures)
		{
			sf::Shape* shape = (sf::Shape*)(new SFMLShape(figure));
			shapes.push_back(shape);
		}
		for (auto& shape : shapes)
		{
			window->draw(*shape);
		}

		for (auto& shape : shapes)
		{
			delete shape;
		}

		

		window->display();

	
	}
}

void SFMLWorker::manageEvent(sf::Event event)
{
	//1 -  Create Rectangle
	 if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
	{
	Controller::getState().createRectangle();
	}
	//2 - Create Circle 
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
	{
		Controller::getState().createCircle();
	}
	// Q - Change color
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
	{
		Controller::getState().changeColor();
	}
	// Left Click - Select figure
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mouse_position;
		mouse_position.x = sf::Mouse::getPosition(*window).x;
		mouse_position.y = sf::Mouse::getPosition(*window).y;

		Controller::getState().selectFigure(mouse_position.x, mouse_position.y);
	}
	// Right Click - Aggregate / Deaggregate all figures 
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		Controller::getState().setAggregation(!Controller::getState().isAggregated());
	}

	//P - Clone aggregates
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Controller::getState().cloneAggreagte();
	}
	//E - Auto move
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
	{
		Controller::getState().moveAuto();
	}
	// Move
	else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up ||
		event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left ||
		event.key.code == sf::Keyboard::Right))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Controller::getState().move(LEFT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Controller::getState().move(RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Controller::getState().move(UP);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Controller::getState().move(DOWN);
		}
	}
	// F5 - Save figures to file "figures.txt"
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
	{
		Controller::getState().saveProgress();
	}
	//  F9 - Load figures from file "figures.txt"
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F9)
	{
		Controller::getState().loadProgress();
	}
}
