#!/bin/bash
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
sudo apt-get install qt5-default checkinstall

git clone https://github.com/opencv/opencv.git ~/opencv

cd ~/opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_TBB=ON \
-D BUILD_NEW_PYTHON_SUPPORT=ON \
-D WITH_V4L=ON \
-D INSTALL_C_EXAMPLES=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D BUILD_EXAMPLES=ON \
-D WITH_QT=ON ..
#-D WITH_OPENGL=ON ..

make -j 2

sudo checkinstall
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig


#Reference:
#http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html
# https://help.ubuntu.com/community/OpenCV
