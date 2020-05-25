#pragma once
#include "Figures.h"
#include <sstream>


class Aggregate: public Figure
{//----------------------------------COMPOSITE------------------------||
private:
	std::vector<Figure*> figures;

	friend class AggregateMemento;

public:
	Aggregate();
	~Aggregate();
	std::vector<PropertiesOfFigure*> getFigures();
	int containsType(std::string type);
	bool addFigure(Figure* figure);
	Figure* getFigure(int index);
	FigureMemento* save();
	void restore(FigureMemento* memento);
	// Color Changing
	void changeColor();
	// Type
	std::string getType();
	// Movement
	void move(float speed, int direction);
	void autoMove(float speed);
	// Cloning
	Figure* clone();
};

//--------------------------MEMENTO-------------------------||
class AggregateMemento: private FigureMemento
{
private:
	std::string data;
	//Aggregate info > file < file
	std::string serializeAggregate(Aggregate* _aggregate);
	Aggregate* deserializeAggregate(std::stringstream& stream);

public:
	AggregateMemento(std::string _data);
	AggregateMemento(Aggregate* _aggregate);
	Figure* getFigure();
	std::string getData();
};


class AggregateCaretaker
{
private:
	const std::string NAMES_FILE = "names.txt";

public:
	AggregateCaretaker();
	std::vector<Aggregate*> restoreState();
	void saveState(std::vector<Aggregate*> aggregates);
};