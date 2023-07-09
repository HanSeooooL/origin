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

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void addbookUI(void); //책 등록 화면 o
static void finishedaddbookUI(void); //책 등록 완료 화면 o
static void viewbooklistUI(void); //등록도서 열람 화면
static void searchbookUI(void); //도서 검색 화면
static void bookdetailsUI(Book* one);   //세부정보 조회 화면
static void detailretouchordeleteUI(Book *one); //세부정보 수정 및 삭제 화면
void checkretouchUI(Book *old, Book afterrewrite);  //수정내용 확인 화면
static void checkdeleteUI(Book* one);   //도서정보 삭제 확인 화면
static void rentalbookUI(Book* one);    //대여 등록 화면
static void finishedrentalbookUI(void); //대여 등록 완료 화면
static void returnbookUI(Book *one);    //반납 처리 화면
static void finishedreturnbookUI(void);    //반납 처리 완료 화면

//screens
void titlescreen(void);
void addbookscreen(void);




void titlescreen(void) {
    system("clear");
    printf("                                                개인 도서관리 프로그램                                \n\n\n");
    printf("┌────────────────────────────────────────────┐     ┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                                            │     │     not returned book                                       │\n");
    printf("│      1. addbook                            │     │     boook name      person  returnday       notday          │\n");
    printf("│      2. view book list                     │     │                                                             │\n");
    printf("│                                            │     │                                                             │\n");
    printf("│                                            │     │                                                             │\n");
    printf("│                                            │     │                                                             │\n");
    printf("│                                            │     │                                                             │\n");
    printf("│      3. stop                               │     │                                                             │\n");
    printf("│                                            │     │                                                             │\n");
    printf("└────────────────────────────────────────────┘     └─────────────────────────────────────────────────────────────┘\n\n");
    
}

void addbookscreen(void) {
    system("clear");
    printf("                                                    도서 등록                                          \n\n\n");
    printf("┌────────────────────────────────────────────┐    \n");
    printf("│                                            │    \n");
    printf("│      bookname:                             │    \n");
    printf("│      writer:                               │    \n");
    printf("│      company:                              │    \n");
    printf("│                                            │   \n");
    printf("│                                            │   \n");
    printf("│                                            │    \n");
    printf("│                                            │    \n");
    printf("│                                            │    \n");
    printf("└────────────────────────────────────────────┘     \n\n");
}

void bookdetailsscreen(void) {
    system("clear");
    printf("                                                    세부정보                            \n\n\n");
    printf("┌──────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                                                  │\n");
    printf("│      bookname:                             rentedperson:                         │\n");
    printf("│                                                                                  │\n");
    printf("│      writer:                               rentedday :                           │\n");
    printf("│                                                                                  │\n");
    printf("│      company:                              returnday:                            │\n");
    printf("│                                                                                  │\n");
    printf("│      rent:                                 notday:                               │\n");
    printf("│                                                                                  │\n");
    printf("└──────────────────────────────────────────────────────────────────────────────────┘\n\n");
}


void title(void) {
    int choice;
    //printf("타이틀 화면입니다.\n");
    
    while(1) {
        titlescreen();
        printf("선택: ");
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
    
    addbookscreen();
    //예비 스크린
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
    int n, rn, choice, changetherentedunrented = 0;      //n은 대여중이지 않은 도서의 개수, rn은 대여중인 도서의 개수
    int page = 1, i, display, max;
    Book **pagelist;
    n = 0; rn = 0;
    
    fileLead("Book.txt", &n, &rn);
    if(n == 0) {
        if(rn == 0) {
            printf("등록된 도서가 없습니다. \n");
            return;
        }
        else changetherentedunrented = 1;
    }
    
    while(1) {
        int bookchoice;
        if(changetherentedunrented == 0)    max = n;
        else    max = rn;
        
        pagelist = getbooklist(changetherentedunrented, max, page, &display);
        for(i = 0; i < display % 5; i++) {
            printf("%s      %s      %s      %d\n", pagelist[i] -> bookname, pagelist[i] ->writername, pagelist[i] ->company, pagelist[i] ->rent);
        }
        if(page != 1)
            printf("1. 이전페이지");
        if(max != display)
            printf("2. 다음페이지");
        printf("3. 리스트 선택   4. 키워드 검색   ");
        if (changetherentedunrented == 1) {
            if(n > 0) {
                printf("5. 보유중인 도서 조회   ");
            }
        }
        else {
            if(rn > 0) {
                printf("5. 대여중인 도서 조회   ");
            }
        }
        printf("0. 뒤로가기");
        printf("\n번호를 입력하세요. ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(page == 1) {
                    printf("잘못된 입력입니다.");
                }
                else {
                    page -= 1;
                }
                break;
            case 2:
                if(max != display) {
                    printf("잘못된 입력입니다.");
                }
                else {
                    page += 1;
                }
                break;
            case 3:
                printf("책을 선택하세요. ");
                scanf("%d", &bookchoice);
                
                //display되고 있는 도서 리스트 각각 왼쪽에 index + 1 출력하는 코드 추가
                
                bookdetailsUI(pagelist[bookchoice - 1]);
                fileLead("Book.txt", &n, &rn);
                break;
            case 4:
                searchbookUI();
            case 5:
                if(changetherentedunrented) {
                    if(n > 0) {
                        changetherentedunrented = 0;
                    }
                    else
                        printf("잘못된 입력입니다.\n");
                }
                else {
                    if(rn > 0) {
                        changetherentedunrented = 1;
                    }
                    else
                        printf("잘못된 입력입니다.\n");
                }
                break;
            case 0:
                return;
        }
    }
}

void bookdetailsUI(Book* one) {
    int choice, recentdays;
    while(1) {
        bookdetailsscreen();
        
        printf("도서명: %s     저자: %s     출판사:    %s      대여여부: %d     ",
               one -> bookname, one -> writername, one -> company, one -> rent);
        if(one -> rent == 1) {
            printf("대여인: %s     대여일: %s     반납예정일: %s     ",
                   one -> rentalname, one -> rentaltime, one -> retutime);
        }
        recentdays = checkhowdoyouDIDNTreturn(one -> retutime);
        
        if(recentdays <= 0) {
            printf("남은 기한: ");
            printf("%d", abs(recentdays));
        }
        else {
            printf("연체일: ");
            printf("%d", recentdays);
        }
        
        
        printf("1. 수정/삭제    ");
        if(one -> rent == 0)
            printf("2. 대여   ");
        else
            printf("2. 반납   ");
        printf("0. 뒤로가기\n");
        printf("\n번호를 입력하세요. ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                detailretouchordeleteUI(one);
                if(one -> rent == -1)
                    return;
                break;
            case 2:
                if(one -> rent == 0)
                    rentalbookUI(one);
                else
                    //returnbookUI(one);
                break;
            case 0:
                return;
        }
    }
}

void rentalbookUI(Book* one) {
    char rentalname[60], chrentalday[20], chreturnday[20];
    int d, rentalday, returnday;
    printf("%s  %s  %s\n", one -> bookname, one -> writername, one -> company);
    printf("대여인: ");
    fflush(stdin);
    scanf("%s", rentalname);
    printf("대여일: ");
    fflush(stdin);
    scanf("%d", &rentalday);
    sprintf(chrentalday, "%d", rentalday);
    printf("반납 예정일: ");
    fflush(stdin);
    scanf("%d", &returnday);
    sprintf(chreturnday, "%d", returnday);
    printf("%s  %s  %s  %d  %s  %s  %s\n", one -> bookname, one -> writername, one -> company, 1, rentalname, chrentalday, chreturnday);
    printf("진행하시겠습니까? ");
    scanf("%d", &d);
    
    if (d == 1) {
        rentthebook(one, rentalname, chrentalday, chreturnday);
        return;
    }
    return;
    
}

void detailretouchordeleteUI(Book *one) {
    int choice;
    Book afterrewrite;
    
    afterrewrite = *one;
    
    while(1) {
        printf("1. 도서명: %s     2. 저자: %s     3. 출판사: %s     대여여부: %d    ", afterrewrite.bookname, afterrewrite.writername, afterrewrite.company, afterrewrite.rent);
        if(one -> rent == 1) {
            printf("4. 대여인: %s     5. 대여일: %s     6. 반납예정일: %s \n", afterrewrite.rentalname, afterrewrite.rentaltime, afterrewrite.retutime);
        }
        
        printf("수정할 번호를 입력해주세요. ");
        scanf("%d", &choice);
        fflush(stdin);
        
        switch(choice) {
            case 1:
                printf("도서명: ");
                scanf("%s", afterrewrite.bookname);
                fflush(stdin);
                break;
            case 2:
                printf("저자: ");
                scanf("%s", afterrewrite.writername);
                fflush(stdin);
                break;
            case 3:
                printf("출판사: ");
                scanf("%s", afterrewrite.company);
                fflush(stdin);
                break;
            case 4:
                if(afterrewrite.rent == 0) {
                    printf("잘못된 입력입니다.\n");
                    break;
                }
                printf("대여인: ");
                scanf("%s", afterrewrite.rentalname);
                fflush(stdin);
                break;
            case 5:
                if(afterrewrite.rent == 0) {
                    printf("잘못된 입력입니다.\n");
                    break;
                }
                printf("대여일: ");
                scanf("%s", afterrewrite.rentaltime);
                fflush(stdin);
                break;
            case 6:
                if(afterrewrite.rent == 0) {
                    printf("잘못된 입력입니다.\n");
                    break;
                }
                printf("반납예정일: ");
                scanf("%s", afterrewrite.retutime);
                fflush(stdin);
                break;
            case 8:
                checkretouchUI(one, afterrewrite);
                return;
            case 9:
                checkdeleteUI(one);
                return;
            case 0:
                return;
        }
    }
    
}

void checkretouchUI(Book *old, Book afterrewrite) {
    int choice;
    printf("oldone\n");
    printf("도서명: %s     저자: %s     출판사: %s     대여여부: %d     ", old -> bookname, old -> writername, old -> company, old -> rent);
    if(old -> rent == 1) {
        printf("대여인: %s     대여일: %s     반납예정일: %s \n", old -> rentalname, old -> rentaltime, old -> retutime);
    }
    printf("afterrewrite\n");
    printf("도서명: %s     저자: %s     출판사: %s     대여여부: %d     ", afterrewrite.bookname, afterrewrite.writername, afterrewrite.company, afterrewrite.rent);
    if(afterrewrite.rent == 1) {
        printf("대여인: %s     대여일: %s     반납예정일: %s \n", afterrewrite.rentalname, afterrewrite.rentaltime, afterrewrite.retutime);
    }
    
    printf("1. 완료   0. 취소\n");
    scanf("%d", &choice);
    
    if(choice == 1) {
        *old = afterrewrite;
        savethefile("Book.txt");
    }
    
    return;
    
    
}

void checkdeleteUI(Book *one) {
    int choice;
    
    while(1) {
        printf("도서명: %s     저자: %s     출판사:    %s      대여여부: %d", one -> bookname, one -> writername, one -> company, one -> rent);
        if(one -> rent == 1) {
            printf("    대여인: %s     대여일: %s     반납예정일: %s     연체일: %d\n", one -> rentalname, one -> rentaltime, one -> retutime, 0);
        }
        printf("정말로 삭제하시겠습니까? \n");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                one -> rent = -1;
                savethefile("Book.txt");
                return;
            case 2:
                return;
            default:
                printf("잘못된 입력입니다.\n");
                break;
        }
    }
}

void returnbookUI(Book *one) {
    int choice;
    
}


//list -> 등록도서 목록 포인터, n -> 등록된 도서 개수
void searchbookUI(void) {
    char keyword[200];
    Book *searchresult;
    int n, count;
    count = 0;
    printf("키워드 입력: ");
    fflush(stdin);
    scanf("%s", keyword);
    
    searchresult = search_book(keyword, &n);
    while(1) {
        for(int i = count * 5; i < (n % 5) + count * 5; i++) {
            
        }
    }
    
}
