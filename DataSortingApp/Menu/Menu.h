#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "../Manager/Manager.h"

class Menu
{
public:
	Menu(std::shared_ptr<Manager> manager);
	~Menu() = default;

	void chooseFilters();

private:
	void createFilters();

	void requestName(std::wstring& name);
	void requestType(int& type);
	void requestParentName(std::wstring& name);
	void requestPopulationInterval(int& minPopulation, int& maxPopulation);
	void requestBuiltUpRateInterval(double& builtUpRateMin, double& builtUpRateMax);

	void doFiltration();

	inline void addSeparator();

private:
	std::vector<int> m_filterNumbers;
	std::shared_ptr<Manager> m_manager;
};

