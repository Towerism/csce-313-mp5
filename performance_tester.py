import math
import time
import subprocess
from functools import wraps

def test_performance():
    testing_buf = [10, 100, 1000, 10000]
    #testing_work = [10, 100, 1000, 10000]
    testing_work = [5, 10, 25, 50, 100, 150]
    for i in range(len(testing_buf)):
        print "---------- buffer size = " + str(testing_buf[i]) + " ----------"
        for j in range(len(testing_work)):
            print "worker thread count = " + str(testing_work[j])
            #-n = request count | -b is buffer size | -w is worker thread count | -x specifies no graphics
            start = time.time()
            external_call(testing_buf[i], testing_work[j])
            print (time.time() - start)

def external_call(b, w):
    subprocess.call(['./client', '-n 2000', '-b '+ str(b), '-w ' + str(w), '-x'], shell=False)




if __name__ == '__main__':
    test_performance()
