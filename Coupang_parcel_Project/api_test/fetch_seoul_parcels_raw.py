import requests
import json
import os

# 1. 인증키 및 기본 URL 설정
API_KEY = "614661766b31323236324e62704769"
BASE_URL = f"http://openapi.seoul.go.kr:8088/{API_KEY}/json/seoulGuGu/1/100/"

# 2. API 요청
response = requests.get(BASE_URL)

# 3. 응답 확인 및 저장
if response.status_code == 200:
    data = response.json()

    # 4. 저장 경로 지정
    output_dir = "c:/Users/c/Desktop/Data_Structure_class/Coupang_parcel_Project/data"
    os.makedirs(output_dir, exist_ok=True)
    output_path = os.path.join(output_dir, "seoul_parcels_raw.json")

    # 5. 파일 저장
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

    print("✅ 저장 완료 →", output_path)
else:
    print("❌ API 요청 실패:", response.status_code)
