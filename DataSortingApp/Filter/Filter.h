
#include "../Interfaces/IFilter.h"
#include "../Criterion/Criterion.h"

class Filter : public IFilter
{

public:
    Filter() = default;
    ~Filter() = default;

    bool hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parent) const override;
    bool hasName(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::wstring& name) const override;
    bool hasType(const std::shared_ptr<ITerritorialUnit>& territorialUnit, TerritorialUnitType type) const override;
    bool hasPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit, unsigned int minInterval, unsigned int maxInterval) const override;
    bool hasBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit, double minInterval, double maxInterval) const override;

private:
    std::unique_ptr<ICriterion> m_criterion = std::make_unique<Criterion>();
};