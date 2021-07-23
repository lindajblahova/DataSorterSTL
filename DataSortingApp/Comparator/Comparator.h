#pragma once

#include "../Criterion/Criterion.h"
#include "../Interfaces/IComparator.h"

class Comparator : public IComparator
{
public:
    Comparator() = default;
    ~Comparator() = default;

    inline void setOrder(bool isAscending) override;
    virtual bool compareTerritorialUnits(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const override = 0;

protected:
    std::unique_ptr<ICriterion> m_criterion = std::make_unique<Criterion>();
    bool m_ascendingOrder{ true };
};

inline void Comparator::setOrder(bool isAscending)
{
    m_ascendingOrder = isAscending;
}