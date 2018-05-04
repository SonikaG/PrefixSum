'''
This script creates files of data for us to run our programs on
Authors: Madeline Stager and Sonika Garg 
'''

import random

# MIN_VALUE = -1000000
# MAX_VALUE = 1000000
MIN_VALUE = -1000
MAX_VALUE = 1000


#method to create a file (named fileName) of numValues length and random data
def createFile(numValues, fileName):
    file = open(fileName, "w")
    
    file.write(str(numValues) + "\n")
    for i in range(numValues):
        num = random.randint(MIN_VALUE, MAX_VALUE)
        file.write(str(num) + " ")
    
    file.write("\n")
    file.close()



# createFile(5, "prefix5.txt")
# createFile(20, "prefix20.txt")
# createFile(100, "prefix100.txt")
# createFile(1000, "prefix1000.txt")
createFile(1000, "prefix10000.txt")
# createFile(100000, "prefix100000.txt")
# createFile(1000000, "prefix1000000.txt")
# createFile(10000000, "prefix10000000.txt")
# createFile(100000000, "prefix100000000.txt")
    

