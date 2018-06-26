#!/bin/bash

taskset --cpu-list 0-3 \
    sysbench --db-driver=mysql --mysql-user=$1 \
        --mysql-password=$2 --table-size=2000000 --mysql-db=test \
        --mysql-host=127.0.0.1 --mysql-port=$3 --time=30 --max-requests=0 \
        --threads=$4 \
        /usr/share/sysbench/oltp_read_only.lua run

