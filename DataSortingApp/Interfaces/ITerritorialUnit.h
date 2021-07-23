#pragma once

#include <string>
#include <memory>
#include "../TerritorialUnit/TerritorialUnitType.h"


class ITerritorialUnit
{
public:
	virtual ~ITerritorialUnit() = default;
	virtual std::wstring getName() const = 0;
	virtual std::shared_ptr<ITerritorialUnit> getParent() const  = 0;
	virtual unsigned int getPreProductive() const = 0;
	virtual unsigned int getProductive() const = 0;
	virtual unsigned int getPostProductive() const = 0;
	virtual double getTotalArea() const = 0;
	virtual double getBuiltUpArea() const = 0;
	virtual TerritorialUnitType getType() const = 0;

	virtual void addValues(unsigned int preProductive, unsigned int productive, unsigned int postProductive, double totalArea, double buildUp) = 0;
};