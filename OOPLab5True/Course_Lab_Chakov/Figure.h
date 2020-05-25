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

// �������� ������-�������� Memento ��� Figure
class FigureMemento;

class FigureSettings
{
private:
	virtual void checkBorders() = 0;

public:
	// ��������� ���������� ������
	virtual void setDefault() = 0;
	virtual void setCustom(float radius, std::vector<int> color, float position_x, float position_y, float scale) = 0;

};

class PropertiesOfFigure
{
public:
	// ���������� ��������  ������
	virtual float getRadius() = 0;
	virtual void setRadius(float _radius) = 0;

	// ��������� �� ������ ������ � ����
	virtual float getSide() = 0;

	// ���������� RGB ������
	virtual std::vector<int> getColor() = 0;
	virtual void setColor(std::vector<int> _color) = 0;

	// ���������� ������ ������ (���-�� ����� - ��� ������)
	virtual int getPointsCount() = 0;
	virtual void setPointsCount(int _points) = 0;

	// ���������� �������� ������ �� ������
	virtual float getPositionX() = 0;
	virtual void setPositionX(float _x) = 0;

	virtual float getPositionY() = 0;
	virtual void setPositionY(float _y) = 0;

	// ����� ������
	virtual float getOriginX() = 0;
	virtual float getOriginY() = 0;

	// ���������� ��������� ������
	virtual float getScale() = 0;
	virtual void setScale(float _scale) = 0;

	// ������� ������ ��� ����������� �����������
	virtual float getRotation() = 0;
};

// ����������� ����� ������������ �������� ������
class Figure
{
public:
	// ��� ������
	virtual std::string getType() = 0;

	virtual void move(float speed, int direction) = 0;
	virtual void autoMove(float speed) = 0;

	virtual void changeColor() = 0;

	// ���������� ��������� ������
	virtual FigureMemento* save() = 0;
	virtual void restore(FigureMemento* memento) = 0;
	//----------------------------------------PROTOTYPE------------------------||
	// ������������ ������ (������� - ��������)
	virtual Figure* clone() = 0;
};

