
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
void printQueue (QueueNode *head){
	QueueNode *cur = head;
	while (cur != NULL){
		printf("%d ", cur->data->item);
		cur = cur->nextPtr;
	}
	printf("\n");
}


void levelOrderTraversal(BSTNode* root)
{

    /* add your code here */

	// 큐의 head와 tail 포인터 초기화
	QueueNode *head = NULL;
	QueueNode *tail = NULL;

	// 트리의 시작점인 루트를 큐에 넣는다
    // 레벨 순서 순회는 항상 루트부터 시작하므로 root를 enqueue
	enqueue(&head, &tail, root);

	// 큐가 빌때까지 반복
	while (!isEmpty(head)){
		// 큐에서 맨 앞 노드를 꺼낸다 (방문할 노드)
		BSTNode *cur = dequeue(&head, &tail);
		// 현재 노드의 값을 출력 (방문 처리)
		printf("%d ", cur->item);
		// 현재 노드의 왼쪽 자식이 있다면 큐에 추가
		if(cur->left != NULL)
			enqueue(&head, &tail, cur->left);
		// 현재 노드의 오른쪽 자식이 있다면 큐에 추가
		if(cur->right != NULL)
			enqueue(&head, &tail, cur->right);
	}
}


///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)   // 현재 노드가 비어있으면 넣을자리
	{
		*node = malloc(sizeof(BSTNode));   // 새 노드 동적 할당

		if (*node != NULL) {        // malloc에 성공하면
			(*node)->item = value;  // 노드의 item 값 세팅
			(*node)->left = NULL;   // 왼쪽, 오른쪽 자식을 초기화한다
			(*node)->right = NULL;
		}
	}
	else  // 현재 노드가 있으면 (어디로 갈까?)
	{
		if (value < (*node)->item)   // 값이 루트보다 작으면 왼쪽에 넣음
		{
			insertBSTNode(&((*node)->left), value);  // 재귀
		}
		else if (value >(*node)->item)  // 값이 루트보다 크면 오른쪽에 넣음
		{
			insertBSTNode(&((*node)->right), value);
		}
		else        // 값이 같으면 아무것도 안함 (중복 방지)
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
