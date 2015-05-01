#! /bin/bash

REQUESTS=1000
PORT=97450
BACKLOG=64
CLIENTS=

declare -a CLIENT_ARRAY
CLIENT_ARRAY[0]=1
CLIENT_ARRAY[1]=2
CLIENT_ARRAY[2]=4
CLIENT_ARRAY[3]=8
CLIENT_ARRAY[4]=16
CLIENT_ARRAY[5]=32
CLIENT_ARRAY[6]=64
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

for i in $CLIENT_ARRAY; do
    echo $CLIENT_ARRAY
    CLIENTS=$i
    echo $CLIENTS
    exectest
done


# server with backlog 128
let "PORT++"
BACKLOG=128
./data_server -p $PORT -b $BACKLOG &

for i in $CLIENT_ARRAY; do
    echo $CLIENT_ARRAY
    CLIENTS=$i
    echo $CLIENTS
    exectest
done


# server with backlog 256
let "PORT++"
BACKLOG=256
./data_server -p $PORT -b $BACKLOG &

for i in $CLIENT_ARRAY; do
    echo $CLIENT_ARRAY
    CLIENTS=$i
    echo $CLIENTS
    exectest
done


# server with backlog 512
let "PORT++"
BACKLOG=512
./data_server -p $PORT -b $BACKLOG &

for i in $CLIENT_ARRAY; do
    echo $CLIENT_ARRAY
    CLIENTS=$i
    echo $CLIENTS
    exectest
done
