#pragma once

#include <string>
#include <memory>
#include "TypeTU.h"
#include "ITerritorialUnit.h"
#include <list>

class TerritorialUnit : public ITerritorialUnit
{
public:
	TerritorialUnit() = delete;
	TerritorialUnit(const std::wstring& name, TypeTU type,const std::shared_ptr<ITerritorialUnit>& parent, int preProductive, int productive, int postProductive, double totalArea, double buildUpArea);
	~TerritorialUnit();

	std::wstring getName() const override;
	TypeTU getType() const override;
	std::shared_ptr<ITerritorialUnit> getParent() const override;
	int getPreProductive() const override;
	int getProductive() const override;
	int getPostProductive() const override;
	double getTotalArea() const override;
	double getBuiltUpArea() const override;

	void addValues(int preProductive, int productive, int postProductive, double totalArea, double buildUpArea) override;

private:
	std::wstring m_name;
	TypeTU m_type { TypeTU::None };
	std::shared_ptr<ITerritorialUnit> m_parent;
	int m_preProductive { 0 };
	int m_productive {0};
	int m_postProductive {0};
	double m_totalArea {0.0};
	double m_builtUpArea {0.0};
};