/*
 * =====================================================================================
 *
 *       Filename:  tpc.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/01/27 14时02分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  bigdog (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _TPC_H_
#define _TPC_H_

#define tpc_pot_max 56000
#define tpc_node_pot 256

#pragma pack(push)
#pragma pack(1)
typedef struct _tpc_point_ {
    double pt[5];
}tpc_pot;

typedef struct _tpc_node {
    int m[2];
    int num;
    int ct;
    tpc_pot *pots[tpc_node_pot];
} tpc_node ;

typedef struct _tpc_mgt_ {
    int node_count;
    tpc_node *node;
    tpc_node *cur_node;
    int pot_count;
    tpc_pot *pot;
    tpc_pot *cur_pot;
} mgt;

#pragma pack(pop)

int buf_init(mgt **mg) ;
void buf_release(mgt *mg) ;
int tpc_analysis ( const char *path, mgt *m ) ;
void pot_debug(mgt *m) ;

#endif
