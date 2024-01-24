echo "***start making offline apt source.***"
mkdir offline-packages
cd offline-packages
mkdir archives
cd ..
cp ../bin/download/* ./offline-packages/archives/
cd ./offline-packages
touch Packages.gz
chmod 666 Packages.gz
dpkg-scanpackages -m . /dev/null | gzip -9c > Packages.gz
cp Packages.gz ./archives
cd ..
tar -zcvf offline-apt-packages.tar.gz offline-packages
echo "output apt source: ./offline-apt-packages.tar.gz"
