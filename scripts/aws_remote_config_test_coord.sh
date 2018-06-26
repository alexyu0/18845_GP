#!/bin/bash

if [ $# -lt 2 ];
then
    echo 1>&2 "$0: not enough arguments, need IP and user"
    exit 2
fi

IP="$1"
user="$2"

ACCESS_export="export AWS_ACCESS_KEY_ID=$personal_AWS_ACCESS_KEY_ID"
ACCESS_echo="echo $ACCESS_export >> ~/.bashrc"
SECRET_export="export AWS_SECRET_ACCESS_KEY=$personal_AWS_SECRET_ACCESS_KEY"
SECRET_echo="echo $SECRET_export >> ~/.bashrc"

scp -i ~/.ssh/845_rsa.pem ~/.ssh/config "$user"@"$IP":~/.ssh
scp -i ~/.ssh/845_rsa.pem ~/.ssh/git_rsa "$user"@"$IP":~/.ssh
scp -i ~/.ssh/845_rsa.pem ~/.basic_vimrc "$user"@"$IP":~/

ssh -t -i ~/.ssh/845_rsa.pem "$user"@"$IP" \
    'mv ~/.basic_vimrc ~/.vimrc && ' \
    'git config --global user.email "alexyu0925@gmail.com" && ' \
    'git config --global user.name "Alex Yu" && ' \
    'git clone git@github.com:alexyu0/18845_GP.git'
#     echo '""' >> ~/.bashrc  && \
#     eval $ACCESS_echo && \
#     eval $SECRET_echo"
