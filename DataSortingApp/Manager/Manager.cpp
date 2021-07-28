#include "Manager.h"
#include "../Comparator/ComparatorByName.h"
#include "../Comparator/ComparatorByPopulation.h"
#include "../Comparator/ComparatorByBuiltUpRate.h"

#include <fcntl.h>
#include <io.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>

void Manager::readTerritorialUnitsFromFiles()
{
	std::wstring name, commune, district, region;
	unsigned int preProd{ 0 }, prod{ 0 }, postProd{0};
	double totalArea{ 0.0 }, bulidUpArea{ 0.0 };

	std::wifstream dataCommune("data/file.txt");

	std::wifstream dataParent("data/file2.txt");

	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);

	dataCommune.imbue(std::locale("sk_SK.UTF8"));
	dataParent.imbue(std::locale("sk_SK.UTF8"));

	std::shared_ptr<ITerritorialUnit> stateTU = std::make_shared<TerritorialUnit>(L"Slovensko", TerritorialUnitType::State, nullptr, 0, 0, 0, 0.0, 0.0);
	m_territorialUnits.push_back(stateTU);

	std::shared_ptr<ITerritorialUnit> regionTU;
	std::shared_ptr<ITerritorialUnit> districtTU;
	std::shared_ptr<ITerritorialUnit> communeTU;

	if (dataCommune.is_open() && dataParent.is_open())
	{
		std::wstring line;
		getline(dataCommune, line);
		getline(dataParent, line);

		while (dataCommune.good() && dataParent.good())
		{
			std::getline(dataCommune, line, L';');
			name = line;
			std::getline(dataCommune, line, L';');
			preProd = stoi(line);
			std::getline(dataCommune, line, L';');
			prod = stoi(line);
			std::getline(dataCommune, line, L';');
			postProd = stoi(line);
			std::getline(dataCommune, line, L';');
			totalArea = stod(line);
			std::getline(dataCommune, line, L'\n');
			bulidUpArea = stod(line);
			
			std::getline(dataParent, line, L';');
			commune = line;
			std::getline(dataParent, line, L';');
			district = line;
			std::getline(dataParent, line, L'\n');
			region = line;

			stateTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);

			auto itrRegion = std::find_if(m_territorialUnits.begin(), m_territorialUnits.end(), [region](std::shared_ptr<ITerritorialUnit> value) { return value->getName() == region; });

			if (itrRegion  != m_territorialUnits.end())
			{
				regionTU = *itrRegion;
				regionTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);
			}
			else
			{
				regionTU = std::make_shared<TerritorialUnit>(region, TerritorialUnitType::Region, stateTU, preProd, prod, postProd, totalArea, bulidUpArea);
				m_territorialUnits.push_back(regionTU);
			}
			
			auto itrDistrict = std::find_if(m_territorialUnits.begin(), m_territorialUnits.end(), [district](std::shared_ptr<ITerritorialUnit> value) { return value->getName() == district; });

			if (itrDistrict != m_territorialUnits.end())
			{
				districtTU = *itrDistrict;
				districtTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);
			}
			else
			{
				districtTU = std::make_shared<TerritorialUnit>(district, TerritorialUnitType::District, regionTU, preProd, prod, postProd, totalArea, bulidUpArea);
				m_territorialUnits.push_back(districtTU);
			}
			
			communeTU = std::make_shared<TerritorialUnit>(name, TerritorialUnitType::Commune, districtTU, preProd, prod, postProd, totalArea, bulidUpArea);
			m_territorialUnits.push_back(communeTU);
		}
		dataCommune.close();
		dataParent.close();
	}
	
}

void Manager::writeTerritorialUnitsAllData(const std::list<std::shared_ptr<ITerritorialUnit>>& territorialUnitsToWrite)
{
	std::unique_ptr<ICriterion> criterion = std::make_unique<Criterion>();
	for (auto const& i : territorialUnitsToWrite) {
		
		std::shared_ptr<ITerritorialUnit> territorialUnitTMP = i;
		changeColor(11);
		while (territorialUnitTMP->getParent() != nullptr)
		{
			territorialUnitTMP = territorialUnitTMP->getParent();
			std::wcout << (territorialUnitTMP->getType() == TerritorialUnitType::District ? L" | District: "  : 
				(territorialUnitTMP->getType() == TerritorialUnitType::Region ? L" | Region: " : L" | State: "))
				<< criterion->name(territorialUnitTMP) ;
		}
		std::wcout << std::endl;

		changeColor(14);
		std::wcout << L" | Territorial unit: " << criterion->name(i);
		changeColor(6);
		std::wcout << L" | Population: " << criterion->population(i);
		changeColor(4);
		std::wcout << L" | Preproductive: " << criterion->preProductive(i);
		changeColor(2);
		std::wcout << L" | Productive: " << criterion->productive(i);
		changeColor(3);
		std::wcout << L" | PostProductive: " << criterion->postProductive(i);
		changeColor(8);
		wprintf(L" | Total Area: %.2f km²", (criterion->totalArea(i) / 1000.0));        // TODO inak ? 
		changeColor(15);
		wprintf(L" | Built up area: %.2f km²", (criterion->builtUpArea(i) / 1000.0));
		changeColor(10);
		wprintf(L" | Built up rate: %.2f", criterion->builtUpRate(i));
		std::wcout << L"%" << std::endl << std::endl;
	}
	changeColor(7);
}

void Manager::writeTerritorialUnitsSomeData(const std::list<std::shared_ptr<ITerritorialUnit>>& territorialUnitsToWrite, SortBy sortBy)
{
	std::unique_ptr<ICriterion> criterion = std::make_unique<Criterion>();
	for (auto const& i : territorialUnitsToWrite) {

		changeColor(14);
		std::wcout << L" | Territorial unit: " << criterion->name(i);

		switch (sortBy)
		{
		case SortBy::Name:
			std::wcout << std::endl;
			break;
		case SortBy::Population:
			changeColor(6);
			std::wcout << L" | Population: " << criterion->population(i) << std::endl << std::endl;
			break;
		case SortBy::BuiltUpRate:
			changeColor(10);
			wprintf(L" | Built up rate: %.2f", criterion->builtUpRate(i));
			std::wcout << L"%" << std::endl << std::endl;
			break;
		default:
			break;
		}
	
	}
	changeColor(7);

}

void Manager::clearChosenFilters()
{
	m_allFilters.clear();
}

void Manager::clearChosenTerritorialUnits()
{
	m_chosenTerritorialUnits.clear();
}

void Manager::clearAllTerritorialUnits()
{
	m_territorialUnits.clear();
}

void Manager::addFilterName(const std::wstring& name)
{
	m_allFilters.push_back([name, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasName(teritorialUnit, name);
		});
}

void Manager::addFilterType(int typeNumber)
{
	TerritorialUnitType type = mapToTerritorialUnitType(typeNumber);
	m_allFilters.push_back([type, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasType(teritorialUnit, type);
		});
}

void Manager::addFilterParent(const std::wstring& nameOfParent)
{
	auto itrParent = std::find_if(m_territorialUnits.begin(), m_territorialUnits.end(), [&nameOfParent](const std::shared_ptr<ITerritorialUnit>& territorialUnit)
		{ return territorialUnit->getName() == nameOfParent; });

	if (itrParent != m_territorialUnits.end())
	{
		auto parentTerritorialUnit = *itrParent;
		m_allFilters.push_back([parentTerritorialUnit, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
			return m_filter->hasParent(teritorialUnit, parentTerritorialUnit);
			});
	}
	else
	{
		std::wcout << L"Zadana rodicovska jednotka neexistuje, filter nebol aplikovany" << std::endl; // TODO what ?
	}
}

void Manager::addFilterPopulation(unsigned int minInterval, unsigned int maxInterval)
{
	m_allFilters.push_back([minInterval, maxInterval, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasPopulation(teritorialUnit, minInterval, maxInterval);
		});
}

void Manager::addFilterBuiltUpRate(double minInterval, double maxInterval)
{
	m_allFilters.push_back([minInterval, maxInterval, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasBuiltUpRate(teritorialUnit, minInterval, maxInterval);
		});
}

void Manager::filterTerritorialUnits(Tasks taskToPerform)
{
	std::copy_if(m_territorialUnits.begin(), m_territorialUnits.end(), std::back_inserter(m_chosenTerritorialUnits),
		[this](std::shared_ptr<ITerritorialUnit>& territorialUnit)
		{
			return meetsRequirements(territorialUnit);
		});
}

void Manager::setSortParameters(bool inAscendingOrder, SortBy sortBy)
{
	m_comparator = createComparator(sortBy);

	m_comparator->setOrder(inAscendingOrder);
}

std::list<std::shared_ptr<ITerritorialUnit>>& Manager::chooseTerritorialUnitsToUse(Tasks taskToPerform)
{
	switch (taskToPerform)
	{
	case Tasks::Sort:
		return m_territorialUnits;
	default:
		return m_chosenTerritorialUnits;
	}
}

void Manager::sortTerritorialUnits(std::list<std::shared_ptr<ITerritorialUnit>>& territorialUnitsToSort)
{
	territorialUnitsToSort.sort([this](const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
		{ 
			return m_comparator->compare(territorialUnit1, territorialUnit2);
		});
}

bool Manager::meetsRequirements(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return std::all_of(m_allFilters.begin(), m_allFilters.end(),
		[this, territorialUnit](const auto& filterFunction) {return filterFunction(territorialUnit); });
}

TerritorialUnitType Manager::mapToTerritorialUnitType(int type)
{
	switch (type)
	{
	case 1:
		return TerritorialUnitType::Commune;
	case 2:
		return TerritorialUnitType::District;
	case 3:
		return TerritorialUnitType::Region;
	case 4:
		return TerritorialUnitType::State;
	default:
		return TerritorialUnitType::None;
	}
}

std::unique_ptr<IComparator> Manager::createComparator(SortBy sortBy)
{
	switch (sortBy)
	{
	case SortBy::Name:
		return std::make_unique<ComparatorByName>();
	case SortBy::Population:
		return std::make_unique<ComparatorByPopulation>();
	case SortBy::BuiltUpRate:
		return std::make_unique<ComparatorByBuiltUpRate>();
	}
}

inline void Manager::changeColor(int desiredColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}