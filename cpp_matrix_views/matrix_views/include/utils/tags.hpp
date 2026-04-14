#pragma once

namespace matrix_views::utils {

/*
 * Row tag. Represents horizontal stripes directed from left to right
 */
constexpr struct kRowTag final {
} kRow;

/*
 * Column tag. Represents vertical stripes directed from top to bottom
 */
constexpr struct kColumnTag final {
} kColumn;

/*
 * Diagonal tag. Represents diagonal stripes
 * directed from the top left corner to the bottom right cornet
 */
constexpr struct kDiagonalTag final {
} kDiagonal;

/*
 * Antidiagonal tag. Represents diagonal stripes
 * directed from the top right corner to the bottom left corner
 */
constexpr struct kAntidiagonalTag final {
} kAntidiagonal;

/*
 * Tag representing some value known at compile time
 */
constexpr struct kCompileTimeTag final {
} kCompileTime;

}  // namespace matrix_views::utils
