//
//  bookcontroll.c
//  2023 summerVac bookcontroll
//
//  Created by 한설 on 2023/06/28.
//

#include "bookcontroll.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include "windows.h"

static long changethecalendertoDays(int year, int month, int day);

void init_book(Book *a) {
    strcpy(a -> rentalname, "_");
    strcpy(a -> rentaltime, "_");
    strcpy(a -> retutime, "_");
    a -> rent = 0;
}

//순차탐색방식
Book* search_book(char *keyword, int *how) {
    
    Book *list, *res;
    char *check;
    int n, *indexcheck, howmanysearched;
    howmanysearched = 0;
    list = gettheAllbookList(&n);
    
    indexcheck = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++) {
        check = strstr(list[i].bookname, keyword);
        if(check != NULL) {
            indexcheck[howmanysearched] = i;
            howmanysearched++;
            break;
        }
        check = strstr(list[i].writername, keyword);
        if(check != NULL) {
            indexcheck[howmanysearched] = i;
            howmanysearched++;
            break;
        }
        check = strstr(list[i].company, keyword);
        if(check != NULL) {
            indexcheck[howmanysearched] = i;
            howmanysearched++;
            break;
        }
    }
    
    res = (Book*)malloc(sizeof(Book) * howmanysearched);
    *how = howmanysearched;
    
    
    for(int i = 0; i < howmanysearched; i++) {
        res[i] = list[indexcheck[i]];
    }
    
    
    
    free(list);
    free(indexcheck);
    return res;
}

//연월일 일로 합쳐서 출력
long changethecalendertoDays(int year, int month, int day) {
    long res;
    int monthdayys[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int yunmonthdayys[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    res = 0;
    
    //1. 년 계산
    res += ((year - 1) / 4) * 366;
    res += ((year - 1) - (year - 1) / 4) * 365;
    
    //2. 달 계산
    if(year % 4) {
        for(int i = 0; i < month - 1; i++) {
            res += monthdayys[i];
        }
    }
    else
        for(int i = 0; i < month - 1; i++) {
            res += yunmonthdayys[i];
        }
    
    //3. 일 계산
    res += day;
    return res;
}

//연체 일수를 출력
int checkhowdoyouDIDNTreturn(char *returnday) {
    time_t raw;
    struct tm* t;
    int month, day;
    long res, returndayslong, nowdayslong;
    char year[4];
    
    returndayslong = 0; nowdayslong = 0;
    raw = time(NULL);
    t = localtime(&raw);
    
    for(int i = 0; i < 4; i++) {
        year[i] = returnday[i];
    }
    month = (returnday[4] - '0') * 10 + (returnday[5] - '0');
    day = (returnday[6] - '0') * 10 + (returnday[7] - '0');
    
    returndayslong = changethecalendertoDays(atoi(year), month, day);
    nowdayslong = changethecalendertoDays(t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday);
    
    //차를 계산한다.
    res = nowdayslong - returndayslong;
    //지났을 경우
    return (int)res;
}

void rentthebook(Book *rentbook, char *rentperson, char *rentday, char *returnday) {
    strcpy(rentbook -> rentalname, rentperson);
    strcpy(rentbook -> rentaltime, rentday);
    strcpy(rentbook -> retutime, returnday);
    rentbook -> rent = 1;
    savethefile("Book.txt");
}


char* gettheCharactersfromUser(char **str, int *length, char *index) {
    char *res;
    int key;
    
    while (1) {
        key = _getch();
        if(key == '\n')
        {
            *str = (char*)malloc(sizeof(*length));
            
            (*length)--;
            
            *index = *length;
            
            *(*str + *index) = 0;
            (*index)--;
        }
        
        else {
            
            gettheCharactersfromUser(str, length, index);
            
            *(*str + *index) = key;
            (*index)--;
            
            
        }
        
        
    }
    
    return res;
}
