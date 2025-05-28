# 📦 Coupang Parcel Project

<aside>


> **쿠팡 허브센터 택배 정렬 시스템**
> 
> 
> *Coupang Hub Parcel Dispatch Manager*
> 

**Tree & Linked List 기반 지역 분류 및 WOW 우선 출고 시뮬레이터**

</aside>
 
자료구조 수업 기말 프로젝트 (2025-1)

---

## 프로젝트 개요

쿠팡 물류센터를 모델로 하여 **지역 기반 트리(Tree)** 와 **WOW 회원 우선 연결 리스트(Singly Linked List)** 구조를 활용한  
C언어 기반 택배 상하차 관리 시뮬레이터 프로젝트입니다.

- **지역 분류**: 시 → 구 구조로 트리(Tree) 구성
- **배송 순서**: WOW 회원 우선 연결 리스트(Linked-List) 삽입
- **공공데이터 연동**: 서울 열린데이터광장 생활물류 OPEN API 사용
- **실시간 클라우드**: `AWS S3`로부터 JSON 정제 데이터 자동 다운로드 및 사용
- **데이터 정제**: Python으로 자치구별 배송량 비율 기반 JSON 생성
- **GUI 구성**:`PyQt5` 기반 기능 UI → 사용자 입력 택배 정보 시뮬레이터 제공

---
## 팀원👨‍💻

- 팀장: 202111044 백승찬 (전체 설계, API 데이터 정제, UI 구성 담당)
- 팀원: 202111042 박준범 (백엔드 + 엔진(C) 구현, 발표 담당)

---
## 폴더 구조

```
Coupang_parcel_Project/
├─ src/💡                    # 핵심 자료구조 엔진 (C)
│  ├─ main.c                        # 전체 흐름 제어 및 메뉴 시스템
│  ├─ tree.c / tree.h               # 지역 분류 트리
│  ├─ list.c / list.h               # WOW 우선순위 연결 리스트
│  └─ parser.c / parser.h           # JSON 파싱 및 구조체 변환
│
├─ gui/🖥️                    # PyQt5 사용자 입력 GUI
│  └─ parcel_simulator.py           # 수동 택배 등록 입력창 (버튼 1번에 연결됨됨)
│
├─ api_test/🌐               # API 연동 및 병합 스크립트
│  ├─ fetch_seoul_parcels_raw.py    # 서울 생활물류 OpenAPI 호출 스크립트
│  ├─ convert_to_seoul_parcels.py   # 정제 데이터 생성
│  └─ merge_gui_and_base.py         # AWS + GUI 입력 데이터 병합
│
├─ data/📦                   # JSON 데이터 저장 위치
│  ├─ seoul_parcels_raw.json        # OPEN-API 원본 raw data (100개 추출)
│  ├─ seoul_parcels.json            # AWS 정제 데이터 (자동 다운로드)
│  ├─ seoul_parcels_gui.json        # PyQt5 GUI 등록 결과
│  └─ merged_parcels.json           # 병합된 최종 JSON (C에서 사용)
│
├─ doc/📝                    # 순서도, 발표자료, 문서 등
│  └─ ... (PPT, 시연 시나리오 등)
│
├─ .gitignore               
├─ Coupang_parcel_Project.sln         
└─ Coupang_parcel_Project.vcxproj      

```

---

## Python 실행 예시

```bash
# OpenAPI로 원본 데이터 받아오기
python api_test/fetch_seoul_parcels_raw.py

# 정제 JSON 생성 (자치구별 배송량 반영)
python api_test/convert_to_seoul_parcels.py
```

결과: `data/seoul_parcels.json` 생성


---

## 사용 데이터 출처

- [서울 생활물류 데이터 (서울 열린데이터광장)](https://data.seoul.go.kr/dataVisual/seoul/SeoulConsumerLogistics.do)
- 공공누리 1유형 (출처표시 후 자유 이용 가능)

---

