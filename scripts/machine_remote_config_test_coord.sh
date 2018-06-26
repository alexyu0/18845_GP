#!/bin/bash

if [ $# -lt 1 ]; then
    echo 1>&2 "$0: not enough arguments, need Andrew machine"
    exit 2
fi

machine="$1"
if [ "$machine" == "ece" ]; then
    machine_no=`awk -v min=0 -v max=31 \
        'BEGIN{srand(); print int(min+rand()*(max-min+1))}'`
    padded_no=`printf %03d $machine_no`
    address="ayu1@ece$padded_no.ece.local.cmu.edu"
elif [ "$machine" == "unix" ]; then
    address="ayu1@unix.andrew.cmu.edu"
elif [ "$machine" == "chimps" ]; then
    address="alex@128.2.177.203"
    ssh_port="-p 22222"
    scp_port="-P 22222"
else
    echo "not valid machine, specify ece or unix"
    exit 2
fi

ACCESS_export="export AWS_ACCESS_KEY_ID=$personal_AWS_ACCESS_KEY_ID"
ACCESS_echo="echo $ACCESS_export >> ~/.bashrc"
SECRET_export="export AWS_SECRET_ACCESS_KEY=$personal_AWS_SECRET_ACCESS_KEY"
SECRET_echo="echo $SECRET_export >> ~/.bashrc"

scp $scp_port ~/.ssh/config $address:~/.ssh
scp $scp_port ~/.ssh/git_rsa $address:~/.ssh
ssh -t $address $ssh_port \
    'git config --global user.email alexyu0925@gmail.com && ' \
    'git config --global user.name "Alex Yu" && ' \
    'git clone git@github.com:alexyu0/18845_GP.git'
