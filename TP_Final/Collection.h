/*
 * Collection.h
 *
 *  Created on: 1 may. 2017
 *      Author: Admin
 */
#include "Node.h"

#ifndef COLLECTION_H_
#define COLLECTION_H_

typedef struct _Collection {
	Node* head;
	Node* back;
	unsigned dataTypeSize;
	unsigned elementCount;
} Collection;

/**
 * Inicializa la colecci�n sin ning�n elemento
 *
 * @param dataTypeSize: 		el sizeof del tipo de dato que compone cada elemento de la colecci�n
 *
 * @return colecci�n inicializada sin elementos
 */
Collection* collection_init_empty(Collection* this, unsigned dataTypeSize);

/**
 *  Inicializa la colecci�n a partir de un vector de valores de cualquier tipo
 *
 *  @param data: 				puntero al array que se usar� para inicializar la colecci�n
 *  @param dataTypeSize: 	el sizeof del tipo de dato que compone cada elemento de la colecci�n
 *  @param arraySize: 		el volumen del array que se usa para inicializar la colecci�n
 *
 *  @return colecci�n inicializada a partir de un conjunto de valores
 */
Collection* collection_init(Collection* this, void* data, unsigned dataTypeSize,
	unsigned arraySize);

/**
 * Agrega un elemento al final de la colecci�n
 *
 * @param data: puntero al elemento a agregar
 *
 * @return colecci�n con el nuevo valor incorporado
 */
Collection* collection_add(Collection* this, void* data);

/**
 * Remueve el �ltimo elemento de la colecci�n
 *
 * @return colecci�n sin el �ltimo elemento
 */
Collection* collection_pop(Collection* this);

/**
 * Remueve la primera aparici�n de un elemento espec�fico de la colecci�n
 *
 * @param data: puntero al elemento a eliminar
 *
 * @return colecci�n con el elemento removido
 */
Collection* collection_remove(Collection* this, void* data);

/**
 * Busca un dato y devuelve el nodo que lo contiene
 *
 * @param data: el dato a buscar
 *
 * @return nodo con el dato, o 0x0 si no se encontr�
 */
Node* collection_find_node(Collection* this, void* data);

/**
 * Busca un dato y lo devuelve
 *
 * @param data: el dato a buscar
 *
 * @return dato, o 0x0 si no se encontr�
 */
void* collection_find(Collection* this, void* data);

/**
 * Ejecuta una acci�n para cada elemento de la colecci�n
 *
 * @param func: puntero a funci�n que se aplicar�
 *
 * @return colecci�n
 */
Collection* collection_iterate(Collection* this, void (*func)(void*));

/**
 * Ejecuta una acci�n para cada elemento de la colecci�n y copia el nuevo elemento en
 * una colecci�n destino
 *
 * @param dst: colecci�n destino
 * @param func: puntero a funci�n que se aplicar�
 *
 * @return colecci�n
 */
Collection* collection_collect(Collection* this, Collection* dst, void (*func)(void*));

/**
 * Selecciona elementos de la colecci�n que satisfacen una condici�n, y los copia en una
 * colecci�n destino
 *
 * @param dst: colecci�n destino
 * @param func: puntero a funci�n condici�n
 *
 * @return colecci�n
 */
Collection* collection_select(Collection* this, Collection* dst, int (*func)(void*));

/**
 * Aplica la funcion reduce desde el inicio de la colecci�n.
 *
 * @param neutral: elemento neutro de la operacion
 * @param result: puntero donde se almacenara la referencia del resultado
 * @param func: puntero a funcion de la operacion binaria
 *
 * @return puntero a resultado
 */
void* collection_reduce_left(Collection* this, void* neutral, void* result,
	void (*func)(void*, void*, void*));

/**
 * Aplica la funcion reduce desde el final de la colecci�n.
 *
 * @param neutral: elemento neutro de la operacion
 * @param result: puntero donde se almacenara la referencia del resultado
 * @param func: puntero a funcion de la operacion binaria
 *
 * @return puntero a resultado
 */
void* collection_reduce_right(Collection* this, void* neutral, void* result,
	void (*func)(void*, void*, void*));

/**
 * Elimina elementos de la coleccion que no cumplen con una condicion
 *
 * @param func: puntero a funci�n condici�n
 *
 * @return colecci�n
 */
Collection* collection_filter(Collection* this, int (*func)(void*));

/**
 * Realiza una concatenacion de dos colecciones, y la guarda en una coleccion destino
 *
 * @param other: la concatenacion se realiza con la coleccion actual y a la que apunte
 *  este puntero
 * @param dst: coleccion destino
 *
 * @return coleccion
 */
Collection* collection_union(Collection* this, Collection* other, Collection* dst);

/*
 * Realiza la interseccion de dos coleciones, y la guarda en una coleccion destino
 *
 * @param other: la interseccion se realiza con la coleccion actual y a la que apunte
 *  este puntero
 * @param dst: coleccion destino
 *
 * @return coleccion
 */
Collection* collection_intersect(Collection* this, Collection* other, Collection* dst);

void collection_free(Collection* this);

#endif /* COLLECTION_H_ */
