#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <type of host (bare, vm, container)> " \
        "<benchmark (kernel, pxz, linpack, filebench, ycsb, stream, mysql)>"
    exit 1
fi

# clear previous results
rm -f /vagrant/benchmarks/$2/results_$1.txt

# run environment specific stuff
case ${1}+${2 in
    "vm"
        
        ;;
