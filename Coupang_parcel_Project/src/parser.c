#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cJSON.h"
#include "list.h"
#include "tree.h"

// BOM 정의 (가독성 상승)
#define UTF8_BOM "\xEF\xBB\xBF"

void load_parcels_from_file(const char* filename, TreeNode** root) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "파일 열기 실패: %s\n", filename);
        return;
    }

    // 파일 크기 구하기
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    // 파일 내용 읽기
    char* data = (char*)malloc(length + 1);
    if (!data) {
        fprintf(stderr, "메모리 할당 실패\n");
        fclose(file);
        return;
    }
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    // BOM 제거 (더 안전하게)
    char* json_data = data;
    if (length >= 3 && memcmp(data, UTF8_BOM, 3) == 0) {
        printf("BOM 발견 → 제거 후 파싱 진행\n");
        json_data = data + 3;
    }

    // cJSON 파싱
    cJSON* json = cJSON_Parse(json_data);
    if (!json) {
        fprintf(stderr, "JSON 파싱 실패\n");
        free(data);
        return;
    }

    int count = cJSON_GetArraySize(json);
    printf("총 %d개의 데이터가 로드되었습니다.\n", count);

    for (int i = 0; i < count; ++i) {
        cJSON* item = cJSON_GetArrayItem(json, i);
        cJSON* name_json = cJSON_GetObjectItem(item, "name");
        cJSON* address_json = cJSON_GetObjectItem(item, "address");
        cJSON* is_wow_json = cJSON_GetObjectItem(item, "is_wow");

        if (!cJSON_IsString(name_json) || !cJSON_IsString(address_json) || !cJSON_IsBool(is_wow_json)) {
            continue;
        }

        const char* name = name_json->valuestring;
        const char* address = address_json->valuestring;
        bool is_wow = cJSON_IsTrue(is_wow_json);

        //  구 추출 안정화 핵심 로직:
        char gu_name[50] = { 0 };
        const char* start = strstr(address, "서울특별시 ");
        if (start != NULL) {
            start += strlen("서울특별시 ");

            // 구 단어만 추출: 첫 번째 공백까지 추출
            const char* space = strchr(start, ' ');
            if (space != NULL) {
                int gu_len = space - start;
                strncpy(gu_name, start, gu_len);
                gu_name[gu_len] = '\0';
            }
            else {
                // 공백이 없다면 전체를 복사 (마지막 주소까지 다 구일 수도 있으므로)
                strncpy(gu_name, start, sizeof(gu_name) - 1);
            }
        }
        else {
            strcpy(gu_name, "기타");
        }

        // Parcel 생성 및 트리에 삽입
        Parcel* p = create_parcel(name, address, is_wow);
        insert_parcel_to_tree(root, gu_name, p);
    }

    cJSON_Delete(json);
    free(data);
}
