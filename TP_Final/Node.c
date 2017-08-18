/*
 * Node.c
 *
 *  Created on: 1 may. 2017
 *      Author: Admin
 */
#include <stdlib.h>
#include <string.h>
#include "Node.h"

Node* node_init(Node* this, void* data, unsigned dataTypeSize) {
	this->data = malloc(dataTypeSize);
	this->next = 0x0;
	this->prev = 0x0;
	memcpy(this->data, data, dataTypeSize);
    return this;
}

void node_rearrange_after_add(Node* this, Node* newNode) {

	while (this->next) {
        this = this->next;
    }
    
    this->next = newNode;
    newNode->prev = this;
}

void node_rearrage_after_remove(Node* this, Node** head, Node** back) {

	if (this->prev) {
		this->prev->next = this->next;

		if (this->next) {
			this->next->prev = this->prev;
		}

	} else {
		*head = this->next;
	}

	if (*back == this) {
		*back = this->prev;
	}
}

void node_free(Node* this) {
	free(this->data);
	this->data = 0x0;
	this->next = 0x0;
	this->prev = 0x0;
	free(this);
}