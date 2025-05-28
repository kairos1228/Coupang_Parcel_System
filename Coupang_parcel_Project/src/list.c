#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

static int next_id = 1;

Parcel* create_parcel(const char* name, const char* address, bool is_wow) {
    Parcel* new_parcel = (Parcel*)malloc(sizeof(Parcel));
    if (!new_parcel) exit(EXIT_FAILURE);

    new_parcel->id = next_id++;
    new_parcel->name = (char*)malloc(strlen(name) + 1);
    new_parcel->address = (char*)malloc(strlen(address) + 1);

    strcpy(new_parcel->name, name);       // �ܼ��� strcpy ���
    strcpy(new_parcel->address, address);

    new_parcel->is_wow = is_wow;
    new_parcel->next = NULL;

    return new_parcel;
}

// WOW �켱���� ���� ����Ʈ ����
void insert_parcel(Parcel** head, Parcel* new_parcel) {
    if (*head == NULL) {
        *head = new_parcel;
        return;
    }

    Parcel* current = *head;
    Parcel* prev = NULL;

    if (new_parcel->is_wow) {
        // WOW ��: ������ WOW �� �ڿ� ����
        while (current && current->is_wow) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            new_parcel->next = *head;
            *head = new_parcel;
        }
        else {
            new_parcel->next = prev->next;
            prev->next = new_parcel;
        }
    }
    else {
        // �Ϲ� ��: ����Ʈ ���� ����
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_parcel;
    }
}

// ���� ����Ʈ ���
void print_parcels(Parcel* head) {
    Parcel* current = head;
    while (current != NULL) {
        printf("�̸�: %s, �ּ�: %s, %sȸ��\n",
            current->name,
            current->address,
            current->is_wow ? "WOW" : "�Ϲ�");
        current = current->next;
    }
}
