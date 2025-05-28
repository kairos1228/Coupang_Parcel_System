#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"  

// Parcel 구조체 생성 및 초기화
Parcel* create_parcel(const char* name, const char* address, bool is_wow) {
    Parcel* new_parcel = (Parcel*)malloc(sizeof(Parcel));
    if (new_parcel == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }

    new_parcel->name = (char*)malloc(strlen(name) + 1);
    new_parcel->address = (char*)malloc(strlen(address) + 1);
    if (new_parcel->name == NULL || new_parcel->address == NULL) {
        fprintf(stderr, "문자열 메모리 할당 실패\n");
        exit(1);
    }

    strcpy(new_parcel->name, name);
    strcpy(new_parcel->address, address);
    new_parcel->is_wow = is_wow;
    new_parcel->next = NULL;

    return new_parcel;
}

// WOW 우선순위 연결 리스트 삽입
void insert_parcel(Parcel** head, Parcel* new_parcel) {
    if (*head == NULL) {
        *head = new_parcel;
        return;
    }

    Parcel* current = *head;
    Parcel* prev = NULL;

    if (new_parcel->is_wow) {
        // WOW 고객: 마지막 WOW 고객 뒤에 삽입
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
        // 일반 고객: 리스트 끝에 삽입
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_parcel;
    }
}

// 연결 리스트 출력
void print_parcels(Parcel* head) {
    Parcel* current = head;
    while (current != NULL) {
        printf("이름: %s, 주소: %s, %s회원\n",
            current->name,
            current->address,
            current->is_wow ? "WOW" : "일반");
        current = current->next;
    }
}
