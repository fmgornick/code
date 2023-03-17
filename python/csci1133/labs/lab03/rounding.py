def roundFloat(floating):
    integer = int(floating + 0.5)
    return integer

def main():
    floating = float(input('Insert a floating point-number: '))
    print(roundFloat(floating))

main()
