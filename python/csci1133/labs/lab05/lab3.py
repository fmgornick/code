def minimumIndex(lis, indexnum):
    small = indexnum + 2
    for i in range(indexnum, len(lis)-1):
        if lis[i] > lis[i + 1]:
            small = i + 1
    print(small)

