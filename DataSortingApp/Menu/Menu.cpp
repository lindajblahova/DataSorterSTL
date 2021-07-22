#include "Menu.h"

Menu::Menu()
{
	m_manager->read();
}

void Menu::chooseFilters()
{
	m_manager->read();
	std::wcout << L"Choose which filters you want to apply" << std::endl;
	std::wcout << L" 1 - Name Filter" << std::endl;
	std::wcout << L" 2 - Type Filter" << std::endl;
	std::wcout << L" 3 - Belongs to Filter" << std::endl;
	std::wcout << L" 4 - Population Filter" << std::endl;
	std::wcout << L" 5 - Built up rate Filter" << std::endl;
	std::wcout << L" 0 - Continue" << std::endl;

	addSeparator();

	std::wstring line;

	while (true)
	{
		std::wcout << L"Filter number: ";
		std::getline(std::wcin, line);
		if (line == L"0")
		{
			break;
		}
		m_filterNumbers.push_back(std::stoi(line));
	}

	createFilters();
}

void Menu::chooseSorting()
{
	std::wstring line;
	bool ascendingOrder = true;
	SortBy sortBy = SortBy::Name;

	std::wcout << L"Choose a sorting criterion: ";
	std::wcout << L" 1 - Sort by name" << std::endl;
	std::wcout << L" 2 - Sort by population" << std::endl;
	std::wcout << L" 3 - Sort by built up rate" << std::endl;
	std::getline(std::wcin, line);

	switch (std::stoi(line))
	{
	case 1:
		sortBy = SortBy::Name;
		break;
	case 2:
		sortBy = SortBy::Population;
		break;
	case 3:
		sortBy = SortBy::BuiltUpRate;
		break;
	default:
		break;
	}

	std::wcout << L"Choose a sorting order: ";
	std::wcout << L" 1 - Ascending" << std::endl;
	std::wcout << L" 2 - Descending" << std::endl;
	std::getline(std::wcin, line);
	ascendingOrder = std::stoi(line) == 2 ? false : true; // 2 descending otherwise ascending
	m_manager->sortTerritorialUnits(ascendingOrder, sortBy);
}

void Menu::createFilters()
{
	std::wstring name, parentName;
	int typeNumber{ 0 }, minPopulation{ 0 }, maxPopulation{ 0 };
	double builtUpRateMin{ 0.0 }, builtUpRateMax{ 0.0 };

	for (int i = 0; i < m_filterNumbers.size(); i++)
	{
		addSeparator();

		switch (m_filterNumbers[i])
		{
		case 1:
			requestName(name);
			m_manager->addFilterName(name);
			break;
		case 2:
			requestType(typeNumber);
			m_manager->addFilterType(typeNumber);
			break;
		case 3:
			requestParentName(parentName);
			m_manager->addFilterParent(parentName);
			break;
		case 4:
			requestPopulationInterval(minPopulation, maxPopulation);
			m_manager->addFilterPopulation(minPopulation, maxPopulation);
			break;
		case 5:
			requestBuiltUpRateInterval(builtUpRateMin, builtUpRateMax);
			m_manager->addFilterBuiltUpRate(builtUpRateMin, builtUpRateMax);
			break;
		default:
			break;
		}
	}

	addSeparator();
	doFiltration();
}

void Menu::requestName(std::wstring& name)
{
	std::wcout << L"Enter name of territorial unit: ";
	std::getline(std::wcin, name);
}

void Menu::requestType(int& type)
{
	std::wcout << L"Enter type (1 - Commune, 2 - District, 3 - Region, 4 - State) of territorial unit: " << std::endl;
	std::wcin >> type;
}

void Menu::requestParentName(std::wstring& parentName)
{
	std::wcout << L"Enter name of parent territorial unit: ";
	std::getline(std::wcin, parentName);
}

void Menu::requestPopulationInterval(int& minPopulation, int& maxPopulation)
{
	std::wcout << L"Enter minimal population of territorial unit: ";
	std::wcin >> minPopulation;

	std::wcout << L"Enter maximal population of territorial unit: ";
	std::wcin >> maxPopulation;
}

void Menu::requestBuiltUpRateInterval(double& builtUpRateMin, double& builtUpRateMax)
{
	std::wcout << L"Enter minimal built up rate of territorial unit: ";
	std::wcin >> builtUpRateMin;

	std::wcout << L"Enter maximal built up rate of territorial unit: ";
	std::wcin >> builtUpRateMax;
}

void Menu::doFiltration()
{
	m_manager->filterTerritorialUnits();
}

inline void Menu::addSeparator()
{
	std::wcout << L"___________________________________________________________________________________________" << std::endl << std::endl;
}
