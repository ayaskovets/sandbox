#pragma once

#include "iterators/base_random_access_iterator.hpp"
#include "utils/tags.hpp"

namespace matrix_views::iterators {

/*
 * Concept representing the set of valid tags for tagged_random_access_iterator
 */
template <typename Tag>
concept tagged_random_access_iterator_tag =
    std::same_as<Tag, utils::kRowTag> || std::same_as<Tag, utils::kColumnTag> ||
    std::same_as<Tag, utils::kDiagonalTag> ||
    std::same_as<Tag, utils::kAntidiagonalTag>;

/*
 * Concept representing a callable that implements the storage access
 */
template <typename StorageProxy>
concept tagged_random_access_iterator_storage_proxy =
    std::invocable<const StorageProxy, utils::index>;

/*
 * Tagged iterator class with a set direction. Implements iterator movement but
 * leaves dereferencing unimplemented
 */
template <tagged_random_access_iterator_tag Tag,
          tagged_random_access_iterator_storage_proxy StorageProxy>
class tagged_random_access_iterator final
    : public base_random_access_iterator<
          tagged_random_access_iterator<Tag, StorageProxy>>,
      public StorageProxy {
 private:
  static inline const constinit bool kRowTag =
      std::is_same_v<Tag, utils::kRowTag>;
  static inline const constinit bool kColumnTag =
      std::is_same_v<Tag, utils::kColumnTag>;
  static inline const constinit bool kDiagonalTag =
      std::is_same_v<Tag, utils::kDiagonalTag>;
  static inline const constinit bool kAntidiagonalTag =
      std::is_same_v<Tag, utils::kAntidiagonalTag>;

  using difference_type = base_random_access_iterator<
      tagged_random_access_iterator>::difference_type;
  using reference = typename StorageProxy::reference;

 public:
  constexpr tagged_random_access_iterator() noexcept = default;
  constexpr tagged_random_access_iterator(Tag, utils::index index,
                                          StorageProxy&& storage_proxy) noexcept
      : base_random_access_iterator<tagged_random_access_iterator>(index),
        StorageProxy(std::move(storage_proxy)) {}

 public:
  constexpr tagged_random_access_iterator& operator+=(
      difference_type n) noexcept {
    if constexpr (kRowTag) {
      this->index_.column += n;
    } else if constexpr (kColumnTag) {
      this->index_.row += n;
    } else if constexpr (kDiagonalTag) {
      this->index_.row += n, this->index_.column += n;
    } else {
      static_assert(kAntidiagonalTag);
      this->index_.row += n, this->index_.column -= n;
    }
    return *this;
  }

  constexpr difference_type operator-(
      const tagged_random_access_iterator& that) const noexcept {
    if constexpr (kRowTag) {
      return this->index_.column - that.index_.column;
    } else if constexpr (kColumnTag) {
      return this->index_.row - that.index_.row;
    } else if constexpr (kDiagonalTag) {
      return this->index_.row - that.index_.row;
    } else {
      static_assert(kAntidiagonalTag);
      return this->index_.row - that.index_.row;
    }
  }

  constexpr reference operator*() const { return (*this)(this->index_); }
};

}  // namespace matrix_views::iterators
