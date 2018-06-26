#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container)"
    exit 1
fi

# run necessary environment specific stuff
port=6379
host=127.0.0.1
case $1 in
    vm) rm -f /vagrant/benchmarks/ycsb-0.12.0/results_$1.txt
        sudo apt-get -y install python
        cp -r /vagrant/benchmarks/ycsb-0.12.0 .
        cd ycsb-0.12.0
        ;;
    container_run) rm -f results_$1.txt results_container_cmd.txt
        docker run --name=test_ycsb \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --net=host \
            -d \
            redis
        port=6379
        host=0.0.0.0
        ;;
    bare) rm -f results_$1.txt
        port=6380
        ;;
esac

for run in {1..10}
do
    taskset --cpu-list 0-3 ./bin/ycsb load redis -s -P workloads/workloada \
        -p "redis.host=$host" -p "redis.port=$port" >> results_$1.txt
    taskset --cpu-list 0-3 ./bin/ycsb run redis -s -P workloads/workloada \
        -p "redis.host=$host" -p "redis.port=$port" >> results_$1.txt
    { echo "" && echo "" ; } >> results_$1.txt
done

# clean up
case $1 in
    vm) mv results_$1.txt /vagrant/benchmarks/ycsb-0.12.0
        cd ..
        rm -rf ycsb-0.12.0
        ;;
    container_run) docker stop test_ycsb
        docker rm test_ycsb
        ;;
esac

