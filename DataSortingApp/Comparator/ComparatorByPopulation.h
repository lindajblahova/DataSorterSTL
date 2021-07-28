#pragma once

#include "Comparator.h"

class ComparatorByPopulation : public Comparator
{
public:
    ComparatorByPopulation() = default;
    ~ComparatorByPopulation() = default;

    bool compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const override;
};

bool ComparatorByPopulation::compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1,
    const std::shared_ptr<ITerritorialUnit>& territorialUnit2) const
{
    return m_ascendingOrder ?
        m_criterion->population(territorialUnit1) < m_criterion->population(territorialUnit2) :
        m_criterion->population(territorialUnit1) > m_criterion->population(territorialUnit2);
}