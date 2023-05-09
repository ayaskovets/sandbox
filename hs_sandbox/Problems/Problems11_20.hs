module Problems.Problems11_20 where

import Problems.Problems1_10 (problem10)

-- Modified run-length encoding
data RLItem a = Single a | Multiple Int a
    deriving (Show)

problem11 :: Eq a => [a] -> [RLItem a]
problem11 x = aux <$> (problem10 x)
    where aux (1, x) = Single x
          aux (n, x) = Multiple n x

-- Decode a run-length encoded list
problem12 :: [RLItem a] -> [a]
problem12 = foldr (\x acc -> (aux x) ++ acc) []
    where aux (Single x)     = [x]
          aux (Multiple n x) = take n (repeat x)

-- Run-length encoding of a list (direct solution)
fromRLItem :: RLItem a -> a
fromRLItem (Single a)     = a
fromRLItem (Multiple _ a) = a

incRLItem :: RLItem a -> RLItem a
incRLItem (Single a)     = Multiple 2 a
incRLItem (Multiple n a) = Multiple (n+1) a

problem13 :: Eq a => [a] -> [RLItem a]
problem13 x = foldr aux [Single $ last x] x
    where aux x (a:cc) = if x == (fromRLItem a) then (incRLItem a):cc else (Single x):a:cc

-- Duplicate the elements of a list
problem14 :: [a] -> [a]
problem14 []     = []
problem14 (x:xs) = x:x:(problem14 xs)

-- Replicate the elements of a list a given number of times
problem15 :: [a] -> Int -> [a]
problem15 x n = foldr (\x acc -> (take n (repeat x)) ++ acc) [] x

-- Drop every N'th element from a list
problem16 :: [a] -> Int -> [a]
problem16 x n = [ i | (i, c) <- zip x [1..], mod c n /= 0 ]

-- Split a list into two parts; the length of the first part is given
problem17 :: [a] -> Int -> ([a], [a])
problem17 x n = (aux1 x n, aux2 x ((length x)-n))
    where aux1 x n = if length x > n then aux1 (init x) n else x
          aux2 x n = if length x > n then aux2 (tail x) n else x

-- Extract a slice from a list
problem18 :: [a] -> Int -> Int -> [a]
problem18 x a b = drop (a-1) $ take b x

-- Rotate a list N places to the left.
problem19 :: [a] -> Int -> [a]
problem19 x n = let l = length x
                    m = head [ i | i <- [n,n+l..], i >= l ] `mod` l
                in drop m x ++ take m x

-- Remove the N'th element from a list
problem20 :: [a] -> Int -> (a, [a])
problem20 x n = (x !! (n-1), take (n-1) x ++ drop n x)
