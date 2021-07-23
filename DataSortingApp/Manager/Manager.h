#pragma once

#include <fcntl.h>
#include <io.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <functional>

#include <Windows.h>

#include "../TerritorialUnit/TerritorialUnit.h"
#include "../Filter/Filter.h"
#include "../Sort/Sort.h"
#include "../Menu/Tasks.h"

class Manager
{
public:
	Manager() = default;
	~Manager() = default;

	void read();
	
	void addFilterName(const std::wstring& name);
	void addFilterType(int type);
	void addFilterParent(const std::wstring& nameOfParent);
	void addFilterPopulation(unsigned int minInterval, unsigned int maxInterval);
	void addFilterBuiltUpRate(double minInterval, double maxInterval);

	void filterTerritorialUnits(Tasks taskToPerform);

	void sortTerritorialUnits(bool inAscendingOrder, SortBy sortBy, Tasks taskToPerform);

private:
	bool meetsRequirements(const std::shared_ptr<ITerritorialUnit>& territorialUnit);

	void writeTerritorialUnitsAllData(const std::list<std::shared_ptr<ITerritorialUnit>>& listToWrite);
	void writeTerritorialUnitsSomeData(const std::list<std::shared_ptr<ITerritorialUnit>>& listToWrite, SortBy sortBy);

	inline void changeColor(int desiredColor);

private:

	typedef std::function<bool(const std::shared_ptr<ITerritorialUnit>&)> FilterFunction;

	std::list<std::shared_ptr<ITerritorialUnit>> m_territorialUnits;
	std::list<std::shared_ptr<ITerritorialUnit>> m_chosenTerritorialUnits;
	std::list<FilterFunction> m_allFilters;
	std::unique_ptr<Filter> m_filter = std::make_unique<Filter>();
	std::unique_ptr<Sort> m_sort = std::make_unique<Sort>();



};
