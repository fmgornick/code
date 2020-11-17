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

hist(rap$PercentageDistinct, main="Histogram for Percentage of Distinct Words in Rap Songs", xlab="Percentage", ylab="Number of Songs", xlim=c(15,45), ylim=c(0,10))
hist(country$PercentageDistinct, main="Histogram for Percentage of Distinct Words in Country Songs", xlab="Percentage", ylab="Number of Songs")
boxplot(rap$PercentageDistinct,country$PercentageDistinct,main="Boxplot of Distinct Word Percentages", names=c("Rap","Country"),ylab="Percentage")

cat("\n\n")

summary(rap$PercentageDistinct)
cat("\n")
summary(country$PercentageDistinct)

qqnorm(rap$PercentageDistinct, pch = 1, frame = FALSE, main="QQ Plot for Percentage of Distinct Words in Rap Songs")
qqline(rap$PercentageDistinct, col="steelblue", lwd = 2)

qqnorm(country$PercentageDistinct, pch = 1, frame = FALSE, main="QQ Plot for Percentage of Distinct Words in Country Songs")
qqline(country$PercentageDistinct, col="steelblue", lwd = 2)
