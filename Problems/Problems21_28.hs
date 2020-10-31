module Problems.Problems21_28 where

import System.Random

-- Insert an element at a given position into a list
problem21 :: a -> [a] -> Int -> [a]
problem21 e x n = take (n-1) x ++ e:(drop ((length x)-n-1) x)

-- Create a list containing all integers within a given range
problem22 :: Int -> Int -> [Int]
problem22 a b
    | a < b     = a:(problem22 (a+1) b)
    | a > b     = a:(problem22 (a-1) b)
    | otherwise = [a]

-- Extract a given number of randomly selected elements from a list

-- Lotto: Draw N different random numbers from the set 1..M

-- Generate a random permutation of the elements of a list

-- Generate the combinations of K distinct objects chosen from the N elements of a list

-- Group the elements of a set into disjoint subsets

-- Sorting a list of lists according to length of sublists