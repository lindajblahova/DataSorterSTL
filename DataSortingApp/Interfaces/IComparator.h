#pragma once

#include "../Interfaces/ITerritorialUnit.h"

class IComparator
{
public:
    virtual ~IComparator() = default;

    virtual void setOrder(bool isAscending) = 0;
    virtual bool compareTerritorialUnits(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const = 0;
};