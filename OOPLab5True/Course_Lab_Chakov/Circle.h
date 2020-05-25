#pragma once
#include "Figure.h"


//class Circle: public Figure
//{
//private:
//	float radius;
//	int points;
//	std::vector<int> color;
//	float position_x;
//	float position_y;
//	float origin_x;
//	float origin_y;
//	float scale;
//
//	void setOrigins(float _radius);
//
//protected:
//	void setPointsCount(int _points);
//
//public:
//	Circle();
//
//	Circle(float radius, std::vector<int> color, float position_x, float position_y, float scale);
//
//	virtual void setDefault();
//	void setCustom(float radius, std::vector<int> color, float position_x, float position_y, float scale);
//	
//	virtual std::string getType();
//
//	float getRadius();
//	void setRadius(float _radius);
//
//	virtual float getSide();
//
//	std::vector<int> getColor();
//	void setColor(std::vector<int> _color);
//
//	int getPointsCount();
//
//	float getPositionX();
//	void setPositionX(float _x);
//
//	float getPositionY();
//	void setPositionY(float _y);
//
//	float getOriginX();
//	float getOriginY();
//
//	float getScale();
//	void setScale(float _scale);
//
//	virtual float getRotation();
//
//	FigureMemento* save();
//	void restore(FigureMemento* memento);
//
//	Figure* clone();
//};