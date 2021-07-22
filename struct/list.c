#include <stdio.h>


typedef struct _node {
	int data;
	struct _node *next;
} node;

node* revert(node *head)
{
	node *pre, *cur, *tmp;

	if (head == NULL || head->next == NULL)
		return head;

	pre = head;
	cur = head->next;

	while (cur) {
		tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}

	head->next = NULL;

	return pre;
}


int hascycle(node *head)
{
	int step = 0;
	node *fast, *slow;

	fast = slow = head;

	//如果两个指针相遇，则说明有环
	while (fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;

		if (fast == slow)
			break;
	}

	//得知有环以后，让slow移到链表头，slow和fast每次都移动一步，
	//则再次相遇的的点就是链表的开始点

	/*slow = head;

	while (fast && fast->next) {
		fast = fast->next;
		slow = slow->next;
		step++;

		if (fast == slow)
			return step;
	}*/

	//得知有环以后，让fast移到链表头，且每次移动一步,slow不动，
	//则再次相遇时fast的移动步数就是环长度
	fast = head;
	while (fast && fast->next) {
		fast = fast->next;
		step++;

		if (fast == slow)
			return step;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	node nodes[4];
	node *n = &nodes[0];

	nodes[0].data = 10;
	nodes[0].next = &nodes[1];
	nodes[1].data = 20;
	nodes[1].next = &nodes[2];
	nodes[2].data = 30;
	nodes[2].next = &nodes[1];
	nodes[3].data = 40;
	nodes[3].next = NULL;

	/*while (n) {
		printf("%d\n", n->data);
		n = n->next;
	}

	n = revert(&nodes[0]);

	while (n) {
		printf("%d\n", n->data);
		n = n->next;
	}*/

	printf("%d\n", hascycle(&nodes[0]));

	return 0;
}
