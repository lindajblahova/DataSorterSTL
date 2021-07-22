#include "Menu.h"

Menu::Menu()
{
	m_manager->read();
}

void Menu::chooseTasks()
{
	int taskToPerform = { 0 };
	std::wcout << L"Choose which task do you want to perform>" << std::endl;
	std::wcout << L" 1 - Filter territorial units by criteria" << std::endl;
	std::wcout << L" 2 - Sort territorial units by criterion" << std::endl;
	std::wcout << L" 3 - Filter and Sort filtered territorial units" << std::endl;
	std::wcout << L" Any other number - Close application" << std::endl;

	std::wcout << L" Task: " ;
	std::wcin >> taskToPerform;

	addSeparator();

	switch (taskToPerform)
	{
	case 1:
		m_taskToPerform = Tasks::Filter;
		chooseFilters();
		break;
	case 2:
		m_taskToPerform = Tasks::Sort;
		chooseSorting();
		break;
	case 3:
		m_taskToPerform = Tasks::Both;
		chooseFilters();
		chooseSorting();
		break;
	default:
		return;
	}

	addSeparator();
	std::wcout << L"Press enter to continue." << std::endl;
	std::wcin.get();
	chooseTasks();
}

void Menu::chooseFilters()
{
	std::wcout << L"Choose which filters you want to apply" << std::endl;
	std::wcout << L" 1 - Name Filter" << std::endl;
	std::wcout << L" 2 - Type Filter" << std::endl;
	std::wcout << L" 3 - Belongs to Filter" << std::endl;
	std::wcout << L" 4 - Population Filter" << std::endl;
	std::wcout << L" 5 - Built up rate Filter" << std::endl;
	std::wcout << L" 0 - Continue" << std::endl;

	addSeparator();

	int filterInput{ 1 };

	while (true)
	{
		std::wcout << L"Filter number: ";
		std::wcin >> filterInput;
		if (filterInput == 0)
		{
			break;
		}
		m_filterNumbers.push_back(filterInput);
	}

	createFilters();
}

void Menu::chooseSorting()
{
	int sortByInput{ 1 };
	bool ascendingOrder = true;
	SortBy sortBy = SortBy::Name;

	std::wcout << L"Choose a sorting criterion: " << std::endl;
	std::wcout << L" 1 - Sort by name" << std::endl;
	std::wcout << L" 2 - Sort by population" << std::endl;
	std::wcout << L" 3 - Sort by built up rate" << std::endl;
	addSeparator();

	std::wcout << L" Sort by: " << std::endl;
	std::wcin >> sortByInput;

	switch (sortByInput)
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

	requestSortingOrder(ascendingOrder);
	m_manager->sortTerritorialUnits(ascendingOrder, sortBy, m_taskToPerform);
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
	m_manager->filterTerritorialUnits(m_taskToPerform);
}

void Menu::requestName(std::wstring& name)
{
	std::wcout << L"Enter name of territorial unit: ";
	std::getline(std::wcin, name);
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

void Menu::requestSortingOrder(bool& ascendingOrder)
{
	addSeparator();
	int sortOrder{ 0 };
	std::wcout << L"Choose a sorting order: " << std::endl;
	std::wcout << L" 1 - Ascending" << std::endl;
	std::wcout << L" 2 - Descending" << std::endl;
	std::wcout << L"Sorting order: " << std::endl;
	std::wcin >> sortOrder;
	addSeparator();
	ascendingOrder = sortOrder == 2 ? false : true; // 2 descending otherwise ascending
}

inline void Menu::addSeparator()
{
	std::wcout << L"___________________________________________________________________________________________" << std::endl << std::endl;
}
