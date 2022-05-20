#include <aio.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <fcntl.h>

struct aiocb createIoRequest(int fd,
                             off_t offset,
                             volatile void * content,
                             size_t length){

    struct aiocb ret = {0};
    {
        ret.aio_fildes = fd;
        ret.aio_offset = offset;
        ret.aio_buf = content;
        ret.aio_nbytes = length;
    }
    return ret;
}

void write_vector(std::vector<std::string>& names, int fd)
{
    for(int i = 0; i< names.size(); i++)
    {
        struct aiocb op = createIoRequest(fd, 0, (volatile void *)names[i].c_str(), names[i].size());
        int ret = aio_write(&op);
        printf("aio_write 1: %d\n", ret);
        {
            const struct aiocb *aiolist[1];
            aiolist[0] = &op;

            int ret = aio_suspend(aiolist, 1, NULL);
            printf("aio_suspend: %d\n", ret);

            // report possible errors
            {
                ret = aio_error(&op);
                printf("errno 1: %d\n", ret);
            }
        }
    }
}


int main(){

    FILE * file = fopen("/home/dungeonmaster/file.txt","a+");
    int fd = fileno(file);
    std::string f = "aboba1";
    std::vector<std::string> names;
    names.emplace_back("aboba1");
    names.emplace_back("aboba2");
    names.emplace_back("aboba3");
    names.emplace_back("aboba4");
    write_vector(names, fd);
    fclose(file);
    return 0;
}