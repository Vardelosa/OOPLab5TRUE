#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int SPEED = 15;

// Прототип класса-паттерна Memento для Figure
class FigureMemento;

class FigureSettings
{
private:
	virtual void checkBorders() = 0;

public:
	// Установка параметров фигуры
	virtual void setDefault() = 0;
	virtual void setCustom(float radius, std::vector<int> color, float position_x, float position_y, float scale) = 0;

};

class PropertiesOfFigure
{
public:
	// Управление радиусом  фигуры
	virtual float getRadius() = 0;
	virtual void setRadius(float _radius) = 0;

	// Растояние от центра фигуры к краю
	virtual float getSide() = 0;

	// Управление RGB цветом
	virtual std::vector<int> getColor() = 0;
	virtual void setColor(std::vector<int> _color) = 0;

	// Управление формой фигуры (кол-во точек - тип фигуры)
	virtual int getPointsCount() = 0;
	virtual void setPointsCount(int _points) = 0;

	// Управление позицией фигуры на экране
	virtual float getPositionX() = 0;
	virtual void setPositionX(float _x) = 0;

	virtual float getPositionY() = 0;
	virtual void setPositionY(float _y) = 0;

	// Центр фигуры
	virtual float getOriginX() = 0;
	virtual float getOriginY() = 0;

	// Управление масштабом фигуры
	virtual float getScale() = 0;
	virtual void setScale(float _scale) = 0;

	// Поворот фигуры для правильного отображения
	virtual float getRotation() = 0;
};

// Абстрактный класс определяющий сущность фигуры
class Figure
{
public:
	// Тип фигуры
	virtual std::string getType() = 0;

	virtual void move(float speed, int direction) = 0;
	virtual void autoMove(float speed) = 0;

	virtual void changeColor() = 0;

	// Сохранение состояния фигуры
	virtual FigureMemento* save() = 0;
	virtual void restore(FigureMemento* memento) = 0;
	//----------------------------------------PROTOTYPE------------------------||
	// Клонирование фигуры (паттерн - Прототип)
	virtual Figure* clone() = 0;
};

