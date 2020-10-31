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
problem26 :: Int -> [a] -> [[a]]
problem26 0 _      = [[]]
problem26 _ []     = []
problem26 k (x:xs) = ((x:) <$> problem26 (k-1) xs) ++ problem26 k xs -- Derived from: K (X:XS) = X:(K-1 XS) ++ (K XS)

-- Group the elements of a set into disjoint subsets
problem27 :: [Int] -> [a] -> [[[a]]]
problem27 [] _     = [[]]
problem27 (n:ns) x = [ g:gs | (g, rs) <- aux n x, gs <- problem27 ns rs ]
    where aux 0 xs     = [([], xs)]
          aux _ []     = []
          aux n (x:xs) = [ (x:r, rs) | (r, rs) <- aux (n-1) xs ] ++ [ (r, x:rs) | (r, rs) <- aux n xs ]

-- Sorting a list of lists according to length of sublists
problem28 :: Ord a => [[a]] -> [[a]]
problem28 [x]    = [x]
problem28 [x, y] = if length x >= length y then [x, y] else [y, x]
problem28 x      = let l2 = length x `div` 2 in aux (problem28 $ take l2 x) (problem28 $ drop l2 x)
    where aux [] []         = []
          aux (a:as) []     = a:(aux as [])
          aux [] (b:bs)     = b:(aux [] bs)
          aux (a:as) (b:bs) = if length a >= length b then a:(aux as (b:bs)) else b:(aux (a:as) bs)
