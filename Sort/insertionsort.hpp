#pragma once
#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>

namespace sandbox {

  namespace sort {

    template <class ContainerIter, class Compare>
    void insertionsort(ContainerIter first, ContainerIter last, Compare comp) {
      for (ContainerIter iter = std::next(first); std::distance(iter, last) > 0; std::advance(iter, 1)) {
        for (ContainerIter insert = iter; std::distance(first, insert) > 0 && !comp(*std::prev(insert), *insert); std::advance(insert, -1)) {
          std::iter_swap(std::prev(insert), insert);
        }
      }
    }

    template <class ContainerIter, class Compare>
    void shellsort(ContainerIter first, ContainerIter last, Compare comp) {
      const auto container_size = std::distance(first, last);

      std::vector<typename std::iterator_traits<ContainerIter>::difference_type> gaps;
      gaps.reserve(container_size / 2);

      // Ciura's gap sequence
      gaps = { 1, 4, 10, 23, 57, 132, 301, 701 };

      if (gaps.back() > container_size) {
        do {
          gaps.pop_back();
        } while (gaps.back() > container_size);
      }
      else {
        typename std::iterator_traits<ContainerIter>::difference_type next_ciura_val = static_cast<size_t>(gaps.back() * 2.25);
        while (next_ciura_val < container_size) {
          gaps.push_back(next_ciura_val);
          next_ciura_val *= 2.25;
        }
      }

      for (auto gap = gaps.crbegin(); gap < gaps.crend(); std::advance(gap, 1)) {
        const auto dist = *gap;
        for (ContainerIter iter = std::next(first, dist); iter < last; std::advance(iter, 1)) {
          for (ContainerIter insert = iter; std::distance(first, insert) >= dist && !comp(*std::prev(insert), *insert); std::advance(insert, -dist)) {
            std::iter_swap(insert, std::next(insert, -dist));
          }
        }
      }
    }

  }

}

#endif // INSERTIONSORT_HPP
