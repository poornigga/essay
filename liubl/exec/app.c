/*
 * =====================================================================================
 *
 *       Filename:  app.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/01/27 14时05分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  bigdog (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "common.h"
#include "tpc.h"
#include "xpf.h"


/* 
int main(void) {

    int serial = 21;
    int size   = 70;
    int row = 8, column = 9;

    exit(EXIT_SUCCESS);
} */

int main(void) {

    mgt *m = NULL;

    if (no == buf_init(&m)) {
        printf ( "memery init faild\n" );
        exit(EXIT_FAILURE);
    }

    if (no == tpc_analysis("../ayx2.tpc", m)) {
        printf ( "analysis tpc file faild\n" );
        free(m);
    }

    pot_debug(m);

    free(m);
    exit(EXIT_SUCCESS);
} 
