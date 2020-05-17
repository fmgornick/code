# CSCI 1133, Lab Section 002, HW 3, Problem B
# Fletcher Gornick, GORNI025
    
def play_game(P1P, P2P):
    if P1P == P2P:
        return 'T'

    elif P1P == 'R' and P2P == 'P':
        return 2
    
    elif P1P == 'R' and P2P == 'SC':
        return 1
    
    elif P1P == 'R' and P2P == 'SP':
        return 2
    
    elif P1P == 'R' and P2P == 'L':
        return 1
    
    elif P1P == 'P' and P2P == 'R':
        return 1
    
    elif P1P == 'P' and P2P == 'SC':
        return 2
    
    elif P1P == 'P' and P2P == 'SP':
        return 1
    
    elif P1P == 'P' and P2P == 'L':
        return 2
    
    elif P1P == 'SC' and P2P == 'R':
        return 2
    
    elif P1P == 'SC' and P2P == 'P':
        return 1
    
    elif P1P == 'SC' and P2P == 'SP':
        return 2
    
    elif P1P == 'SC' and P2P == 'L':
        return 1
    
    elif P1P == 'SP' and P2P == 'R':
        return 1
    
    elif P1P == 'SP' and P2P == 'P':
        return 2
    
    elif P1P == 'SP' and P2P == 'SC':
        return 1
    
    elif P1P == 'SP' and P2P == 'L':
        return 2
    
    elif P1P == 'L' and P2P == 'R':
        return 2
    
    elif P1P == 'L' and P2P == 'P':
        return 1
    
    elif P1P == 'L' and P2P == 'SC':
        return 2
    
    elif P1P == 'L' and P2P == 'SP':
        return 1



def play_round(P1L, P2L):
    P1W = 0
    P2W = 0
    for i in range(1,4):
        P1P = P1L[i]
        P2P = P2L[i]
        play_game(P1P, P2P)
        if play_game(P1P, P2P) == 1:
            P1W += 1
        elif play_game(P1P, P2P) == 2:
            P2W += 1

    if P1W == 2 or P2W == 2:

        if P1W > P2W:
            if P1L[0] == 1:
                return 1
            else:
                return 2


    elif P1W > P2W:
        if P1L[0] == 1:
            return 1
        else:
            return 2

    elif P1W < P2W:
        if P2L[0] == 2:
            return 2
        else:
            return 1

    else:
        return 'T'




def main():
    P1L = [1]
    P2L = [2]
    P1_1 = input('P1:  ')
    P1L.append(P1_1)
    P2_1 = input('P2:  ')
    P2L.append(P2_1)
    P1_2 = input('P1:  ')
    P1L.append(P1_2)
    P2_2 = input('P2:  ')
    P2L.append(P2_2)
    P1_3 = input('P1:  ')
    P1L.append(P1_3)
    P2_3 = input('P2:  ')
    P2L.append(P2_3)
    print(play_round(P1L, P2L))



if __name__ == "__main__":
    main()
