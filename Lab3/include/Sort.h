
#include "Stats.h"



Stats Bubble_Sort(std::vector<int>& data)
{
	Stats res;
	for (size_t i = 0; i < data.size() - 1; i++)
	{
		for (size_t j = 0; j < data.size() - 1 - i; j++)
		{
			res.comparison_count++;
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
				res.copy_count++;
			}
		}
	}
	return res;
}


Stats Cocktail_Sort(std::vector<int>& data) {
    Stats result;
    bool swapped = true;
    int start = 0;
    int end = data.size() - 1;

    while (swapped)
    {
        swapped = false;
        for (int i = start; i < end; ++i)
        {
            result.comparison_count++;
            if (data[i] > data[i + 1]) {
                int tmp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = tmp;
                ++result.copy_count;
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i)
        {
            result.comparison_count++;
            if (data[i] > data[i + 1]) {
                int tmp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = tmp;
                ++result.copy_count;;
                swapped = true;
            }
        }
        ++start;
    }
    return result;
}


void Natural_Merge(std::vector<int>& a, size_t left, size_t middle, size_t right, Stats& stats) {
    size_t left_size = middle - left + 1;
    size_t right_size = right - middle;

    std::vector<int> left_a(left_size);
    std::vector<int> right_a(right_size);

    for (size_t i = 0; i < left_size; ++i) {
        left_a[i] = a[left + i];
        ++stats.copy_count;
    }
    for (size_t j = 0; j < right_size; ++j) {
        right_a[j] = a[middle + 1 + j];
        ++stats.copy_count;
    }

    size_t i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        ++stats.comparison_count;
        if (left_a[i] <= right_a[j]) {
            a[k] = left_a[i];
            ++i;
        }
        else {
            a[k] = right_a[j];
            ++j;
        }
        ++stats.copy_count;
        ++k;
    }

    while (i < left_size) {
        a[k] = left_a[i];
        ++i;
        ++k;
        ++stats.copy_count;
    }

    while (j < right_size) {
        a[k] = right_a[j];
        ++j;
        ++k;
        ++stats.copy_count;
    }
}

void Natural_Merge_Sort(std::vector<int>& a, size_t left, size_t right, Stats& stats) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;

        Natural_Merge_Sort(a, left, middle, stats);
        Natural_Merge_Sort(a, middle + 1, right, stats);

        Natural_Merge(a, left, middle, right, stats);
    }
}

Stats NaturalMergeSortWrapper(std::vector<int>& a) {
    Stats stats;
    Natural_Merge_Sort(a, 0, a.size() - 1, stats);
    return stats;
}