#pragma once

#include "../Interfaces/ICriterion.h"
#include <string>

class Criterion : public ICriterion
{
public:
    Criterion() = default;
    ~Criterion() = default;

    std::wstring name(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    TerritorialUnitType type(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    bool hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parentTerritorialUnit) const override;
    int preProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    int productive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    int postProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    int population(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    double totalArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    double builtUpArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;
    double builtUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const override;

};
