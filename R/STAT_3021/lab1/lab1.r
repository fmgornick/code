rappers <- c("Sheck Wes", "Travis Scott", "NF", "MGK")
count <- c(12, 78, 30, 32)

pie(count, labels=rappers, main="Best Rappers Survey")
barplot(count, names=rappers, main="Best Rappers Survey")

nba <- read.table("http://users.stat.umn.edu/~wuxxx725/data/NBAsalary.txt", sep='\t', header=TRUE)
stem(nba$Salary)

summary(nba$Salary)
iqr <- IQR(nba$Salary)
sprintf("IQR: %.0f", iqr)

nba_smallest_to_largest <- nba[order(nba$Salary),]

hist(nba$Salary, main="NBA Team Salary", xlab="USD", breaks=10)

hist(nba$Salary[nba$Conference == "E"], main="Eastern Conference Team Salary", xlab="USD")
hist(nba$Salary[nba$Conference == "W"], main="Western Conference Team Salary", xlab="USD")

boxplot(nba$Salary, main="NBA Salary", ylab="USD")
boxplot(nba$Salary~nba$Conference, main="NBA Salary by Conference", ylab="USD", names=c("Eastern", "Western"))
