#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

//���������� ����� ����� ������ (����� - �������)
struct node
{
	int key;
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

//���������� ����� ����� ������ (����� - ������������)
struct doubnode
{
	double key;
	doubnode* prev;
};
void doubpush(doubnode* head, double key)
{
	doubnode* temp = new doubnode;
	*temp = *head;
	head->key = key;
	head->prev = temp;
}
void doubpop(doubnode* head)
{
	doubnode* temp = new doubnode;
	*temp = *head->prev;
	head->key = temp->key;
	head->prev = temp->prev;
}

//������� �������������� ������ � ��������� ������� ��������� � ������ � �������� �������� �������
char* ToPolish(char* expression)
{
	char* polska;
	polska = new char[100];
	strcpy(polska, ""); //������ ������ ��� ����������
	node *headsym = new node; // ���� �������� ��������
	headsym->key = NULL;
	headsym->prev = NULL;
	int i = 0;
	while (expression[i] != '\0') //��������� ������
	{
		if (isdigit(expression[i]))
		{//����� ���������� ����� � �������� ������
			int t = strlen(polska);
			polska[t] = expression[i];
			if (isdigit(expression[i + 1]) == 0)
			{
				polska[t + 1] = ' '; //����� ������� ����� ���������� ������: ����� ����������� ���������� � ������������� �������
				polska[t + 2] = '\0';
			}
			else polska[t + 1] = '\0';
		}
		else
		{
			if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-')
			{ //���� ��������� ������ ��������, ���������� ��� �������������� � ��������������� ������� � ���� �����
				//���� ��� �� ����, ����������� �������� �� ����� � �������� ������
				while ((expression[i] == '*' && headsym->key == '*') || (expression[i] == '/' && headsym->key == '/')
					|| (expression[i] == '*' && headsym->key == '/') || (expression[i] == '/' && headsym->key == '*')
					|| (expression[i] == '+' && headsym->key == '+') || (expression[i] == '+' && headsym->key == '-')
					|| (expression[i] == '+' && headsym->key == '*') || (expression[i] == '+' && headsym->key == '/') 
					|| (expression[i] == '-' && headsym->key == '+') || (expression[i] == '-' && headsym->key == '-')
					|| (expression[i] == '-' && headsym->key == '*') || (expression[i] == '-' && headsym->key == '/'))
				{
					int t = strlen(polska);
					polska[t] = headsym->key;
					polska[t + 1] = '\0'; //����������� �������� ����� � ������ � �������� �������
					pop(headsym);
				}
				push(headsym, expression[i]); //��������� ������ �������� � ����
			}
			else
			{
				if (expression[i] == '(')
					push(headsym, expression[i]); //����� ������ ��������� � ����
				else
				{//�������� ������ ������, ����������� �������� �� ����� ������ �� �����, ����� ������� �� �����
					//������ ������ �� ������
					while (headsym->key != '(')
					{
						int t = strlen(polska);
						polska[t] = headsym->key;
						polska[t + 1] = '\0';
						pop(headsym);
					}
					pop(headsym);
				}
			}
		}
		i++;
	}

	while (headsym ->key != NULL)
	{
		int t = strlen(polska); //����������� � ������ ������� �����
		polska[t] = headsym->key;
		polska[t + 1] = '\0';
		pop(headsym);
	}
	int t = strlen(polska);
	polska[t + 1] = '\0';
	return polska;
}
//�������, ����������� �������� ��������� ������ � ���
double Calculate(char* polish)
{
	doubnode *head = new doubnode; // ���������� ���� � ������������� �������
	head->key = NULL;
	head->prev = NULL;
	for (int i = 0; i < strlen(polish); i++)
	{
		if (isdigit(polish[i]))
		{//��������� ����� �� ������� � ��������� � ����
			int j = 1;
			double num = 0.;
			num = (double) (polish[i] - 48);
			while (isdigit(polish[i + j]))
			{
				num *= 10.;
				num += (double) (polish[i + j] - 48);
				j++;
			}
			doubpush (head, num);
			i += j;
		}

		else
		{//�������� ������ ��������, ������� ��� ������� �������� ����� � ��������� �������� � ���, ��������� ��������� � ����
			double temp1 = head->key;
			doubpop(head);
			double temp2 = head->key;
			doubpop(head);
			switch (polish[i])
			{
			case '*':
			{
				doubpush (head, temp2 * temp1);
				break;
			}
			case '+':
			{
				doubpush(head, temp2 + temp1);
				break;
			}
			case '-':
			{
				doubpush(head, temp2 - temp1);
				break;
			}
			case '/':
			{
				doubpush(head, temp2 / temp1);
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
	return head->key;
}

int main()
{
	return 0;
}