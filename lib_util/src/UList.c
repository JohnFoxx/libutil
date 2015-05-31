/*
 * UList.c
 *
 *  Created on: 31 mai 2015
 *      Author: MoZ
 */


#include "UList.h"
#include <stdlib.h>
#include <stdio.h>

static ULWagoon *__ulistIterate__( UList *list, UUint32 pos ) {

	ULWagoon *l_currentWag = list->first_wagoon;
	UUint32 l_currentPos = 0;

	if( pos > list->size + 1 )
		return NULL;

	while( ( l_currentPos != pos ) && ( l_currentWag != NULL ) ) {

		l_currentWag = l_currentWag->next_wagoon;
		l_currentPos++;
	}

	return l_currentWag;
}


UList *UListCreate( void ) {
	UList* l_list = NULL;

	l_list = (UList*)malloc( sizeof(UList) );
	if( l_list == NULL )
		return NULL;

	l_list->first_wagoon = NULL;
	l_list->last_wagoon = NULL;
	l_list->size = 0;

	return l_list;
}

UBool UListEmpty( UList *list) {
	return ( (list == NULL) || (list->size == 0));
}

UUint32 UListSize( UList *list ) {
	if( list == NULL )
		return 0;
	else
		return list ->size;
}

UPtr UListGetFirst( UList *list ) {

	if( ( list == NULL ) || (list->first_wagoon == NULL) )
		return NULL;

	return list->first_wagoon->content;

}

UPtr UListGetLast( UList *list ) {

	if( ( list == NULL ) || (list->last_wagoon == NULL) )
		return NULL;

	return list->last_wagoon->content;
}

UPtr UListGetAt( UList *list, UUint32 pos ) {

	ULWagoon* l_concerned = NULL;
	if( list == NULL )
		return NULL;

	if( pos == 0 ) {
		if( list->first_wagoon != NULL )
			return list->first_wagoon->content;
	}
	else if( pos == ( list->size-1) ) {
		if( list->last_wagoon != NULL )
			return list->last_wagoon->content;
	}
	else {
		l_concerned = __ulistIterate__( list, pos);
		if ( l_concerned == NULL )
			return NULL;

		return l_concerned->content;
	}

	return NULL;
}

UBool UListPushEnd( UList *list, UPtr content ) {

	ULWagoon* l_new = NULL;

	if( list == NULL )
		return false;

	l_new = (ULWagoon*)malloc( sizeof(ULWagoon));
	/**
	 * Problème allocation mémoire => Erreur
	 */
	if( l_new == NULL )
		return false;

	l_new->content = content;
	l_new->next_wagoon = NULL;

	/**
	 * si liste vide, premier wagon == dernier wagon
	 */
	if( list->size == 0 )
		list->first_wagoon = l_new;
	else
		list->last_wagoon->next_wagoon = l_new;

	list->last_wagoon = l_new;
	list->size++;

	return true;
}

UBool UListPushBegin( UList *list, UPtr content ) {

	ULWagoon* l_new = NULL;

	if( list == NULL )
		return false;

	l_new = (ULWagoon*)malloc( sizeof(ULWagoon));
	/**
	 * Problème allocation mémoire => Erreur
	 */
	if( l_new == NULL )
		return false;

	l_new->content = content;
	l_new->next_wagoon = list->first_wagoon;
	list->first_wagoon = l_new;

	/**
	 * si liste vide, premier wagon == dernier wagon
	 */
	if( list->size == 0 )
		list->last_wagoon = l_new;
	list->size++;

	return true;
}

UBool UListPushAt( UList *list, UUint32 pos, UPtr content ) {

	ULWagoon* l_new = NULL;
	ULWagoon* l_previous = NULL;

	/**
	 * Liste Nulle => Erreur
	 */
	if( list == NULL )
		return false;

	/**
	 * Position de taille supérieure à la liste => Erreur
	 */
	if( pos == 0 )
		return UListPushBegin( list, content);
	else if( pos == (list->size-1) )
		return UListPushEnd(list,content);
	else if( pos >= list->size )
		return false;

	/**
	 * Contenu vide => Erreur
	 */
	if( content == NULL )
		return false;

	l_previous = __ulistIterate__(list,pos-1);
	/**
	 * Impossible de trouver Wagon précdent => Erreur
	 */
	if( l_previous == NULL )
		return false;

	l_new = (ULWagoon*)malloc( sizeof(ULWagoon));
	/**
	 * Problème allocation mémoire => Erreur
	 */
	if( l_new == NULL )
		return false;

	l_new->content = content;
	l_new->next_wagoon = l_previous->next_wagoon;
	l_previous->next_wagoon = l_new;
	list->size++;
	return true;
}

void UListDestroy( UList *list ) {

		UList* l_list = list;
		ULWagoon* l_current = NULL;
		ULWagoon* l_next = NULL;

		if( l_list == NULL)
			return;

		l_current = l_list->first_wagoon;

		while ( l_current != NULL ) {
			l_next = l_current->next_wagoon;

			l_current->next_wagoon = NULL;
			free(l_current);

			l_current = l_next;

		}

		l_list->first_wagoon = NULL;
		l_list->last_wagoon = NULL;
		l_list->size = 0;

		free(l_list);
		l_list = NULL;
}

UPtr UListPopEnd( UList *list ) {

	UPtr l_content = NULL;
	ULWagoon *l_last = NULL;
	ULWagoon *l_previousOfLast = NULL;

	if( list == NULL || list->last_wagoon == NULL )
		return NULL;

	l_last = list->last_wagoon;
	l_content = l_last->content;

	/**
	 * Si le dernier wagon est le premier également (un seul maillon)
	 */
	if( list->first_wagoon == list->last_wagoon ) {
		list->first_wagoon = NULL;
		list->last_wagoon = NULL;
	}
	/**
	 * Sinon il faut mettre à NULL l'avant-dernier maillon
	 */
	else {
		l_previousOfLast = __ulistIterate__(list,list->size-2);
		if( l_previousOfLast == NULL )
			return NULL;
		l_previousOfLast->next_wagoon = NULL;
	}

	/**
	 * Libere le dernier
	 */
	free(l_last);
	list->size--;

	return l_content;

}

UPtr UListPopBegin( UList *list ) {

	UPtr l_content = NULL;
	ULWagoon *l_first = NULL;

	if( list == NULL || list->first_wagoon == NULL )
		return NULL;

	l_first = list->first_wagoon;
	list->first_wagoon = l_first->next_wagoon;
	l_content = l_first->content;

	free(l_first);
	list->size--;

	return l_content;
}

UPtr UListPopAt( UList *list, UUint32 pos ) {

	UPtr l_content = NULL;
	ULWagoon *l_current = NULL;
	ULWagoon *l_previous = NULL;

	if( ( list == NULL) || ( list->size == 0 ) )
		return NULL;

	if( pos == 0 )
		return UListPopBegin( list );
	else if( pos == list->size -1 )
		return UListPopEnd( list );
	else if ( pos >= list->size )
		return NULL;

	l_previous = __ulistIterate__(list,pos-1);
	if(l_previous == NULL)
		return NULL;

	l_current = l_previous->next_wagoon;
	l_content = l_current->content;
	l_previous->next_wagoon = l_current->next_wagoon;
	free(l_current);

	list->size--;

	return l_content;


}

UBool UListReplaceEnd( UList *list, UPtr content ) {

	if( ( list == NULL ) || ( list->last_wagoon == NULL ) || ( content == NULL) )
		return false;

	list->last_wagoon->content = content;
	return true;
}

UBool UListReplaceBegin( UList *list, UPtr content ) {

	if( ( list == NULL ) || ( list->first_wagoon == NULL ) || ( content == NULL) )
		return false;

	list->first_wagoon->content = content;
	return true;

}

UBool UListReplaceAt( UList *list, UUint32 pos, UPtr content ) {

	ULWagoon *l_current = NULL;

	if( ( list == NULL ) || ( content == NULL) || ( list->size == 0) )
		return false;

	if( pos == 0)
		return UListReplaceBegin(list,content);
	else if( pos == (list->size-1))
		return UListReplaceEnd(list,content);
	else if( pos >= list->size )
		return false;


	l_current = __ulistIterate__(list,pos-1);
	if( l_current == NULL )
		return false;

	l_current->content = content;
	return true;
}
