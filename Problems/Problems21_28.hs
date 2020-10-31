module Problems.Problems21_28 where

import Data.List
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
problem23 :: [a] -> Int -> IO [a]
problem23 _ 0 = return []
problem23 x n = do
    i  <- getStdRandom (randomR (0, (length x)-1))
    xs <- problem23 (take i x ++ drop (i+1) x) (n-1)
    return ((x !! i):xs)

-- Lotto: Draw N different random numbers from the set 1..M
problem24 :: Int -> Int -> IO [Int]
problem24 n m
    | n > m     = error "Invalid arguments"
    | otherwise = do
        g <- getStdGen
        return . take n . nub $ randomRs (1, m) g

-- Generate a random permutation of the elements of a list
problem25 :: [a] -> IO [a]
problem25 x = problem23 x (length x)

-- Generate the combinations of K distinct objects chosen from the N elements of a list

-- Group the elements of a set into disjoint subsets

-- Sorting a list of lists according to length of sublists