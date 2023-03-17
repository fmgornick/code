# CSCI 1133, Fletcher Gornick, gorni025
# lab Section 002, HW 3, Problem A

def CMYK_to_RGB(C, M, Y, K):
    R = 255 * (1 - C) * (1 - K)
    G = 255 * (1 - M) * (1 - K)
    B = 255 * (1 - Y) * (1 - K)
    return [int(round(R)), int(round(G)), int(round(B))]

def main():
    C = 0.01 * int(input('Cyan component:  '))
    M = 0.01 * int(input('Magenta component:  '))
    Y = 0.01 * int(input('Yellow component:  '))
    K = 0.01 * int(input('Black (Key) component:  '))
    RGB = CMYK_to_RGB(C, M, Y, K)
    print('RGB represtentation:  ', RGB[0], RGB[1], RGB[2])

if __name__ == "__main__":
    main()
