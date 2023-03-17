file = open("text.txt", "r")
file = file.read()

uppercase = file.upper()

occur = []
for char in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    n = 0
    for ch in uppercase:
        if ch == char:
            n += 1
    print(char, ':', n)
 