#include "Criterion.h"

std::wstring Criterion::name(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getName();
}

TerritorialUnitType Criterion::type(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getType();
}

bool Criterion::hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parentTerritorialUnit) const
{
    if (territorialUnit->getType() == TerritorialUnitType::Commune &&
        (territorialUnit->getParent() == parentTerritorialUnit || territorialUnit->getParent()->getParent() == parentTerritorialUnit))
    {
        return true;
    }

    if (territorialUnit->getType() == TerritorialUnitType::District && territorialUnit->getParent() == parentTerritorialUnit)
    {
        return true;
    }

    if (parentTerritorialUnit != nullptr && parentTerritorialUnit->getType() == TerritorialUnitType::State)
    {
        return true;
    }

    return false;
}

int Criterion::preProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getPreProductive();
}

int Criterion::productive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getProductive();
}

int Criterion::postProductive(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getPostProductive();
}

int Criterion::population(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return (territorialUnit->getPreProductive() + territorialUnit->getProductive() + territorialUnit->getPostProductive());
}

double Criterion::totalArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getTotalArea();
}

double Criterion::builtUpArea(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return territorialUnit->getBuiltUpArea();
}

double Criterion::builtUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit) const
{
	return (double)((territorialUnit->getBuiltUpArea() / territorialUnit->getTotalArea()) * 100.0);
}