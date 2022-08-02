data <- c(18.71, 21.41, 20.72, 21.81, 19.29, 22.43, 20.17, 23.71, 19.44, 20.50, 
          18.92, 20.33, 23.00, 22.85, 19.25, 21.77, 22.11, 19.77, 18.04, 21.12)

data_trimmed <- c(20.72, 21.81, 19.29, 22.43, 20.17, 23.71, 19.44, 20.50, 
                  18.92, 20.33, 23.00, 22.85, 19.25, 21.77, 22.11, 19.77) 

sprintf("mean: %.2f", mean(data))
sprintf("median: %.2f", median(data))

sprintf("mean trimmed: %.2f", mean(data_trimmed))

stripchart(data)
stem(data)
print("no, they seem pretty similar")

sprintf("sample variance: %.2f", var(data))
sprintf("sample standard deviation: %.2f", sd(data))

mean_value <- mean(data)
sd_value <- sd(data)
sprintf("interval: %.2f - %.2f", mean_value - 3*sd_value, mean_value + 3*sd_value)
sprintf("")

cereal <- read.csv("http://sites.williams.edu/bklingen/files/2015/05/cereal.csv")
head(cereal)

print("Categorical: Cereal and Type")
print("Quantitative: Sodium and Sugar")

boxplot(cereal$Sugar, main="Sugar in Cereal", ylab="grams")
summary(cereal$Sugar)

print("being that the median is slightly greater than the mean, the plot is most
      likely sweked left, but being that all these pairings are based off cereal
      brands, it's probably not significant")

hist(cereal$Sugar, breaks=10, main="Sugar in Cereal", xlab="grams of sugar")

print("this actually looks very bimodal")

boxplot(cereal$Sugar~cereal$Type, main="Type A vs. Type C", ylab="Sugar (g)", names=c("Type A", "Type C"))

print("looks like type c has a higher average of sugar, and it's IQR is much tighter
      above type a.  Type a is most likely a low sugar cereal")
