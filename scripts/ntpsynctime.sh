#!/bin/sh

#sudo apt-get install ntp -y
#sudo touch /etc/ntp.drift
sudo ntpd -q -g
#vim /etc/ntp.drift
sudo service ntp stop
sudo service ntp start
