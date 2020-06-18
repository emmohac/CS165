#include "project1.h"
#include <math.h>

void shell_sort2(std::vector<int> &v);

void shell_sort2(std::vector<int> &v){
    const std::vector<int> gaps{2147483647, 1073741823, 536870911, 268435455, 134217727, 67108863, 33554431, 16777215, 8388607, 4194303,
        2097151, 1048575, 524287, 262143, 131071, 65535, 32767, 16383, 8191, 4095, 2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1};

    for (const int gap : gaps)
        for (int i = gap; i < v.size(); ++i){
            int to_swap = v[i];
            int j = i;
            while (j >= gap && to_swap < v[j - gap]){
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = to_swap;
        }
}
