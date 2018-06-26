#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 type of host (bare, vm, container)"
    exit 1
fi

# run necessary environment specific stuff
host=127.0.0.1
port=3360
mysql_user="root"
mysql_pwd="test"
case $1 in
    vm) rm -f /vagrant/benchmarks/mysql/results_$1*
        mysql -u $mysql_user -p$mysql_pwd < \
            /vagrant/benchmarks/mysql/setup_vm_and_bare_db.sql
        port=3306
        ;;
    container_run) rm -f results_$1* results_container_cmd*
        current_dir=$(pwd)
        docker run --name=test_mysql \
            --cpuset-cpus="0-3" \
            --memory=4g \
            --net=host \
            -v $current_dir:/etc/mysql/conf.d \
            -e MYSQL_ROOT_PASSWORD=test \
            -d \
            alexyu0/sysbench_mysql
        sleep 60
        port=3306
        host=0.0.0.0
        docker cp sysbench_run.sh test_mysql:/
        eval mysql -uroot -ptest -P3306 -h0.0.0.0 < setup_container_db.sql
        ;;
    bare) rm -f results_$1*
        sudo service mysql start
        sleep 60
        eval mysql -uroot -ptest -P3360 -h127.0.0.1 < setup_vm_and_bare_db.sql
        ;;
esac

# run mysql benchmarks with sysbench
taskset --cpu-list 0-3 \
    sysbench --db-driver=mysql --mysql-user=$mysql_user \
        --mysql-password=$mysql_pwd --table-size=2000000 --mysql-db=test \
        --mysql-host=$host --mysql-port=$port --time=30 --max-requests=0 \
        --threads=300 \
        /usr/share/sysbench/oltp_read_only.lua prepare
numCli=10
while [ $numCli -lt 300 ]
do
    for run in {1..5}
    do
        echo "$numCli - $run"
        if [ "$1" = "container_run" ]; then
            docker exec test_mysql \
                ./sysbench_run.sh \
                    $mysql_user \
                    $mysql_pwd \
                    $port \
                    $numCli \
            >> results_$1_$numCli.txt
        else
            taskset --cpu-list 0-3 \
                sysbench --db-driver=mysql --mysql-user=$mysql_user \
                    --mysql-password=$mysql_pwd --table-size=2000000 --mysql-db=test \
                    --mysql-host=127.0.0.1 --mysql-port=$port --time=30 --max-requests=0 \
                    --threads=$numCli \
                    /usr/share/sysbench/oltp_read_only.lua run \
                >> results_$1_$numCli.txt
        fi
        { echo "" && echo "" ; } >> results_$1_$numCli.txt
    done

    numCli=$(($numCli + 20))
done

# clean up
case $1 in
    vm) mv results_$1* /vagrant/benchmarks/mysql
        ./drop_all_tables.sh root test test
        ;;
    container_run) docker stop test_mysql
        docker rm test_mysql
        ;;
    bare) ./drop_all_tables.sh root test test $port $host
        sudo service mysql stop
        ;;
esac

