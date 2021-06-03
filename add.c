#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAXCHAR 256
#define DEFAULTSIZE 512

//정수를 문자로 바꾸는 함수
int itochar(int value, char * str){

    *str = (value / 100) + 48;
    value = value % 100;
    *(str+1) = (value / 10) + 48;
    value = value % 10;
    *(str+2) = value + 48;
    *(str+3) = '\0';

    return 0;
}

int main(int argc, char ** argv){

    int srcID, dstID;// 소스파일설명자, 목적파일설명자
    int delsrc = 0;//파일을 삭제할지
    int option[4] = {0};//옵션 이용 여부(bool 대신)
    int fileCount;//파일 개수
    int len;//길이 저장
    char * srcname;//소스파일이름
    char * dstname;//목적파일이름
    char * directory;//디렉토리 경로
    const char * OPTION[4] = {"-n", "-o", "-d", "-x"};//파일옵션
    char * optionValue[4] = {0};//파일 옵션 값
    char data[MAXCHAR+1];//소스파일에서 읽은 값
    char name[MAXCHAR+1];//실제파일을 만들때 사용
    char charcnt[4];//생성파일 번호
    ssize_t nread;
    struct stat srcstat;//파일 상태 저장


    if(argc > 9){
        printf("옵션이 너무 많습니다\n");
        exit(0);
    }
    if(argc < 2){
        printf("옵션이 너무 적습니다.\n");
        exit(0);
    }
	//옵션정보 저장 및 전달
    for(int i=1; i<argc; i+=2){
        for(int j=0; j<4; j++){
            if(!strcmp(argv[i], OPTION[j])){
                if(option[j]){
                    printf("옵션이 중복되었습니다.\n");
                    exit(0);
                }

                optionValue[j] = argv[i+1];
                option[j] = 1;
                break;
            }
        }
    }
//옵션 검사, 형변환, 저장
    if(!option[1]){
        printf("-o 옵션은 반드시 포함되어야 합니다.\n");
        exit(1);
    }
    else{
        srcname = optionValue[1];
        len = strlen(srcname);
        srcname[len-3] = '\0';
    }
    if(option[0]){
        dstname = optionValue[0];
    }
    else{
        dstname = srcname;
    }
    if(option[2]){
        directory = optionValue[2];
        strcat(directory, "/");
    }
    else{
        directory = "./";
    }
    if(option[3]){
        delsrc = 1;
    }

	//디렉토리 생성
    if(opendir(directory) == NULL){
        mkdir(directory,0777);
    }

    //파일 열기
    strcpy(name, directory);
    strcat(name, dstname);
    dstID = open(name, O_WRONLY | O_CREAT, 0666);
	
    //원본파일 제작
    for(int i = 0; i < 1000 ; i++){

        itochar(i, charcnt);
        strcpy(name, srcname);
        strcat(name, charcnt);
        if((srcID = open(name, O_RDONLY)) < 0){
            break;
        }
        while((nread = read(srcID, data, MAXCHAR)) > 0){
            write(dstID, data, nread);
        }

        close(srcID);

        if(delsrc == 1){
            unlink(name);
			
        }

    }
	//목록 출력, 완료
	system("ls -al");
	printf("완료...\n");
    close(dstID);
}
