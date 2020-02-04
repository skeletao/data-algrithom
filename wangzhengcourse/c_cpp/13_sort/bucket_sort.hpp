#ifndef BUCKET_SORT_HPP_
#define BUCKET_SORT_HPP_

#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>

template <size_t bucket_size,
            typename iter_t,
            typename T = typename std::iterator_traits<iter_t>::value_type,
            typename Compare = std::less<T>>
        
void bucket_sort(iter_t first, iter_t last, Compare comp = Compare())
{
    const T min = *std::min_element(first, last);
    const T max = *std::max_element(first, last);
    const T range = max - min + 1;
    const size_t bucket_num = (range-1)/bucket_size + 1;

    std::vector<std::vector<T>> buckets(bucket_num);
    for (auto b: buckets)
    {
        b.reserve(2 * bucket_size);
    }

    for (iter_t i = first; i != last; i++)
    {
        size_t idx = (*i - min)/bucket_size;
        buckets[idx].emplace_back(*i);
    }

    iter_t dest = first;
    for (auto b : buckets)
    {
        std::sort(b.begin(), b.end(), comp);
        std::copy(b.begin(), b.end(), dest);
        dest += b.size();
    }

    return;
}


#endif