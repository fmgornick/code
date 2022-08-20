import Data.Char (toLower)
import Data.List (isInfixOf)
import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

-- get words from user
getWords :: IO [String]
getWords = helper []
  where
    helper words = do
      putStr "> "
      w <- getLine
      case w of
        "" -> return words
        word -> helper (words ++ [word])

-- check if words in file (also change everything to lowercase)
findStrings :: [String] -> String -> [String]
findStrings targets input = filter (\word -> map toLower word `isInfixOf` file) targets
  where
    file = map toLower input

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStrLn "specify the words to search:"
  words <- getWords

  putStr "file to search: "
  file <- getLine
  contents <- readFile file

  let found = findStrings words contents
  let notFound = [w | w <- words, w `notElem` found]

  mapM_ (\w -> putStrLn $ "\"" ++ w ++ "\" found") found
  mapM_ (\w -> putStrLn $ "\"" ++ w ++ "\" NOT found") notFound
