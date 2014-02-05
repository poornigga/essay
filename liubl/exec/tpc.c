/*
 * =====================================================================================
 *
 *       Filename:  tpc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/01/26 13时28分36秒
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

int buf_init(mgt **mg) {
    if (NULL == mg)
        return no;

    size_t mlen = sizeof(mgt) + sizeof(tpc_node)*256 + sizeof(tpc_pot)*tpc_pot_max;

    char *buf = malloc(mlen);
    if (NULL == buf) {
        printf ( "malloc error\n" );
        return -1;
    }
    memset(buf, '\0', mlen);

    mgt *m = (mgt *)buf;
    tpc_node *node = (tpc_node *)(buf + sizeof(mgt));
    tpc_pot  *pot = (tpc_pot *)(buf + sizeof(mgt) + sizeof(tpc_node)*256);
    m->node = node;
    m->cur_node = NULL;
    m->pot = pot;
    m->cur_pot = m->pot;
    m->node_count = 0;
    m->pot_count = 0;

    *mg = m;
    return yes;
}

void buf_release(mgt *mg) {
    if (NULL == mg)
        return;

    free(mg);
    mg = NULL;
}

int tpc_analysis ( const char *path, mgt *m ) {
    if (NULL == path || NULL == m) {
        return no;
    }

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = " \r\n";

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getdelim(&line, &len, '\n', fp)) != -1) {
        if (read > 13) {
            char *token;  
            int i=0;
            for(token = strtok(line, delim); token != NULL; token = strtok(NULL, delim)) {  
                m->cur_pot->pt[i++] = atof(token);
                if (i == 5) { break; }
            }
            m->cur_node->pots[m->cur_node->ct++] = m->cur_pot;
            m->pot_count ++ ;
            m->cur_pot ++;

        } else if (read > 7 ) {
            if (m->cur_node == NULL) {
                m->cur_node = m->node;
            } else {
                m->cur_node ++;
            }
            char *token;  
            int i=0;
            for(token = strtok(line, delim); token != NULL; token = strtok(NULL, delim)) {  
                // update m, n
                // m->cur_node->m[i++] = atoi(token);
                if (i%2) {
                    m->cur_node->y = atoi(token);
                } else {
                    m->cur_node->x = atoi(token);
                }
                i++;
            }
            m->node_count ++ ;

        } else if (read > 3) {
            m->cur_node->ct = 0;
            char *token = strtok(line, delim);
            m->cur_node->num = atoi(token);
        }
    }

    if (line) {
        free(line);
    }

    return yes;
}



void pot_debug(mgt *m) {
    if (NULL == m) return ;
    printf ( "Mgt : node->count [%d], pot->count[%d]\n", m->node_count, m->pot_count );

    tpc_node *node = m->node;
    tpc_pot *pot ;
    for (int i=0; i<m->node_count; ++i) {
        printf ( "node<%d of %d> :: m [%d] n[%d] num [%d] : \n",i, m->node_count,  node->x, node->y , node->num);
        for (int j=0; j<node->ct; j++) {
            pot = node->pots[j];
            printf ( "\tPot : %.0f / %.6f / %.6f / %.3f / %.3f\n", pot->pt[0], pot->pt[1] , pot->pt[2] , pot->pt[3] , pot->pt[4]  );
        }
        node ++;
    }
}


#if 0
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

#endif
