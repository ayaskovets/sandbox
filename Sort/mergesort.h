#ifndef MERGESORT_H
#define MERGESORT_H

#include <algorithm>
#include <iterator>

// TODO : implement inplace with double-buffer & compare efficiency

namespace sandbox {

  namespace sort {

    template <class ContainerIter, class Compare>
    void mergesort(ContainerIter first, ContainerIter last, Compare comp) {
      const auto size = std::distance(first, last);
      if (size > 1) {
        const ContainerIter mid = std::next(first, size / 2);

        mergesort(first, mid, comp);
        mergesort(mid, last, comp);

        std::inplace_merge(first, mid, last, comp);
      }
    }

  }

}

#endif // MERGESORT_H
