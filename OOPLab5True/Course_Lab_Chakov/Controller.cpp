#include "Controller.h"
#include "SFML/Graphics.hpp"

Controller::Controller()
{
	setAggregation(false);
};

Controller::~Controller()
{
	for (auto& aggregate : aggregates)
	{
		delete aggregate;
	}
}


Controller* Controller::operator=(Controller&)
{
	return this;
}

void Controller::checkTouch()
{
	std::vector<PropertiesOfFigure*> figures = getFigures();

	for (int index = 0; index < figures.size(); ++index)
	{
		for (int jndex = index + 1; jndex < figures.size(); ++jndex)
		{
			float first_left_x = figures[index]->getPositionX() - figures[index]->getSide();
			float first_left_y = figures[index]->getPositionY() - figures[index]->getSide();
			float first_right_x = figures[index]->getPositionX() + figures[index]->getSide();
			float first_right_y = figures[index]->getPositionY() + figures[index]->getSide();

			float second_left_x = figures[jndex]->getPositionX() - figures[jndex]->getSide();
			float second_left_y = figures[jndex]->getPositionY() - figures[jndex]->getSide();
			float second_right_x = figures[jndex]->getPositionX() + figures[jndex]->getSide();
			float second_right_y = figures[jndex]->getPositionY() + figures[jndex]->getSide();

			if (first_left_x > second_right_x || second_left_x > first_right_x)
			{
				continue;
			}

			if (first_left_y > second_right_y || second_left_y > first_right_y)
			{
				continue;
			}

			const float SCALE_INDEX = 0.95f;

			figures[index]->setScale(figures[index]->getScale() * SCALE_INDEX);
			figures[jndex]->setScale(figures[jndex]->getScale() * SCALE_INDEX);
		}
	}
}
//---------------------------------SINGLETON----------------------------------------||
Controller& Controller::getState()
{
	static Controller state;

	return state;
}

std::vector<PropertiesOfFigure*> Controller::getFigures()
{
	std::vector<PropertiesOfFigure*> figures;

	for (auto& aggregate : aggregates)
	{
		for (auto& figure : aggregate->getFigures())
		{
			figures.push_back(figure);
		}
	}

	return figures;
}

void Controller::generateFigure(std::string type)
{
	int aggregate_index = -1;
	int figure_index = -1;
	bool is_figure_exists = false;

	for (int index = 0; index < aggregates.size(); ++index)
	{
		figure_index = aggregates[index]->containsType(type);

		if (figure_index != -1)
		{
			is_figure_exists = true;
			aggregate_index = index;
			break;
		}
	}

	Figure* figure = nullptr;

	if (!is_figure_exists)
	{
		if (type == "Circle")
		{
			figure = new Circle();
		}
		else if (type == "Rectangle")
		{
			figure = new Rectangle();
		}
	}
	else
	{
		Figure* cloned_figure = aggregates[aggregate_index]->getFigure(figure_index);

		figure = cloned_figure->clone();
		dynamic_cast<FigureSettings*>(figure)->setDefault();
	}

	Aggregate* aggregate = new Aggregate();

	aggregate->addFigure(figure);

	selected_aggregate = aggregate;

	aggregates.push_back(aggregate);
}

std::vector<std::string> Controller::getAggregatesNames()
{
	std::ifstream file(FILE);

	std::vector<std::string> aggregates_names;

	while (!file.eof())
	{
		std::string temp;
		std::getline(file, temp, '\n');

		if (temp == "")
		{
			break;
		}

		aggregates_names.push_back(temp);
	}

	file.close();

	return aggregates_names;
}

void Controller::saveAggregatesNames()
{
	std::vector<std::string> names = getAggregatesNames();

	for (auto& name : names)
	{
		remove(name.c_str());
	}

	std::ofstream file(FILE);
	file.clear();

	for (int index = 0; index < aggregates.size() && file.is_open(); ++index)
	{
		file << "aggregate_" << index << ".txt" << '\n';
	}

	file.close();
}

void Controller::doAggregation(float mouse_position_x, float mouse_position_y)
{
	Aggregate* aggregate = getSelectedAggregate(mouse_position_x, mouse_position_y);

	if (!aggregate || selected_aggregate == aggregate)
	{
		return;
	}

	selected_aggregate->addFigure(aggregate);

	aggregates.erase(std::find(aggregates.begin(), aggregates.end(), aggregate));
}


void Controller::selectAggregate(float mouse_position_x, float mouse_position_y)
{
	selected_aggregate = getSelectedAggregate(mouse_position_x, mouse_position_y);
}


void Controller::createCircle()
{
	generateFigure("Circle");
}

void Controller::createRectangle()
{
	generateFigure("Rectangle");
}

void Controller::selectFigure(float mouse_position_x, float mouse_position_y)
{
	Aggregate* aggregate = getSelectedAggregate(mouse_position_x, mouse_position_y);

	if (!isAggregated() || !selected_aggregate)
	{
		selectAggregate(mouse_position_x, mouse_position_y);
	}
	else
	{
		doAggregation(mouse_position_x, mouse_position_y);
	}
}

void Controller::setAggregation(bool _is_aggregated)
{
	is_aggregated = _is_aggregated;
}

bool Controller::isAggregated()
{
	return is_aggregated;
}

void Controller::move(int direction)
{
	if (selected_aggregate)
	{
		selected_aggregate->move(SPEED, direction);

		checkTouch();
	}
}

void Controller::cloneAggreagte()
{
	aggregates.push_back(dynamic_cast<Aggregate*>(aggregates[0]->clone()));
}

void Controller::changeColor()
{
	if (selected_aggregate)
	{
		selected_aggregate->changeColor();
	}
}


void Controller::moveAuto()
{
	if (selected_aggregate)
	{
		selected_aggregate->autoMove(SPEED);

		checkTouch();
	}
}


Aggregate* Controller::getSelectedAggregate(float mouse_position_x, float mouse_position_y)
{
	for (auto& aggregate : aggregates)
	{
		if (getSelectedFigure(mouse_position_x, mouse_position_y, aggregate))
		{
			return aggregate;
		}
	}

	return nullptr;
}

Figure* Controller::getSelectedFigure(float mouse_position_x, float mouse_position_y, Aggregate* aggregate)
{
	std::vector<PropertiesOfFigure*> figures = aggregate->getFigures();

	for (auto& figure : figures)
	{
		if (mouse_position_x >= figure->getPositionX() - figure->getSide() &&
			mouse_position_x <= figure->getPositionX() + figure->getSide() &&
			mouse_position_y >= figure->getPositionY() - figure->getSide() &&
			mouse_position_y <= figure->getPositionY() + figure->getSide())
		{

			return dynamic_cast<Figure*>(figure);
		}
	}

	return nullptr;
}


void Controller::saveProgress()
{
	AggregateCaretaker caretaker = AggregateCaretaker();

	caretaker.saveState(aggregates);
}

void Controller::loadProgress()
{
	for (auto& aggregate : aggregates)
	{
		delete aggregate;
	}

	selected_aggregate = nullptr;

	AggregateCaretaker caretaker = AggregateCaretaker();

	aggregates = caretaker.restoreState();
}

