#pragma once
#include "Aggregate.h"


class Controller
{
private:
	std::vector<Aggregate*> aggregates;
	Aggregate* selected_aggregate;
	bool is_aggregated;
	bool is_delete;
	const std::string FILE = "list.txt";

	Controller();
	Controller(const Controller&);
	~Controller();
	Controller* operator=(Controller&);

	void checkTouch();

	Aggregate* getSelectedAggregate(float mouse_position_x, float mouse_position_y);
	Figure* getSelectedFigure(float mouse_position_x, float mouse_position_y, Aggregate* aggregate);

	void generateFigure(std::string type);

	std::vector<std::string> getAggregatesNames();
	void saveAggregatesNames();

	void doAggregation(float mouse_position_x, float mouse_position_y);
	void selectAggregate(float mouse_position_x, float mouse_position_y);

public:
	static Controller& getState();
	std::vector<PropertiesOfFigure*> getFigures();

	void createCircle();
	void createRectangle();

	void selectFigure(float mouse_position_x, float mouse_position_y);

	void setAggregation(bool is_aggregated);
	bool isAggregated();

	void move(int direction);

	void cloneAggreagte();

	void changeColor();

	void moveAuto();

	void saveProgress();
	void loadProgress();
};

