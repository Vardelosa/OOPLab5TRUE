#include "Figures.h"
#include <time.h>


std::string FigureMemento::serializeFigure(Figure* figure)
{
	PropertiesOfFigure* props = dynamic_cast<PropertiesOfFigure*>(figure);

	return figure->getType() + ' ' + std::to_string(props->getRadius()) + ' ' +
		std::to_string(props->getColor()[0]) + ' ' + std::to_string(props->getColor()[1]) + ' ' + std::to_string(props->getColor()[2]) + ' ' +
		std::to_string(props->getPositionX()) + ' ' + std::to_string(props->getPositionY()) + ' ' + std::to_string(props->getScale());
}


Figure* FigureMemento::deserializeFigure(std::string _data)
{
	std::string temp = _data;

	std::string type = temp.substr(0, temp.find(' '));
	temp = temp.substr(temp.find(' ') + 1);

	float radius = std::stof(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	int color_red = std::stoul(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	int color_green = std::stoul(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	int color_blue = std::stoul(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	float position_x = std::stof(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	float position_y = std::stof(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	float scale = std::stof(temp.substr(0, temp.find(' ')));
	temp = temp.substr(temp.find(' ') + 1);

	Figure* figure = nullptr;

	if (type == "Circle")
	{
		figure = new Circle(radius, { color_red, color_green, color_blue }, position_x, position_y, scale);
	}
	else if (type == "Rectangle")
	{
		figure = new Rectangle(radius, { color_red, color_green, color_blue }, position_x, position_y, scale);
	}

	return figure;
}


FigureMemento::FigureMemento()
{
}

FigureMemento::FigureMemento(Figure* figure)
{
	data = serializeFigure(figure);
}


FigureMemento::FigureMemento(std::string _data)
{
	data = _data;
}


Figure* FigureMemento::getFigure()
{
	return deserializeFigure(data);
}


std::string FigureMemento::getData()
{
	return data;
}


Circle::Circle()
{
	const int POINTS = 30;
	setPointsCount(POINTS);

	setDefault();
}


Circle::Circle(float _radius, std::vector<int> _color, float _position_x, float _position_y, float _scale)
{
	const int POINTS = 30;
	setPointsCount(POINTS);

	setCustom(_radius, _color, _position_x, _position_y, _scale);
}


void Circle::setDefault()
{
	const float RADIUS = 100.0f;
	const std::vector<int> COLOR = { 255, 204, 0 };
	const float POSITION_X = RADIUS;
	const float POSITION_Y = RADIUS;
	const float SCALE = 1.0f;

	setCustom(RADIUS, COLOR, POSITION_X, POSITION_Y, SCALE);
}


void Circle::setCustom(float _radius, std::vector<int> _color, float _position_x, float _position_y, float _scale)
{
	setRadius(_radius);
	setColor(_color);
	setPositionX(_position_x);
	setPositionY(_position_y);
	setOrigins(_radius);
	setScale(_scale);
}


std::string Circle::getType()
{
	return "Circle";
}


float Circle::getRadius()
{
	return radius;
}

void Circle::setRadius(float _radius)
{
	radius = _radius;
}


float Circle::getSide()
{
	return getRadius() * getScale();
}


std::vector<int> Circle::getColor()
{
	return color;
}


void Circle::setColor(std::vector<int> _color)
{
	color = _color;
}


int Circle::getPointsCount()
{
	return points;
}


void Circle::setPointsCount(int _points)
{
	points = _points;
}


void Circle::setOrigins(float _radius)
{
	origin_x = _radius;
	origin_y = _radius;
}

void Circle::checkBorders()
{
	const int WINDOW_SIZE = 800;

	int y_top_coordinate = getPositionY();
	int x_left_coordinate = getPositionX();

	float side = getSide();

	if (x_left_coordinate > WINDOW_SIZE - side)
	{
		setPositionX(WINDOW_SIZE - side);
	}
	if (x_left_coordinate < side)
	{
		setPositionX(side);
	}
	if (y_top_coordinate > WINDOW_SIZE - side)
	{
		setPositionY(WINDOW_SIZE - side);
	}
	if (y_top_coordinate < side)
	{
		setPositionY(side);
	}
}


float Circle::getPositionX()
{
	return position_x;
}


void Circle::setPositionX(float _x)
{
	position_x = _x;
}


float Circle::getPositionY()
{
	return position_y;
}


void Circle::setPositionY(float _y)
{
	position_y = _y;
}


float Circle::getOriginX()
{
	return origin_x;
}

float Circle::getOriginY()
{
	return origin_y;
}


float Circle::getScale()
{
	return scale;
}


void Circle::setScale(float _scale)
{
	scale = _scale;
}


float Circle::getRotation()
{
	return 0.0f;
}


FigureMemento* Circle::save()
{
	return new FigureMemento(this);
}


void Circle::restore(FigureMemento* memento)
{
	Figure* figure = memento->getFigure();

	//setCustom(figure->getRadius(), figure->getColor(), figure->getPositionX(), figure->getPositionY(), figure->getScale());

	delete figure;
}


Figure* Circle::clone()
{
	return new Circle(*this);
}

void Circle::move(float speed, int direction)
{
	if (direction == LEFT)
	{
		setPositionX(getPositionX() - SPEED);
	}
	if (direction == RIGHT)
	{
		setPositionX(getPositionX() + SPEED);
	}
	if (direction == UP)
	{
		setPositionY(getPositionY() - SPEED);
	}
	if (direction == DOWN)
	{
		setPositionY(getPositionY() + SPEED);
	}

	checkBorders();
}

void Circle::autoMove(float speed)
{
	const float RADIUS = getRadius() / 2;
	static float angle = 0.0f;

	float x = getPositionX() + cos(angle) * RADIUS;
	float y = getPositionY() + sin(angle) * RADIUS;

	setPositionX(x);
	setPositionY(y);

	checkBorders();

	angle += 0.2f;
}

void Circle::changeColor()
{
	srand(time(NULL));

	const int SIZE = 7;
	static std::vector<std::vector<int>> colors = { {255, 204, 0},
													{255, 0, 0},
													{51, 153, 51},
													{0, 102, 204},
													{204, 0, 153},
													{255, 255, 255},
													{255, 102, 204}
	};

	int color_index = rand() % SIZE;

	setColor(colors[color_index]);
}


Rectangle::Rectangle()
{
	const int POINTS = 4;
	setPointsCount(POINTS);

	setDefault();
}


Rectangle::Rectangle(float radius, std::vector<int> color, float position_x, float position_y, float scale)
{
	const int POINTS = 4;
	setPointsCount(POINTS);

	setCustom(radius, color, position_x, position_y, scale);
}


void Rectangle::setDefault()
{
	const float RADIUS = 100.0f;
	const std::vector<int> COLOR = { 0, 102, 204 };
	const float POSITION_X = 800 - RADIUS / sqrt(2.0f);
	const float POSITION_Y = RADIUS / sqrt(2.0f);
	const float SCALE = 1.0f;

	setCustom(RADIUS, COLOR, POSITION_X, POSITION_Y, SCALE);
}


float Rectangle::getSide()
{
	return getRadius() / sqrt(2.0f) * getScale();
}


float Rectangle::getRotation()
{
	return 45.0f;
}


std::string Rectangle::getType()
{
	return "Rectangle";
}

Figure* Rectangle::clone()
{
	return new Rectangle(*this);
}
