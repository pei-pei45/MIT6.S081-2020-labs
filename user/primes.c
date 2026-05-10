#include "kernel/types.h"
#include "user/user.h"

void sieve(int input_fd){
    int p;
    if(read(input_fd,&p,sizeof(int))<=0){
        close(input_fd);
        exit(0);
    }

    printf("prime %d\n",p);

    int fd_pipe[2];
    pipe(fd_pipe);

    if(fork()==0){
        close(fd_pipe[1]);
        sieve(fd_pipe[0]);
        close(fd_pipe[0]);
        exit(0);
    }else{
        close(fd_pipe[0]);
        int num;
        while(read(input_fd,&num,sizeof(int))>0){
            if(num%p!=0){
                write(fd_pipe[1],&num,sizeof(int));
            }
        }
        close(fd_pipe[1]);
        wait(0);
        close(input_fd);
        exit(0);
    }
}

int main(){
    int initial_pipe[2];
    pipe(initial_pipe);

    if(fork()==0){
        close(initial_pipe[1]);
        sieve(initial_pipe[0]);
        close(initial_pipe[0]);
        exit(0);

    }else{
        close(initial_pipe[0]);
        for(int i=2;i<35;i++){
            write(initial_pipe[1],&i,sizeof(int));
        }
            close(initial_pipe[1]);
            wait(0);
            exit(0);
    }

}