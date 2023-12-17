
#include "Stats.h"



Stats Bubble_Sort(std::vector<int>& value)
{
	Stats res;
	for (size_t i = 0; i < value.size() - 1; i++)
	{
		for (size_t j = 0; j < value.size() - 1 - i; j++)
		{
			res.comparison_count++;
			if (value[j] > value[j + 1])
			{
				int tmp = value[j];
				value[j] = value[j + 1];
				value[j + 1] = tmp;
				res.copy_count++;
			}
		}
	}
	return res;
}

