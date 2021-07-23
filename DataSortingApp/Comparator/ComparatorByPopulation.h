#pragma once

#include "Comparator.h"

class ComparatorByPopulation : public Comparator
{
public:
    ComparatorByPopulation() = default;
    ~ComparatorByPopulation() = default;

    inline bool compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const override;
};

inline bool ComparatorByPopulation::compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1,
    const std::shared_ptr<ITerritorialUnit>& territorialUnit2) const
{
    return m_ascendingOrder ?
        this->m_criterion->population(territorialUnit1) < this->m_criterion->population(territorialUnit2) :
        this->m_criterion->population(territorialUnit1) > this->m_criterion->population(territorialUnit2);
}