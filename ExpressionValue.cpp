#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

//реализация стека через список (ключи - символы)
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

//реализация стека через список (ключи - вещественные)
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

//функция преобразования строки с инфиксной записью выражения в строку с обратной польской записью
char* ToPolish(char* expression)
{
	char* polska;
	polska = new char[100];
	strcpy(polska, ""); //пустая строка для результата
	node *headsym = new node; // стек символов операций
	headsym->key = NULL;
	headsym->prev = NULL;
	int i = 0;
	while (expression[i] != '\0') //считываем строку
	{
		if (isdigit(expression[i]))
		{//числа записываем сразу в итоговую строку
			int t = strlen(polska);
			polska[t] = expression[i];
			if (isdigit(expression[i + 1]) == 0)
			{
				polska[t + 1] = ' '; //после каждого числа записываем пробел: чтобы производить вычисления с многозначными числами
				polska[t + 2] = '\0';
			}
			else polska[t + 1] = '\0';
		}
		else
		{
			if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-')
			{ //если встречаем символ операции, сравниваем его приоритетность с приоритетностью символа в топе стека
				//пока она не выше, выталкиваем элементы из стека в итоговую строку
				while ((expression[i] == '*' && headsym->key == '*') || (expression[i] == '/' && headsym->key == '/')
					|| (expression[i] == '*' && headsym->key == '/') || (expression[i] == '/' && headsym->key == '*')
					|| (expression[i] == '+' && headsym->key == '+') || (expression[i] == '+' && headsym->key == '-')
					|| (expression[i] == '+' && headsym->key == '*') || (expression[i] == '+' && headsym->key == '/') 
					|| (expression[i] == '-' && headsym->key == '+') || (expression[i] == '-' && headsym->key == '-')
					|| (expression[i] == '-' && headsym->key == '*') || (expression[i] == '-' && headsym->key == '/'))
				{
					int t = strlen(polska);
					polska[t] = headsym->key;
					polska[t + 1] = '\0'; //выталкиваем элементы стека в строку с польской записью
					pop(headsym);
				}
				push(headsym, expression[i]); //добавляем символ операции в стек
			}
			else
			{
				if (expression[i] == '(')
					push(headsym, expression[i]); //левую скобку добавляем в стек
				else
				{//встретив правую скобку, выталкиваем элементы из стека вплоть до левой, левую удаляем из стека
					//правую никуда не вносим
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
		int t = strlen(polska); //выталкиваем в строку остаток стека
		polska[t] = headsym->key;
		polska[t + 1] = '\0';
		pop(headsym);
	}
	int t = strlen(polska);
	polska[t + 1] = '\0';
	return polska;
}
//функция, вычисляющая значение выражения строки с ОПЗ
double Calculate(char* polish)
{
	doubnode *head = new doubnode; // используем стек с вещественными ключами
	head->key = NULL;
	head->prev = NULL;
	for (int i = 0; i < strlen(polish); i++)
	{
		if (isdigit(polish[i]))
		{//считываем число до пробела и добавляем в стек
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
		{//встретив символ операций, достаем два верхних элемента стека и применяем операцию к ним, результат добавляем в стек
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