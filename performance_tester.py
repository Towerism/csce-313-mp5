import math
import subprocess
if __name__ == '__main__':
    testing_nums = []
for i in range(10):
    testing_nums.append(math.pow(5, i))
    for i in range(10):
        print "---------- buffer size = " + str(testing_nums[i]) + " ----------"
        for j in range(10):
            print "worker thread count = " + str(testing_nums[j])
            #-n = request count | -b is buffer size | -w is worker thread count | -x specifies no graphics
            subprocess.call(['./mp4 ', "-x" , "-n 1000" , "-b " + str(testing_nums[i]), "-w " + str(testing_nums[i])])
