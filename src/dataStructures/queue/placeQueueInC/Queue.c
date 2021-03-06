#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

// Queue_Entry() is a useful macro; there is a full discussion of a similar
// macro for a generic doubly-linked list implementation in the CS 2505 notes.
// Converts pointer to queue element NODE into a pointer to the structure that
// NODE is embedded inside.  Supply the name of the outer structure STRUCT and
// the member name MEMBER of the NODE.  See the big comment at the top of the
// file for an example.

#define Queue_Entry(NODE, STRUCT, MEMBER)                              \
  ((STRUCT *) ((uint8_t *) (NODE) - offsetof (STRUCT, MEMBER)))

// Initialize QNode pointers to NULL.
//
// Pre:  pN points to a QNode object
// Post: pN->prev and pN->next are NULL
//
void QNode_Init(QNode* const pN) {
	pN->prev = NULL;
	pN->next = NULL;
}

// Initialize Queue to empty state.
//
// Pre:  pQ points to a Queue object
// Post: *pQ has been set to an empty state (see preceding comment
//
void Queue_Init(Queue* const pQ) {
	pQ->fGuard.prev = NULL;
	pQ->fGuard.next = &(pQ->rGuard);
	pQ->rGuard.prev = &(pQ->fGuard);
	pQ->rGuard.next = NULL;
}

// Return whether Queue is empty.
//
// Pre:  pQ points to a Queue object
// Returns true if *pQ is empty, false otherwise
//
bool Queue_Empty(const Queue* const pQ) {
	if (pQ->fGuard.next == &(pQ->rGuard)) {
		return true;
	} else {
		return false;
	}
}

// Insert *pNode as last interior element of Queue.
//
// Pre:  pQ points to a Queue object
//       pNode points to a QNode object
// Post: *pNode has been inserted at the rear of *pQ
//
void Queue_Push(Queue* const pQ, QNode* const pNode) {
	// connect new pNode to Qnode before rear node
	pQ->rGuard.prev->next = pNode;
	pNode->prev = pQ->rGuard.prev;

	// connect pNode to rear node
	pNode->next = &(pQ->rGuard);
	pQ->rGuard.prev = pNode;
}

// Remove first interior element of Queue and return it.
//
// Pre:  pQ points to a Queue object
// Post: the interior QNode that was at the front of *pQ has been removed
// Returns pointer to the QNode that was removed, NULL if *pQ was empty
//
QNode* const Queue_Pop(Queue* const pQ) {
	if (Queue_Empty(pQ)) {
		printf("In method Queue_Pop of class Queue the"
				" linked queue is empty and cannot be dequeued");
		return NULL;
	}
	QNode *QNodeToRemove = pQ->fGuard.next;

	// remove links to QNodeToRemove
	pQ->fGuard.next = pQ->fGuard.next->next;
	pQ->fGuard.next->prev = &(pQ->fGuard);

	return QNodeToRemove;
}

// Return pointer to the first interior element, if any.
//
// Pre:  pQ points to a Queue object
// Returns pointer first interior QNode in *pQ, NULL if *pQ is empty
//
QNode* const Queue_Front(const Queue* const pQ) {
	if (Queue_Empty(pQ)) {
		printf("In method Queue_Front of class Queue the"
		 " linked queue is empty so no front element exists");
		return NULL;
	}

	return pQ->fGuard.next;
}

// Return pointer to the last interior element, if any.
//
// Pre:  pQ points to a Queue object
// Returns pointer last interior QNode in *pQ, NULL if *pQ is empty
//
QNode* const Queue_Back(const Queue* const pQ) {
	if (Queue_Empty(pQ)) {
		printf("In method Queue_Back of class Queue the"
			" linked queue is empty so no back element exists");
		return NULL;
	}

	return pQ->rGuard.prev;
}

// Return pointer to the rear guard; useful for traversal logic.
//
// Pre:  pQ points to a Queue object
// Returns pointer rear guard element.
//
const QNode* const Queue_End(const Queue* const pQ) {
	return &(pQ->rGuard);
}
