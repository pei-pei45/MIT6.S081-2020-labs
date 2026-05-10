#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    
    // 创建两个管道描述符，前者用于父进程向子进程通信（读和写），后者用于子进程向父进程通信（读和写）
    // 每个管道描述符长度为 2，其中，0 用于读数据，1 用于写数据。
    int fd_p1[2], fd_p2[2]; //管道描述符
    pipe(fd_p1); //创建管道1
    pipe(fd_p2); //创建管道2

    if(fork()==0){
        int port_read = fd_p1[0]; //子进程从管道1读
        int port_write = fd_p2[1]; //子进程向管道2写

        char buf_read[1024]={0};
        char buf_write[1024]={"pong\n"};

        read(port_read,buf_read,1024);
        printf("child received %s\n",buf_read);
        printf("%d: received ping\n\n", getpid());

        write(port_write,buf_write,1024);
        exit(0);
    }else{
        int port_read = fd_p2[0];
        int port_write = fd_p1[1];

        char buf_read[1024]={0};
        char buf_write[1024]={"ping\n"};

        write(port_write,buf_write,1024);
        read(port_read,buf_read,1024);
        printf("%d: sent ping\n", getpid());
        printf("%d: received pong\n", getpid());

         exit(0);
    }
}