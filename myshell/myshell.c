#include"myshell.h"
#define REDIR_NONE 0
#define REDIR_INPUT 1
#define REDIR_OUTPUT 2
#define REDIR_APPEND 3
static char USER[16];
static char CWD[256];
static char HOSTNAME[32];
static char inputLine[256];
static char* argv[64];
static unsigned int argc;
static int exitcode;
static char* env[128];
static size_t envnum;
static int status=REDIR_NONE;
static char filename[256];
static void doRedir();
static void getEnv()
{
    envnum=0;
    extern char** environ;
    while(environ[envnum]!=NULL&&envnum<127)
    {
        env[envnum]=environ[envnum];
        envnum++;
    }
    env[envnum]=NULL;
}
static void getUSER()
{
    char* user=getenv("USER");
    strcpy(USER,(user==NULL?"无内容":user));
}
static void getHOSTNAME()
{
    int i=gethostname(HOSTNAME,sizeof(HOSTNAME));
    if(i!=0)
    {
        strcpy(HOSTNAME,"无内容");
    }
    else
    {
        HOSTNAME[sizeof(HOSTNAME)-1]='\0';
    }
}
static void getCWD()
{
    char* cwd=getcwd(CWD,sizeof(CWD));
    if(cwd==NULL)
    {
        strcpy(CWD,"无内容");
    }
}
static void PrintSheang()
{
    getUSER();
    getCWD();
    getHOSTNAME();
    printf("%s@%s:%s$ ",USER,HOSTNAME,CWD);
    fflush(stdout);
}
static void getLine()
{
    fgets(inputLine,sizeof(inputLine),stdin);
    inputLine[strcspn(inputLine,"\n")]='\0';
}
static void cutLine(char* inputLine)
{
    argc=0;
    argv[argc++]=strtok(inputLine," ");
    while((argv[argc++]=strtok(NULL," ")));
    argc--;
}
static void excute()
{
    pid_t pid=fork();
    if(pid==0)
    {
        doRedir();
        execvp(argv[0],argv);
    }
    else if(pid>0)
    {
    }
    else
    {
        perror("子进程创建错误\n");
        return;
    }
    int status;
    int ret=waitpid(pid,&status,0);
    exitcode=WEXITSTATUS(status);
}
static int cheackCommand()
{
    int ret;
    if(strcmp(argv[0],"cd")==0)
    {
        if(argv[1]==NULL)
        {
            chdir(getenv("HOME"));
            return 1;
        }
        int result=chdir(argv[1]);
        if(result==-1)
        {
            perror("cd失败\n");
            return 1;
        }
        return 1;
    }
    else if(strcmp(argv[0],"echo")==0)
    {
        if(argv[1][0]=='$')
        {
            if(strcmp(argv[1],"$?")==0)
            {
                printf("%d\n",exitcode);
                exitcode=0;
            }
        }
        return 1;
    }
    else if(strcmp(argv[0],"env")==0)
    {
        getEnv();
        for(int i=0;i<envnum;i++)
        {
            printf("%s\n",env[i]);
        }
        return 1;
    }
    else if(strcmp(argv[0],"exit")==0)
    {
        exit(0);
    }
    return 0;
}
static void getFilename(char* start,char* end)
{
    int i=0;
    while(start<end)
    {
        if(*start!=' ')
        {
            filename[i++]=*start;
        }
        start++;
    }
    filename[i]='\0';
}
static void redir()
{
    status=REDIR_NONE;
    char* start=inputLine;
    char* end=inputLine+strlen(inputLine);
    while(start<end)
    {
        if(*start=='>')
        {
            if((start+1)<end&&*(start+1)=='>')
            {
                status=REDIR_APPEND;
                *start='\0';
                start+=2;
            }
            else
            {
                status=REDIR_OUTPUT;
                *start='\0';
                start++;
            }
            getFilename(start,end);
        }
        else if(*start=='<')
        {
            status=REDIR_INPUT;
            *start='\0';
            start++;
            getFilename(start,end);
        }
        else
        {
            start++;
        }
    }
}
static void doRedir()
{
    if(status==REDIR_OUTPUT)
    {
        int fd=open(filename,O_CREAT|O_WRONLY|O_TRUNC,0666);
        if(fd==-1)
        {
            perror("open");
            return;
        }
        int ret=dup2(fd,1);
        if(ret==-1)
        {
            perror("dup2");
            return;
        }
        close(fd);
    }
    else if(status==REDIR_APPEND)
    {
        int fd=open(filename,O_CREAT|O_APPEND|O_WRONLY,0666);
        if(fd==-1)
        {
            perror("open");
            return;
        }
        int ret=dup2(fd,1);
        if(ret==-1)
        {
            perror("dup2");
            return;
        }
        close(fd);
    }
    else if(status==REDIR_INPUT)
    {
        int fd=open(filename,O_RDONLY);
        if(fd==-1)
        {
            perror("open");
            return;
        }
        int ret=dup2(fd,0);
        if(ret==-1)
        {
            perror("dup2");
            return;
        }
        close(fd);
    }
    else
    {
    }
}
void Bash()
{
    while(1)
    {
        PrintSheang();
        getLine();
        redir();
        cutLine(inputLine);
        if(argc==0)
            continue;
        if(cheackCommand())
            continue;
        excute();
    }
}
