morseDictionary = {
    ' ': '/',
    'A': '.-', 
    'B': '-...',
    'C': '-.-.', 
    'D': '-..', 
    'E': '.', 
    'F': '..-.', 
    'G': '--.', 
    'H': '....', 
    'I': '..', 
    'J': '.---', 
    'K': '-.-',
    'L': '.-..', 
    'M': '--',
    'N': '-.', 
    'O': '---', 
    'P': '.--.',
    'Q': '--.-', 
    'R': '.-.', 
    'S': '...',
    'T': '-', 
    'U': '..-',
    'V': '...-',
    'W': '.--',
    'X': '-..-',
    'Y': '-.--',
    'Z': '--..'
    }


def morse_code_translator(string):
    string = string.upper()
    new_string = ''
    for char in string:
        for letter in ' ABCDEFGHIJKLMNOPQRSTUVWXYZ':
            if char == letter:
                new_string += morseDictionary[letter]
    return new_string


