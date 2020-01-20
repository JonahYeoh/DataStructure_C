#include <stdio.h>
#include <stdlib.h>

struct listNode {
	char data;
	struct listNode *NextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

// function prototype 

void insert( ListNodePtr *start, char data);
int delete(ListNodePtr *start, char data);
void show(ListNodePtr currentPtr);
int insertAt(ListNodePtr *start, char data, int index );
int deleteAt(ListNodePtr *start, int index);
int update(ListNodePtr *start, char data, int index);
int hasNext(ListNodePtr currentPtr);
char selectAt( ListNodePtr *start, int index );
void reverse( ListNodePtr *start );
int size(ListNodePtr currentPtr);

// End of prototype

int main( void ){
	ListNodePtr startPtr = NULL;
	int choice;
	char item;
	int FLAG = 0;
	int index = -1;
	scanf("%d", &choice);
	printf("%d", choice);
	
	while( choice != 99 ) {
		printf("looping\n");
		
		switch(choice){
			case 1:
				printf("void insert( ListNodePtr *start, char data );\n");
				getchar();
				scanf("%c", &item);
				insert(&startPtr, item);
				break;
			case 2:
				if( size( startPtr ) != 0 ){
					printf("int delete( ListNodePtr *start, char data ); \n");
					getchar();
					scanf("%c", &item);
					item = delete( &startPtr, item );
					if (  item == -2 ) 
						printf("Not found\n");
					else
						printf("%c was deleted\n", item);
				}
				else
					printf("Empty List\n");
				break;
			case 3:
				printf("void show( ListNodePtr currentPtr ); \n");
				show(startPtr);
				break;
			case 4:
				printf("int size( ListNodePtr currentPtr ); \n");
				printf("Size : %3d\n", size(startPtr) );
				break;
			case 5: 
				printf("int hasNext( ListNodePtr currentPtr ); \n");
				FLAG = hasNext(startPtr);
				printf("FLAG : %6s\n", ((FLAG == 1)?"TRUE":"FALSE"));
				break;
			case 6: 
				if( size( startPtr ) != 0 ){
					printf("int deleteAt( ListNodePtr *start, int index ); \n");
					getchar();
					scanf("%d", &index);
					printf("Deleted index : %d\n", deleteAt(&startPtr, index ));
				}
				else
					printf("Empty list\n");
				break;
			case 7:
				printf("void insertAt( ListNodePtr *start, char data, int index );\n");
				getchar();
				scanf("%c", &item);
				scanf("%d", &index);
				insertAt(&startPtr, item, index);
				break;
			case 8:
				if ( size( startPtr ) != 0 ) {
					printf("int update( ListNodePtr *start, char data, int index ); \n");
					getchar();
					scanf("%c", &item);
					scanf("%d", &index);
					printf("Affected index : %d\n", update(&startPtr, item, index) );
				}
				else
					printf("Empty list\n");
				break;
			case 9:
				if ( size( startPtr ) != 0 ) {
					printf("char selectAt( ListNodePtr *start, int index ); \n");
					getchar();
					scanf("%d", &index );
					printf("Captured character : %c\n", selectAt(&startPtr, index));
				}
				else
					printf("Empty list\n");
				break;
			case 10:
				if ( size( startPtr ) != 0 ) {
					printf("void reverse( ListNodePtr *start )\n");
					reverse( &startPtr );
				}
				else
					printf("Empty list\n");
				break;
			default:
				break;			
		}	// end of switch
		show(startPtr);
		scanf("%d",  &choice);
	}	// end of while
	return 0;
}	// end of main function 

void insert(ListNodePtr *start, char data){
	printf("insert function\n");
	ListNodePtr currentPtr = NULL, previousPtr = NULL;
	ListNodePtr newPtr = malloc(sizeof(ListNode));
	if( newPtr != NULL )
	{
		newPtr->data = data;
		newPtr->NextPtr = NULL;
		currentPtr = *start;
		while( currentPtr != NULL && data > currentPtr->data ){
			previousPtr = currentPtr;
			currentPtr = currentPtr->NextPtr;
		}
		if( previousPtr == NULL ){
			newPtr->NextPtr = *start;
			*start = newPtr;
		}
		else{
			previousPtr->NextPtr = newPtr;
			newPtr->NextPtr = currentPtr;
		}
	}
	else{
		printf("%s\n", "No memory available");
	}	
}

int delete( ListNodePtr *start, char data ) {
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
	ListNodePtr tempPtr;
	if( *start != NULL ){
		if( data == ( *start )->data ){
			tempPtr = *start;
			*start = ( *start )->NextPtr;
			free( tempPtr );
			return data;
		}
		else{
			previousPtr = *start;
			currentPtr = ( *start )->NextPtr;
			while( currentPtr != NULL && currentPtr->data != data ){
				previousPtr = currentPtr;
				currentPtr = currentPtr->NextPtr;
			}
			if( currentPtr != NULL ){
				tempPtr = currentPtr;
				previousPtr->NextPtr = currentPtr->NextPtr;
				free( tempPtr );
				return data;
			}
		}
		return -2;
	}
	
}

void show( ListNodePtr currentPtr ){
	if( currentPtr == NULL ) {
		puts("Empty list");
	}
	else {
		puts("Printing list\n");
		while( currentPtr != NULL ){
			printf("%c ===> ", currentPtr->data);
			currentPtr = currentPtr->NextPtr;
		}
		puts("End Of List");
	}
}

int insertAt(ListNodePtr *start, char data, int index ){
	printf("Insert At\n");
	ListNodePtr currentPtr = NULL, previousPtr = NULL;
	ListNodePtr newPtr = malloc(sizeof(ListNode));
	int currentIndex = 0;
	if( newPtr != NULL ){
		newPtr->data = data;
		newPtr->NextPtr = NULL;
		currentPtr = *start;
		if( index == 0 ){
			newPtr->NextPtr = *start;
			*start = newPtr;
			return 0;
		}
		while( currentPtr != NULL && currentIndex != index ){
			previousPtr = currentPtr;
			currentPtr = currentPtr->NextPtr;
			currentIndex++;
		}
		
		if( previousPtr == NULL )
			return -1;
		else{
			previousPtr->NextPtr = newPtr;
			newPtr->NextPtr = currentPtr;
			return index;
		}
	}
	else{
		puts("No memory available");
		return -1;
	}
	
}

int deleteAt(ListNodePtr *start, int index){
	ListNodePtr currentPtr = NULL, previousPtr = NULL;
	ListNodePtr tempPtr = NULL;
	int currentIndex = 0;
	if( currentIndex == index ){
		tempPtr = *start;
		*start = ( *start )->NextPtr;
		free( tempPtr );
		return currentIndex;
	}
	else{
		previousPtr = *start;
		currentPtr = ( *start )->NextPtr;
		currentIndex++;
		while( currentPtr != NULL && currentIndex != index){
			previousPtr = currentPtr;
			currentPtr = currentPtr->NextPtr;
			currentIndex++;
		}
		if( currentPtr != NULL ){
			tempPtr = currentPtr;
			previousPtr->NextPtr = currentPtr->NextPtr;
			free( tempPtr );
			printf("%d %d", currentIndex, index );
			return currentIndex;
		}
	}
	return -1;
}

int update(ListNodePtr *start, char data, int index){
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
	int currentIndex = 0;
	currentPtr = *start;
	previousPtr = currentPtr;
	currentPtr = ( *start )->NextPtr;
	currentIndex++;
	while( currentPtr != NULL && currentIndex != index ){
		previousPtr = currentPtr;
		currentPtr = currentPtr->NextPtr;
		currentIndex++;
	}
	currentPtr->data = data;
	return currentIndex;
}

char selectAt( ListNodePtr *start, int index ){
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;
	int currentIndex = 0;
	
	currentPtr = *start;
	if( currentPtr != NULL ){
		if( index == 0 )
			return currentPtr->data;
		printf("cont\ts");
		previousPtr = currentPtr;
		currentPtr = (*start)->NextPtr;
		currentIndex++;
		while( currentPtr != NULL && currentIndex != index ){
			previousPtr = currentPtr;
			currentPtr = currentPtr->NextPtr;
			currentIndex++;
		}
		if( currentIndex == index )
			return currentPtr->data;
		else{
			printf("item not found\n");
			return '\0';
		}
	}
	else {
		printf("empty list\n");
		return '\0';
	}
}

int size(ListNodePtr currentPtr){
	int size = 0;
	if( currentPtr == NULL )
		return size;
	else{
		while( currentPtr != NULL ){
			size++;
			currentPtr = currentPtr->NextPtr;
		}
		return size;
	}
}

int hasNext(ListNodePtr currentPtr){
	if( currentPtr == NULL )
		return 0;
	else{
		return ((currentPtr->NextPtr == NULL)?0:1);
	}
} 

void reverse( ListNodePtr *start ){
	ListNodePtr currentPtr = NULL;
	ListNodePtr previousPtr;
	ListNodePtr tempPtr;
	
	previousPtr = *start;
	
	int FLAG = 0;
	if( previousPtr != NULL ){
		if( previousPtr->NextPtr != NULL ){
			currentPtr = previousPtr->NextPtr;
			while( currentPtr != NULL ){
				if( FLAG == 0 ){
					printf("%c ", currentPtr->data);
					if( hasNext(currentPtr) ){
						tempPtr = currentPtr->NextPtr;
						currentPtr->NextPtr = previousPtr;
						previousPtr->NextPtr = NULL;
						previousPtr = currentPtr;
						currentPtr = tempPtr;
						FLAG = 1;
						printf("%c ", currentPtr->data);
					}
					else{
						currentPtr->NextPtr = previousPtr;
						previousPtr->NextPtr = NULL;
						previousPtr = currentPtr;
						currentPtr = tempPtr;
						FLAG = 1;
						printf("%c ", currentPtr->data);
						break;
					}
				}
				else{
					printf("%c ", currentPtr->data);
					if( hasNext(tempPtr) ){
						tempPtr = tempPtr->NextPtr;
						currentPtr->NextPtr = previousPtr;
						previousPtr = currentPtr;
						currentPtr = tempPtr;
					}
					else{
						currentPtr->NextPtr = previousPtr;
						previousPtr = currentPtr;
						break;
					}
				}
			}
		}
		else {
			printf("Single Node\n");
		}
		*start = previousPtr;
	}
	else {
		printf("Empty list\n");
	}	
}
