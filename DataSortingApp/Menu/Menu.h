#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "../Manager/Manager.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	void chooseFilters();

	void chooseSorting();

private:
	void createFilters();

	void requestName(std::wstring & name);
	void requestType(int& type);
	void requestParentName(std::wstring & parentName);
	void requestPopulationInterval(int& minPopulation, int& maxPopulation);
	void requestBuiltUpRateInterval(double& builtUpRateMin, double& builtUpRateMax);

	void doFiltration();

	inline void addSeparator();

private:
	std::vector<int> m_filterNumbers;
	SortBy m_sortBy;
	std::unique_ptr<Manager> m_manager = std::make_unique<Manager>();
};

