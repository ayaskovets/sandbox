#pragma once

#include <iterator>

namespace sandbox {

  namespace search {

    template <class ContainerIter, class Compare, typename ValueType = typename std::iterator_traits<ContainerIter>::value_type>
    ContainerIter binarysearch(ContainerIter first, ContainerIter last, Compare comp, const ValueType& value) {
      const ContainerIter not_found = last;
      for (auto distance = std::distance(first, last); distance > 1; distance = std::distance(first, last)) {
        const ContainerIter mid = std::next(first, std::distance(first, last) / 2);
        if (comp(value, *mid)) {
          last = mid;
        }
        else if (comp(*mid, value)) {
          first = mid;
        }
        else {
          return mid;
        }
      }

      return not_found;
    }

  }

}
