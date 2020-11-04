p=c(.1,.3,.5,.8)
n = 10
x<-c(1:n)
par(mfrow=c(2,2))

for (i in c(1:4)) {
    plot(x,dbinom(x,n,p[i]),xlab="",ylab=p[i])
}

n = 1000
x <- c(1:n)

par(mfrow=c(1,1))

for (i in c(1:4)) {
    plot(x,dbinom(x,n,p[i]),xlab="",ylab="", main=paste("Binom of", p[i], "Probability"))
}

plot(x, dbinom(x,n,.3), xlab="", ylab=0.3, xlim=c(250,350), main="Binom of 0.3 Probability")
