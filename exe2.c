#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


#define LEN 128

pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t soma_value_lock;
int soma_global, values_per_thread, num_threads, num_values;



void *soma(void *list_ptr){
	
    int *partial_list_ptr, soma_local, i;
    partial_list_ptr = (int *)list_ptr;
    int id = pthread_self();
    printf("Sou o thread : %d\n", id);


    for(i=0; i<values_per_thread; i++){
        pthread_mutex_lock(&_mutex);
        soma_global += partial_list_ptr[i];
        pthread_mutex_unlock(&_mutex);
    }
    
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){

	pthread_mutex_init(&soma_value_lock, NULL);
	num_values = atoi(argv[1]);
	char err_msg[LEN];
	int arg[num_values];
    for (int i = 0; i < num_values; ++i)
    {
        /* code */
        printf("%d ", arg[i] = rand() % 100);

    }

	num_threads = atoi(argv[2]);
	pthread_t threads[num_threads];

	values_per_thread = num_values/num_threads;


	int d, p = 0;
	int v[values_per_thread];
	for (int i = 0; i < num_threads; ++i)
	{
		d = 0;
		

		while(d < values_per_thread){
			v[d] = arg[p];
			++d;
			++p;
		}

		printf("Criando thread %d\n", i);
		int status = pthread_create(&threads[i], NULL, soma, (void *) &v[0]); 
		if(status){
			strerror_r(status,err_msg,LEN);
			printf("Falha da criacao da thread %d (%d): %s\n",i,status,err_msg);
			exit(EXIT_FAILURE);
		}else{
			printf("Thread criada\n");
			printf("%d\n", v[0]);
		}

	}
printf("%d\n", soma_global);
}