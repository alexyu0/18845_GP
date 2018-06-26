VAGRANTFILE_API_VERSION = "2"

benchmarks = {
    "general" => ["ubuntu/xenial64"],
    "kernel" => ["ubuntu/xenial64"],
    "pxz" => ["ubuntu/xenial64"],
    "linpack" => ["alexyu0/mkl_linpack"],
    "stream" => ["ubuntu/xenial64"],
    "filebench" => ["ubuntu/xenial64"],
    "ycsb" => ["alexyu0/ycsb_redis"],
    "mysql" => ["alexyu0/sysbench_mysql"],
    "docker-test" => ["envimation/ubuntu-xenial-docker"]
}

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
    benchmarks.each do |key, value|
        config.vm.define "#{key}" do |box| 
            box.vm.box = value[0]
            box.vm.hostname = "test-#{key}"
            box.ssh.forward_agent = true

            # configure VM resource settings
            box.vm.provider "virtualbox" do |vbox|
                vbox.name = "test-#{key}"
                vbox.memory = 4000
                vbox.cpus = 4
                vbox.customize ["modifyvm", :id, "--uartmode1", "disconnected"]
            end
            box.disksize.size = "10GB"
            
            # configure other VM settings, such as synced folders and networking
            box.vm.network :forwarded_port, 
                guest: 80, 
                host: 8000, 
                auto_correct: true
            
            if Vagrant.has_plugin?("vagrant-cachier")
                box.cache.scope = :box
                box.cache.enable :apt
                box.cache.synced_folder_opts = {
                    owner: "_apt",
                    group: "vagrant"
                }
            end

            box.vm.provision :shell, path: "scripts/general_setup", privileged: true
        end
    end
end
