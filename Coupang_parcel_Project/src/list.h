#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct Parcel {
    int id;
    char name[50];            // ������ �̸�
    char address[100];        // ��ü �ּ�
    bool is_wow;              // WOW ȸ�� ����
    struct Parcel* next;      // ���� ����Ʈ ���� ������
} Parcel;

Parcel* create_parcel(const char* name, const char* address, bool is_wow);
void insert_parcel(Parcel** head, Parcel* new_parcel);
void print_parcels(Parcel* head);

#endif
