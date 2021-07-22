#pragma once

#include <string>
#include <memory>
#include "TypeTU.h"

class ITerritorialUnit
{
public:
	virtual ~ITerritorialUnit() = default;
	virtual std::wstring getName() const = 0;
	virtual std::shared_ptr<ITerritorialUnit> getParent() const  = 0;
	virtual int getPreProductive() const = 0;
	virtual int getProductive() const = 0;
	virtual int getPostProductive() const = 0;
	virtual double getTotalArea() const = 0;
	virtual double getBuiltUpArea() const = 0;
	virtual TypeTU getType() const = 0;

	virtual void addValues(int preprod, int prod, int postprod, double totalArea, double buildUp) = 0;
};