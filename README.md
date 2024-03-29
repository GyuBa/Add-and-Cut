## 문제
### 1. 파일의 절단
옵션은 기본적으로 4개가 사용가능함. (선택적으로 순서에 상관없이 적용 가능해야 함)

-n : 절단해서 생성되는 파일의 이름을 주기 위한 옵션. 이 옵션이 없는 경우는 default 로 절단 하는 파일
의 이름을 사용

-s : 생성되는 파일의 크기를 주기 위한 옵션. 이 옵션이 없는 경우 default 로 512KB 크기의 파일들이 생
성

-o : 절단할 파일의 이름을 주기 위한 옵션 (반드시 포함되어야할 옵션)

-d : 절단한 파일들을 현재 directory가 아닌 원하는 directory에 저장하고자 할 경우. directory가 없는 경우 생성하여 저장하도록 함. 절단된 파일의 위치는 default 가 실행 프로그램이 있는 directory

○ 절단된 파일들의 파일명은 "abc001", "abc002", .... 로 진행되도록 함.

○ 절단된 파일의 개수가 1000개는 넘는 경우는 너무 잘게 잘리므로 다시 명령을 주도록 함.

### 2. 파일의 합침
옵션은 기본적으로 4개가 사용가능함. (선택적으로 순서에 상관없이 적용 가능해야 함)

-n : 절단된 파일을 합친 경우 최종 파일의 이름을 지정하기 위한 옵션. 이 옵션이 없는 경우는 default 로
절단되어 있는 파일의 이름을 사용

-o : 합치고자 하는 파일의 이름을 주기위한 옵션

-d : 현재 directory가 아닌 다른 directory에 있는 파일을 합치고자 할 때 사용하는 옵션. 합쳐진 파일의 위치는 기본적으로 실행 프로그램이 실행되는 위치이나 이 옵션이 사용된 경우는 지정된 directory 에 
위치
-x : 이 옵션이 포함된 경우는 절단된 파일을 합친 후, 기존의 절단된 파일을 모두 지움
## 가정
+ add, cut 둘다 -o 옵션과 그와 관련된 옵션 데이터가 필요하다.
+ 옵션의 개수는 2~8개이다.
+ 옵션은 중복되지 않는다.
