#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include <iterator>

namespace sandbox {

  namespace sort {

    template <class ContainerIter, class Compare>
    void quicksort(ContainerIter first, ContainerIter last, Compare comp) {
      if (std::distance(first, last) > 1) {
        const ContainerIter pivot = std::prev(last);

        ContainerIter mid = first;
        for (ContainerIter iter = first; std::distance(iter, last) > 1; std::advance(iter, 1)) {
          if (comp(*iter, *pivot)) {
            std::iter_swap(iter, mid);
            std::advance(mid, 1);
          }
        }

        std::iter_swap(mid, pivot);

        if (mid == first) {
          std::advance(mid, 1);
        }

        quicksort(first, mid, comp);
        quicksort(mid, last, comp);
      }
    }

  }

}

#endif // QUICKSORT_H
