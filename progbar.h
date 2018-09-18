//
// Created by TowardsTheStars on 2018/9/11.
//

/**
 * c语言版本的进度条，原代码用的c++
 */

#ifndef COMPUTATIONALPHYSICS_PROCEDURE_H
#define COMPUTATIONALPHYSICS_PROCEDURE_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct
{
    char buf[102];
    int bar_control;
    double percent;
    int digits;
    int i;
    pthread_t thread;
    int fin;

    useconds_t interval_us;
} ProcBar;

ProcBar* createProcBar();
void updateProcBar(ProcBar* bar, double percentage);
void __updateProcBar(ProcBar*);
void threadFlush(void*);
void finishProgBar(ProcBar* bar);

#endif //COMPUTATIONALPHYSICS_PROCEDURE_H
