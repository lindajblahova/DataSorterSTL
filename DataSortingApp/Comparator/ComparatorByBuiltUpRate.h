#pragma once

#include "Comparator.h"

class ComparatorByBuiltUpRate : public Comparator
{
public:
    ComparatorByBuiltUpRate() = default;
    ~ComparatorByBuiltUpRate() = default;

    inline bool compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const override;
};

inline bool ComparatorByBuiltUpRate::compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1,
    const std::shared_ptr<ITerritorialUnit>& territorialUnit2) const
{
    return m_ascendingOrder ?
        m_criterion->builtUpRate(territorialUnit1) < m_criterion->builtUpRate(territorialUnit2) :
        m_criterion->builtUpRate(territorialUnit1) > m_criterion->builtUpRate(territorialUnit2);
}