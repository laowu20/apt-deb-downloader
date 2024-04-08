if ! type dpkg-scanpackages >/dev/null 2>&1
then
    echo "dpkg-dev not installed, please run \"apt install dpkg-dev\"." 
    exit 0
fi
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
rm -rf ./offline-packages
echo "output apt source: ./offline-apt-packages.tar.gz"
