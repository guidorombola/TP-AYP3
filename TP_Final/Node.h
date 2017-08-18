/*
 * Node.h
 *
 *  Created on: 1 may. 2017
 *      Author: Admin
 */

#ifndef NODE_H_
#define NODE_H_

typedef struct _Node {
	void* data;
	struct _Node* next;
	struct _Node* prev;
} Node;

/**
 *	Inicializa un nodo con un dato
 *
 *	@param data: puntero al dato que quiero almacenar
 *	@param dataTypeSize: el sizeof del dato que contendrá el nodo
 *
 *	@return nodo inicializado
 */
Node* node_init(Node* this, void* data, unsigned dataTypeSize);

/**
 * Libera la memoria alocada para el nodo
 */
void node_free(Node* this);

/**
 * Reacomoda los punteros afectados por agregar un elemento a la colección.
 *
 * @newNode: nodo a agregar
 */
void node_rearrange_after_add(Node* this, Node* newNode);

/**
 * Reacomoda los punteros afectados al agregar a la colección.
 *
 * @head: puntero a nodo inicial
 * @back: puntero a nodo final
 */
void node_rearrage_after_remove(Node* this, Node** head, Node** back);

#endif /* NODE_H_ */
