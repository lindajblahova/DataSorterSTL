#pragma once

#include "../Criterion/Criterion.h"
#include "SortBy.h"

class Sort
{
public:
    Sort() = default;
    ~Sort() = default;

    void setOrder(bool isAscending);
    bool byName(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2);
    bool byPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2);
    bool byBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2);

private:
    std::unique_ptr<ICriterion> m_criterion = std::make_unique<Criterion>();
    bool m_ascendingOrder{ true };
};
