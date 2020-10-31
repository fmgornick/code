rap <- read.csv("rapData.csv", header = TRUE)[c("SongName", "PercentageDistinct")]
country <- read.csv("countryData.csv", header = TRUE)[c("SongName", "PercentageDistinct")]

cat("for this project we have two separate csv files that want to keep separate for now, until we compare in pt 3\n\n")

cat("RAP\n")
names(rap)

cat("head\n")
head(rap)
cat("\n")
cat("tail\n")
tail(rap)

cat("\n\n")

cat("COUNTRY\n")
names(country)
cat("head\n")
head(country)
cat("\n")
cat("tail\n")
tail(country)
