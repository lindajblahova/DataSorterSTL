#include <memory>
#include  "Manager/Manager.h"

int main() 
{
	std::unique_ptr<Manager> man = std::make_unique<Manager>();

	man->read();

	return 0;
}

