#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container_run, container_cmd)"
    exit 1
fi

# run necessary environment specific stuff
case $1 in
    vm) rm -f /vagrant/benchmarks/linux-4.2.2/results_$1.txt
        cp -r /vagrant/benchmarks/linux-4.2.2 .
        sudo chown vagrant:vagrant -R linux-4.2.2
        cd linux-4.2.2
        make clean > /dev/null

        sudo apt-get install bc
        ;;
    container_run) docker build -t kernel_compile .
        docker run --name=test_kernel_compile \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --privileged \
            kernel_compile
        ;;
    container_cmd) unzip linux-4.2.2.zip
        cd linux-4.2.2
        rm -f results_$1.txt results_container_run.txt
        make clean > /dev/null
        ;;
    bare) rm -f results_$1.txt
        make clean > /dev/null
        ;;
esac

# time linux kernel compilation using 4 threads/cores
if [ "$1" != "container_run" ]; then
    for run in {1..10}
    do
        echo "run no. $run"
        { time taskset --cpu-list 0-3 make -j4 > /dev/null 2>&1 ; } 2>> results_$1.txt
        make clean > /dev/null
    done
fi

# clean up
case $1 in
    vm) mv results_$1.txt /vagrant/benchmarks/linux-4.2.2
        cd ..
        rm -rf linux-4.2.2
        ;;
    container_run) containerId=$(docker ps -aqf "name=test_kernel_compile")
        docker cp $containerId:/linux-4.2.2/results_container_cmd.txt .
        docker stop test_kernel_compile
        docker rm test_kernel_compile
        ;;
esac

