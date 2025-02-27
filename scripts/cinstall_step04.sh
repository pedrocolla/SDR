#!/bin/sh

cd /home/pi
git clone https://github.com/sivel/speedtest-cli.git
cd speedtest-cli
sudo python setup.py install
