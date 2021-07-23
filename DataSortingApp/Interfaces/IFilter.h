#pragma once

#include "../Interfaces/ITerritorialUnit.h"

class IFilter
{

public:
    virtual ~IFilter() = default;

    virtual bool hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parent) const = 0;
    virtual bool hasName(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::wstring& name) const = 0;
    virtual bool hasType(const std::shared_ptr<ITerritorialUnit>& territorialUnit, TerritorialUnitType type) const = 0;
    virtual bool hasPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit, unsigned int minInterval, unsigned int maxInterval) const = 0;
    virtual bool hasBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit, double minInterval, double maxInterval) const = 0;

};