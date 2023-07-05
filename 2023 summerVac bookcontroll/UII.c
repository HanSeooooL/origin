//
//  UII.c
//  2023 summerVac bookcontroll
//
//  Created by 한설 on 2023/07/05.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "windows.h"
#include "bookcontroll.h"

void addbookUI(void); //책 등록 화면
void finishedaddbookUI(void); //책 등록 완료 화면
void viewbooklistUI(void); //등록도서 열람 화면
void searchbookUI(void); //도서 검색 화면
void bookdetailsUI(void);   //세부정보 조회 화면
void detailretouchordeleteUI(void); //세부정보 수정 및 삭제 화면
void checkretouchUI(void);  //수정내용 확인 화면
void checkdeleteUI(void);   //도서정보 삭제 확인 화면
void rentalbookUI(void);    //대여 등록 화면
void finishedrentalbookUI(void); //대여 등록 완료 화면
void returnbookUI(void);    //반납 처리 화면
void finishedreturnbookUI(void);    //반납 처리 완료 화면


void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void title(void) {
    int choice;
    printf("타이틀 화면입니다.\n");
    
    while(1) {
        printf("번호를 입력하세요. 1 도서 등록 2 도서정보 열람 3 종료\n");
        scanf("%d", &choice);
        if (choice == 1) {
            addbookUI();
        }
        else if (choice == 2) {
            viewbooklistUI();
        }
        else if (choice == 3) {
            return;
        }
    }
}

void addbookUI(void) {
    Book newone;
    int choice;
    init_book(&newone);
    
    //예비 스크린
    printf("책 등록 화면입니다. \n");
    printf("도서명: ");
    scanf("%s", newone.bookname);
    fflush(stdin);
    printf("저자: ");
    scanf("%s", newone.writername);
    fflush(stdin);
    printf("출판사: ");
    scanf("%s", newone.company);
    fflush(stdin);
    printf("1. 진행 0. 취소");
    scanf("%d", &choice);
    //예비 스크린
    
    if(choice == 1) {
        addbook("Book.txt", newone);
        finishedaddbookUI();
        return;
    }
    else
        return;
}

void finishedaddbookUI(void) {
    printf("등록 완료 되었습니다.\n");
}

void viewbooklistUI(void) {
    int n, rn;      //n은 대여중이지 않은 도서의 개수, rn은 대여중인 도서의 개수
    Book *unrented = NULL, *rented = NULL;
    unrented = fileLead("Book.txt", rented, &n, &rn);
    printf("도서명     저자      출판사\n");
    for(int i = 0; i < n; i++) {
        printf("%s      %s      %s\n", unrented[i].bookname, unrented[i].writername, unrented[i].company);
    }
}
