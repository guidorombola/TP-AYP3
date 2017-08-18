/*
 * Collection.c
 *
 *  Created on: 1 may. 2017
 *      Author: Admin
 */
#include <stdlib.h>
#include <string.h>
#include "Collection.h"

Collection* collection_init_empty(Collection* this, unsigned dataTypeSize) {
    this->elementCount = 0;
    this->dataTypeSize = dataTypeSize;
    this->head = 0x0;
    this->back = 0x0;
    return this;
}

Collection* collection_init(Collection* this, void* data, unsigned dataTypeSize, 
    unsigned arraySize) {

    collection_init_empty(this, dataTypeSize);
    void* current = data;
    
    while (arraySize) {
        collection_add(this, current);
        current += dataTypeSize;
        arraySize -= dataTypeSize;
    }
    
    return this;
}

Collection* collection_add(Collection* this, void* data){
    Node* newNode = (Node*) malloc(sizeof(Node));
    node_init(newNode, data, this->dataTypeSize);
    Node* current = this->head;
    
    if (current) {
        node_rearrange_after_add(current, newNode);
        
    } else {
        this->head = newNode;
    }
    
    this->back = newNode;
    this->elementCount++;
    return this;
}

Collection* collection_pop(Collection* this) {
    Node* temp = this->back;

    if (this->back) {
        this->back = this->back->prev;

        if (this->back) {
            this->back->next = 0x0;

        } else {
        	this->head = 0x0;
        }

        this->elementCount--;
        node_free(temp);
    }

    return this;
}

Collection* collection_remove(Collection* this, void* data) {
    Node* found = collection_find_node(this, data);

    if (found) {
		node_rearrage_after_remove(found, &this->head, &this->back);
		node_free(found);
		this->elementCount--;
	}

    return this;
}

Node* collection_find_node(Collection* this, void* data){
	Node* current = this->head;

	if (this->elementCount != 0) {

		while (current) {

			if (memcmp(current->data, data, this->dataTypeSize) == 0) {
				return current;
			}

			current = current->next;
	    }
	}

	return 0x0;
}

void* collection_find(Collection* this, void* data){
	Node* found = collection_find_node(this, data);

	if (found) {
		return found->data;
	}

	return 0x0;
}

Collection* collection_iterate(Collection* this, void (*func)(void*)) {
    Node* current = this->head;

    while (current) {
        (*func)(current->data);
        current = current->next;
    }

    return this;
}

void check_and_free(Collection* this, Collection* dst) {

	if (dst->elementCount != 0) {
		collection_free(dst);
		dst->dataTypeSize = this->dataTypeSize;
	}
}

Collection* collection_collect(Collection* this, Collection* dst, 
	void (*func)(void*)) {
	
	check_and_free(this, dst);
	Node* current = this->head;

	while (current) {
		collection_add(dst, current->data);
		(*func)(dst->back->data);
		current = current->next;
	}

	return this;
}

Collection* collection_select(Collection* this, Collection* dst, int (*func)(void*)) {
	check_and_free(this, dst);
	Node* current = this->head;

	while (current) {

		if ((*func)(current->data)) {
			collection_add(dst, current->data);
		}

		current = current->next;
	}

	return this;
}

void* collection_reduce_left(Collection* this, void* neutral, void* result, 
	void (*func)(void*, void*, void*)) {

	Node* current = this->head;
	memcpy(result, neutral, this->dataTypeSize);

	while (current) {
		(*func)(result, current->data, result);
		current = current->next;
	}

	return result;
}

void* collection_reduce_right(Collection* this, void* neutral, void* result, 
	void (*func)(void*, void*, void*)) {

	Node* current = this->back;
	memcpy(result, neutral, this->dataTypeSize);

	while (current) {
		(*func)(result, current->data, result);
		current = current->prev;
	}

	return result;
}

Collection* collection_filter(Collection* this, int (*func)(void*)) {
	Node* current = this->head;

	while (current) {

		if (!(*func)(current->data)) {
			Node* temp = current->next;
			collection_remove(this, current->data);
			current = temp;

		} else {
			current = current->next;
		}
	}

	return this;
}

void collection_free(Collection* this) {

	while(this->elementCount) {
		collection_pop(this);
	}

	collection_init_empty(this, 0);
}

Collection* collection_union(Collection* this, Collection* other, Collection* dst){
	Node* current = this->head;
	check_and_free(this, dst);
	while (current) {
		collection_add(dst, current->data);
		current = current->next;
	}
	current = other->head;
	while (current) {
		collection_add(dst, current->data);
		current = current->next;
	}
	return this;
}

Collection* collection_intersect(Collection* this, Collection* other, Collection* dst){
	Node* current = this->head;
	void* element = 0x0;
	check_and_free(this, dst);
	while(current){
		element = current->data;
		if(collection_find_node(other, element) && !collection_find_node(dst, element)){
			collection_add(dst, element);
		}
		current = current->next;
	}
	return this;
}

