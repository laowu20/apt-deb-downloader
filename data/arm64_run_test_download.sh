apt download $(apt depends --recurse --no-recommends --no-suggests --no-conflicts --no-breaks --no-replaces --no-enhances vim | grep "^\w" | sort -u | sed "s/$/:arm64/g")
