/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [Yongho Bae] [2020039008] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h); //이미 할당되었을 경우 메모리 해제
	*h = (headNode*)malloc(sizeof(headNode)); //헤드노드 메모리할당
	(*h)->first = NULL; //헤드노드 초기화
	return 1;
}

int freeList(headNode* h){
	listNode* curr = h->first; //이전 노드 메모리 할당 해제 후에 넘어가기 위한 노드포인터

	listNode* prev = NULL;//메모리 할당 해제할 이전 노드포인터
	while(curr != NULL) {
		prev = curr;
		curr = curr->rlink;
		free(prev);
	} // 모든 노드 할당된 메모리 해제
	free(h); //헤드노드 할당된 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 node 생성
	listNode* last = h->first; // 마지막 노드포인터
	node->key = key; //node에 key 대입
	node->llink = node->rlink = NULL; //node의 link 초기화

	if(h->first==NULL){
		h->first = node;
		return 0;
	} //리스트가 비어있을 경우

	while(last->rlink != NULL){
		last = last->rlink;
	} //last가 마지막 노드를 가리킬 경우 탈출

	last->rlink = node;
	node->llink = last; //마지막에 node 연결
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* last = h->first; //마지막 노드 포인터

	if(h->first == NULL){
		printf("비어있는 리스트입니다.\n");
		return 0;
	}// 비어있는 리스트일 경우
	else if(last->rlink == NULL){
		h->first = NULL;
		free(last);
		return 0;
	}//리스트의 노드가 하나일 경우
	while(last->rlink != NULL){
		last = last->rlink; 
	}//last가 마지막 노드를 가리키면 탈출
	(last->llink)->rlink = NULL;//마지막노드의 이전노드 rlink를 NULL
	free(last);//마지막노드 메모리할당 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 메모리할당
	node->key = key; //node의 key값 대입
	node->rlink = h->first; 
	node->rlink->llink = node; //node를 첫번째 노드와 연결
	h->first = node;
	node->llink = NULL; //node를 헤더노드와 연결
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* first = h->first;
	if(h->first == NULL){
		printf("비어있는 리스트입니다.\n");
		return 0;
	}// 비어있는 리스트일 경우
	h->first = first->rlink; //헤더노드와 두번째 노드 연결
	free(first); //첫번째 노드 메모리할당 해제
	
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* prev = NULL; //이전노드
	listNode* curr = h->first; //현재노드
	if(h->first == NULL){
		printf("비어있는 리스트입니다.\n");
		return 0;
	}// 비어있는 리스트일 경우
	while(curr->rlink != NULL){
		curr->llink = curr->rlink;
		curr->rlink = prev; //llink와 rlink 교환
		prev = curr;
		curr = curr->llink; //prev, curr 다음 노드로 이동
	}//curr가 마지막 노드를 가리키면 탈출
	h->first=curr; //마지막 노드에 헤더노드 연결
	curr->llink=NULL;
	curr->rlink=prev; //마지막노드와 마지막이전노드 순서도 변경
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 메모리할당
	listNode* search = h->first; //입력받은 key보다 큰 key를 가진 노드 탐색을 위한 노드 포인터
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL; //node에 key 대입 및 link 초기화

	while(search != NULL){
		if(search->key >= key){//입력받은 key보다 큰 key를 가진 노드를 찾을 경우
			if(search == h->first)
				insertFirst(h ,key); //입력받은 key값이 가장 작을 경우
			else{
			node->rlink = search;
			node->llink = search->llink;
			search->llink->rlink = node;
			}//입력받은 key값이 중간에 들어갈 경우
			return 0;
		}
		search = search->rlink;
	}//끝까지 입력받은 key보다 큰 key를 가진 노드를 찾지 못했을 때 탈출
	insertLast(h, key);// 탈출후 마지막에 노드 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* search = h->first; //

	if(h->first == NULL){
		printf("비어있는 리스트입니다.\n");
		return 1;
	}// 비어있는 리스트일  경우
	while(search != NULL){
		if(search->key == key){//해당 key를 가진 노드를 찾을 경우
			if(search == h->first){
				deleteFirst(h);
			}//해당 key를 가진 노드가 첫번째일 경우
			else if(search->rlink == NULL){
				deleteLast(h);
			}//해당 key를 가진 노드가 마지막일 경우
			else{
				search->llink->rlink = search->rlink;
				search->rlink->llink = search->llink;
				free(search);
			}//중간에 있는 노드일 경우
		return 1;
		}
		search = search->rlink;
	}//해당 key를 찾을 수 없는 경우 탈출
	printf("해당 key=%d가 없습니다.\n",key);
	return 1;
}