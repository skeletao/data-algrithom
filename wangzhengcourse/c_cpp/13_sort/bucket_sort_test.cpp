#include <iostream>
#include <vector>
#include <functional>

#include "bucket_sort.hpp"

template <size_t bucket_size,
            typename Container,
            typename T = typename Container::value_type,
            typename Compare = std::less<T>>

void test_bucket_sort(Container cont, Compare comp = Compare())
{
    bucket_sort<bucket_size>(cont.begin(), cont.end(), comp);
    std::transform(cont.begin(), cont.end(), std::ostream_iterator<T>(std::cout, " "), [](T i){return i;});
    std::cout << std::endl;
}

int main() 
{
    std::vector<int> test{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};

    test_bucket_sort<2>(test);
    test_bucket_sort<3>(test);
    test_bucket_sort<4>(test);
    test_bucket_sort<5>(test);
    test_bucket_sort<6>(test);
    return 0;
}