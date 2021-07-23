#include "TerritorialUnit.h"

TerritorialUnit::TerritorialUnit(const std::wstring& name, TypeTU type, const std::shared_ptr<ITerritorialUnit>& parent, unsigned int preProductive, 
	unsigned int productive, unsigned int postProductive, double totalArea, double buildUpArea)
	: m_name(name), m_type(type), m_parent(parent), m_preProductive(preProductive), m_productive(productive), m_postProductive(postProductive),
	m_totalArea(totalArea), m_builtUpArea(buildUpArea)
{
}

std::wstring TerritorialUnit::getName() const
{
	return m_name;
}

TypeTU TerritorialUnit::getType() const
{
	return m_type;
}

std::shared_ptr<ITerritorialUnit> TerritorialUnit::getParent() const
{
	return m_parent;
}

unsigned int TerritorialUnit::getPreProductive() const
{
	return m_preProductive;
}

unsigned int TerritorialUnit::getProductive() const
{
	return m_productive;
}

unsigned int TerritorialUnit::getPostProductive() const
{
	return m_postProductive;
}

double TerritorialUnit::getTotalArea() const
{
	return m_totalArea;
}

double TerritorialUnit::getBuiltUpArea() const
{
	return m_builtUpArea;
}

void TerritorialUnit::addValues(unsigned int preProductive, unsigned int productive, unsigned int postProductive, double totalArea, double builtUpArea)
{
	m_preProductive += preProductive;
	m_productive += productive;
	m_postProductive += postProductive;
	m_totalArea += totalArea;
	m_builtUpArea += builtUpArea;
}

TerritorialUnit::~TerritorialUnit()
{
}
