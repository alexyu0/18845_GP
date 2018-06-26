#!/bin/bash
MUSER="$1"
MPASS="$2"
MDB="$3"
MPORT="$4"
MHOST="$5"
 
# Detect paths
MYSQL=$(which mysql)
AWK=$(which awk)
GREP=$(which grep)
 
if [ $# -ne 5 ]
then
    echo "Usage: $0 {MySQL-User-Name} {MySQL-User-Password} 
    {MySQL-Database-Name} {PORT}"
    echo "Drops all tables from a MySQL"
    exit 1
fi
 
TABLES=$($MYSQL -u $MUSER -p$MPASS $MDB -e 'show tables' | $AWK '{ print $1}' | $GREP -v '^Tables' )
 
for t in $TABLES
do
    echo "Deleting $t table from $MDB database..."
    $MYSQL -u$MUSER -p$MPASS -P$MPORT -h$MHOST $MDB -e "drop table $t"
done
