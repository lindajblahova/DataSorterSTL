#pragma once

#include "../TerritorialUnit/TerritorialUnit.h"

class IComparator
{
public:
    virtual ~IComparator() = default;

    virtual void setOrder(bool isAscending) = 0;
    virtual bool compare(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
        const = 0;
};