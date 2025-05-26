# 📦 Coupang Parcel Project

**쿠팡 택배 상하차 관리 시스템**  
자료구조 수업 기말 프로젝트 (2025-1)

---

## 프로젝트 개요

쿠팡 물류센터를 모델로 하여 **지역 기반 트리(Tree)** 와 **WOW 회원 우선 연결 리스트(Singly Linked List)** 구조를 활용한  
택배 상하차 관리 시뮬레이터 프로젝트입니다.

- **지역 분류**: 시 → 구 구조로 트리 구성
- **배송 순서**: WOW 회원 우선 연결 리스트 삽입
- **공공데이터 연동**: 서울 열린데이터광장 생활물류 API 사용
- **데이터 정제**: Python으로 자치구별 배송량 비율 기반 JSON 생성

---
## 팀원👨‍💻

- 팀장: 202111044 백승찬 (전체 설계, API 데이터 정제, UI 구성 담당)
- 팀원: 202111042 박준범 (백엔드 + 엔진(C) 구현, 발표 담당)

---
## 폴더 구조

```
Coupang_parcel_Project/
├─ data/
│  ├─ seoul_parcels_raw.json            # 공공 API 원본 데이터
│  ├─ seoul_parcels.json                # 정제된 100건 샘플 (API 비율 반영)
│  └─ seoul_parcels_gui.json            # GUI 결과 저장 파일
├─ api_test/
│  ├─ fetch_seoul_parcels_raw.py        # OpenAPI 호출 스크립트
│  └─ convert_to_seoul_parcels.py       # 정제 데이터 생성 스크립트
├─ src/
│  ├─ main.c                            # 프로그램 시작점, 메뉴 구성 및 실행 흐름 제어
│  ├─ parser.c / parser.h               # JSON 파일 파싱 → Parcel 구조체 생성 및 트리 삽입
│  ├─ tree.c / tree.h                   # 지역명(구 단위) 기반 이진 탐색 트리 생성 및 탐색
│  ├─ list.c / list.h                   # WOW 우선순위 기반 연결 리스트 삽입 및 출력
├─ doc/
│  └─ 순서도, 발표자료 등
├─ gui/                           
│  └─ parcel_simulator.py               # PyQt5 GUI 코드
└─ README.md

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

## 향후 구현 예정

- [ ] `TreeNode` 기반 구 단위 트리 구조 생성
- [ ] `Parcel` 삽입 (WOW 우선 삽입 리스트)
- [ ] `load_parcels_from_file()`로 JSON 자동 삽입
- [ ] 콘솔 메뉴 구현 (등록, 조회, 배송 등)

---

## 사용 데이터 출처

- [서울 생활물류 데이터 (서울 열린데이터광장)](https://data.seoul.go.kr/dataVisual/seoul/SeoulConsumerLogistics.do)
- 공공누리 1유형 (출처표시 후 자유 이용 가능)

---

