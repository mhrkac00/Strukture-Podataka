#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (1024)

struct _Dir;
typedef struct _Dir* Position;
typedef struct _Dir {
	char name[MAX];
	Position sibling;
	Position child;
}Dir;

struct _Stack;
typedef struct _Stack* StackPosition;
typedef struct _Stack {
	Position directory;
	StackPosition next;
}Stack;


Position insertDir(Position current, Position newElement);
Position CreateDir(char* name);
StackPosition CreateStackElement(Position directory);
int PushStack(StackPosition head, StackPosition newStackElement);
Position PopStack(StackPosition head, Position current);
int PrintDir(Position current);
Position Move(Position current, char* destinationName, StackPosition stack);
int Free(Position root);
int UserInput();

int main()
{
	Dir Root = { .name = "root", .sibling = NULL, .child = NULL };
	Position root = &Root;
	Position current = root;

	Stack Head = { .directory = NULL, .next = NULL };
	StackPosition head = &Head;

	int choice = 0;
	char directoryName[MAX] = { 0 };

	printf("Enter your choice: \n");

	printf("1 - md (Make directory) \n");
	printf("2 - cd dir (Change position to an another directory) \n");
	printf("3 - cd .. (Move to parent directory) \n");
	printf("4 - dir (Print the content of the directory)\n");
	printf("5 - exit \n");

	choice = UserInput();

	while (choice != 5)
	{

		switch (choice)
		{
		case 1:
		{
			printf("Enter the name of the new directory: ");
			scanf(" %s", directoryName);
			Position newDirectory = CreateDir(directoryName);
			current->child = insertDir(current->child, newDirectory);
			break;
		}

		case 2:
		{
			printf("Enter the name of the destination directory: ");
			scanf(" %s", directoryName);
			current = Move(current, directoryName, head);
			break;
		}
		case 3:
		{
			current = PopStack(head, current);
			break;
		}
		case 4:
		{
			printf("/%s: \n", current->name);
			PrintDir(current);
			break;
		}
		default:
		{
			if (choice != 5)
			{
				printf("Wrong input, please try again.\n\n");
				break;
			}
		}
		}
		puts("\n");

		printf("1 - md (Make directory) \n");
		printf("2 - cd dir (Change position to an another directory) \n");
		printf("3 - cd .. (Move to parent directory) \n");
		printf("4 - dir (Print the content of the directory)\n");
		printf("5 - exit \n");

		choice = UserInput();

	} 

	Free(root->child);

	return EXIT_SUCCESS;
}

Position insertDir(Position current, Position newEl)
{
	if (!current)
		return newEl;

	if (strcmp(current->name, newEl->name) < 0)
		current->sibling = insertDir(current->sibling, newEl);

	else if (strcmp(current->name, newEl->name) > 0)
	{
		newEl->sibling = current;
		return newEl;
	}
	return current;
}

Position CreateDir(char* name)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(Dir));

	if (!newEl)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, name);
	newEl->sibling = NULL;
	newEl->child = NULL;

	return newEl;
}

StackPosition CreateStackElement(Position current)
{
	StackPosition newEl = NULL;
	newEl = (StackPosition)malloc(sizeof(Stack));

	if (!newEl)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	newEl->directory = current;
	newEl->next = NULL;

	return newEl;
}


int PushStack(StackPosition head, StackPosition newEl)
{
	newEl->next = head->next;
	head->next = newEl;

	return EXIT_SUCCESS;
}

Position PopStack(StackPosition head, Position current)
{
	StackPosition first = NULL;
	first = head->next;

	Position temp = NULL;

	if (!first)
	{
		printf("This directory does not have a parent");
		return current;
	}
	temp = first->directory;

	head->next = first->next;
	free(first);

	return temp;
}

int PrintDir(Position current)
{
	Position temp = current->child;

	while (temp)
	{
		printf(" -%s \n", temp->name);
		temp = temp->sibling;
	}

	return EXIT_SUCCESS;
}

Position Move(Position current, char* name, StackPosition stack)
{
	Position temp = current->child;
	while (temp && strcmp(temp->name, name))
		temp = temp->sibling;

	if (temp == NULL)
	{
		printf("There is no subdirectory with name: %s ", name);
		return current;
	}
	else
	{
		StackPosition newEl = CreateStackElement(current);
		PushStack(stack, newEl);
		return temp;
	}
	return temp;
}

int UserInput()
{
	char Input[MAX] = { 0 };
	int num = 0;
	int status = 0;
	do {

		scanf("%s", Input);
		for (int i = 0; i < strlen(Input); i++)
		{
			status = 0;

			if (!isdigit(Input[i]))
			{
				status = 1;
				printf("Wrong input, please enter a number \n");
				break;
			}
		}

	} while (status == 1);

	num = atoi(Input);

	return num;
}

int Free(Position current)
{
	if (current && current->sibling)
		Free(current->sibling);

	if (current && current->child)
		Free(current->child);

	free(current);

	return EXIT_SUCCESS;
}