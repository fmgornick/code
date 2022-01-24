#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

/* 	Add a new node to the linked list with the specified data.
	The new node should be added to the front of the list.
	*/
int add_node(int data){

	NODE* node = NULL;
	if (HEAD == NULL){
		HEAD=(NODE*)malloc(sizeof(NODE));
		if (HEAD == NULL){
			printf("Error allocating memory!\n");
			exit(1);
		}
		/* We are creating the very first node
		   Allocate memory to HEAD here and check for any errors 
		   */
		HEAD->next=NULL;
		HEAD->data = data;
	}
	else{
		/*  Allocate memory for a node here and check for any errors 
			Make sure you rearange the HEAD to point to this node.
			*/
		node=(NODE *)malloc(sizeof(NODE));
		if (node == NULL){
			printf("Error allocating memory!\n");
			exit(1);
		}
		node->next=HEAD;
		HEAD=node;
		node->data = data;
	}
	printf("Allocated node for %d\n", data);
	return 0;
}

int search(int data){

	NODE* node = HEAD;
	int index = 0;
	while(node != NULL){
		/* Search through the list and look for the node with the specified data 
		   If found, return 0.
		   */
		if(node->data==data){
			printf("Found a node with data %d at position %d\n", data, index);
			return 0;
		}
		node=node->next;
		index++;
	}
	printf("Did not find %d\n", data);
	return -1;
}

/*	Delete a node having the specified data */

int delete_node(int data){

	NODE* node = NULL; 
	NODE* tmp = NULL;

	// If there are no nodes at all, return 0 
	if (HEAD == NULL){
		printf("HEAD is NULL\n");
		return 0;
	}
	// If the HEAD has data delete it and return 0 
	if (HEAD->data == data){
		node=HEAD;
		HEAD=HEAD->next;
		free(node);
		return 0;
	}
	// Search through the list 
	node = HEAD;
	tmp = HEAD->next;
	while(tmp != NULL){
		if (tmp->data == data){
			// Appropriately handle the "next" pointer and delete the data 		
			node->next=tmp->next;
			free(tmp);
			return 0;
		}
		node = tmp;
		tmp = tmp->next;
	}
	printf("Could not find %d\n", data);
	return -1;	
}


int main(){
	add_node(0);
	add_node(1);
	search(1);
}
