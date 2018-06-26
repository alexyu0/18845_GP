#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container_run, container_cmd)"
    exit 1
fi

# run environment specific stuff
case $1 in
    vm) sudo apt-get -y install libtool \
            autotools-dev \
            automake
	
        rm -f /vagrant/benchmarks/filebench-1.5-alpha3/results_$1.txt
        cp -r /vagrant/benchmarks/filebench-1.5-alpha3 .
        cd filebench-1.5-alpha3
        
        libtoolize
        aclocal
        autoheader
        automake --add-missing
        autoconf
        ./configure
        make
        sudo make install
        ;;
    container_run) rm -f results_$1.txt results_container_cmd.txt
        docker build -t filebench .
        docker run --name=test_filebench \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --privileged \
            --mount source=filebench_vol,target=/docker_volumes \
            filebench
        ;;
    bare) rm -f results_$1.txt
        ;;
esac

# run filebench
if [ "$1" != "container_run" ]; then
    for run in {1..10}
    do
        echo $run
        if [ "$1" = "container_cmd" ]; then
            filebench -f randomrw.f >> results_$1.txt
        else
            sudo filebench -f randomrw.f >> results_$1.txt
        fi
        { echo "" && echo "" ; } >> results_$1.txt
        break
    done
fi

# clean up
case $1 in
    vm) mv results_$1.txt /vagrant/benchmarks/filebench-1.5-alpha3
        cd ..
        rm -rf filebench-1.5-alpha3
        ;;
    container_run) containerId=$(docker ps -aqf "name=test_filebench")
        docker cp $containerId:/results_container_cmd.txt .
        docker stop test_filebench
        #docker rm test_filebench
        ;;
esac

