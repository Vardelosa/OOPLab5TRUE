#pragma once
#include "Figure.h"


// Прототип класса-паттерна Memento для Figure
class FigureMemento;


// Класс определяющий сущность фигуры - круг
//
// Любая фигура - круг с разным количеством точек для отрисовки
//
class Circle : public Figure, public FigureSettings, public PropertiesOfFigure
{
private:
	// Радиус
	float radius;
	//Кол-во точек
	int points;
	// Цвет
	std::vector<int> color;
	// Положение на экране
	float position_x;
	float position_y;
	// Центр фигуры
	float origin_x;
	float origin_y;
	// Масштаб
	float scale;

	// Установка центра круга
	void setOrigins(float _radius);
	void checkBorders();

protected:
	// Установка кол-ва точек
	void setPointsCount(int _points);

public:
	Circle();

	Circle(float radius, std::vector<int> color, float position_x, float position_y, float scale);

	// Стандартные параметры
	virtual void setDefault();
	// Кастомные параметры
	void setCustom(float radius, std::vector<int> color, float position_x, float position_y, float scale);

	// Тип
	virtual std::string getType();

	// Радиус
	float getRadius();
	void setRadius(float _radius);

	// Сторона - радиус
	virtual float getSide();

	// Цвет
	std::vector<int> getColor();
	void setColor(std::vector<int> _color);

	// Кол-во точек
	int getPointsCount();

	// Позиция на экране
	float getPositionX();
	void setPositionX(float _x);

	float getPositionY();
	void setPositionY(float _y);

	// Центр круга
	float getOriginX();
	float getOriginY();

	// Масштаб
	float getScale();
	void setScale(float _scale);

	// Поворот фигуры для нормального отображения
	virtual float getRotation();

	// Сохранение состояния фигуры
	FigureMemento* save();
	void restore(FigureMemento* memento);

	// Клонирование фигуры
	virtual Figure* clone();

	// Движение
	void move(float speed, int direction);
	void autoMove(float speed);

	// Смена цвета
	void changeColor();
};


class Rectangle : public Circle
{
public:
	Rectangle();
	Rectangle(float radius, std::vector<int> color, float position_x, float position_y, float scale);

	void setDefault();

	float getSide();

	float getRotation();

	std::string getType();

	Figure* clone();
};

//----------------------MEMENTO------------------||
class FigureMemento
{
private:
	std::string data;

protected:
	std::string serializeFigure(Figure* figure);
	Figure* deserializeFigure(std::string _data);

	FigureMemento();

public:
	
	FigureMemento(Figure* figure);
	FigureMemento(std::string data);

	virtual Figure* getFigure();
	virtual std::string getData();
};


