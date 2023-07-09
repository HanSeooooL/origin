//
//  bookcontroll.h
//  2023 summerVac bookcontroll
//
//  Created by 한설 on 2023/06/28.
//

#ifndef bookcontroll_h
#define bookcontroll_h

#define UISTARTPOINTX 0 //UI출력 X축 시작지점
#define UISTARTPOINTY 0 //UI출력 Y축 시작지점ㄴ

//책 구조체 선언
typedef struct _book {
    int prime;
    char bookname[100]; //책 이름
    char writername[30];  //저자 이름
    char company[30];   //출판사 이름
    int rent;   //0이면 보유 1이면 대여
    char rentalname[30]; //빌려간 사람 이름
    char rentaltime[20];    //빌려간 연월일
    char retutime[20];      //반납예정 연월일
} Book;


//Algorithm
void init_book(Book *a); //initialize book(have변수 뒤의 초기값)
int checkhowdoyouDIDNTreturn(char *returnday);  //연체일 계산
void rentthebook(Book *rentbook, char *rentperson, char *rentday, char *returnday);
Book* search_book(char *keyword, int *how);


//file In / OUT
void addbook(char *name, Book newone);  //책 추가
void fileLead(char *name, int *n, int *rn);    //파일 불러오기
Book** getbooklist(int rentedunrented, int n, int page, int *display); //페이지에 알맞은 책의 배열을 반환하는 함수.
void savethefile(char *name);
Book* gettheAllbookList(int *n);

//UI
void title(void);



#endif /* bookcontroll_h */
