#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 256

struct _directory;
typedef struct _directory* Position;
typedef struct _directory {
	char name[MAX];
	Position child;
	Position sibling;
}directory;

struct _stack;
typedef struct _stack* StackPosition;
typedef struct _stack {
	Position parent;
	StackPosition next;
}Stack;

Position md(Position current, Position element);
int dir(Position q);
StackPosition CreateStack();
Position CreateDirectory();
int FreeMemory(Position parent);
Position cd_dir(StackPosition stack, Position current);
int push(StackPosition stack, Position current);
StackPosition pop(StackPosition stack);


int main()
{
	int x = 1;
	

	StackPosition Stack = NULL;
	Position Parent = NULL, current = NULL, element = NULL;

	Stack = CreateStack();
	Parent = CreateDirectory();
	current = Parent;

	while (x)
	{
		printf("1- md(Make new directory)\n");
		printf("2 - cd dir(Change position to an another directory)\n");
		printf("3 - cd..(Move to parent directory)\n");
		printf("4 - dir(Print directory)\n");
		printf("0 - exit\n\n");
		scanf("%d", &x);

		switch (x) {
		case 1:
			element = CreateDirectory();
			current->child = md(current->child, element);
			break;
		case 2:
			element = cd_dir(Stack, current);
			current = element;
			break;
		case 3:
			element = pop(Stack);
			if (!element)
				printf("The action is not possible!");
			else
				current = element;
			break;
		case 4:
			dir(current);
			break;
		case 0:
			FreeMemory(Parent);
			break;
		default:
			printf("WRONG INPUT!\nTRY AGAIN: \n");
			break;
		}
	}
	return EXIT_SUCCESS;
}
StackPosition CreateStack()
{
	StackPosition NewEl = NULL;
	NewEl = (StackPosition)malloc(sizeof(Stack));
	if (NewEl == NULL)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}
	NewEl->next = NULL;

	return NewEl;
}

Position CreateDirectory()
{
	Position NewEl = NULL;
	NewEl = (Position)malloc(sizeof(directory));
	if (NewEl == NULL)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}
	NewEl->child = NULL;
	NewEl->sibling = NULL;

	printf("\nEnter directory name: ");
	scanf(" %s", NewEl->name);

	return NewEl;
}


Position md(Position current, Position element)
{
	if (current == NULL)
		return element;

	if (strcmp(current->name, element->name) < 0)
	{
		current->sibling = md(current->sibling, element);
	}
	else if (strcmp(current->name, element->name) > 0)
	{
		element->sibling = current;
		return element;
	}
	else if (strcmp(current->name, element->name) == 0)
	{
		printf("\nThat name already exist!");
	}
	return current;
}
int dir(Position current)
{
	Position pom = NULL;
	printf("%s: \n", current->name);

	if (current->child != NULL)
	{
		pom = current->child;
		while (pom != NULL)
		{
			printf("\t%s\t", pom->name);
			pom = pom->sibling;
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int FreeMemory(Position parent)
{
	if (parent == NULL)
		return EXIT_SUCCESS;
	FreeMemory(parent->sibling);
	FreeMemory(parent->child);
	return EXIT_SUCCESS;
}

Position cd_dir(StackPosition stack, Position current)
{
	Position p = NULL;
	Position pom = NULL;
	char  name[MAX] = { 0 };

	printf("Enter directory name: \n");
	scanf(" %s", name);

	if (current->child == NULL)
	{
		printf("Direktorij je prazan!\n");
		return NULL;
	}
	pom = current->child;
	while (pom != NULL)
	{
		if (strcmp(pom->name, name) == 0)
			p = pom;
		pom = pom->sibling;
	}
	push(stack, current);
	return p;
}
int push(StackPosition stack, Position current)
{
	StackPosition q = NULL;
	q = CreateStack();
	q->parent = current;
	q->next = stack->next;
	stack->next = q;
	return 0;
}

StackPosition pop(StackPosition stack)
{
	StackPosition pom = NULL;
	Position q = NULL;

	if (stack == NULL || stack->next == NULL)
		return NULL;
	pom = stack->next;
	q = pom->parent;
	stack->next = pom->next;

	free(pom);
	return q;
}