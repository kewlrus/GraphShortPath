#include "stdafx.h"

StrikerAnimGraphInterface* _stdcall CreateStrikerAnimGraph(void)
{
	return (new StrikerAnimGraph());
}

void _stdcall DeleteStrikerAnimGraph(StrikerAnimGraphInterface* SAG)
{
	delete SAG;
}