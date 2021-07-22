#pragma once

#include <fcntl.h>
#include <io.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <functional>

#include "../TerritorialUnit/TerritorialUnit.h"
#include "../Filter/Filter.h"
#include "../Sort/Sort.h"

class Manager
{
public:
	Manager();
	~Manager();

	void read();
	std::list<std::shared_ptr<ITerritorialUnit>> getTerritorialUnits();
	bool meetsRequirements(std::shared_ptr<ITerritorialUnit>& territorialUnit);

	void addFilterName(const std::wstring& name);
	void addFilterType(const TypeTU type);
	void addFilterParent(const std::wstring& nameOfParent);
	void addFilterPopulation(const int minInterval, const int maxInterval);
	void addFilterBuiltUpRate(const double minInterval, const double maxInterval);

private:

	typedef std::function<bool(const std::shared_ptr<ITerritorialUnit>&)> FilterFunction;

	std::list<std::shared_ptr<ITerritorialUnit>> m_territorialUnits;
	std::unique_ptr<Filter> m_filter = std::make_unique<Filter>();
	std::unique_ptr<Sort> m_sort = std::make_unique<Sort>();
	std::list<std::shared_ptr<ITerritorialUnit>> m_chosenTerritorialUnits;
	std::list<FilterFunction> m_allFilters;


};
