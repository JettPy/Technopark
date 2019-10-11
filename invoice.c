#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct object
{
	char articul[21];
	size_t count;
	int price;
	int weight;
};

void swiftDown(size_t i, struct object* arr, size_t count, size_t command)
{
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;
	size_t largest = i;
	if (command == 1) {
		if (left < count && arr[left].price > arr[i].price) {
			largest = left;
		}
		if (right < count && arr[right].price > arr[largest].price) {
			largest = right;
		}
	}
	else {
		if (left < count && arr[left].weight > arr[i].weight) {
			largest = left;
		}
		if (right < count && arr[right].weight > arr[largest].weight) {
			largest = right;
		}
	}
	if (largest != i) {
		struct object tmp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = tmp;
		swiftDown(largest, arr, count, command);
	}
}

void sort(struct object* arr, int count, int command)
{
	int heapSize = count;
	for (int i = count / 2 - 1; i >= 0; i--) {
		swiftDown(i, arr, count, command);
	}
	while (heapSize > 1) {
		struct object result = arr[0];
		arr[0] = arr[heapSize - 1];
		arr[heapSize - 1] = result;
		--heapSize;
		swiftDown(0, arr, heapSize - 1, command);
	}
}

int fillingInvoice(struct object* object_ptr, size_t size, size_t alen)
{
	for (size_t i = 0; i < size; ++i) {
		getchar();
		if (fgets(object_ptr[i].articul, alen + 1, stdin) == NULL) {
			return 0;
		}
		if (scanf("%ld %d %d", &object_ptr[i].count, &object_ptr[i].price, &object_ptr[i].weight) != 3) {
			return 0;
		}
	}
	return 1;
}

int getCommand()
{
	int command;
	printf("Select command:\n1 - price\n2 - weight\n");
	if (scanf("%d", &command) != 1 || (command != 1 && command != 2)) {
		return -1;
	}
	else {
		return command;
	}
}

size_t invoiceSize()
{
	return sizeof(struct object);
}

struct object** splitInvoice(struct object* from, size_t size, struct object** pare, size_t* sizeof_first, int command)
{
	struct object* tmp_invoice1 = NULL;
	struct object* tmp_invoice2 = NULL;

	tmp_invoice1 = (struct object*)malloc(size * invoiceSize());
	tmp_invoice2 = (struct object*)malloc(size * invoiceSize());
	int sum1 = 0, sum2 = 0;
	size_t size1 = 0, size2 = 0;

	switch (command) {

	case 1:

		for (size_t i = size; i != 0; --i) {
			if (abs(sum1 + from[i - 1].price - sum2) < abs(sum2 + from[i - 1].price - sum1)) {
				tmp_invoice1[size1] = from[i - 1];
				++size1;
				sum1 += from[i - 1].price;
			}
			else {
				tmp_invoice2[size2] = from[i - 1];
				++size2;
				sum2 += from[i - 1].price;
			}
		}
		break;

	case 2:

		for (size_t i = size; i != 0; --i) {
			if (abs(sum1 + from[i - 1].weight - sum2) < abs(sum2 + from[i - 1].weight - sum1)) {
				tmp_invoice1[size1] = from[i - 1];
				++size1;
				sum1 += from[i - 1].weight;
			}
			else {
				tmp_invoice2[size2] = from[i - 1];
				++size2;
				sum2 += from[i - 1].weight;
			}
		}
		break;
	}

	*sizeof_first = size1;
	pare = (struct object**)malloc(2 * invoiceSize());
	if (pare != NULL) {
		pare[0] = (struct object*)realloc(tmp_invoice1, size1 * invoiceSize());
		pare[1] = (struct object*)realloc(tmp_invoice2, size2 * invoiceSize());

		free(from);

		if (pare[0] == NULL && size1 != 0 || pare[1] == NULL && size2 != 0) {
			printf("Memory error occured!\n");
			free(pare[0]);
			free(pare[1]);
			return NULL;
		}
	}

	return pare;

}

void printInvoice(struct object* object_ptr, size_t size)
{
	if (size == 0) {
		printf("NO data\n");
	}
	else {
		for (size_t i = 0; i < size; ++i) {
			printf("%s %ld %d %d\n", object_ptr[i].articul, object_ptr[i].count, object_ptr[i].price, object_ptr[i].weight);
		}
	}
}
