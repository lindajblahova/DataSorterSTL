
#include "Menu/Menu.h"

int main() 
{
	std::unique_ptr<Menu> menu = std::make_unique<Menu>();

	bool run = true;

	while (run)
	{
		Tasks taskToPerform = menu->chooseTaskToPerform();
		SortBy sortBy = SortBy::None;

		switch (taskToPerform)
		{
		case Tasks::Filter:
			menu->chooseFiltersToUse();
			menu->createFilters();
			menu->performFiltration();
			menu->writeFilteredResults();
			break;
		case Tasks::Sort:
			sortBy = menu->chooseSortingProperties();
			menu->performSorting(sortBy);
			menu->writeSortedResults(sortBy);
			break;
		case Tasks::Both:
			menu->chooseFiltersToUse();
			menu->createFilters();
			menu->performFiltration();
			sortBy = menu->chooseSortingProperties();
			menu->performSorting(sortBy);
			menu->writeSortedResults(sortBy);
			break;
		default:
			run = false;
		}
	}

	return 0;
}

