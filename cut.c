#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define NAME 0
#define SIZE 1
#define TARGET 2
#define DIR 3

int itochar(int value, char * str){

    *str = (value / 100) + 48;
    value = value % 100;
    *(str+1) = (value / 10) + 48;
    value = value % 10;
    *(str+2) = value + 48;
    *(str+3) = '\0';

    return 0;
}

int main(int argc, char *argv[]){
    const char *OPTION[] = {"-n","-s", "-o", "-d"};//옵션 목록
    int srcID, dstID;//소스파일 설명자, 목적파일 설명자
    int option[4] = {0};//옵션 이용 여부(bool 대신)
    int fileCount = 0;//파일의 개수

    char * srcNme;//소스파일이름
    char * dstName;//목적파일이름
    char * directory;//디렉토리 경로
    int fileSize = 512;//파일의 크기

    char name[256];//저장될 파일이름
    char data[256];//저장될 실제 데이터
    char *optionValue[4] = {0};//전달받은 옵션정보
    char charNum[4];//넘버링
    ssize_t nread;
    struct stat srcstat;//파일 정보를 저장하고 있는 구조체

    if(argc > 9){
        printf("옵션이 너무 많습니다.\n");
        exit(0);
    }
    if(argc < 2){
        printf("옵션이 너무 적습니다.\n");
        exit(0);
    }
	//옵션정보 출력
    for(int i=1; i<argc; i+=2){
        printf("%s %s\n", argv[i], argv[i+1]);
    }

	//옵션정보 저장 및 전달
    for(int i=1; i<argc; i+=2){
        for(int j=0; j<4; j++){
            if(!strcmp(argv[i], OPTION[j])){
                if(option[j]){
                    printf("옵션 정보가 중복됩니다.\n");
                    exit(0);
                }

                optionValue[j] = argv[i+1];
                option[j] = 1;
                break;
            }
        }
    }

	//옵션 검사, 형변환, 저장
    if(!option[TARGET]) {
        printf("-o 옵션은 반드시 포함되어야합니다.\n");
        exit(0);
    }
    else{
        dstName = optionValue[TARGET];
    }

    if(option[NAME])
        srcNme= optionValue[NAME];
    else
        srcNme = optionValue[TARGET];
    if(option[SIZE])
        fileSize = atoi(optionValue[SIZE]);
    else{
        fileSize = 512;
    }

    if(option[DIR]){
        directory = optionValue[DIR];
        strcat(directory,"/");
    }
    else{
        directory = "./";
    }
	
	//파일 열기
    if((srcID = open(optionValue[TARGET], O_RDONLY)) < 0){
        printf("file을 찾을 수 없습니다.\n");
        exit(0);
    }
	//파일 정보 저장
    if(fstat(srcID, &srcstat) < 0){
        printf("fstat error\n");
        close(srcID);
        exit(0);
    }
	//파일 크기 검사
    if(srcstat.st_size < ((fileSize * 1024))){
        printf("파일의 크기는 적어도 %d Kb 이상이어야 합니다.\n", fileSize);
        close(srcID);
        exit(0);
    }
	//파일 개수 계산 및 확인
    fileCount = (srcstat.st_size / (fileSize*1024)) + 1;
    if(fileCount > 999){
        printf("파일 개수가 너무 많습니다.\n");
        close(srcID);
        exit(1);
    }
	//디렉토리 생성
    if(opendir(directory) == NULL) {
        mkdir(directory, 0777);
    }
	//파일 분할
    for(int i = 0; i < fileCount; i++) {
        strcpy(name, directory);
        strcat(name, srcNme);
        itochar(i, charNum);
        strcat(name, charNum);

        dstID = open(name, O_WRONLY | O_CREAT, srcstat.st_mode);

        for(int j = 0; j < fileSize*1024/255 ; j++){
            if((nread = read(srcID, data, 255)) <= 0)
                break;
            write(dstID, data, nread);
        }

        close(dstID);
    }
	//목록 출력, 완료
	system("ls -al");
	printf("완료...\n");
}
