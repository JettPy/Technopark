#include "invoice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main()
{
	size_t n = 0, articulLen = 0;
	printf("Enter number of objects in invoice: ");

	if (scanf("%ld", &n) != 1) {
		printf("Error occured!\n");
		return 1;
	}

	printf("Enter articul length(max 50): ");

	if (scanf("%ld", &articulLen) != 1 || articulLen > 50) {
		printf("Error occured!\n");
		return 1;
	}

	struct object* invoice = NULL;

	invoice = (struct object*)malloc(n * invoiceSize());

	if (invoice == NULL) {
		printf("Memory error occured!\n");
		return 1;
	}

	printf("Enter invoice:\n");

	if (fillingInvoice(invoice, n, articulLen) == 0) {
		printf("Error occured!\n");
		free(invoice);
		return 1;
	}

	size_t command = getCommand();

	if (command == -1) {
		printf("Error occured!\n");
		free(invoice);
		return 1;
	}

	sort(invoice, n, command);

	struct object** twoInvoices = NULL;
	size_t firstSize = 0;
	twoInvoices = splitInvoice(invoice, n, twoInvoices, &firstSize, command);
	if (twoInvoices == NULL) {
		printf("Memory error occured!\n");
		return 1;
	}

	printf("Here two invoices:\nFirst:\n");
	printInvoice(twoInvoices[0], firstSize);
	printf("Second:\n");
	printInvoice(twoInvoices[1], n - firstSize);
	free(twoInvoices[0]);
	free(twoInvoices[1]);
	free(twoInvoices);
	return 0;
}
