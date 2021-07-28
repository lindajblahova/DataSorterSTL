#pragma once

#include <vector>
#include "../Manager/Manager.h"
#include "Tasks.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	Tasks chooseTaskToPerform();

	void chooseFiltersToUse();
	void createFilters();
	void performFiltration();
	void writeFilteredResults();

	SortBy chooseSortingProperties();
	void performSorting(SortBy sortBy);
	void writeSortedResults(SortBy sortBy);

private:

	void requestName(std::wstring& name);
	void requestType(int& type);
	void requestParentName(std::wstring& parentName);
	void requestPopulationInterval(unsigned int& minPopulation, unsigned int& maxPopulation);
	void requestBuiltUpRateInterval(double& builtUpRateMin, double& builtUpRateMax);
	void requestSortingOrder(bool& ascendingOrder);

	SortBy mapToSortBy(int sortByInput);
	Tasks mapToTasks(int taskToPerform);

	std::list<std::shared_ptr<ITerritorialUnit>>& getTerritorialUnits();

	void writeTasksMenu();
	void writeFilterMenu();
	void writeSortMenu();
	
	inline void addSeparator();

private:
	std::vector<int> m_filterNumbers;
	SortBy m_sortBy = SortBy::None;
	Tasks m_taskToPerform = Tasks::None;
	std::unique_ptr<Manager> m_manager = std::make_unique<Manager>();
};

