rap <- read.csv("rapData.csv", header = TRUE)[c("SongName", "PercentageDistinct")]
country <- read.csv("countryData.csv", header = TRUE)[c("SongName", "PercentageDistinct")]

r <- c(rap$PercentageDistinct)
c <- c(country$PercentageDistinct)


sd(r)
sd(c)

t <- (mean(r) - mean(c)) / sqrt(sd(r)^2/30 + sd(c)^2/30)
v <- 29

p <- 1 - pt(t,df=v)

cat(t)

t.test(r,c,alternative="two.sided",var.equal=FALSE,conf.level=0.95)
sd(r)
sd(c)
