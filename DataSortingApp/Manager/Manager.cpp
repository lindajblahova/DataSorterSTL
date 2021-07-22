﻿#include "Manager.h"

void Manager::read()
{
	std::wstring name, commune, district, region;
	unsigned int preProd, prod, postProd;
	double totalArea, bulidUpArea;

	std::wifstream dataCommune("data/file.txt");

	std::wifstream dataParent("data/file2.txt");

	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);

	dataCommune.imbue(std::locale("sk_SK.UTF8"));
	dataParent.imbue(std::locale("sk_SK.UTF8"));

	std::shared_ptr<ITerritorialUnit> stateTU = std::make_shared<TerritorialUnit>(L"Slovensko", TypeTU::State, nullptr, 0, 0, 0, 0.0, 0.0);
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
				regionTU = std::make_shared<TerritorialUnit>(region, TypeTU::Region, stateTU, preProd, prod, postProd, totalArea, bulidUpArea);
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
				districtTU = std::make_shared<TerritorialUnit>(district, TypeTU::District, regionTU, preProd, prod, postProd, totalArea, bulidUpArea);
				m_territorialUnits.push_back(districtTU);
			}
			
			communeTU = std::make_shared<TerritorialUnit>(name, TypeTU::Commune, districtTU, preProd, prod, postProd, totalArea, bulidUpArea);
			m_territorialUnits.push_back(communeTU);
		}
		dataCommune.close();
		dataParent.close();
	}
	
}

std::list<std::shared_ptr<ITerritorialUnit>> Manager::getTerritorialUnits()
{
	return m_territorialUnits;
}

void Manager::writeTerritorialUnitsAllData(std::list<std::shared_ptr<ITerritorialUnit>>& listToWrite)
{

	std::unique_ptr<Criterion> criteria;
	for (auto const& i : listToWrite) {
		
		std::shared_ptr<ITerritorialUnit> territorialUnitTMP = i;
		changeColor(11);
		while (territorialUnitTMP->getParent() != nullptr)
		{
			territorialUnitTMP = territorialUnitTMP->getParent();
			std::wcout << (territorialUnitTMP->getType() == TypeTU::District ? L" | District: "  : 
				(territorialUnitTMP->getType() == TypeTU::Region ? L" | Region: " : L" | State: "))
				<< criteria->name(territorialUnitTMP) ;
		}
		std::wcout << std::endl;

		changeColor(14);
		std::wcout << L" | Territorial unit: " << criteria->name(i);
		changeColor(6);
		std::wcout << L" | Population: " << criteria->population(i);
		changeColor(4);
		std::wcout << L" | Preproductive: " << criteria->preProductive(i);
		changeColor(2);
		std::wcout << L" | Productive: " << criteria->productive(i);
		changeColor(3);
		std::wcout << L" | PostProductive: " << criteria->postProductive(i);
		changeColor(8);
		wprintf(L" | Total Area: %.2f km²", (criteria->totalArea(i) / 1000.0));        // TODO inak ? 
		changeColor(15);
		wprintf(L" | Built up area: %.2f km²", (criteria->builtUpArea(i) / 1000.0));
		changeColor(10);
		wprintf(L" | Built up rate: %.2f", criteria->builtUpRate(i));
		std::wcout << L"%" << std::endl << std::endl;
	}
	changeColor(7);
}


void Manager::addFilterName(const std::wstring& name)
{
	m_allFilters.push_back([name, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasName(teritorialUnit, name);
		});
}

void Manager::addFilterType(const int typeNumber)
{
	TypeTU type{ TypeTU::None };
	switch (typeNumber)
	{
	case 1:
		type = TypeTU::Commune;
	case 2:
		type = TypeTU::District;
	case 3:
		type = TypeTU::Region;
	case 4:
		type = TypeTU::State;
	default:
		break;
	}
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

void Manager::addFilterPopulation(const int minInterval, const int maxInterval)
{
	m_allFilters.push_back([minInterval, maxInterval, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasPopulation(teritorialUnit, minInterval, maxInterval);
		});
}

void Manager::addFilterBuiltUpRate(const double minInterval, const double maxInterval)
{
	m_allFilters.push_back([minInterval, maxInterval, this](const std::shared_ptr<ITerritorialUnit>& teritorialUnit) {
		return m_filter->hasBuiltUpRate(teritorialUnit, minInterval, maxInterval);
		});
}

void Manager::filterTerritorialUnits()
{
	std::copy_if(m_territorialUnits.begin(), m_territorialUnits.end(), std::back_inserter(m_chosenTerritorialUnits),
		[this](std::shared_ptr<ITerritorialUnit>& territorialUnit)
		{
			return meetsRequirements(territorialUnit);
		});
	writeTerritorialUnitsAllData(m_chosenTerritorialUnits);
}

void Manager::sortTerritorialUnitsByName()
{
	m_territorialUnits.sort([this](const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
	{return m_sort->byName(territorialUnit1, territorialUnit2); });
}

void Manager::sortTerritorialUnitsByPopulation()
{
	m_territorialUnits.sort([this](const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
	{return m_sort->byPopulation(territorialUnit1, territorialUnit2); });
}

void Manager::sortTerritorialUnitsByBuiltUpRate()
{
	m_territorialUnits.sort([this](const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
		{return m_sort->byBuiltUpRate(territorialUnit1, territorialUnit2); });
}

void Manager::sortTerritorialUnits(bool inAscendingOrder, SortBy sortBy )
{
	m_sort->setOrder(inAscendingOrder);

	switch (sortBy)
	{
	case SortBy::Name:
		sortTerritorialUnitsByName();
		break;
	case SortBy::Population:
		sortTerritorialUnitsByPopulation();
		break;
	case SortBy::BuiltUpRate:
		sortTerritorialUnitsByBuiltUpRate();
		break;
	default:
		break;
	}
	writeTerritorialUnitsAllData(m_territorialUnits);
}

bool Manager::meetsRequirements(std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return std::all_of(m_allFilters.begin(), m_allFilters.end(),
		[this, territorialUnit](const auto& filterFunction) {return filterFunction(territorialUnit); });
}

inline void Manager::changeColor(int desiredColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}