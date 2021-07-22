#include <memory>
#include <string>
#include "../TerritorialUnit/ITerritorialUnit.h"
#include "../Criterion/Criterion.h"

class Filter
{

public:
    Filter();
    ~Filter();

    bool hasParent(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::shared_ptr<ITerritorialUnit>& parent);
    bool hasName(const std::shared_ptr<ITerritorialUnit>& territorialUnit, const std::wstring& name);
    bool hasType(const std::shared_ptr<ITerritorialUnit>& territorialUnit, TypeTU type);
    bool hasPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit, int minInterval, int maxInterval);
    bool hasBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit, double minInterval, double maxInterval);

private:
    std::unique_ptr<Criterion> m_criterion;
};