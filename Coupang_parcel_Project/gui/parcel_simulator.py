
from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QLineEdit,
    QVBoxLayout, QHBoxLayout, QRadioButton, QSpinBox, QMessageBox
)
import json
import sys
import os

class ParcelSimulator(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("쿠팡 허브센터 시뮬레이터")
        self.setGeometry(300, 300, 400, 300)

        # 이름 입력
        self.name_label = QLabel("수취인 이름:")
        self.name_input = QLineEdit()

        # 주소 입력
        self.address_label = QLabel("주소 (서울특별시 ○○구 ○○동):")
        self.address_input = QLineEdit()

        # WOW 여부
        self.wow_label = QLabel("WOW 회원 여부:")
        self.wow_yes = QRadioButton("Y")
        self.wow_no = QRadioButton("N")
        self.wow_yes.setChecked(True)
        wow_layout = QHBoxLayout()
        wow_layout.addWidget(self.wow_yes)
        wow_layout.addWidget(self.wow_no)

        # 수량
        self.count_label = QLabel("수량:")
        self.count_input = QSpinBox()
        self.count_input.setMinimum(1)
        self.count_input.setMaximum(100)

        # 버튼
        self.submit_btn = QPushButton("택배 등록")
        self.submit_btn.clicked.connect(self.register_parcels)

        # 레이아웃 구성
        layout = QVBoxLayout()
        layout.addWidget(self.name_label)
        layout.addWidget(self.name_input)
        layout.addWidget(self.address_label)
        layout.addWidget(self.address_input)
        layout.addWidget(self.wow_label)
        layout.addLayout(wow_layout)
        layout.addWidget(self.count_label)
        layout.addWidget(self.count_input)
        layout.addWidget(self.submit_btn)

        self.setLayout(layout)

    def register_parcels(self):
        name = self.name_input.text()
        address = self.address_input.text()
        is_wow = self.wow_yes.isChecked()
        count = self.count_input.value()

        if not name or not address:
            QMessageBox.warning(self, "입력 오류", "이름과 주소를 모두 입력하세요.")
            return

        # 데이터 생성
        parcels = []
        for i in range(count):
            parcel = {
                "id": i + 1,
                "name": name,
                "address": address,
                "is_wow": is_wow
            }
            parcels.append(parcel)

        # 저장
        output_path = os.path.join("..", "data", "seoul_parcels_gui.json")
        with open(output_path, "w", encoding="utf-8") as f:
            json.dump(parcels, f, ensure_ascii=False, indent=2)

        QMessageBox.information(self, "등록 완료", f"{count}건의 택배가 등록되었습니다.")
        self.name_input.clear()
        self.address_input.clear()
        self.count_input.setValue(1)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ParcelSimulator()
    window.show()
    sys.exit(app.exec_())
