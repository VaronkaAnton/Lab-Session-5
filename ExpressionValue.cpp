#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

//ðåàëèçàöèÿ ñòåêà ÷åðåç ñïèñîê (êëþ÷è - ñèìâîëû)
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

//ðåàëèçàöèÿ ñòåêà ÷åðåç ñïèñîê (êëþ÷è - âåùåñòâåííûå)
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

//ôóíêöèÿ ïðåîáðàçîâàíèÿ ñòðîêè ñ èíôèêñíîé çàïèñüþ âûðàæåíèÿ â ñòðîêó ñ îáðàòíîé ïîëüñêîé çàïèñüþ
char* ToPolish(char* expression)
{
	char* polska;
	polska = new char[100];
	strcpy(polska, ""); //ïóñòàÿ ñòðîêà äëÿ ðåçóëüòàòà
	node *headsym = new node; // ñòåê ñèìâîëîâ îïåðàöèé
	headsym->key = NULL;
	headsym->prev = NULL;
	int i = 0;
	while (expression[i] != '\0') //ñ÷èòûâàåì ñòðîêó
	{
		if (isdigit(expression[i]))
		{//÷èñëà çàïèñûâàåì ñðàçó â èòîãîâóþ ñòðîêó
			int t = strlen(polska);
			polska[t] = expression[i];
			if (isdigit(expression[i + 1]) == 0)
			{
				polska[t + 1] = ' '; //ïîñëå êàæäîãî ÷èñëà çàïèñûâàåì ïðîáåë: ÷òîáû ïðîèçâîäèòü âû÷èñëåíèÿ ñ ìíîãîçíà÷íûìè ÷èñëàìè
				polska[t + 2] = '\0';
			}
			else polska[t + 1] = '\0';
		}
		else
		{
			if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-')
			{ //åñëè âñòðå÷àåì ñèìâîë îïåðàöèè, ñðàâíèâàåì åãî ïðèîðèòåòíîñòü ñ ïðèîðèòåòíîñòüþ ñèìâîëà â òîïå ñòåêà
				//ïîêà îíà íå âûøå, âûòàëêèâàåì ýëåìåíòû èç ñòåêà â èòîãîâóþ ñòðîêó
				while ((expression[i] == '*' && headsym->key == '*') || (expression[i] == '/' && headsym->key == '/')
					|| (expression[i] == '*' && headsym->key == '/') || (expression[i] == '/' && headsym->key == '*')
					|| (expression[i] == '+' && headsym->key == '+') || (expression[i] == '+' && headsym->key == '-')
					|| (expression[i] == '+' && headsym->key == '*') || (expression[i] == '+' && headsym->key == '/') 
					|| (expression[i] == '-' && headsym->key == '+') || (expression[i] == '-' && headsym->key == '-')
					|| (expression[i] == '-' && headsym->key == '*') || (expression[i] == '-' && headsym->key == '/'))
				{
					int t = strlen(polska);
					polska[t] = headsym->key;
					polska[t + 1] = '\0'; //âûòàëêèâàåì ýëåìåíòû ñòåêà â ñòðîêó ñ ïîëüñêîé çàïèñüþ
					pop(headsym);
				}
				push(headsym, expression[i]); //äîáàâëÿåì ñèìâîë îïåðàöèè â ñòåê
			}
			else
			{
				if (expression[i] == '(')
					push(headsym, expression[i]); //ëåâóþ ñêîáêó äîáàâëÿåì â ñòåê
				else
				{//âñòðåòèâ ïðàâóþ ñêîáêó, âûòàëêèâàåì ýëåìåíòû èç ñòåêà âïëîòü äî ëåâîé, ëåâóþ óäàëÿåì èç ñòåêà
					//ïðàâóþ íèêóäà íå âíîñèì
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
		int t = strlen(polska); //âûòàëêèâàåì â ñòðîêó îñòàòîê ñòåêà
		polska[t] = headsym->key;
		polska[t + 1] = '\0';
		pop(headsym);
	}
	int t = strlen(polska);
	polska[t + 1] = '\0';
	return polska;
}
//ôóíêöèÿ, âû÷èñëÿþùàÿ çíà÷åíèå âûðàæåíèÿ ñòðîêè ñ ÎÏÇ
double Calculate(char* polish)
{
	doubnode *head = new doubnode; // èñïîëüçóåì ñòåê ñ âåùåñòâåííûìè êëþ÷àìè
	head->key = NULL;
	head->prev = NULL;
	for (int i = 0; i < strlen(polish); i++)
	{
		if (isdigit(polish[i]))
		{//ñ÷èòûâàåì ÷èñëî äî ïðîáåëà è äîáàâëÿåì â ñòåê
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
		{//âñòðåòèâ ñèìâîë îïåðàöèé, äîñòàåì äâà âåðõíèõ ýëåìåíòà ñòåêà è ïðèìåíÿåì îïåðàöèþ ê íèì, ðåçóëüòàò äîáàâëÿåì â ñòåê
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

void assert(char* key, double ans)
{
	if (Calculate(ToPolish(key)) == ans)
		cout << "OK" << endl;
	else cout << "FAIL" << endl;
}

int main()
{
	assert("2+4/2", 4);
	assert("3-2+(6+18)*2-30", 19);
	assert("2+1*2*3*4*5*(7-6)-100", 22);
	assert("9999/(1+2+3+3)", 1111);
	assert("243-5*32/(84-82)", 163);
	assert("(10000/(10*10*10)-8)*(3+60)", 126);
	return 0;
}
