/*
 * main.c
 *
 *  Created on: 1 may. 2017
 *      Author: Admin
 */
#include "Collection.h"
#include <stdio.h>

void printInt(void* p) {
    printf("%d\n",*((int*)p));
}

void printDouble(void* p){
	printf("%f\n", *((double*)p));
}

void duplicate(void* p){
	int* pi = (int*) p;
	*pi *= 2;
}

void addDouble(void* x, void* y, void* resultado){
	double* p1 = x;
	double* p2 = y;
	double* pRes = resultado;
	*pRes = *p1+*p2;
}

void productDouble(void* x, void* y, void* resultado){
	double* p1 = x;
	double* p2 = y;
	double* pRes = resultado;
	*pRes = (*p1)*(*p2);
}

int isOdd(void* dato){
	int* pi = dato;
	return *pi % 2;
}

int main(int argc, char **argv) {
  {
    puts("Test collection_init_int:");
    Collection c;
    int array[] = {1, 2, 3, 4, 5};
    collection_init(&c, array, sizeof(int), sizeof(array));
    collection_iterate(&c, &printInt);
    collection_free(&c);
  }
  {
    puts("Test collection_pop_int:");
    Collection c;
    int array[] = {1, 2, 3, 4, 5};
    collection_init(&c, array, sizeof(int), sizeof(array));
    collection_pop(&c);
    collection_iterate(&c, &printInt);
    collection_free(&c);
  }
  {
    puts("Test collection_remove_int:");
    Collection c;
    int array[] = {1, 2, 3, 4, 5};
    collection_init(&c, array, sizeof(int), sizeof(array));
    int x = 2;
    collection_remove(&c, &x);
    collection_iterate(&c, &printInt);
    collection_free(&c);
  }
  {
	puts("Test collection_find_int:");
	Collection c;
	int array[] = {1, 2, 3, 4, 5};
	collection_init(&c, array, sizeof(int), sizeof(array));
	int x = 2;
	int* pi = (int*)collection_find(&c, &x);

	if (*pi == x) {
		 puts("Found");
	}

	collection_free(&c);
  }
  {
	puts("Test collection_collect_int:");
	Collection c;
	Collection c2;
	int array[] = {1, 2, 3, 4, 5};
	collection_init(&c, array, sizeof(int), sizeof(array));
	collection_init_empty(&c2, sizeof(int));
	collection_collect(&c, &c2, &duplicate);
	collection_iterate(&c2, &printInt);
	collection_free(&c);
	collection_free(&c2);
  }
  {
	puts("Test collection_select_int:");
	Collection c;
	Collection c2;
	int array[] = {1, 2, 3, 4, 5};
	collection_init(&c, array, sizeof(int), sizeof(array));
	collection_init_empty(&c2, sizeof(int));
	collection_select(&c, &c2, &isOdd);
	collection_iterate(&c2, &printInt);
	collection_free(&c);
	collection_free(&c2);
  }
  {
    puts("Test collection_init_double:");
    Collection c;
    double array[] = {1.54, 2.87, 3.44, 4.11, 5.99};
    collection_init(&c, array, sizeof(double), sizeof(array));
    collection_iterate(&c, &printDouble);
    collection_free(&c);
  }
  {
	puts("Test collection_pop_double:");
	Collection c;
	double array[] = {1.54, 2.87, 3.44, 4.11, 5.99};
	collection_init(&c, array, sizeof(double), sizeof(array));
	collection_pop(&c);
	collection_iterate(&c, &printDouble);
	collection_free(&c);
  }
  {
	puts("Test collection_remove_double:");
	Collection c;
	double array[] = {1.54, 2.87, 3.44, 4.11, 5.99};
	collection_init(&c, array, sizeof(double), sizeof(array));
	double x = 2.87;
	collection_remove(&c, &x);
	collection_iterate(&c, &printDouble);
	collection_free(&c);
  }
  {
	puts("Test collection_reduce_left_double:");
	Collection c;
	double array[] = {1.54, 2.87, 3.44, 4.11, 5.99};
	collection_init(&c, array, sizeof(double), sizeof(array));
	double neutro = 1;
	double resultado = 0;
	collection_reduce_left(&c, &neutro, &resultado, productDouble);
	printf("%f\n", resultado);
	collection_free(&c);
  }
  {
  	puts("Test collection_reduce_left_double colleción vacia:");
  	Collection c;
  	double array[] = {};
  	collection_init(&c, array, sizeof(double), sizeof(array));
  	double neutro = 1;
  	double resultado = 0;
  	collection_reduce_left(&c, &neutro, &resultado, productDouble);
  	printf("%f\n", resultado);
  	collection_free(&c);
  }
  {
	puts("Test collection_reduce_left_double colleción de 1 elemento:");
	Collection c;
	double array[] = {2};
	collection_init(&c, array, sizeof(double), sizeof(array));
	double neutro = 1;
	double resultado = 0;
	collection_reduce_left(&c, &neutro, &resultado, productDouble);
	printf("%f\n", resultado);
	collection_free(&c);
   }
  {
    puts("Test collection_reduce_right_double:");
    Collection c;
    double array[] = {1.54, 2.87, 3.44, 4.11, 5.99};
    collection_init(&c, array, sizeof(double), sizeof(array));
    double neutro = 1;
    double resultado = 0;
    collection_reduce_right(&c, &neutro, &resultado, productDouble);
    printf("%f\n", resultado);
    collection_free(&c);
  }
  {
  	puts("Test collection_reduce_right_double coleccion vacia:");
    Collection c;
    double array[] = {};
    collection_init(&c, array, sizeof(double), sizeof(array));
    double neutro = 1;
    double resultado = 0;
    collection_reduce_right(&c, &neutro, &resultado, productDouble);
    printf("%f\n", resultado);
    collection_free(&c);
  }
  {
	puts("Test collection_reduce_right_double coleccion 1 elemento:");
	Collection c;
	double array[] = {4};
	collection_init(&c, array, sizeof(double), sizeof(array));
	double neutro = 1;
	double resultado = 0;
	collection_reduce_right(&c, &neutro, &resultado, productDouble);
	printf("%f\n", resultado);
	collection_free(&c);
  }
  {
	puts("Test filter");
    Collection c;
    int array[] = {1, 2, 3, 4, 5};
    collection_init(&c, array, sizeof(int), sizeof(array));
    collection_filter(&c, &isOdd);
    collection_iterate(&c, &printInt);
    collection_free(&c);
  }
  {
  	puts("Test filter coleccion 1 elemento que no cumple condicion");
	Collection c;
	int array[] = {2};
	collection_init(&c, array, sizeof(int), sizeof(array));
	collection_filter(&c, &isOdd);
	collection_iterate(&c, &printInt);
	collection_free(&c);
  }
  {
  	puts("Test filter coleccion 1 elemento que  cumple condicion");
	Collection c;
	int array[] = {1};
	collection_init(&c, array, sizeof(int), sizeof(array));
	collection_filter(&c, &isOdd);
	collection_iterate(&c, &printInt);
	collection_free(&c);
  }
  {
  	puts("Test filter coleccion vacia");
	Collection c;
	int array[] = {};
	collection_init(&c, array, sizeof(int), sizeof(array));
	collection_filter(&c, &isOdd);
	collection_iterate(&c, &printInt);
	collection_free(&c);
  }
  {
	puts("Test union");
	Collection c;
	int array[] = {1, 2};
	collection_init(&c, array, sizeof(int), sizeof(array));
	Collection other;
	int arrayOther[] = {3, 4};
	collection_init(&other, arrayOther, sizeof(int), sizeof(arrayOther));
	Collection dst;
	collection_init_empty(&dst, sizeof(int));
	collection_union(&c, &other, &dst);
    collection_iterate(&dst, &printInt);
    collection_free(&c);
  }
  {
  	puts("Test union con coleccion vacia");
  	Collection c;
  	int array[] = {1, 2};
  	collection_init(&c, array, sizeof(int), sizeof(array));
  	Collection other;
  	collection_init_empty(&other, sizeof(int));
  	Collection dst;
  	collection_init_empty(&dst, sizeof(int));
  	collection_union(&c, &other, &dst);
    collection_iterate(&dst, &printInt);
    collection_free(&c);
    }
  {
  	puts("Test intersection");
  	Collection c;
  	int array[] = {1, 2, 3, 9, 21, 112};
  	collection_init(&c, array, sizeof(int), sizeof(array));
  	Collection other;
  	int arrayOther[] = {3, 4, 5, 3, 21, 52};
  	collection_init(&other, arrayOther, sizeof(int), sizeof(arrayOther));
  	Collection dst;
  	collection_init_empty(&dst, sizeof(int));
  	collection_intersect(&c, &other, &dst);
    collection_iterate(&dst, &printInt);
    collection_free(&c);
    }
  {
  	puts("Test intersection con coleccion vacia");
  	Collection c;
  	int array[] = {1, 2, 3, 9, 21, 112};
  	collection_init(&c, array, sizeof(int), sizeof(array));
  	Collection other;
  	collection_init_empty(&other, sizeof(int));
  	Collection dst;
  	collection_init_empty(&dst, sizeof(int));
  	collection_intersect(&c, &other, &dst);
  	collection_iterate(&dst, &printInt);
  	collection_free(&c);
    }
}
