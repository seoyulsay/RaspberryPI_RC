# 원격 사료 배급기 - 봉자밥
장시간 집을 비울때 반려견의 먹이 급여 문제 고민을 해결해주는 원격 조종 배급기 입니다.
카카오톡, 라즈베리파이를 이용합니다.
# 프로젝트 정보
## 프로젝트 기간
2017.10.16 ~ 2017.12.29
## 인원
3명
## 개발 플랫폼
Raspbian (debian)
## 개발 툴
vim
## 사용언어
Python, C++
## 사용기술
MQTT, Javascript, JSON
## 배포환경
AWS Lambda
# 제공 서비스
## MQTT protocol Listening
**AWS IoT, MQTT protocol, Python**<br>
라즈베리파이는 MQTT 프로토콜을 이용해 항상 메시지 수신대기 상태입니다.<br>
AWS IoT는 인터넷에 연결된 모듈의 AWS Lambda와 상호작용을 중계하며, 메시지가 도착한 경우 알맞은 함수를 실행시킵니다.<br>
이 프로젝트에서는 DC모터를 작동하는 프로그램을 실행하였습니다.
## DC Mortor Control
**python, ic2 interface, C++**<br>
i2c 인터페이스를 이용하여 DC 모터와 시계를 제어합니다.<br>
수신된 명령어에 따라 DC Mortor를 실시간 제어 또는 프로그램 시간 예약 함수를 작동하여, 시간에 따라 모듈의 모터를 작동시킵니다.
