#include "Filter.h"
#include <iostream>

Filter::Filter() : m_criterion(std::make_unique<Criterion>())
{
}

Filter::~Filter()
{
}

bool Filter::hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parent)
{
    return m_criterion->hasParent(territorialUnit, parent);
}

bool Filter::hasName(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::wstring& name)
{
    return m_criterion->name(territorialUnit) == name;
}

bool Filter::hasType(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const TypeTU type)
{
    return m_criterion->type(territorialUnit) == type;
}

bool Filter::hasPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit, int minInterval, int maxInterval)
{
    int population = m_criterion->population(territorialUnit);
    return population >= minInterval && population <= maxInterval;
}

bool Filter::hasBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit, double minInterval, double maxInterval)
{
    double builtUpRate = m_criterion->builtUpRate(territorialUnit);
    return builtUpRate >= minInterval && builtUpRate <= maxInterval;
}