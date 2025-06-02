#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>  // 로케일 추가
#include <windows.h>  // 콘솔 한글 출력 안정화
#include "parser.h"
#include "tree.h"
#include "list.h"

int main() {
    setlocale(LC_ALL, "");  // 한글 출력 안정화
    SetConsoleOutputCP(65001);  // UTF-8 코드페이지 직접 지정

    TreeNode* root = NULL;
    int menu;

    printf("========== 쿠팡 허브센터 시뮬레이터 ==========");

    // 0. 프로그램 시작 시 AWS 정제 데이터 기본 다운로드
    int result = system("curl -s -o ./data/seoul_parcels.json https://seoul-parcel-data.s3.ap-northeast-2.amazonaws.com/seoul_parcels.json");
    if (result != 0) {
        printf("\nAWS JSON 다운로드 실패. 프로그램을 종료합니다.\n");
        return 1;
    }
    printf("\nAWS 정제 JSON 다운로드 완료: seoul_parcels.json\n");
    
    // 다음 코드를 추가하여 다운로드된 데이터를 즉시 로드 --> 1번을 실행하지 않아도 나머지가 실행되려면 로드해야함
    printf("\n초기 AWS 데이터 로드 중...\n");
    load_parcels_from_file("./data/seoul_parcels.json", &root); 
    printf("초기 AWS 데이터 로드 완료.\n");
    
    while (1) {
        printf("\n\n============ 쿠팡 허브센터 시뮬레이터 ============\n");    
        printf("1. 수동 택배 등록 (GUI 실행)\n");
        printf("2. 특정 구의 택배 리스트 조회\n");
        printf("3. 전체 배송 순서 보기 (WOW 우선)\n");
        printf("4. 트리 구조 출력\n");
        printf("5. 종료\n");
        printf(">> 메뉴 선택: ");
        scanf("%d", &menu);
        getchar();  // <-- 이거 추가 (버퍼에 남은 개행 제거)

        if (menu == 1) {
            // PyQt5 GUI 실행
            printf("\n택배 등록 입력창 실행 중...\n");
            system("python ./gui/parcel_simulator.py");

            // 병합 스크립트 실행 (AWS + GUI 데이터)
            printf("\n입력 데이터 병합 중...\n");
            system("python ./api_test/merge_gui_and_base.py");

            // 병합된 JSON 파일 삽입
            load_parcels_from_file("./data/merged_parcels.json", &root);
            printf("\n택배 등록 및 자료구조 반영 완료.\n");

        }
        else if (menu == 2) {
            char gu[50];
            printf("\n조회할 구를 입력하세요 (예: 강남구): ");
            fgets(gu, sizeof(gu), stdin);
            gu[strcspn(gu, "\n")] = 0;  // 줄바꿈 제거
           
            TreeNode* node = find_tree_node(root, gu);
            if (node && node->parcel_list_head) {
                print_parcels(node->parcel_list_head);
            }
            else {
                printf("해당 구에 등록된 택배가 없습니다.\n");
            }

        }
        else if (menu == 3) {
            printf("\n[전체 배송 리스트 (WOW 우선)]\n");
            print_all_parcels(root);

        }
        else if (menu == 4) { //문자열 기준 사전순 정렬
            printf("\n[지역 트리 구조 출력]\n");
            print_tree(root);

        }
        else if (menu == 5) {
            printf("\n프로그램을 종료합니다.\n");
            break;

        }
        else {
            printf("\n잘못된 메뉴입니다. 다시 입력해주세요.\n");
        }
    }

    return 0;
}