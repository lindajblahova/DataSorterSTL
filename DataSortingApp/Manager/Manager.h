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
#include "../SortBy.h"

class Manager
{
public:
	Manager() = default;
	~Manager() = default;

	void read();
	std::list<std::shared_ptr<ITerritorialUnit>> getTerritorialUnits();
	
	void addFilterName(const std::wstring& name);
	void addFilterType(const int type);
	void addFilterParent(const std::wstring& nameOfParent);
	void addFilterPopulation(const int minInterval, const int maxInterval);
	void addFilterBuiltUpRate(const double minInterval, const double maxInterval);

	void filterTerritorialUnits();

	void sortTerritorialUnits(bool inAscendingOrder, SortBy sortBy);

private:
	bool meetsRequirements(std::shared_ptr<ITerritorialUnit>& territorialUnit);

	void sortTerritorialUnitsByName();
	void sortTerritorialUnitsByPopulation();
	void sortTerritorialUnitsByBuiltUpRate();

	void writeTerritorialUnitsAllData(std::list<std::shared_ptr<ITerritorialUnit>>& listToWrite);

	inline void changeColor(int desiredColor);

private:

	typedef std::function<bool(const std::shared_ptr<ITerritorialUnit>&)> FilterFunction;

	std::list<std::shared_ptr<ITerritorialUnit>> m_territorialUnits;
	std::list<std::shared_ptr<ITerritorialUnit>> m_chosenTerritorialUnits;
	std::unique_ptr<Filter> m_filter = std::make_unique<Filter>();
	std::unique_ptr<Sort> m_sort = std::make_unique<Sort>();
	std::list<FilterFunction> m_allFilters;


};
