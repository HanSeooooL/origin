//
//  test.c
//  2023 summerVac bookcontroll
//
//  Created by 한설 on 2023/06/28.
//

#include "test.h"
#include <stdio.h>




void TC1_fileInOut(void) {
    Book newone;
    init_book(&newone);
    printf("도서명: ");
    scanf("%s", newone.bookname);
    fflush(stdin);
    printf("저자: ");
    scanf("%s", newone.writername);
    fflush(stdin);
    printf("출판사: ");
    scanf("%s", newone.company);
    newone.prime = 0;
    addbook("Book.txt", newone);
}
