Use apt to download deb packages and all dependencies.
All debs will be saved at ./download/
build offline apt source.
install offline apt source.
## dependency
dpkg-dev is needed.

```shell
sudo apt install dpkg-dev
```

## Quick start:
To download debs for vim,lrzsz and make,just run:

```shell
cd ./bin
./apt-deb-downloader -d vim
./apt-deb-downloader -d lrzsz
./apt-deb-downloader -d make
```

or run

```shell
cd ./bin
./apt-deb-downloader -i ../data/test_input_file.txt
```
then all debs will be saved at "./bin/download/".

## build offline apt source
after download debs, run 
```shell
cd ./data
sh ./build_offline_packages.sh 
```
then it output offline-apt-packages.tar.gz

## install offline apt source
after build out offline-apt-packages.tar.gz, run 
```shell
cd ./data
sudo sh ./install_apt_source.sh
```
it will install offline-apt-packages.tar.gz as apt source.
