//
//  bookcontroll.h
//  2023 summerVac bookcontroll
//
//  Created by 한설 on 2023/06/28.
//

#ifndef bookcontroll_h
#define bookcontroll_h

//책 구조체 선언
typedef struct _book {
    int prime;
    char bookname[100]; //책 이름
    char writername[30];  //저자 이름
    char company[30];   //출판사 이름
    int rent;   //0이면 보유 1이면 대여
    char rentalname[30]; //빌려간 사람 이름
    char rentaltime[8];    //빌려간 연월일
    char retutime[8];      //반납예정 연월일
} Book;


//Algorithm
void init_book(Book *a); //initialize book(have변수 뒤의 초기값)


//file In / OUT
void addbook(char *name, Book newone);  //책 추가
Book* fileLead(char *name, Book* unrented, int *n, int *rn);     //파일 불러오기

//UI
void title(void);



#endif /* bookcontroll_h */
