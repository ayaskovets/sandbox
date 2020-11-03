#pragma once
#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <algorithm>
#include <iterator>

namespace sandbox {

  namespace sort {

    template <class ContainerIter, class Compare>
    void heapsort(ContainerIter first, ContainerIter last, Compare comp) {
      auto siftDown = [&first, &last, &comp](size_t heap_size, ContainerIter heap_beg) {
        for (ContainerIter root = heap_beg;; root = heap_beg) {
          size_t root_left_idx = std::distance(first, root) * 2 + 1, root_right_idx = root_left_idx + 1;

          if (root_left_idx < heap_size) {
            ContainerIter root_left = std::next(first, root_left_idx);
            if (comp(*heap_beg, *root_left)) {
              heap_beg = root_left;
            }
          }

          if (root_right_idx < heap_size) {
            ContainerIter root_right = std::next(first, root_right_idx);
            if (comp(*heap_beg, *root_right)) {
              heap_beg = root_right;
            }
          }

          if (root == heap_beg) {
            break;
          }

          std::iter_swap(root, heap_beg);
        }
      };

      size_t heap_size = std::distance(first, last);
      for (ContainerIter iter = std::next(first, heap_size / 2); std::distance(first, iter) > 0; std::advance(iter, -1)) {
        siftDown(heap_size, std::prev(iter));
      }

      for (ContainerIter iter = last; std::distance(first, iter) > 0; std::advance(iter, -1)) {
        std::iter_swap(first, std::prev(iter));

        heap_size -= 1;
        siftDown(heap_size, first);
      }
    }

  }

}

#endif // HEAPSORT_HPP
