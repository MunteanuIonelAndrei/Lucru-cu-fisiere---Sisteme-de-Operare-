#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include "errno.h"
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

sem_t semaphore;
sem_t semaphore2;
sem_t semaphore3;
sem_t semaphore4;


int start1=0;
int start23=0;
int stop2=0;
int start91=0;
int done=0;
int done2=0;
int done3=0;
int done4=0;
int done5=0;
int count=0;
int nrthreaduri=0;
pthread_mutex_t mutex;
pthread_mutex_t mutex2;

pthread_mutex_t mutex3;
pthread_mutex_t mutex4;

pthread_cond_t condition;
pthread_cond_t condition2;

pthread_cond_t condition3;
pthread_cond_t condition4;
pthread_barrier_t barrier;


typedef struct
{
    int thread_no;
} TH_STRUCT;



void *thread_fn_max(void *param)
{
    TH_STRUCT *s = (TH_STRUCT*)param;

   /* if(s->thread_no==3)
    {

        printf(" ALOOOOOOOOOOOO am intrat in %d \n",s->thread_no);
        pthread_mutex_lock(&mutex3);
        while(start23!=1)
        {
            pthread_cond_wait(&condition3, &mutex3);
        }
        info(BEGIN, 2, s->thread_no);
        info(END, 2, s->thread_no);
        start91++;
        printf(" ALOOOOOO ASTA_I strart ul 91:%d\n",start91);


//semnaleaza ca poate incepe 9.1
        pthread_cond_signal(&condition4);

        pthread_mutex_unlock(&mutex3);

    }
    else*/
 sem_t *sem;
    if(s->thread_no==3){
       
        
        sem = sem_open("/semaphor", O_CREAT, 0644, 0);
        sem_wait(sem);
        sem_unlink("/semaphor");
        sem_close(sem);
        info(BEGIN, 2, s->thread_no);
        info(END, 2, s->thread_no);
        sem = sem_open("/semaphor2", O_CREAT, 0644, 0);
        sem_post(sem);
        sem_close(sem);

    }else

     if(s->thread_no==1)
        {
            pthread_mutex_lock(&mutex);
            while(start1!=1)
            {
                pthread_cond_wait(&condition2, &mutex);
            }
            info(BEGIN, 2, s->thread_no);
            stop2++;
            info(END, 2, s->thread_no);

//semnaleaza ca se poate opri 2
            pthread_cond_signal(&condition);

            pthread_mutex_unlock(&mutex);


        }
        else if(s->thread_no==2)
        {
            info(BEGIN, 2, s->thread_no);

//semnaleaza ca a inceput 2
            start1++;
            pthread_cond_signal(&condition2);


            pthread_mutex_lock(&mutex);
            while(stop2!=1)
            {
                pthread_cond_wait(&condition, &mutex);
            }
            info(END, 2, s->thread_no);
            pthread_mutex_unlock(&mutex);
        }else if(s->thread_no==3){

        }
        else
        {
            info(BEGIN, 2, s->thread_no);
            info(END, 2, s->thread_no);
        }

    return NULL;
}


void *thread_fn_2(void *param)
{
   /* TH_STRUCT *s = (TH_STRUCT*)param;
    if(s->thread_no==14)
    {

        info(BEGIN, 8, s->thread_no);
        done=1;

    }

    if (done==1 && done2<4)
    {


        if(s->thread_no==14)
        {
            done2 ++;

            //  pthread_barrier_wait(&barrier);
            info(END, 8, s->thread_no);
            // done2=1;
            return NULL;

        }
        else
        {
            // pthread_mutex_lock(&mutex2);
            done2 ++;
            //pthread_mutex_unlock(&mutex2);
            info(BEGIN, 8, s->thread_no);
            //pthread_barrier_wait(&barrier);
            info(END, 8, s->thread_no);
            return NULL;

        }

    }

    if(done2==4)
    {

        sem_wait(&semaphore);
        TH_STRUCT *s1 = (TH_STRUCT*)param;

        info(BEGIN, 8, s1->thread_no);


        info(END, 8, s1->thread_no);
        sem_post(&semaphore);

    }

    

    info(BEGIN, 8, s1->thread_no);

     pthread_mutex_lock(&mutex2);

    //sem_wait(&semaphore2);
    TH_STRUCT *s1 = (TH_STRUCT*)param;

    info(BEGIN, 8, s1->thread_no);

    done=1;
    info(END, 8, s1->thread_no);
    //sem_post(&semaphore2);

    pthread_mutex_unlock(&mutex2);
    pthread_cond_signal(&condition3);

    }

    if(done)



    else if(s->thread_no!=14){
        pthread_mutex_lock(&mutex2);
    while(done!=1){
        pthread_cond_wait(&condition3,&mutex2);
    }*/
   nrthreaduri++;
   printf("ALOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO nr thread rui terminate: %d\n\n", nrthreaduri );
TH_STRUCT *s = (TH_STRUCT*)param;
 pthread_mutex_lock(&mutex4);
 if(s->thread_no==14){
    printf("ALOOOOOOOOOOOOOOOOOOOOOOOO aici a intrat thread ul 14:     %d",s->thread_no);
 }

//***pana aici in functia asta codul de mai sus a fost pt debugging
 //*** urmatorul if imi incrementeaza done4,
 //*** o variabica care imi va lasa sa treaca in IF1 doar 3 thread-uri diferite de thread ul 14)
 //***

  sem_wait(&semaphore);
if(done4<=3&& s->thread_no!=14){
    done4++; // cazul in care thread14 e creeat printre primele 3
}pthread_mutex_unlock(&mutex4);

if(done3==0&&(done4<=3||s->thread_no==14)){  //*** IF1 *** se trece mai departe doar daca thread ul curent e printre primele 3 diferite de 14 sau daca e 14
                                             //*** done3 se incrementeaza la linia 275 si are rolul de a nu mai lasa thread urile sa intre in acest if dupa ce 
                                             //*** am terminat(s-a ridicat bariera si cele 4 thread uri au trecut/// tot acolo se incrementeaza si done3, dupa ce s-a trecut de beriera)
     pthread_mutex_lock(&mutex4);
    //sem_wait(&semaphore);
    if(s->thread_no==14){
        done5=1;
    }/*else if(s->thread_no!=14){
       


}*/
pthread_mutex_unlock(&mutex4);

// done4 = 1,2,3
// done5=1
//done=1, done =2, done =2 (3 thread uri)

    info(BEGIN, 8, s->thread_no); //***inainte de bariera

sem_wait(&semaphore2);
//pthread_mutex_lock(&mutex3);
count++; // 1,2,3,4
printf("ALOOOOOOOOOOOOOOOOOO aici e count :%d incrementat de thread ul: %d,  cUUUUUUUU done4=:%d \n",count,s->thread_no,done4);
//pthread_mutex_unlock(&mutex3);
if(count==4 && (s->thread_no==14 || done5==1)){ //***done5 e 1 daca thread ul 14 a fost printre primele 3 thread-uri intrate in acest if
    sem_post(&semaphore3);
}
sem_post(&semaphore2);
sem_wait(&semaphore3);
sem_post(&semaphore3);

pthread_mutex_lock(&mutex3);
if(done5==1){
  info(END, 8, s->thread_no);  
}
done3++;
sem_post(&semaphore);
pthread_mutex_unlock(&mutex3);

}else // pe else ul asta se intra daca am sus 3 thread uri care asteapta dupa thread ul 14 sa apaara sau daca sus s-a terminat if ul (done3 != 0) 
{

//wait = down 
//post = up


 //   sem_wait(&semaphore);
    TH_STRUCT *s1 = (TH_STRUCT*)param;
printf("\nELSE: %d\n", s1->thread_no);
    info(BEGIN, 8, s1->thread_no);



    info(END, 8, s1->thread_no);
    sem_post(&semaphore);
   // pthread_mutex_unlock(&mutex2);

    }
    return NULL;
}

void *thread_fn_3(void *param)
{
    TH_STRUCT *s = (TH_STRUCT*)param;

   /* if(s->thread_no==4 || s->thread_no==1)
    {

        if(s->thread_no==4)
        {
            printf(" ALOOOOOO ASTA_I threadul :%d\n",s->thread_no);
            info(BEGIN, 9, s->thread_no);

            info(END, 9, s->thread_no);
            pthread_mutex_lock(&mutex3);
            start23++;
            printf(" ALOOOOOO ASTA_I strart 23 ul :%d\n",start23);
            pthread_mutex_unlock(&mutex3);

            pthread_cond_signal(&condition3);
        }
//semnaleaza ca a inceput 2


        if(s->thread_no==1)
        {
            printf(" ALOOOOOO ASTA_I threadul :%d\n",s->thread_no);
            pthread_mutex_lock(&mutex3);
            while(start91!=1)
            {
                pthread_cond_wait(&condition4, &mutex3);
            }
            info(BEGIN, 9, s->thread_no);

            info(END, 9, s->thread_no);
            pthread_mutex_unlock(&mutex3);
        }

    }*/
    sem_t *sem;
    if(s->thread_no==4){
        info(BEGIN, 9, s->thread_no);
        info(END, 9, s->thread_no);
        sem = sem_open("/semaphor", O_CREAT, 0644, 0);
        sem_post(sem);
        sem_close(sem);

    }
    else if(s->thread_no==1){

           sem = sem_open("/semaphor2", O_CREAT, 0644, 0);
           sem_wait(sem);
            info(BEGIN, 9, s->thread_no);
            info(END, 9, s->thread_no);
           sem_unlink("/semaphor2");
           sem_close(sem);

        
    }else
    {


        info(BEGIN, 9, s->thread_no);
        info(END, 9, s->thread_no);
    }
    return NULL;
}



int main()
{
    init();
    info(BEGIN, 1, 0);
    pid_t pid2=-1, pid3=-1, pid4=-1, pid5=-1, pid6=-1, pid7=-1, pid8=-1, pid9=-1;
    printf("Procesul p1 are pid ul: %d\n",getpid());

    pthread_mutex_init(&mutex3, NULL);
    pthread_mutex_init(&mutex4, NULL);
    pthread_cond_init(&condition3, NULL);
    pthread_cond_init(&condition4, NULL);


    pid2 = fork();
    if(pid2 == 0)
    {

        info(BEGIN, 2, 0);

        int nr_threads =4;
        TH_STRUCT params[nr_threads];
        pthread_t tid[nr_threads];
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&condition, NULL);
        pthread_cond_init(&condition2, NULL);

        for(int i=0; i<nr_threads; i++)
        {

            params[i].thread_no=i+1;

            pthread_create(&tid[i],NULL,thread_fn_max,&params[i]);
        }

        for(int i=0; i<nr_threads; i++)
        {
            pthread_join(tid[i],NULL);
        }

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&condition);
        pthread_cond_destroy(&condition2);


        pid4 = fork();
        if (pid4 == 0)
        {
            info(BEGIN, 4, 0);

//sleep(60);

            info(END, 4, 0);
        }
        else if(pid4>0)
        {
            waitpid(pid4, NULL, 0);
            info(END, 2, 0);
        }


    }
    else if(pid2>0)
    {

        pid3 = fork();
        if(pid3==0)
        {


            info(BEGIN, 3, 0);


            pid7=fork();

            if (pid7 == 0)
            {

                info(BEGIN, 7, 0);

//sleep(60);


                info(END, 7, 0);
            }
            else if(pid7>0)
            {


                pid8= fork();

                if (pid8 == 0)
                {

                    info(BEGIN, 8, 0);



                    int nr_threads =37;
                    TH_STRUCT params[nr_threads];
                    pthread_t tid[nr_threads];
                    sem_init(&semaphore,0,4);
                    sem_init(&semaphore2,0,1);
                    sem_init(&semaphore3,0,0);
                    sem_init(&semaphore4,0,4);
                    pthread_barrier_init(&barrier,NULL,4);
                    pthread_mutex_init(&mutex2,NULL);
                    // pthread_cond_init(&condition3, NULL);
                    for(int i=0; i<nr_threads; i++)
                    {

                        params[i].thread_no=i+1;

                        pthread_create(&tid[i],NULL,thread_fn_2,&params[i]);
                    }

                    for(int i=0; i<nr_threads; i++)
                    {
                        pthread_join(tid[i],NULL);
                    }

                    sem_destroy(&semaphore);
                    sem_destroy(&semaphore2);
                    sem_destroy(&semaphore3);
                    sem_destroy(&semaphore4);
                    pthread_mutex_destroy(&mutex2);
                    // pthread_cond_destroy(&condition3);
                    pthread_barrier_destroy(&barrier);


                    info(END, 8, 0);
                }
                else if(pid8>0)
                {
                    pid9= fork();

                    if (pid9 == 0)
                    {

                        info(BEGIN, 9, 0);

                        int nr_threads =6;
                        TH_STRUCT params[nr_threads];
                        pthread_t tid[nr_threads];
                        

                        for(int i=0; i<nr_threads; i++)
                        {

                            params[i].thread_no=i+1;

                            pthread_create(&tid[i],NULL,thread_fn_3,&params[i]);
                        }

                        for(int i=0; i<nr_threads; i++)
                        {
                            pthread_join(tid[i],NULL);
                        }


                        info(END, 9, 0);
                    }
                    else if(pid9>0)
                    {
                        waitpid(pid7, NULL, 0);
                        waitpid(pid8, NULL, 0);
                        waitpid(pid9, NULL, 0);
                        info(END, 3, 0);

                    }
                }


            }

        }
        else if(pid3>0)
        {
            pid5 = fork();
            if (pid5 == 0)
            {

                info(BEGIN, 5, 0);

                pid6 = fork();
                if (pid6 == 0)
                {

                    info(BEGIN, 6, 0);

//sleep(60);


                    info(END, 6, 0);
                }
                if(pid6>0)
                {
                    waitpid(pid6, NULL, 0);
                    info(END, 5, 0);
                }


            }
            else if(pid5>0)
            {
                waitpid(pid2, NULL, 0);
                waitpid(pid3, NULL, 0);
                waitpid(pid5, NULL, 0);
                info(END, 1, 0);
            }

        }
    }


    pthread_mutex_destroy(&mutex3);
    pthread_mutex_destroy(&mutex4);
    pthread_cond_destroy(&condition3);
    pthread_cond_destroy(&condition4);

    return 0;
}