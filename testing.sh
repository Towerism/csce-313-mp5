#! /bin/bash

REQUESTS=1000
PORT=99450
BACKLOG=64
DSERVPID=
CLIENTS=

CLIENT_ARRAY=(1 2 4 8 16 32 64)
echo "client array is ${CLIENT_ARRAY[*]}"

# empty the logging file
echo "" > timing.log

exectest () {
echo "backlog $BACKLOG, $CLIENTS client(s):" >> timing.log
(time ./client -p $PORT -w $CLIENTS -n $REQUESTS -x) 2>> timing.log
echo "==================================" >> timing.log
}


# server with backlog 64
./data_server -p $PORT -b $BACKLOG &
DATASERVPID=$!

for i in ${CLIENT_ARRAY[*]}; do
    CLIENTS=$i
    exectest
done

kill -KILL $DATASERVPID


# server with backlog 128
let "PORT++"
BACKLOG=128
./data_server -p $PORT -b $BACKLOG &
DATASERVPID=$!

for i in ${CLIENT_ARRAY[*]}; do
    CLIENTS=$i
    exectest
done

kill -KILL $DATASERVPID


# server with backlog 256
let "PORT++"
BACKLOG=256
./data_server -p $PORT -b $BACKLOG &
DATASERVPID=$!

for i in ${CLIENT_ARRAY[*]}; do
    CLIENTS=$i
    exectest
done

kill -KILL $DATASERVPID


# server with backlog 512
let "PORT++"
BACKLOG=512
./data_server -p $PORT -b $BACKLOG &
DATASERVPID=$!

for i in ${CLIENT_ARRAY[*]}; do
    CLIENTS=$i
    exectest
done

kill -KILL $DATASERVPID
