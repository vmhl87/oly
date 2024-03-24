-- input parsing

import Data.Char

stoi :: String -> [Int]
stoi "" = [0]
stoi str
  | isDigit x = init xs ++ [last xs * 10 + digitToInt x]
  | otherwise = xs ++ [0]
  where
    x = last str
    xs = stoi (init str)


-- math - factorial & binomial coef

mmul :: Int -> Int -> Int
mmul a b = a * b `mod` 1000000007

fact :: Int -> Int
fact 0 = 1
fact x = x `mmul` fact (x-1)

bexp :: Int -> Int -> Int
bexp a 0 = 1
bexp a p = bexp (a `mmul` a) (p `div` 2) `mmul` if even p then 1 else a

inv :: Int -> Int
inv x = bexp x 1000000005

nck :: Int -> Int -> Int
nck n k = num `mmul` inv den
  where
    num = fact n
    den = fact k `mmul` fact (n-k)


-- compute reductions of prefix/suffixes

reduce :: Int -> [Int] -> Int
reduce n s =
  if length s < 3 then 1
  else
    (reduce n (init s)) `mmul` (fact diff) `mmul` (nck (last s-2) diff)
    where
      diff = (last s) - (last (init s)) - 1
 
rev :: Int -> [Int] -> [Int]
rev n [] = []
rev n s = n+1 - last s : rev n (init s)


-- process test cases

test_case :: Int -> IO ()
test_case 0 = return ()
test_case x = do
  con <- getLine
  let [n,p,s] = stoi con
  prefix <- getLine
  let ps = stoi prefix
  suffix <- getLine
  let ss = stoi suffix
  if last ps /= head ss || 1 /= head ps || n /= last ss
    then print 0
    else
      print ((nck (n-1) (head ss - 1)) `mmul` (reduce n ps) `mmul`
        (reduce n (rev n ss)))
  test_case (x-1)


-- main

main :: IO ()
main = do
  cases <- getLine
  let c = (read cases :: Int)
  test_case c
