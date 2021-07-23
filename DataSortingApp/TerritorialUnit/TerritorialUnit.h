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
	TerritorialUnit(const std::wstring& name, TypeTU type,const std::shared_ptr<ITerritorialUnit>& parent, unsigned int preProductive, 
		unsigned int productive, unsigned int postProductive, double totalArea, double buildUpArea);
	~TerritorialUnit();

	std::wstring getName() const override;
	TypeTU getType() const override;
	std::shared_ptr<ITerritorialUnit> getParent() const override;
	unsigned int getPreProductive() const override;
	unsigned int getProductive() const override;
	unsigned int getPostProductive() const override;
	double getTotalArea() const override;
	double getBuiltUpArea() const override;

	void addValues(unsigned int preProductive, unsigned int productive, unsigned int postProductive, double totalArea, double buildUpArea) override;

private:
	std::wstring m_name;
	TypeTU m_type { TypeTU::None };
	std::shared_ptr<ITerritorialUnit> m_parent;
	unsigned int m_preProductive { 0 };
	unsigned int m_productive {0};
	unsigned int m_postProductive {0};
	double m_totalArea {0.0};
	double m_builtUpArea {0.0};
};