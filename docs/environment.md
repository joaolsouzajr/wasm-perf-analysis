# Enviroment Development 

This document list all tools and dependencies used and necessary for edit and to build the codes this project, tccwasm.

## Tools 

### Editors/IDE

* [Visual Studio Code](https://code.visualstudio.com/)

### Plugins

* [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)


## Operational System

For all builds are settled in a linux virtual machine hosted on VirtualBox and managed from Vagrant. 

* [Linux - Debian Sretch 9](https://www.debian.org/News/2017/20170617.pt.html)
* [VirtualBox 6.0.4](https://www.virtualbox.org/wiki/Downloads)
* [VirtualBox 6.0.4 Oracle VM VirtualBox Extension Pack](https://www.virtualbox.org/wiki/Downloads)
* [Vagrant](https://github.com/hashicorp/vagrant)


Development base enviroment

This porject use the Debian 9.7.0 as base enviroment.

Command to install basic tools for linux:

```shell
    apt-get update
    apt-get install git -y
    apt-get install util-linux -y
    apt-get install htop -y
    apt-get install zsh -y
    apt-get install zip -y
    apt-get install curl -y
    apt-get install dkms -y
    apt-get install sudo -y
    apt-get install net-tools -y
    apt-get instlal openssh-server -y
    apt-get install apt-transport-https -y
    # to c++
    apt-get install build-essential -y
    apt-get install linux-headers-$(uname -r) -y
    apt-get install cmake -y
    # to opencv
    apt-get install libgtk2.0-dev -y 
    apt-get install pkg-config -y
    apt-get install ibavcodec-dev -y
    apt-get install libavformat-dev -y
    apt-get install libswscale-dev -y
```

On Windows 10, is necessary to install VirtualBox and Vagrant, then proceed the previus linux command.
This project provide the Vagrantfile.


Visusal Studio Code

For build opencv

libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev


cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF ..

