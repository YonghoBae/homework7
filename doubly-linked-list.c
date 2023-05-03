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

/* �ʿ��� ������� �߰� if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ���� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h); //�̹� �Ҵ�Ǿ��� ��� �޸� ����
	*h = (headNode*)malloc(sizeof(headNode)); //����� �޸��Ҵ�
	(*h)->first = NULL; //����� �ʱ�ȭ
	return 1;
}

int freeList(headNode* h){
	listNode* curr = h->first; //���� ��� �޸� �Ҵ� ���� �Ŀ� �Ѿ�� ���� ���������

	listNode* prev = NULL;//�޸� �Ҵ� ������ ���� ���������
	while(curr != NULL) {
		prev = curr;
		curr = curr->rlink;
		free(prev);
	} // ��� ��� �Ҵ�� �޸� ����
	free(h); //����� �Ҵ�� �޸� ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); // �߰��� node ����
	listNode* last = h->first; // ������ ���������
	node->key = key; //node�� key ����
	node->llink = node->rlink = NULL; //node�� link �ʱ�ȭ

	if(h->first==NULL){
		h->first = node;
		return 0;
	} //����Ʈ�� ������� ���

	while(last->rlink != NULL){
		last = last->rlink;
	} //last�� ������ ��带 ����ų ��� Ż��

	last->rlink = node;
	node->llink = last; //�������� node ����
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* last = h->first; //������ ��� ������

	if(h->first == NULL){
		printf("����ִ� ����Ʈ�Դϴ�.\n");
		return 0;
	}// ����ִ� ����Ʈ�� ���
	else if(last->rlink == NULL){
		h->first = NULL;
		free(last);
		return 0;
	}//����Ʈ�� ��尡 �ϳ��� ���
	while(last->rlink != NULL){
		last = last->rlink; 
	}//last�� ������ ��带 ����Ű�� Ż��
	(last->llink)->rlink = NULL;//����������� ������� rlink�� NULL
	free(last);//��������� �޸��Ҵ� ����
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node �޸��Ҵ�
	node->key = key; //node�� key�� ����
	node->rlink = h->first; 
	node->rlink->llink = node; //node�� ù��° ���� ����
	h->first = node;
	node->llink = NULL; //node�� ������� ����
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* first = h->first;
	if(h->first == NULL){
		printf("����ִ� ����Ʈ�Դϴ�.\n");
		return 0;
	}// ����ִ� ����Ʈ�� ���
	h->first = first->rlink; //������� �ι�° ��� ����
	free(first); //ù��° ��� �޸��Ҵ� ����
	
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* prev = NULL; //�������
	listNode* curr = h->first; //������
	if(h->first == NULL){
		printf("����ִ� ����Ʈ�Դϴ�.\n");
		return 0;
	}// ����ִ� ����Ʈ�� ���
	while(curr->rlink != NULL){
		curr->llink = curr->rlink;
		curr->rlink = prev; //llink�� rlink ��ȯ
		prev = curr;
		curr = curr->llink; //prev, curr ���� ���� �̵�
	}//curr�� ������ ��带 ����Ű�� Ż��
	h->first=curr; //������ ��忡 ������ ����
	curr->llink=NULL;
	curr->rlink=prev; //���������� ������������� ������ ����
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node �޸��Ҵ�
	listNode* search = h->first; //�Է¹��� key���� ū key�� ���� ��� Ž���� ���� ��� ������
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL; //node�� key ���� �� link �ʱ�ȭ

	while(search != NULL){
		if(search->key >= key){//�Է¹��� key���� ū key�� ���� ��带 ã�� ���
			if(search == h->first)
				insertFirst(h ,key); //�Է¹��� key���� ���� ���� ���
			else{
			node->rlink = search;
			node->llink = search->llink;
			search->llink->rlink = node;
			}//�Է¹��� key���� �߰��� �� ���
			return 0;
		}
		search = search->rlink;
	}//������ �Է¹��� key���� ū key�� ���� ��带 ã�� ������ �� Ż��
	insertLast(h, key);// Ż���� �������� ��� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* search = h->first; //

	if(h->first == NULL){
		printf("����ִ� ����Ʈ�Դϴ�.\n");
		return 1;
	}// ����ִ� ����Ʈ��  ���
	while(search != NULL){
		if(search->key == key){//�ش� key�� ���� ��带 ã�� ���
			if(search == h->first){
				deleteFirst(h);
			}//�ش� key�� ���� ��尡 ù��°�� ���
			else if(search->rlink == NULL){
				deleteLast(h);
			}//�ش� key�� ���� ��尡 �������� ���
			else{
				search->llink->rlink = search->rlink;
				search->rlink->llink = search->llink;
				free(search);
			}//�߰��� �ִ� ����� ���
		return 1;
		}
		search = search->rlink;
	}//�ش� key�� ã�� �� ���� ��� Ż��
	printf("�ش� key=%d�� �����ϴ�.\n",key);
	return 1;
}