CSCE-313-MP4
============

Multi-threading client-server assignment

####Generate Makefiles
```
$ cmake .
```
NOTE: you can run `cmake ../` from `cd bin` to avoid cluttering your local repo.  If you decide to do this you must run `make mp4` from `cd bin` as well.  (Note when we say run `<command>` from `cd <directory>`, we mean first `cd <directory>` and then `<command>`.)

####Running
If you have already generated makefiles
```
$ make mp4
```

####Testing
If you have already generated makefiles
```
$ make test_suite
```
NOTE: Google test must be installed or the test suite will not compile.
