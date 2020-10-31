module Problems.Problems1_10 where

-- Find the last element of a list
problem1 :: [a] -> a
problem1 = last

-- Find the last but one element of a list
problem2 :: [a] -> a
problem2 = last . init

-- Find the K'th element of a list. The first element in the list is number 1
problem3 :: [a] -> Int -> a
problem3 x k = x !! (k - 1)

-- Find the number of elements of a list
problem4 :: [a] -> Int
problem4 = foldr (flip (const . (+1))) 0

-- Reverse a list
problem5 :: [a] -> [a]
problem5 = foldl (flip (:)) []

-- Find out whether a list is a palindrome
problem6 :: Eq a => [a] -> Bool
problem6 x = x == (reverse x)

-- Flatten a nested list structure
data NestedList a = Elem a | List [NestedList a]

problem7 :: NestedList a -> [a]
problem7 (Elem x) = [x]
problem7 (List x) = foldr (++) [] $ map problem7 x

-- Eliminate consecutive duplicates of list elements
problem8 :: Eq a => [a] -> [a]
problem8 x = foldr (\x acc -> if x == head acc then acc else x:acc) [last x] x

-- Pack consecutive duplicates of list elements into sublists
problem9 :: Eq a => [a] -> [[a]]
problem9 x = foldr (\x (a:cc) -> if x == head a then (x:a):cc else [x]:a:cc) [[last x]] x

-- Run-length encoding of a list
problem10 :: Eq a => [a] -> [(Int, a)]
problem10 x = (\x -> (length x, head x)) <$> (problem9 x)
