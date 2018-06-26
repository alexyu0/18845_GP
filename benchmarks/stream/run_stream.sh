#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container)"
    exit 1
fi

# clear previous results

# run necessary environment specific stuff
case $1 in
    vm) rm -f /vagrant/benchmarks/stream/results_$1.txt
        cp -r /vagrant/benchmarks/stream .
        cd stream
        make
        ;;
    container_run) rm -f results_$1.txt results_container_cmd.txt
        make
        docker build -t stream .
        docker run --name=test_stream \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --privileged \
            stream
        ;;
    bare) rm -f results_$1.txt
        make
        ;;
esac

# run stream for uniprocessor benchmark
if [ "$1" != "container_run" ]; then
    for run in {1..10}
    do
        ./stream >> results_$1.txt
        { echo "" && echo "" ; } >> results_$1.txt
    done
fi

# clean up
case $1 in
    vm) mv results_$1.txt /vagrant/benchmarks/stream
        cd ..
        rm -rf stream
        ;;
    container_run) containerId=$(docker ps -aqf "name=test_stream")
        docker cp $containerId:/results_container_cmd.txt .
        docker stop test_stream
        docker rm test_stream
        ;;
esac

