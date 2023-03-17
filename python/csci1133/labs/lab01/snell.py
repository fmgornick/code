# CSCI 1133, Lab Section 002, HW 1, Problem 1A
# FLETCHER_GORNICK, GORNI025

import math
incidentAngle = float (input("Input the incident angle in degrees: "))
incidentAngle = math.radians(incidentAngle)
n1 = float (input("Input the index of refraction for the first medium: "))
n2 = float (input("Input the index of refraction for the second medium: "))
angleOfRefraction = math.asin(math.sin(incidentAngle) * n1/n2)
print("The angle of refraction is ", math.degrees(angleOfRefraction) , "degrees")
