/*
 * UList.h
 *
 *  Created on: 31 mai 2015
 *      Author: MoZ
 */

#ifndef ULIST_H_
#define ULIST_H_

#include "UType.h"


typedef struct __ulist_wagoon__ ULWagoon;
struct __ulist_wagoon__
{
	void* content;
	ULWagoon* next_wagoon;
};



struct __ulist__
{
	ULWagoon* first_wagoon;
	ULWagoon* last_wagoon;
	UUint32 size;
};

typedef struct __ulist__ UList;


UList *UListCreate( void );
void UListDestroy( UList *list );

UUint32 UListSize( UList *list );
UBool UListEmpty( UList *list );

UPtr UListGetFirst( UList *list );
UPtr UListGetLast( UList *list );
UPtr UListGetAt( UList *list, UUint32 pos );

UBool UListPushEnd( UList *list, UPtr content );
UBool UListPushBegin( UList *list, UPtr content );
UBool UListPushAt( UList *list, UUint32 pos, UPtr content );

UPtr UListPopEnd( UList *list );
UPtr UListPopBegin( UList *list );
UPtr UListPopAt( UList *list, UUint32 pos );

UBool UListReplaceEnd( UList *list, UPtr content );
UBool UListReplaceBegin( UList *list, UPtr content );
UBool UListReplaceAt( UList *list, UUint32 pos, UPtr content );


#endif /* ULIST_H_ */
