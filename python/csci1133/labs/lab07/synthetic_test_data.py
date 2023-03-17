import random

fileobj = open('synthetic_test_data.csv' , 'w')

record = ''
for i in range(1,1001):
    record += str(i) + ','
    record += str(random.randint(-1000,1000)) + '\n'

fileobj.write(record)

fileobj.close()