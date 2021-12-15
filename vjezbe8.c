#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int number;
	Position left;
	Position right;

}tree;

Position InsertNewElement(int element, Position root);
Position CreateNewElement(int element);
int PrintInOrder(Position root);
int PrintPreOrder(Position root);
int PrintPostOrder(Position root);
int PrintLevelOrder(Position root);
int PrintCurrentLevel(Position root, int level);
int TreeDepth(Position current);
Position FindElement(int element, Position root);
Position FindMin(Position root);
Position DeleteElement(int element, Position root);



int main(int argc, char** argv)
{

	Position root = NULL;
	Position temp = NULL;

	int input = 0;
	int element = 0;

	printf("Chose an action: \n");
	printf("1 - Insert Element\n");
	printf("2 - Print In Order\n");
	printf("3 - Print Pre Order\n");
	printf("4 - Print Post Order\n");
	printf("5 - Find Element\n");
	printf("6 - Delete Element\n");
	printf("0 - Exit\n");



	scanf("%d", &input);

	while (input != 0) {

		switch (input)
		{
		case 1:
			printf("Which element do you want to insert: ");
			scanf("%d", &element);
			root = InsertNewElement(element, root);
			break;
		case 2:
			PrintInOrder(root);
			break;
		case 3:
			PrintPreOrder(root);
			break;
		case 4:
			PrintPostOrder(root);
			break;
		case 5:
			PrintLevelOrder(root);
		case 6:
			printf("Which element do you want to fint: ");
			scanf("%d", &element);
			temp = FindElement(element, root);
			if (!temp) {
				printf("Element is found\n");
			}
			else {
				printf("Element is not found\n");
			}
			break;
		case 7:
			printf("Which element do you want to delete: ");
			scanf("%d", &element);
			root = DeleteElement(element, root);
		case 0:
			break;
		default:
			printf("Wrong input!\n");
		}

		printf("Chose an action: \n");
		printf("1 - Insert Element\n");
		printf("2 - Print In Order\n");
		printf("3 - Print Pre Order\n");
		printf("4 - Print Post Order\n");
		printf("5 - Find Element\n");
		printf("6 - Delete Element\n");
		printf("0 - Exit\n");


		scanf("%d", &input);

	} 

	

	

	return EXIT_SUCCESS;
}


Position InsertNewElement(int element, Position root)
{
	Position current = NULL;
	current = root;
	Position newEl = NULL;

	if (current == NULL)
	{
		newEl = CreateNewElement(element);
		return newEl;
	}
	else if (element < current->number)
		current->left = InsertNewElement(element, current->left);
	else if (element > current->number)
		current->right = InsertNewElement(element, current->right);
	else
		free(newEl);

	return current;


}

Position CreateNewElement(int element)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(tree));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newEl->number = element;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;

}

int PrintInOrder(Position root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		printf("%d ", current->number);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}

int PrintPreOrder(Position root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		printf("%d ", current->number);
		PrintInOrder(current->left);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}




int PrintPostOrder(Position root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		PrintInOrder(current->right);
		printf("%d ", current->number);
	}

	return EXIT_SUCCESS;
}

int PrintLevelOrder(Position root)
{
	int h = TreeDepth(root);
	int i = 1;
	while (i <= h)
	{
		PrintCurrentLevel(root, i);
		i++;
	}

	return EXIT_SUCCESS;
}


int PrintCurrentLevel(Position root, int level)
{
	Position current = NULL;
	current = root;

	if (root == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", root->number);
	else if (level > 1) {
		PrintCurrentLevel(root->left, level - 1);
		PrintCurrentLevel(root->right, level - 1);
	}
}

int TreeDepth(Position current)
{
	int LeftH = 0;
	int RightH = 0;

	if (current == NULL)
		return 0;
	else {
		LeftH = TreeDepth(current->left);
		RightH = LeftH = TreeDepth(current->left);
		(current->right);

		if (LeftH > RightH)
			return (LeftH + 1);
		else
			return (RightH + 1);
	}

	return EXIT_SUCCESS;
}

Position FindElement(int element, Position root)
{
	Position current = NULL;
	current = root;

	if (current == NULL)
	{
		return NULL;
	}
	else if (element < current->number)
		return FindElement(element, current->left);

	else if (element > current->number)
		return FindElement(element, current->right);
	else
		return current;

}

Position FindMin(Position root)
{

	Position current = NULL;
	current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

Position DeleteElement(int element, Position root)
{
	Position temp = NULL;
	Position current = NULL;
	current = root;

	if (current == NULL)
		printf("Elementa nema unutar stabla!\n");

	else if (current->number > element)
		current->left = DeleteElement(element, current->left);

	else if (current->number < element)
		current->right = DeleteElement(element, current->right);

	else if (current->left != NULL && current->right != NULL) {

		temp = FindMin(current->right);
		current->number = temp->number;
		current->right = DeleteElement(current->number, current->right);
	}

	else {

		temp = current;

		if (current->left == NULL)
			current = current->right;

		else
			current = current->left;

		free(temp);
	}

	return current;
}



