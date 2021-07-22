#include "Criterion.h"

std::wstring Criterion::name(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getName();
}

TypeTU Criterion::type(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getType();
}

bool Criterion::hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parent)
{
    if (territorialUnit->getType() == TypeTU::Commune &&
        (territorialUnit->getParent() == parent || territorialUnit->getParent()->getParent() == parent))
    {
        return true;
    }

    if (territorialUnit->getType() == TypeTU::District && territorialUnit->getParent() == parent)
    {
        return true;
    }

    if (parent != nullptr && parent->getType() == TypeTU::State)
    {
        return true;
    }

    return false;
}

int Criterion::preProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getPreProductive();
}

int Criterion::productive(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getProductive();
}

int Criterion::postProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getPostProductive();
}

int Criterion::population(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return (territorialUnit->getPreProductive() + territorialUnit->getProductive() + territorialUnit->getPostProductive());
}

double Criterion::totalArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getTotalArea();
}

double Criterion::builtUpArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return territorialUnit->getBuiltUpArea();
}

double Criterion::builtUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit)
{
	return (double)((territorialUnit->getBuiltUpArea() / territorialUnit->getTotalArea()) * 100.0);
}