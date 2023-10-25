#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long n = 10000000; // Número de termos na série
int thread_count = 4; // Número de threads
double sum = 0.0; // Variável compartilhada para armazenar a soma

void* thread_sum(void* rank) {
   long my_rank = (long) rank;
   double factor;
   long long i;
   long long my_n = n / thread_count;
   long long my_first_i = my_n * my_rank;
   long long my_last_i = my_first_i + my_n;

   if (my_first_i % 2 == 0) /* my_first_i is even*/
      factor = 1.0;
   else
      factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
      sum += factor / (2 * i + 1);
   }

   return NULL;
}

int main() {
   pthread_t* thread_handles;
   long thread;
   double pi_estimate;

   thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_create(&thread_handles[thread], NULL, thread_sum, (void*) thread);
   }

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }

   pi_estimate = 4 * sum;
   printf("Quantidade de threads: %d\n", thread_count);
   printf("Valor de pi calculado: %lf\n", pi_estimate);

   free(thread_handles);
   return 0;
}
