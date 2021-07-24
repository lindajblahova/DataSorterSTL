#pragma once

#include "../TerritorialUnit/TerritorialUnit.h"

class ICriterion {
public:
    virtual ~ICriterion() = default;

    virtual std::wstring name(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual TerritorialUnitType type(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const  = 0;
    virtual bool hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parentTerritorialUnit) const  = 0;
    virtual int preProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual int productive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual int postProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual int population(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual double totalArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual double builtUpArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;
    virtual double builtUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const = 0;

};