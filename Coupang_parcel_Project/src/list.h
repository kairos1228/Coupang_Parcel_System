#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct Parcel {
    int id;
    char name[50];            // 수취인 이름
    char address[100];        // 전체 주소
    bool is_wow;              // WOW 회원 여부
    struct Parcel* next;      // 연결 리스트 다음 포인터
} Parcel;

Parcel* create_parcel(const char* name, const char* address, bool is_wow);
void insert_parcel(Parcel** head, Parcel* new_parcel);
void print_parcels(Parcel* head);

#endif
