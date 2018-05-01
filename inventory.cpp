#include <stdlib.h>
#include <string.h>
#include <search.h>
#include "savedata.h"
#define item data.itemdata
#define head data.soubi.headdata
#define body data.soubi.bodydata
#define arm data.soubi.armdata
#define foot data.soubi.footdata
#define weapon data.soubi.weapondata
//hoge[0]...itemnum,hoge[1]...itemamount
#define full(a) {\
			for(int i=0;i<(sizeof(a[0])/sizeof(a[0][0]));i++){\
			a[0][i]=9999;\
			a[1][i]=9999;\
			}\
	}

int compare(const void *arg1, const void *arg2 ){
   return( _stricmp( * (char**)arg1, * (char**)arg2 ) );
}
int int_sort( const void * a , const void * b ) {
  /* ˆø”‚Ívoid*Œ^‚Æ‹K’è‚³‚ê‚Ä‚¢‚é‚Ì‚ÅintŒ^‚Écast‚·‚é */
  if( *( int * )a < *( int * )b ) {
    return -1;
  }
  else
  if( *( int * )a == *( int * )b ) {
    return 0;
  }
  return 1;
}

void iteminit(){
	full(item);
	full(head);
	full(body);
	full(arm);
	full(foot);
	full(weapon);
}
void sortinventory() {
	qsort(( void * )item[0] , sizeof(item)/sizeof(item[0]) , sizeof( item[0][0] ) , int_sort );
	qsort(( void * )head[0] , sizeof(head)/sizeof(head[0]) , sizeof( head[0][0] ) , int_sort );
	qsort(( void * )body[0] , sizeof(body)/sizeof(body[0]) , sizeof( body[0][0] ) , int_sort );
	qsort(( void * )arm[0] , sizeof(arm)/sizeof(arm[0]) , sizeof( arm[0][0] ) , int_sort );
	qsort(( void * )foot[0] , sizeof(foot)/sizeof(foot[0]) , sizeof( foot[0][0] ) , int_sort );
	qsort(( void * )weapon[0] , sizeof(weapon)/sizeof(weapon[0]) , sizeof( weapon[0][0] ) , int_sort );

}
void addinventory(int object,int type ,int amount){
	int itemnum, *result;
	const int searchkey=type;
	sortinventory();
	switch(object){
		case 0:
			result = (int*)_lsearch(&searchkey,item[0],(unsigned int *)(sizeof(item[0])/sizeof(item[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &item[0][0]);
			item[0][itemnum]=type;
			item[1][itemnum]+=amount;
			break;
		case 1:
			result = (int*)_lsearch(&searchkey,head[0],(unsigned int *)(sizeof(head[0])/sizeof(head[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &head[0][0]);
			head[0][itemnum]=type;
			head[1][itemnum]+=amount;
			break;
		case 2:
			result = (int*)_lsearch(&searchkey,body[0],(unsigned int *)(sizeof(body[0])/sizeof(body[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &body[0][0]);
			body[0][itemnum]=type;
			body[1][itemnum]+=amount;
			break;
		case 3:
			result = (int*)_lsearch(&searchkey,arm[0],(unsigned int *)(sizeof(arm[0])/sizeof(arm[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &arm[0][0]);
			arm[0][itemnum]=type;
			arm[1][itemnum]+=amount;
			break;
		case 4:
			result = (int*)_lsearch(&searchkey,foot[0],(unsigned int *)(sizeof(foot[0])/sizeof(foot[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &foot[0][0]);
			foot[0][itemnum]=type;
			foot[1][itemnum]+=amount;
			break;
		case 5:
			result = (int*)_lsearch(&searchkey,weapon[0],(unsigned int *)(sizeof(weapon[0])/sizeof(weapon[0][0])),(unsigned int)sizeof(int),compare);
			itemnum =  (int)(result - &weapon[0][0]);
			weapon[0][itemnum]=type;
			weapon[1][itemnum]+=amount;
			break;
	}
	sortinventory();
}