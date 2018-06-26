# install and setup docker
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
apt-cache policy docker-ce
sudo apt-get install -y docker-ce
sudo usermod -aG docker ${USER}
su - ${USER}


# install and setup virtualbox
sudo add-apt-repository "deb http://download.virtualbox.org/virtualbox/debian $(lsb_release -cs) contrib"
wget -q https://www.virtualbox.org/download/oracle_vbox_2016.asc -O- | sudo apt-key add -
wget -q https://www.virtualbox.org/download/oracle_vbox.asc -O- | sudo apt-key add -
sudo apt install virtualbox-5.1
sudo apt-get --reinstall install virtualbox-dkms
wget https://download.virtualbox.org/virtualbox/5.1.34/Oracle_VM_VirtualBox_Extension_Pack-5.1.34.vbox-extpack
sudo vboxmanage extpack install Oracle_VM_VirtualBox_Extension_Pack-5.1.34.vbox-extpack 


# install and setup vagrant and packages
wget https://releases.hashicorp.com/vagrant/2.0.3/vagrant_2.0.3_x86_64.deb
sudo dpkg -i vagrant_2.0.3_x86_64.deb
sudo apt-get build-dep vagrant ruby-libvirt
sudo apt-get install qemu libvirt-bin ebtables dnsmasq
sudo apt-get install libxslt-dev libxml2-dev libvirt-dev zlib1g-dev ruby-dev
vagrant plugin install vagrant-cachier
vagrant plugin install vagrant-libvirt
vagrant box add ubuntu/xenial64


# install and setup git LFS
wget https://github.com/git-lfs/git-lfs/releases/download/v2.4.0/git-lfs-linux-amd64-2.4.0.tar.gz
tar xvf git-lfs-linux-amd64-2.4.0.tar.gz
sudo ./git-lfs-2.4.0/install.sh
git lfs install

