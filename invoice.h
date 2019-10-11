#ifndef INVOICE_H_
#define INVOICE_H_

#include <stddef.h>

struct object;

void swiftDown(size_t i, struct object* arr, size_t count, size_t command);

void sort(struct object* arr, int count, int command);

int fillingInvoice(struct object* object_ptr, size_t size, size_t alen);

int getCommand();

struct object** splitInvoice(struct object* from, size_t size, struct object** pare, size_t* sizeof_first, int command);

void printInvoice(struct object* object_ptr, size_t size);

size_t invoiceSize();

#endif // !INVOICE_H_
