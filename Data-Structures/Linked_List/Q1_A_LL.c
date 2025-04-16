//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// item : 노드 안에 저장된 값
// next : 다음 노드를 가리키는 포인터
typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

// *head : 첫 번째 노드를 가리키는 포인터가 존재한다
typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
// 선언부. * 포인터로 전달해서 원본 리스트를 바꾸겠다. 작업할 값을 매개변수 int로 넘긴다. 
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;            // 링크드 리스트를 ll으로 선언
	int c, i, j;              // c, i, j 인트
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 값을 주면 알아서 적절한 인덱스의 위치에 넣는다
int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	// 새 노드 하나를 동적으로 할당(malloc)해서 거기에 item을 저장하고 리스트 안에 노드로 연결한다

	// 노드(구조체)를 가리켜야 하는 변수를 포인터로 선언한다
	ListNode *pre, *cur, *newNode;

	// 리스트가 비어있음
	if (ll->head == NULL){
		newNode = malloc(sizeof(ListNode));  // 넣을 값만큼 메모리 할당
		newNode->item = item;    // 값 넣어
		newNode->next = NULL;    // next 노드를 널로 연결해
		ll->head = newNode;      // 새 노드를 헤드로 만들어
		ll->size++;              // 사이즈 증가시켜
		return 0;
	}
	// 리스트가 비었는지 확인 -> 헤드로 연결
	// 아니면 어디에 넣을지 찾기 -> head를 순회하면서 item 보다 큰 값을 찾고, 그 앞에 끼운다.
	// 끝까지 돌았는데도 작은 값이 없다 -> 맨 끝에 넣는다
	// 사이즈 증가

	pre = NULL;      //임시 저장 변수 : 현재 노드의 이전을 가리킬 포인터
	cur = ll->head;

	// 현재 노드가 존재하고, 현재 노드 값이 삽입할 값보다 작을 때 이동
	while (cur != NULL && cur->item < item){
		pre = cur;        // 임시에 이전값을 넣고
		cur = cur->next;  // 그 다음 노드 탐색
	}

	// 새 노드 생성
	newNode = malloc(sizeof(ListNode));    //넣을 값만큼 메모리 할당
	newNode-> item = item;   // 값 넣어
	newNode->next = cur;     // 이전에 있던 값을 next에 붙여

	if (pre == NULL){       // 삽입할 곳이 헤드임 (노드 없어)
		ll->head = newNode; // 새 값이 헤드
	} else {                // 중간 또는 끝에 삽입 (노드 있어)
		pre->next = newNode;  // 이전 노드의 next를 새 노드 할당 (pre -> newNode -> cur)
	}
	ll->size++;             // 사이즈 증가
	return 0;

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	// ll = Null or index가 0보다 작음 or index가 리스트 크기보다 크거나
	// 즉 유효하지 않은 index이면, 리턴 -1 
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	// 리스트의 헤드가 NULL or index = 0이면 (리스트가 없음)
	if (ll->head == NULL || index == 0){
		cur = ll->head;   // 임시값 cur에 헤드를 저장해. cur은 NULL
		ll->head = malloc(sizeof(ListNode));  // 새로운 노드를 생성하고 걔가 head
		ll->head->item = value;   // 새 노드에 값을 할당
		ll->head->next = cur;     // 새 노드의 next와 연결. 근데 여기도 값이 없으니까 일단 NULL
		ll->size++;               // 넣은 노드의 크기만큼 리스크 크기 증가
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// pre는 index -1 위치의 노드(새 노드를 넣을곳의 바로 이전 노드)
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;  // cur 임시값은 pre(넣을 위치의 노드)의 next
		pre->next = malloc(sizeof(ListNode));   // 새로운 노드를 pre의 next에 생성
		pre->next->item = value;  // 값 할당
		pre->next->next = cur;    // 노드의 옆의 옆이 cur (넣을 값)
		ll->size++;  // 넣은만큼 사이즈 증가
		return 0;
	}
	// head -> node1 -> node2 (pre) -> 새 노드 -> node3 (cur) -> NULL

	return -1; // 노드를 못찾을때 -1을 반환. (에러 처리)
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	// 유효하지 않은 인덱스이면 리턴 -1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	// 첫번째 인덱스를 삭제한다 (head를 삭제한다)
	if (index == 0){
		cur = ll->head->next;  // head의 next를 임시로 cur에 저장 (next = NULL)
		free(ll->head);  // 헤드 메모리 삭제
		ll->head = cur;  // 헤드를 next로 바꿈 (NULL)
		ll->size--;   // 삭제한만큼 크기 줄임

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	// 삭제할 곳의 이전 노드를 찾음. 그 값은 NULL이 아님
	if ((pre = findNode(ll, index - 1)) != NULL){

		// 삭제할게 없음
		if (pre->next == NULL)
			return -1;
		// 임시값에 next를 저장 
		cur = pre->next;
		pre->next = cur->next; //삭제할 pre의 next를 cur의 next와 연결해
		free(cur);  // 삭제할 값만큼 메모리 삭제
		ll->size--;  // 사이즈 줄임
		return 0;
	}

	return -1;
}
