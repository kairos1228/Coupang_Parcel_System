import boto3

def download_merged_json():
    s3 = boto3.client('s3')
    try:
        s3.download_file(
            Bucket='seoul-parcel-data',
            Key='merged_parcels.json',
            Filename='./data/merged_parcels.json'
        )
        print("✅ 최신 merged_parcels.json 다운로드 완료")
    except Exception as e:
        print(f"❌ 다운로드 실패: {e}")

if __name__ == "__main__":
    download_merged_json()
