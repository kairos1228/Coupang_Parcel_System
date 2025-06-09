#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <io.h>
#include "tree.h"
#include "list.h"
#include "parser.h"

int main() {
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(65001);
    SetConsoleCP(CP_UTF8);

    TreeNode* root = NULL;

    printf("========== 쿠팡 허브센터 시뮬레이터 ==========\n");

	// AWS S3 데이터셋 로드 
    printf("🌐 AWS JSON 다운로드 및 초기 데이터 로딩 중...\n");
    system("python ./api_test/download_dataset_json.py");
    load_parcels_from_file("./data/seoul_parcels.json", &root);

    int choice;
    do {
        printf("\n[메뉴 선택]\n");
        printf("🚚 1. 수동 택배 등록 (GUI 실행)\n");
        printf("🚚 2. 특정 구의 택배 조회\n");
        printf("🚚 3. 전체 배송 리스트 출력 (WOW 우선)\n");
        printf("🚚 4. 지역 트리 출력 (중위순회)\n");
        printf("🚚 5. 종료\n");
        printf("입력: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("택배 등록 입력창 실행 중...\n");
            system("python ./gui/parcel_simulator.py");
            // GUI 등록 → 병합 + AWS 업로드까지 파이썬에서 자동 실행됨
            // 이후 최신 merged 파일 다시 불러오기
            printf("병합 완료 후 반영 중...\n");
            free_tree(root);
            root = NULL;
            load_parcels_from_file("./data/merged_parcels.json", &root);
        }
        else if (choice == 2) {
            char gu[100];
            printf("조회할 구 이름 입력 (예: 강서구): ");
            scanf("%s", gu);
            TreeNode* gu_node = find_tree_node(root, gu);

            if (gu_node) {
                printf("\n📦 %s의 택배 목록:\n", gu);
                print_parcels(gu_node->parcel_list_head);
            }
            else {
                printf("해당 구를 찾을 수 없습니다.\n");
            }
        }
        else if (choice == 3) {
            printf("전체 배송 리스트 (WOW 우선):\n");
            print_all_parcels(root);
        }
        else if (choice == 4) {
            printf("지역 트리 출력 (중위 순회):\n");
            print_tree(root);
        }
        else if (choice == 5) {
            printf("프로그램을 종료합니다.\n");
        }
        else {
            printf("❌ 잘못된 입력입니다. 다시 선택하세요.\n");
        }

    } while (choice != 5);

    free_tree(root);
    return 0;
}
