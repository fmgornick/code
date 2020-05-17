def cnt_occur(n,v):
        k = []
        if n==v:
                return 1 + cnt_occur ( [n+1], v )
#   elif isistance([0], list):
#       return cnt_occur([0] + cnt_occur[n+1]
#    elif[0] !=x             

        else:

                return 0 + cnt_occur ( [n+1], v )

print(cnt_occur([1,1,1], 1))
