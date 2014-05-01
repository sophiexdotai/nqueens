-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- Created by Joseph I. Tannenbaum <joseph.i.tannenbaum gmail com>


module Main( main ) where
import System ( getArgs )
type Queen = (Int, Int)
type Solution = [Queen]

nonattacking :: Queen -> Queen -> Bool
(x1, y1) `nonattacking` (x2, y2) = x1 /= x2 && y1 /= y2 && abs (x2 - x1) /= abs (y2 - y1)

promising :: Solution -> Bool
promising (x:xs) = all (x `nonattacking`) xs

backtracking :: Int -> Solution -> Solution
backtracking n all@((x1, y1):xs)
    | x1 == n = backtracking n $ (succ $ fst (head xs), snd $ head xs) : (tail xs)
    | promising all = if length all == n then all else backtracking n $ (0, succ y1) : all
    | otherwise = backtracking n $ (succ x1, y1) : xs

pprint :: Int -> Solution -> String
pprint n xs = concat [(concat [if elem (x, y) xs then "1 " else "0 " | x <- [0..n-1] ] ) ++ "\n" | y <- [0..n-1]]

main = do
    args <- getArgs
    let n = (read $ head args :: Int)
    putStrLn $ pprint n $ backtracking n [(0,0)]
