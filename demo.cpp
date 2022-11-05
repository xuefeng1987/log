#include "logger.h"

int main()
{
	int m = 0; 
	while (m < 1000)
	{
		LOG_INFO("log test m=%d", m);
		LOG_ERR("log test m=%d", m);
		m++;
		
	}
	for (;;)
	{
		
	}
	std::cout << "over" << std::endl;
	return 0;
}