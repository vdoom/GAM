#include "GAMParallelPocess.h"

GAMParallelPocess::GAMParallelPocess(void)
{
}

GAMParallelPocess::~GAMParallelPocess(void)
{
}

void GAMParallelPocess::Start()
{
#pragma omp parallel
	{
		Run();
	}
}
