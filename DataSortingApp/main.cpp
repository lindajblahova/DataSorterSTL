
#include "Menu/Menu.h"

int main() 
{
	std::unique_ptr<Menu> menu = std::make_unique<Menu>();

	menu->chooseTasks();

	return 0;
}

