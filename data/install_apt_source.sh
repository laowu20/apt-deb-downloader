# Check if the user is root
if [ "$(id -u)" -ne 0 ]
then
	echo "You must be root."
	exit 1
fi
# Check if the sources.list exist
if [ -e "/etc/apt/sources.list" ]; then
    echo "/etc/apt/sources.list exist. please move it away and try again."
    exit
fi
tar -zxvf offline-apt-packages.tar.gz -C /opt
echo "deb [trusted=yes] file:///opt/offline-packages  archives/"| tee /etc/apt/sources.list
apt-get update
