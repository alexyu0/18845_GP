#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container)"
    exit 1
fi

# clear previous results

# run environment specific stuff
case $1 in
    vm) rm -f /vagrant/benchmarks/linpack/bin/results_$1.txt
        cp -r /vagrant/benchmarks/linpack .
        cd linpack/bin
        ;;
    container_run) rm -f results_$1.txt results_container_cmd.txt
        docker build -t linpack .
        docker run --name=test_linpack \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --privileged \
            linpack
        ;;
    bare) rm -f result_$1.txt
        ;;
esac

# run linpack benchmark
if [ "$1" != "container_run" ]; then
    taskset --cpu-list 0-3 ./runme_xeon64 >> results_$1.txt
fi

# clean up
case $1 in
    vm) mv results_$1.txt /vagrant/benchmarks/linpack/bin
        cd ..
        rm -rf linpack
        ;;
    container_run) containerId=$(docker ps -aqf "name=test_linpack")
        docker cp $containerId:/results_container_cmd.txt .
        docker stop test_linpack
        docker rm test_linpack
        ;;
esac

