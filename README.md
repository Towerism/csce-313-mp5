CSCE-313-MP4
============

Multi-threading client-server assignment

####Generate Makefiles
```
$ cd bin
$ cmake ../
```
NOTE: you can run `cmake .` in the root directory, but it will create a mess that you will have to clean up yourself

####Running
If you have already generated makefiles
```
$ cd bin
$ make mp4
$ ./mp4
```

####Testing
If you have already generated makefiles
```
$ cd bin
$ make test_suite
$ ./test_suite
```
NOTE: Google test must be installed or the test suite will not compile.
