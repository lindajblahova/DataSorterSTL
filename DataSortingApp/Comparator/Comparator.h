#pragma once

#include "../Criterion/Criterion.h"
#include "../Interfaces/IComparator.h"

class Comparator : public IComparator
{
public:
    Comparator() = default;
    ~Comparator() = default;

    inline void setOrder(bool isAscending) override;

protected:
    std::unique_ptr<ICriterion> m_criterion = std::make_unique<Criterion>();
    bool m_ascendingOrder{ true };
};

inline void Comparator::setOrder(bool isAscending)
{
    m_ascendingOrder = isAscending;
}