#define _CRT_SEUCRE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
	char data;
	int element;
	struct Node* next;
}Node;

typedef struct {	
	Node* top;
}Stack;
void push(Stack* node, int num) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->element = num;
	tmp->next = node->top;
	node->top = tmp;
}
void push_char(Stack* node, char num) {
	
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = num;
	tmp->next = node->top;
	node->top = tmp;
}
void init(Stack* s)
{
	s->top = NULL;
}

int pop(Stack* node) {
	Node* tmp = node->top;
	printf("%d\n", tmp->element);
	int element = tmp->element;
	node->top = node->top->next;
	free(tmp);
	return element;
}
char pop_char(Stack* node) {
	if (node->top == NULL) {
		printf("Stack is empty\n");
		return '\0';
	}
	Node* tmp = node->top;
	char popped_data = tmp->data;
	node->top = tmp->next;
	free(tmp);
	return popped_data;
}

void print_stack_reverse(Stack* s, Node* p) {
	if (p == NULL)
		return;
	print_stack_reverse(s, p->next);
	printf("%d ", p->element);
}

void print_stack(Stack* s) {
	print_stack_reverse(s, s->top);
	printf("\n");
}
void print(Stack* s) {
	printf("%d\n", s->top->element);
}

int isPalindrome(Stack* stack, char word[], int length) {
	int i;
	for (i = 0; i < length / 2; i++) {
		if (isalpha(word[i])) {
			push_char(stack, tolower(word[i]));
		}
	}
	if (length % 2 == 1) {
		i++;
	}

	while (i < length) {
		char character = pop_char(stack);
			
		if (character != word[i]) {
			return 0;
		}
		i++;
	}
	return 1;
}
int balanced(Stack* stack, char word[], int length) {
	int j;
	char tp;
	for (j = 0; j < length; j++) {
		if (word[j] == '{' || word[j] == '[' || word[j] == '(') {
			push_char(stack, word[j]);
		}
		if (word[j] == '}' || word[j] == ']' || word[j] == ')') {
			tp = pop_char(stack);
			if (word[j] == '}' && tp == '{') {
				continue;
			}
			else if (word[j] == ']' && tp == '[') {
				continue;
			}
			else if (word[j] == ')' && tp == '(') {
				continue;
			}
			return 0;
		}
	}

	return 1;
}

int main(int argc, char* argv[])
{

	FILE* input_file;
	FILE* output_file;
	char operation;
	int a, b, c;
	char line[1000];
	char nextline[1000];
	long int current_position;


	input_file = fopen(argv[1], "r");



	output_file = fopen(argv[2], "w");


	while (fgets(line, sizeof(line), input_file) != NULL) {

		current_position = ftell(input_file);


		if (fgets(nextline, sizeof(nextline), input_file)) {

			fseek(input_file, current_position, SEEK_SET);

			if (line[0] == 'H') {
				Stack s;
				init(&s);
				sscanf(line, "%d",&b);
				push(&s,b);
				fprintf(output_file, "%d\n", c);
			}
			else if (line[0] == 'O') {
				sscanf(line, "%c %d %d", &operation, &a, &b);
				c = a - b;
				fprintf(output_file, "%d\n", c);
			}
			else if (line[0] == 'T') {
				sscanf(line, "%c %s", &operation, line);

				for (int i = strlen(line) - 1; i >= 0; i--) {
					fprintf(output_file, "%c", line[i]);
				}
				fprintf(output_file, "\n");
			}
			else if (line[0] == 'P') {
				int p = 0;
				char word[10000];
				scanf_s("%s", word, sizeof(word));
				Stack s;
				init(&s);
				for (int i = 0; i < strlen(word); i++) {
					if (isalpha(word[i])) {
						p++;
					}
				}
				if (isPalindrome(&s, word, p)) {
					printf("T\n");
				}
				else {
					printf("F\n");
				}
			}

			else if (line[0] == 'B') {
				int p = 0;
				char word[10000];
				scanf_s("%s", word, sizeof(word));
				Stack s;
				init(&s);
				for (int i = 0; i < strlen(word); i++) {
					if (word[i] == '{' || word[i] == '[' || word[i] == '(' || word[i] == '}' || word[i] == ']' || word[i] == ')') {
						p++;
					}
				}
				if (balanced(&s, word, p)) {
					printf("T\n");
				}
				else {
					printf("F\n");
				}
			}
		}

		else {
			if (line[0] == 'H') {
				sscanf(line, "%c %d %d", &operation, &a, &b);
				c = a + b;
				fprintf(output_file, "%d\n", c);
			}
			else if (line[0] == 'O') {
				sscanf(line, "%c %d %d", &operation, &a, &b);
				c = a - b;
				fprintf(output_file, "%d\n", c);
			}
			else if (line[0] == 'T') {
				sscanf(line, "%c %s", &operation, line);

				for (int i = strlen(line) - 1; i >= 0; i--) {
					fprintf(output_file, "%c", line[i]);
				}
				fprintf(output_file, "\n");
			}
			else if (line[0] == 'P') {

			}
			else if (line[0] == 'B') {

			}
		}

	}
	fclose(input_file);
	fclose(output_file);

	return 0;
}

