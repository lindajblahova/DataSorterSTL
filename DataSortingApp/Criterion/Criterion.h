#pragma once

#include "../TerritorialUnit/ITerritorialUnit.h"
#include <string>

class Criterion {
public:
    Criterion() = default;
    ~Criterion() = default;

    std::wstring name(const std::shared_ptr<ITerritorialUnit>& tu);
    TypeTU type(const std::shared_ptr<ITerritorialUnit>& tu);
    bool hasParent(const std::shared_ptr<ITerritorialUnit>& tu, const std::shared_ptr<ITerritorialUnit>& parent);
    int preProductive(const std::shared_ptr<ITerritorialUnit>& tu);
    int productive(const std::shared_ptr<ITerritorialUnit>& tu);
    int postProductive(const std::shared_ptr<ITerritorialUnit>& tu);
    int population(const std::shared_ptr<ITerritorialUnit>& tu);
    double totalArea(const std::shared_ptr<ITerritorialUnit>& tu);
    double builtUpArea(const std::shared_ptr<ITerritorialUnit>& tu);
    double builtUpRate(const std::shared_ptr<ITerritorialUnit>& tu);

};
