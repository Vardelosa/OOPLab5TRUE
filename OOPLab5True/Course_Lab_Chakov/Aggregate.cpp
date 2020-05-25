#include "Aggregate.h"




Aggregate::~Aggregate()
{
	for (int index = 0; index < figures.size(); ++index)
	{
		delete figures[index];
	}
}


Aggregate::Aggregate()
{
	figures = std::vector<Figure*>();
}


bool Aggregate::addFigure(Figure* figure)
{
	figures.push_back(figure);

	return true;
}


Figure* Aggregate::getFigure(int index)
{
	return figures[index];
}


std::vector<PropertiesOfFigure*> Aggregate::getFigures()
{
	std::vector<PropertiesOfFigure*> clear_figures;

	for (Figure* figure : figures)
	{
		if (figure->getType() != "Aggregate")
		{
			clear_figures.push_back(dynamic_cast<PropertiesOfFigure*>(figure));
		}
		else
		{
			std::vector<PropertiesOfFigure*> temp_figures = dynamic_cast<Aggregate*>(figure)->getFigures();

			for (auto& clear_figure : temp_figures)
			{
				clear_figures.push_back(clear_figure);
			}
		}
	}

	return clear_figures;
}




int Aggregate::containsType(std::string type)
{
	for (int index = 0; index < figures.size(); ++index)
	{
		if (figures[index]->getType() == type)
			return index;
	}

	return -1;
}


FigureMemento* Aggregate::save()
{
	return nullptr;//memento;
}


void Aggregate::restore(FigureMemento* memento)
{

}

std::string Aggregate::getType()
{
	return "Aggregate";
}

void Aggregate::move(float speed, int direction)
{
	for (auto& figure : figures)
	{
		figure->move(speed, direction);
	}
}

void Aggregate::autoMove(float speed)
{
	for (auto& figure : figures)
	{
		figure->autoMove(speed);
	}
}

void Aggregate::changeColor()
{
	for (auto& figure : figures)
	{
		figure->changeColor();
	}
}

Figure* Aggregate::clone()
{
	Aggregate* ag = new Aggregate();
	for (auto& temp : figures)
	{
		ag->addFigure(temp->clone());
	}
	return ag;
}

std::string AggregateMemento::serializeAggregate(Aggregate* _aggregate)
{
	std::string main_data = "Aggregate\n";

	for (auto& figure : _aggregate->figures)
	{
		if (figure->getType() == "Aggregate")
		{
			main_data += serializeAggregate(dynamic_cast<Aggregate*>(figure));
		}
		else
		{
			main_data += serializeFigure(figure) + '\n';
		}
	}

	main_data += "/Aggregate\n";

	return main_data;
}

Aggregate* AggregateMemento::deserializeAggregate(std::stringstream& stream)
{
	Aggregate* aggregate = new Aggregate();

	std::string line;

	std::getline(stream, line, '\n');

	if (line == "Aggregate") {
		std::getline(stream, line, '\n');
	}

	while (line != "/Aggregate")
	{
		Figure* figure = nullptr;

		if (line == ("Aggregate"))
		{
			figure = deserializeAggregate(stream);
		}
		else
		{
			figure = deserializeFigure(line);
		}

		aggregate->addFigure(figure);

		std::getline(stream, line, '\n');
	}

	return aggregate;
}

AggregateMemento::AggregateMemento(std::string _data)
{
	data = _data;
}

AggregateMemento::AggregateMemento(Aggregate* _aggregate)
{
	data = serializeAggregate(_aggregate);
}

Figure* AggregateMemento::getFigure()
{
	std::stringstream stream(data);

	return deserializeAggregate(stream);
}

std::string AggregateMemento::getData()
{
	return data;
}

AggregateCaretaker::AggregateCaretaker()
{
}

std::vector<Aggregate*> AggregateCaretaker::restoreState()
{
	std::vector<Aggregate*> aggregates;
	std::ifstream names_file(NAMES_FILE);
	std::string aggregate_name;

	std::getline(names_file, aggregate_name, '\n');

	while(aggregate_name != "")
	{
		std::ifstream aggregate_file(aggregate_name);
		std::string content((std::istreambuf_iterator<char>(aggregate_file)),
			(std::istreambuf_iterator<char>()));
		aggregate_file.close();

		Aggregate* aggregate = dynamic_cast<Aggregate*>(AggregateMemento(content).getFigure());
		aggregates.push_back(aggregate);

		std::getline(names_file, aggregate_name, '\n');
	}

	names_file.close();
	return aggregates;
}

void AggregateCaretaker::saveState(std::vector<Aggregate*> aggregates)
{
	std::ifstream names_file(NAMES_FILE);
	
	std::string old_filename;
	std::getline(names_file, old_filename, '\n');

	while (old_filename != "")
	{
		remove((old_filename + ".txt").c_str());
		std::getline(names_file, old_filename, '\n');
	}
	names_file.close();


	std::ofstream new_names_file(NAMES_FILE);
	new_names_file.clear();

	for (int index = 0; index < aggregates.size(); ++index)
	{
		std::string filename = "agg" + std::to_string(index) + ".txt";
		new_names_file << filename << "\n";

		AggregateMemento memento = AggregateMemento(aggregates[index]);

		std::ofstream aggregate_file(filename);

		aggregate_file << memento.getData();
		aggregate_file.close();
	}

	new_names_file.close();
}
