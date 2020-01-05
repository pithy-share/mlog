#include "mlog.h"
#include "stdio.h"

int main(void)
{

	M_DEBUG("this is debug %s %d\n", "gggg", 123);
	
	M_INFO("this is info %s %d\n", "gggg", 123);

	M_WARN("this is warn %s %d\n", "gggg", 123);

	M_ERROR("this is error %s %d\n", "gggg", 123);

	M_FATAL("this is fatal %s %d\n", "gggg", 123);
	return 0;
}
