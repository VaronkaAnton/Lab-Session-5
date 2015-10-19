#include <iostream>

using namespace std;

struct node
{
	char key;
	node* prev;
};

void push(node* head, char key)
{
	node* temp = new node;
	*temp = *head;
	head->key = key;
	head->prev = temp;
}

void pop(node* head)
{
	node* temp = new node;
	*temp = *head->prev;
	head->key = temp->key;
	head->prev = temp->prev;
}

bool isRightOrder(char str[])
{
	node *head = new node;
	head->key = NULL;
	head->prev = NULL;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		if ((str[i] == '}') || (str[i] == ']') || (str[i] == ')'))
			push(head, str[i]);
		else
		{
			if (((head->key == ')' && str[i] == '(')) || ((head->key == ']' && str[i] == '[')) || ((head->key == '}' && str[i] == '{')))
				pop(head);
			else
				return false;
		}
	}
		return head->key == NULL;
}
int main()
{
	return (0);
}