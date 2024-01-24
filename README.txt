download deb packages and all of its dependencies.

A program using apt to download debs.
Usage: apt-deb-downloader [options] ...
Options:
-a arch <architectrue>           deb target architecture,
                                 such like "arm64".
-d deb_name <deb name>           one name to be apt install,
                                 such like "libglib2.0-dev".
-i input_file <input file path>  file_path to deb_name list file.
                                 Each line of the file
                                 is a deb_name. example: data/test_input_file.txt
-h                               print help info.

All debs will be saved at ./download/
