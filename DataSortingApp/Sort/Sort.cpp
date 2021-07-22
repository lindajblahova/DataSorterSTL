#include "Sort.h"

Sort::Sort() 
{
}

Sort::~Sort()
{
}

void Sort::setOrder(bool isAscending)
{
	m_ascendingOrder = isAscending;
}

bool Sort::byName(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
{
   return m_ascendingOrder ?
        m_criterion->name(territorialUnit1) < m_criterion->name(territorialUnit2) :
        m_criterion->name(territorialUnit1) > m_criterion->name(territorialUnit2);
}

bool Sort::byPopulation(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
{
    return m_ascendingOrder ?
        m_criterion->population(territorialUnit1) < m_criterion->population(territorialUnit2) :
        m_criterion->population(territorialUnit1) > m_criterion->population(territorialUnit2);
}

bool Sort::byBuiltUpRate(const std::shared_ptr<ITerritorialUnit>& territorialUnit1, const std::shared_ptr<ITerritorialUnit>& territorialUnit2)
{

    return m_ascendingOrder ?
        m_criterion->builtUpRate(territorialUnit1) < m_criterion->builtUpRate(territorialUnit2) :
        m_criterion->builtUpRate(territorialUnit1) > m_criterion->builtUpRate(territorialUnit2);
}
