#pragma once

#include <vector>
#include "../Manager/Manager.h"
#include "Tasks.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	void chooseTasks();

private:

	void chooseFilters();
	void chooseSorting();

	void createFilters();

	void requestName(std::wstring& name);
	void requestType(int& type);
	void requestParentName(std::wstring& parentName);
	void requestPopulationInterval(unsigned int& minPopulation, unsigned int& maxPopulation);
	void requestBuiltUpRateInterval(double& builtUpRateMin, double& builtUpRateMax);
	void requestSortingOrder(bool& ascendingOrder);
	
	inline void addSeparator();

private:
	SortBy mapToSortBy(int sortByInput);

private:
	std::vector<int> m_filterNumbers;
	SortBy m_sortBy = SortBy::Name;
	Tasks m_taskToPerform = Tasks::Filter;
	std::unique_ptr<Manager> m_manager = std::make_unique<Manager>();
};

