def DetermineCholesterolRatio(total, HDR):
    ratio = total / HDR
    if ratio <= 3.5:
        comment = 'less than average heart risk'
    elif 3.5 < ratio <= 4.5:
        comment = 'average risk'
    elif ratio > 4.5:
        comment = 'high risk'
    return str(ratio) + ':' + comment

print(DetermineCholesterolRatio(135, 40))
