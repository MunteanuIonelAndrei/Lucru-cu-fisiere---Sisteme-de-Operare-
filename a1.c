#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>

bool compara(char x[], char y[])
{
    int a = strlen(y);
    int nr=0;
    for(int i=0; i<a; i++)
    {
        if(y[i]==x[i])
            nr++;
    }
    if(nr==a)
        return true;
    return false;

}

bool compareCharToPermission(char *perm,int x)
{
    char *start=perm;
    int user=0;
    int group=0;
    int others=0;

    for(int i=0; i<=6; i=i+3)
    {

        if(strstr(start+i,"---")==start+i)
        {
            if(i==0)
            {
                user=0;
            }
            else if(i==3)
            {
                group=0;
            }
            else if(i==6)
            {
                others=0;
            }
        }

        if(strstr(start+i,"--x")==start+i)
        {
            if(i==0)
            {
                user=1;
            }
            else if(i==3)
            {
                group=1;
            }
            else if(i==6)
            {
                others=1;
            }
        }

        if(strstr(start+i,"-w-")==start+i)
        {
            if(i==0)
            {
                user=2;
            }
            else if(i==3)
            {
                group=2;
            }
            else if(i==6)
            {
                others=2;
            }
        }

        if(strstr(start+i,"-wx")==start+i)
        {
            if(i==0)
            {
                user=3;
            }
            else if(i==3)
            {
                group=3;
            }
            else if(i==6)
            {
                others=3;
            }
        }

        if(strstr(start+i,"r--")==start+i)
        {
            if(i==0)
            {
                user=4;
            }
            else if(i==3)
            {
                group=4;
            }
            else if(i==6)
            {
                others=4;
            }
        }

        if(strstr(start+i,"r-x")==start+i)
        {
            if(i==0)
            {
                user=5;
            }
            else if(i==3)
            {
                group=5;
            }
            else if(i==6)
            {
                others=5;
            }
        }

        if(strstr(start+i,"rw-")==start+i)
        {
            if(i==0)
            {
                user=6;
            }
            else if(i==3)
            {
                group=6;
            }
            else if(i==6)
            {
                others=6;
            }
        }

        if(strstr(start+i,"rwx")==start+i)
        {
            if(i==0)
            {
                user=7;
            }
            else if(i==3)
            {
                group=7;
            }
            else if(i==6)
            {
                others=7;
            }
        }
    }

    int ugo = user * 64 + group * 8 + others;
    if (ugo == x)
        return true;
    else return false;

}


void listDirPerm(const char *path,char *name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    char *name1=name;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        printf("SUCCESS\n");
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0
                && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0 && compareCharToPermission(name1,statbuf.st_mode & 0777))
            {
                printf("%s\n", fullPath);

            }
        }
    }

    closedir(dir);
}
int succi=0;
void listDirRecPerm(const char *path,char *name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    char *name1=name;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        if (succi==0)
        {
            printf("SUCCESS\n");
            succi++;
        }
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0
                && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0 && compareCharToPermission(name1,statbuf.st_mode & 0777))
            {
                printf("%s\n", fullPath);
                listDirRecPerm(fullPath,name1);

            }
        }
    }

    closedir(dir);
}

void listDirName(const char *path,char *name)
{

    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    char *name1=name;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        printf("SUCCESS\n");
    }

    while((entry = readdir(dir)) != NULL)
    {
        if(compara(entry->d_name, name1))
        {
            if(strcmp(entry->d_name, ".") != 0
                    && strcmp(entry->d_name, "..") != 0)
            {
                snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
                if(lstat(fullPath, &statbuf) == 0)
                {
                    printf("%s\n", fullPath);


                }
            }
        }
    }


    closedir(dir);
}



int succ=0;
void listRecName(const char *path,char *name)

{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    char *name1=name;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        if (succ==0)
        {
            printf("SUCCESS\n");
            succ++;
        }
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(compara(entry->d_name, name1))
        {
            if(strcmp(entry->d_name, ".") != 0
                    && strcmp(entry->d_name, "..") != 0)
            {
                snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
                if(lstat(fullPath, &statbuf) == 0)
                {
                    printf("%s\n", fullPath);
                    if(S_ISDIR(statbuf.st_mode))
                    {
                        listRecName(fullPath,name1);
                    }
                }
            }
        }
    }

    closedir(dir);
}

void listDir(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        printf("SUCCESS\n");
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0
                && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0)
            {
                printf("%s\n", fullPath);

            }
        }
    }

    closedir(dir);
}

int suc=0;
void listRec(const char *path)

{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("Invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        if (suc==0)
        {
            printf("SUCCESS\n");
            suc++;
        }
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0
                && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0)
            {
                printf("%s\n", fullPath);
                if(S_ISDIR(statbuf.st_mode))
                {
                    listRec(fullPath);
                }
            }
        }
    }

    closedir(dir);
}

int numberOfsections(int fd)
{
    unsigned char c;

    lseek(fd, 8, SEEK_SET);
    read(fd,&c,1);
    int x=(int)(c);
    return x;
}

bool magic(int fd)
{
    char c[5];
    char v[5]= {"Kc3T"};

    lseek(fd, 0, SEEK_SET);
    read(fd,&c,4);
    c[4]=0;
    if(strcmp(c,v)==0)
        return true;
    return false;

}


bool version(int fd)
{
    int c=0;
    lseek(fd, 6, SEEK_SET);
    read(fd,&c,2);
    if (55<=c&&c<=75)
        return true;
    return false;

}
int versionI(int fd)
{
    int c=0;

    lseek(fd, 6, SEEK_SET);
    read(fd,&c,2);
    return c;

}

bool sectType(int fd,int i)
{
    int c=0;
    lseek(fd, i, SEEK_SET);
    read(fd,&c,2);
    if((c==30||c==71)||(c==42))
    {
        return true;
    }
    else

    {
        return false;
    }

}

int sectTypeI(int fd,int i)
{
    int c=0;
    lseek(fd, i, SEEK_SET);
    read(fd,&c,2);
    return c;

}


int sectSizeI(int fd,int i)
{
    int c;
    lseek(fd, i, SEEK_SET);
    read(fd,&c,4);
    return c;

}
void sectName(int fd, int i, char* c)
{


    lseek(fd, i, SEEK_SET);
    read(fd, c, 8);
    c[8] = 0;

}
void parse(const char* x)
{
    int fd1=-1;
    fd1=open(x,O_RDONLY);
    if(fd1 == -1)
    {
        perror("Could not open input file");
        return;
    }
    int nos=numberOfsections(fd1);
    bool nos1= (5<=nos&&nos<=14);
    bool type=true;
    int start = 17;
    for (int i=1; i<=nos; i++)
    {

        if(!sectType(fd1,start))
        {
            type =false;
            break;
        }
        start+=18;


    }

    if(magic(fd1)&&nos1&&version(fd1)&&type)
    {
        int name=9;
        int type=17;
        int size=23;

        printf("SUCCESS\n");
        printf("version=%d\n",versionI(fd1));
        printf("nr_sections=%d\n",numberOfsections(fd1));
        for(int i=1; i<=nos; i++)
        {
            char c[9];
            sectName(fd1, name, c);
            printf("section%d: %s %d %d\n",i, c, sectTypeI(fd1,type), sectSizeI(fd1,size));
            name+=18;
            type+=18;
            size+=18;

        }


    }
    else if((magic(fd1)&&nos1&&version(fd1)&&type) == false)
    {
        if (magic(fd1)==false)
        {
            printf("ERROR\n");
            printf("wrong magic");
            close(fd1);
        }
        else if(version(fd1)==false)
        {
            printf("ERROR\n");
            printf("wrong version");
            close(fd1);
        }
        else if (nos1==false)
        {
            printf("ERROR\n");
            printf("wrong sect_nr");
            close(fd1);
        }
        else if(type==false)
        {
            printf("ERROR\n");
            printf("wrong sect_types");
            close(fd1);

        }

    }


    close(fd1);
}

const int sectSize2(int fd, int section)
{
    int c=0;
    int i=23+((section-1)*18);

    lseek(fd, i, SEEK_SET);
    read(fd,&c,4);

    return c;
}
const int startsect(int fd,int section)
{
    int c=0;
    int i=19+((section-1)*18);
    lseek(fd, i, SEEK_SET);
    read(fd,&c,4);
    return c;

}

int nool1(int fd,int sect)
{
    int w=sectSize2(fd,sect);
    char a[sectSize2(fd,sect)];
    lseek(fd,startsect(fd,sect),SEEK_SET);
    read(fd,a,w);

    char *p=strtok(a,"\r\n");
    int i=1;
    while (p!=NULL)
    {
        p=strtok(NULL,"\r\n");
        i++;
    }

    return i-1;

}

void lineInv(int fd,int sect,int line)
{
    int w=sectSize2(fd,sect);
    char *a=(char*)malloc((w+1)*sizeof(char));
    lseek(fd,startsect(fd,sect),SEEK_SET);

    read(fd,a,w);
    a[w]=0;
    char *p=strtok(a,"\r\n");

    while (p!=NULL&&line!=1)
    {
        p=strtok(NULL,"\r\n");
        line--;
    }
    char *done=(char*)calloc(sizeof(char),(strlen(p))+1);
    int j=0;

    for(int q=strlen(p)-1; q>=0; q--)
    {
        done[j]=p[q];
        j++;
    }

    printf("SUCCESS\n");
    printf("%s",done);

    free(a);
    free(done);

}


void extract(const char* x, int section, int line)
{
    int fd1=-1;
    fd1=open(x,O_RDONLY);
    if(fd1 == -1)
    {
        perror("Could not open input file");
        return;
    }
    int nos=numberOfsections(fd1);
    bool nos1= (5<=nos&&nos<=14);
    bool type=true;
    int start = 17;
    for (int i=1; i<=nos; i++)
    {

        if(!sectType(fd1,start))
        {
            type =false;
            break;
        }
        start+=18;
    }

    if(!(magic(fd1)&&nos1&&version(fd1)&&type))
    {
        printf("ERROR\n");
        printf("invalid file");
        close(fd1);
        return;
    }



    if(!(section>0&&section<=nos))
    {
        printf("ERROR\n");
        printf("invalid section");
        close(fd1);
        return;
    }



    if(!((line>0)&&(line<=nool1(fd1,section))))
    {
        printf("ERROR\n");
        printf("invalid line");
        close(fd1);
        return;

    }

    lineInv(fd1,section,line);

    close(fd1);
}


bool verifica(const char* x)
{
    int fd1=-1;
    fd1=open(x,O_RDONLY);
    if(fd1 == -1)
    {
        perror("Could not open input file");
        return false;
    }
    int nos=numberOfsections(fd1);
    bool nos1= (5<=nos&&nos<=14);
    bool type=true;
    int start = 17;
    for (int i=1; i<=nos; i++)
    {

        if(!sectType(fd1,start))
        {
            type =false;
            break;
        }
        start+=18;
    }

    bool ok=false;

    if(magic(fd1)&&nos1&&version(fd1)&&type)
    {
        for(int sec=1; sec<=nos; sec++)
        {
            int pui=nool1(fd1,sec);
            if(pui>14)
                ok=true;

        }

    }
    return ok;

}

int lol=0;
void findall(const char *path)

{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL)
    {
        printf("ERROR");
        printf("invalid directory path");
        return;
    }
    else if(dir!=NULL)
    {
        if (lol==0)
        {
            printf("SUCCESS\n");
            lol++;
        }
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0
                && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0)
            {
                if(S_ISDIR(statbuf.st_mode))
                {
                    findall(fullPath);
                }
                if(verifica(fullPath))
                {
                    printf("%s\n", fullPath);
                }

            }
        }
    }

    closedir(dir);
}


int main(int argc, char **argv)
{
    if(argc >= 2)
    {
        if(strcmp(argv[1], "variant") == 0)
        {
            printf("34145\n");
        }
        else if(strcmp(argv[1], "list")==0)
        {
            int j;
            int recurs=0;
            int name=0;
            int perm=0;


            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"path=")==argv[i])
                {
                    j=i;
                }
            }

            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"name_starts_with=")==argv[i])
                {
                    name=i;
                }

            }


            for(int i=1; i<argc; i++)
            {
                if(strcmp(argv[i], "recursive")==0)
                {
                    recurs++;
                }
            }

            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"permissions=")==argv[i])
                {
                    perm=i;
                }
            }

            if(recurs==0)
            {
                if(name==0 && perm==0)
                {
                    listDir(argv[j]+5);
                }
                else if(name!=0 && perm ==0)
                {
                    listDirName(argv[j]+5,argv[name]+17);

                }

                if(perm!=0 && name==0)
                {
                    listDirPerm(argv[j]+5,argv[perm]+12);

                }
            }
            else if(recurs!=0)
            {
                if(name==0 && perm==0)
                {
                    listRec(argv[j]+5);
                }
                else if(name!=0 && perm!=0)
                {
                    listRecName(argv[j]+5,argv[name]+17);

                }

                if(perm!=0 && name==0 )
                {
                    listDirRecPerm(argv[j]+5,argv[perm]+12);

                }


            }

        }
        else if (strcmp(argv[1], "parse")==0)
        {
            int j;
            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"path=")==argv[i])
                {
                    j=i;
                }

            }
            parse(argv[j]+5);



        }
        else if(strcmp(argv[1], "extract")==0)
        {
            int j;
            int section;
            int line;
            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"path=")==argv[i])
                {
                    j=i;
                }
            }

            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"section=")==argv[i])
                {
                    section=i;
                }

            }
            for(int i=1; i<argc; i++)
            {
                if(strstr(argv[i],"line=")==argv[i])
                {
                    line=i;
                }

            }

            int nr1=0;
            for(int i=8; argv[section][i]; i++)
            {
                nr1=nr1*10+argv[section][i]-'0';
            }

            int nr2=0;
            for(int i=5; argv[line][i]; i++)
            {
                nr2=nr2*10+argv[line][i]-'0';
            }

            extract(argv[j]+5,nr1,nr2);

        }
        else if(strcmp(argv[1], "findall")==0)
        {

            findall(argv[2]+5);


        }

    }

    return 0;
}

