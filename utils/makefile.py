'''
This script creates files of data for us to run our programs on
Authors: Madeline Stager and Sonika Garg 
'''

import random

MIN_VALUE = -1000000
MAX_VALUE = 1000000


#method to create a file (named fileName) of numValues length and random data
def createFile(numValues, fileName):
    file = open(fileName, "w")
    
    file.write(str(numValues) + "\n")
    for i in range(numValues):
        num = random.randint(MIN_VALUE, MAX_VALUE)
        file.write(str(num) + " ")
    
    file.write("\n")
    file.close()



createFile(6, "prefixTest1.txt")

    

