CSCE-313-MP4
============

Multi-threading client-server assignment

####Compiling
This will make everything you need to run the client and dataserver
```
$ make
```

####Usage
To run with default options (10000 requests, 100 buffer limit, 10 worker threads):
```
$ ./client
```
To specify options, you can use the following
```
-n <num requests>
-b <buffer limit>
-w <num workthreads>
-g <graphic updates/second>
-x disables graphics
```

####Testing
```
$ make test
```
