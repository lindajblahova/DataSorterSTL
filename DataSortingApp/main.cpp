#include <memory>
#include "Menu/Menu.h"

int main() 
{
	std::unique_ptr<Menu> menu = std::make_unique<Menu>();

	//menu->chooseFilters();

	menu->chooseSorting();
	return 0;
}

