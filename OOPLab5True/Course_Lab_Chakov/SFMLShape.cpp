#include "SFMLShape.h"

SFMLShape::SFMLShape(PropertiesOfFigure* figure)
{
	setConfigs(figure);
}

void SFMLShape::setConfigs(PropertiesOfFigure* figure)
{
	points = figure->getPointsCount();
	radius = figure->getRadius();

	setFillColor(sf::Color(figure->getColor()[0], figure->getColor()[1], figure->getColor()[2]));
	setPosition(figure->getPositionX(), figure->getPositionY());
	setOrigin(figure->getOriginX(), figure->getOriginY());
	setScale(sf::Vector2f(figure->getScale(), figure->getScale()));
	rotate(figure->getRotation());

	update();
}

std::size_t SFMLShape::getPointCount() const
{
	return points;
}

sf::Vector2f SFMLShape::getPoint(std::size_t index) const
{
	static const float pi = 3.141592654f;
	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;
	return { radius + x, radius + y };
}
