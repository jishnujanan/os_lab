#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
void main()
{
    printf("\n A:Parent process (pid : %d)\n",getpid() );

    if(fork()==0)
    {
        printf("\n B:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );

        if(fork()==0)
        {

            if(fork()==0)
            {
                if(fork()==0)
                {
                    printf("\n I:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );

                }
                else
                {
                    wait(NULL);
                    printf("\n H:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );
                }
            }
            else
            {
                printf("\n D:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );
                wait(NULL);
            }
        }
        else if(fork()==0)
        {

            printf("\n E:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );
        }
        else
        {
            if(fork()==0)
            {
                printf("\n F:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );

            }
            else
                wait(NULL);
        }

    }
    else if(fork()==0)
    {


        printf("\n C:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );

        if (fork() == 0)
        {
            printf("\n G:Child process (pid : %d) and (ppid:%d)\n",getpid(),getppid() );
        }
        else
            wait(NULL);
    }
    else
    {
        sleep(1);
    }

}

