#pragma once

#include "Comparator.h"

class ComparatorByName : public Comparator
{
public:
    ComparatorByName() = default;
    ~ComparatorByName() = default;

    inline bool compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const override;
};

inline bool ComparatorByName::compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, 
    const std::shared_ptr<ITerritorialUnit>& territorialUnit2) const
{
    return m_ascendingOrder ?
        m_criterion->name(territorialUnit1) < m_criterion->name(territorialUnit2) :
        m_criterion->name(territorialUnit1) > m_criterion->name(territorialUnit2);
}