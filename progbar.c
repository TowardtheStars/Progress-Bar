//
// Created by TowardsTheStars on 2018/9/11.
//

#include "progbar.h"

ProcBar* createProcBar()
{
    ProcBar* re = (ProcBar*)malloc(sizeof(ProcBar));

    re->bar_control = 0;
    re->percent = 0.0;
    re->digits = 2;
    memset(re->buf, ' ', sizeof(re->buf));
    re->buf[101] = '\0';
    re->i = 0;
    re->interval_us = 333333;
    re->fin = 0;
    pthread_create(&re->thread, NULL, threadFlush, re);
    return re;
}

void updateProcBar(ProcBar* bar, double percentage)
{
    int prop = (int)floor(percentage * 100);
    if (fabs(percentage - bar->percent) >= pow(10, -2-bar->digits)) {
        bar->percent = percentage;
        for (int i = bar->bar_control; i < prop; ++i) {
            bar->buf[bar->bar_control] = '=';
        }

    }
}

void __updateProcBar(ProcBar* bar)
{
    static char index[6] = "-\\|/\0";
    printf("[%s] [%.2f%%][%c]\r", bar->buf, bar->percent * 100, index[bar->i++ % 4]);
//    fprintf(stderr, "[%s] [%.2f%%][%c]\r", bar->buf, bar->percent * 100, index[bar->i++ % 4]);
    fflush(stdout);//刷新缓冲区
}

void threadFlush(void* bar_)
{
    ProcBar* bar = (ProcBar*) bar_;
    while (bar->bar_control != 100)
    {
        __updateProcBar(bar);
        usleep(bar->interval_us);
    }
    bar -> fin = 1;
}

void finishProgBar(ProcBar* bar)
{
    bar->bar_control = 100;
    updateProcBar(bar, 1.0);
    __updateProcBar(bar);
    printf("\n");
    while(!(bar->fin));
    free(bar);
}
