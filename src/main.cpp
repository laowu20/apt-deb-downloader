#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include<string>
#include<fstream>
#include<map>
#include<iostream>
void print_help_info()
{
    printf("\nA program using apt to download debs.\n"
            "Options:\n"
            "-a arch            deb target architecture,"
                " such like \"arm64\".\n"
            "-d deb_name        one name to be apt install, "
                "such like \"libglib2.0-dev\".\n"
            "-i input_file      file_path to deb_name"
                " list file. Each line of the file "
                "is a deb_name.\n"
            "-h                 print help info.\n"
            );
}

std::string make_deb_name_list(std::string deb_name\
        , std::string input_file, std::string arch)
{
    std::string deb_name_list;
    std::string arch_tail;
    if(arch.length())
    {
        arch_tail = ":" + arch;
    }
    if(deb_name.length())
    {
        deb_name_list += deb_name + arch_tail + " ";
    }
    if(input_file.length())
    {
        std::ifstream deb_file(input_file);
        if(!deb_file.is_open())
        {
            fprintf(stderr, "open input_file failed.\n");
            return "";
        }
        std::string read_buffer;
        while(!deb_file.eof())
        {
            std::getline(deb_file,read_buffer);
            if(read_buffer.length() == 0)
            {
                continue;
            }
            deb_name_list += read_buffer + arch_tail + " ";
        }
    }
    return deb_name_list;
}
int main(int argc, char** argv)
{
    std::string input_file; /* name list file path */
    std::string deb_name;   /* input name */
    std::string arch;       /* arch, such like arm64 */
    int index;           
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "a:d:i:h")) != -1)
        switch (c)
        {
        case 'a':
            arch.assign(optarg);
        break;
        case 'd':
            deb_name.assign(optarg);
        break;
        case 'i':
            input_file.assign(optarg);
        break;
        case 'h':
            print_help_info();
            return 0;
        case '?':
            if (optopt == 'i' ||optopt == 'd'||optopt == 'a')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
            print_help_info();
            return 1;
        default:
            fprintf (stderr, "Unknown input opt :%c\n", optopt);
            print_help_info();
            return 1;
        }
    for (index = optind; index < argc; index++)
    {
        printf ("Non-option argument %s\n", argv[index]);
        if(index == argc - 1)
        {
            print_help_info();
            return 0;
        }
    }

    if(arch.length())
    {
        std::cout << "arch: " << arch << std::endl;
    }
    else
    {
        std::cout << "arch: " << "your local architecture." << std::endl;
    }
    std::cout << "deb_name: " << deb_name << std::endl;
    std::cout << "input_file: " << input_file << std::endl;
    if(!deb_name.length() && !input_file.length())
    {
        std::cout << "nothing need to be download." << std::endl;
        print_help_info();
        return 0;
    }
    std::string deb_list = make_deb_name_list(deb_name, input_file, arch);
    std::cout << "generate deb_list: " << deb_list << std::endl;
    if(!deb_list.length())
    {
        fprintf(stderr, "no deb can be download.\n");
        return 0;
    }
    printf("download start!\n");
    /* get raw deb list */
    std::string download_sh("apt depends --recurse" 
        " --no-recommends --no-suggests --no-conflicts "
        " --no-breaks --no-replaces --no-enhances ");
    download_sh += deb_list;
    download_sh += " | grep \"^\\w\" | sort -u ";
    download_sh += " > download_list_0.txt";
    system(download_sh.c_str());
    std::ifstream download_list_file_raw("./download_list_0.txt");
    if(!download_list_file_raw.is_open())
    {
        printf("download_list_file_raw open failed.\n");
        return 0;
    }
    /** 
     * transfor all needed deb to target arch,
     * store all to a map
     */
    std::map<std::string,int> download_map;
    std::string read_buffer;
    if(arch.length())
    {
        arch = ":" + arch;
    }
    while(!download_list_file_raw.eof())
    {
        std::getline(download_list_file_raw,read_buffer);
        if(read_buffer.length() == 0)
        {
            break;
        }
        /* all line should end with arch */
        if(read_buffer.length() < arch.length())
        {
            download_map[read_buffer + arch] = 1;
        }
        else
        {
            /* is it end with arch? */
            int start_p = read_buffer.length() - arch.length();
            std::string end_str;
            end_str = read_buffer.substr(start_p, arch.length());
            if(end_str.compare(arch) == 0)
            {
                /* yes, it is.*/
                download_map[read_buffer] = 1;
            }
            else
            {
                /* no, it isn't, add arch to it. */
                download_map[read_buffer + arch] = 1;
            }
        }
    }
    download_list_file_raw.close();
    /* write the download_map to a sh file */
    std::ofstream download_sh2\
        ("./download_1.sh");
    if(!download_sh2.is_open())
    {
        printf("open download_sh2 error. break.\n");
        return 0;
    }
    std::map<std::string,int>::iterator it;
    it = download_map.begin();
    for(it; it!=download_map.end(); it++)
    {
        download_sh2 << "apt download  "<< it->first << std::endl;
    }
    download_sh2.close();
    /* generate download.sh */
    system("chmod 755 ./download_1.sh");
    system(
        "echo 'apt download $(cat ../download_list_0.txt)'>download.sh\n"
        "echo ../download_1.sh>>download.sh\n"
        "chmod 755 download.sh\n");
    /* run download.sh */
    system("mkdir download\n cd download\n"
        "../download.sh"); 
    return 0;
}
