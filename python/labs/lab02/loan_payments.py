r = (int(input("what is the annual interest rate of your loan?...  "))) / 12
la = int(input("what is your loan amount?...  "))
n = int(input("what is the duration of your loan (months)?...  "))
p = ( r * la ) / ( 1 - ( 1 + r )**(-n) )
print("your monthly payment will be " , p , "dollars")
