#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<map>
#include<iostream>
int main(int argc, char** argv)
{
    printf("hello. deb-downloader start!\n");
    /* get raw deb list */
    std::string download_sh("apt depends --recurse" 
        " --no-recommends --no-suggests --no-conflicts "
        " --no-breaks --no-replaces --no-enhances libglib2.0-dev:arm64 | "
        " grep \"^\\w\" | sort -u "
        " > download_list_0.txt");
    system(download_sh.c_str());
    std::ifstream download_list_file("./download_list_0.txt");
    if(!download_list_file.is_open())
    {
        printf("download_list_file open failed.\n");
        return 0;
    }
    /** 
     * transfor all needed deb to target arch,
     * store all to a map
     */
    std::map<std::string,int> download_map;
    std::string read_buffer;
    while(!download_list_file.eof())
    {
        std::getline(download_list_file,read_buffer);
        if(read_buffer.length() == 0)
        {
            break;
        }
        std::string arch(":arm64");
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
    /* write the download_map to a file */
    return 0;
}
