#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container)"
    exit 1
fi

# clear previous results

# run necessary environment specific stuff
case $1 in
    vm) rm -f /vagrant/benchmarks/pxz_enwik9/results_$1.txt
        sudo apt-get -y install unzip
        sudo apt-get -y install pxz

        # set up and run pxz on enwik9
        cp /vagrant/benchmarks/pxz_enwik9/enwik9.zip .
        unzip enwik9.zip
        cp enwik9 /dev/shm
        ;;
    container_run) rm -f results_$1.txt results_container_cmd.txt
        docker build -t pxz .
        docker run --name=test_pxz \
            --cpuset-cpus="0-3" \
            --privileged \
            --shm-size=4g \
            --memory=4g \
            pxz
        ;;
    container_cmd) unzip enwik9.zip
        cp enwik9 /dev/shm
        ;;
    bare) rm -f results_$1.txt
        unzip enwik9.zip
        cp enwik9 /dev/shm
        ;;
esac

# time compression of enwik9 for level 2 compression
if [ "$1" != "container_run" ]; then
    for run in {1..10}
    do
        { time taskset --cpu-list 0-3 \
            pxz -T4 -cf -2 /dev/shm/enwik9 > /dev/null 2>&1 ; } \
            2>> results_$1.txt
        { echo "" && echo "" ; } >> results_$1.txt
    done
fi

# clean up
rm -f /dev/shm/enwik9
case $1 in
    vm) rm enwik9.zip
        rm enwik9
        mv results_$1.txt /vagrant/benchmarks/pxz_enwik9
        ;;
    container_run) containerId=$(docker ps -aqf "name=test_pxz")
        docker cp $containerId:/results_container_cmd.txt .
#        docker stop test_pxz
#        docker rm test_pxz
        ;;
esac

