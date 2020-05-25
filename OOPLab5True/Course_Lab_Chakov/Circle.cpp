#include "Circle.h"

//Circle::Circle()
//{
//	const int POINTS = 30;
//	setPointsCount(POINTS);
//
//	setDefault();
//}
//
//Circle::Circle(float _radius, std::vector<int> _color, float _position_x, float _position_y, float _scale)
//{
//	const int POINTS = 30;
//	setPointsCount(POINTS);
//
//	setCustom(_radius, _color,  _position_x, _position_y, _scale);
//}
//
//void Circle::setDefault()
//{
//	const float RADIUS = 100.0f;
//	const std::vector<int> COLOR = {255, 204, 0};
//	const float POSITION_X = 550.0f;
//	const float POSITION_Y = 250.0f;
//	const float SCALE = 1.0f;
//
//	setCustom(RADIUS, COLOR, POSITION_X, POSITION_Y, SCALE);
//}
//
//void Circle::setCustom(float _radius, std::vector<int> _color, float _position_x, float _position_y, float _scale)
//{
//	setRadius(_radius);
//	setColor(_color);
//	setPositionX(_position_x);
//	setPositionY(_position_y);
//	setOrigins(_radius);
//	setScale(_scale);
//}
//
//std::string Circle::getType()
//{
//	return "Circle";
//}
//
//float Circle::getRadius()
//{
//	return radius;
//}
//
//void Circle::setRadius(float _radius)
//{
//	radius = _radius;
//}
//
//float Circle::getSide()
//{
//	return getRadius() * getScale();
//}
//
//std::vector<int> Circle::getColor()
//{
//	return color;
//}
//
//void Circle::setColor(std::vector<int> _color)
//{
//	color = _color;
//}
//
//int Circle::getPointsCount()
//{
//	return points;
//}
//
//void Circle::setPointsCount(int _points)
//{
//	points = _points;
//}
//
//void Circle::setOrigins(float _radius)
//{
//	origin_x = _radius;
//	origin_y = _radius;
//}
//
//float Circle::getPositionX()
//{
//	return position_x;
//}
//
//void Circle::setPositionX(float _x)
//{
//	position_x = _x;
//}
//
//float Circle::getPositionY()
//{
//	return position_y;
//}
//
//void Circle::setPositionY(float _y)
//{
//	position_y = _y;
//}
//
//float Circle::getOriginX()
//{
//	return origin_x;
//}
//
//float Circle::getOriginY()
//{
//	return origin_y;
//}
//
//float Circle::getScale()
//{
//	return scale;
//}
//
//void Circle::setScale(float _scale)
//{
//	scale = _scale;
//}
//
//float Circle::getRotation()
//{
//	return 0.0f;
//}
//
//FigureMemento* Circle::save()
//{
//	return new FigureMemento(this);
//}
//
//void Circle::restore(FigureMemento* memento)
//{
//	Figure* figure = memento->getFigure();
//
//	setCustom(figure->getRadius(), figure->getColor(), figure->getPositionX(), figure->getPositionY(), figure->getScale());
//
//	delete figure;
//}
//
//Figure* Circle::clone()
//{
//	FigureMemento memento(this);
//
//	return memento.getFigure();
//}
