Use apt to download deb packages and all dependencies.
All debs will be saved at ./download/
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
