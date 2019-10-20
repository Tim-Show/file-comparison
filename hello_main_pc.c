/****************************************************************************
 * examples/hello/hello_main.c
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
/**************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/

void 
normalizeTime(struct timespec  * r)
{
	r->tv_sec += r->tv_nsec / 1000000000;
	r->tv_nsec -= (r->tv_nsec / 1000000000) * 1000000000;

	if (r->tv_sec > 0 && r->tv_nsec < 0) {
		r->tv_sec -= 1;
		r->tv_nsec += 1000000000;
	} else if (r->tv_sec < 0 && r->tv_nsec > 0) {
		r->tv_sec += 1;
		r->tv_nsec -= 1000000000;
	}
}



void 
subTime(struct timespec  * r, const struct timespec  * x, const struct timespec  * y)
{
	r->tv_sec = x->tv_sec - y->tv_sec;
	r->tv_nsec = x->tv_nsec - y->tv_nsec;

	normalizeTime(r);
}


int main(int argc,  char *argv[])
{


  

    while(1)
    {

    struct timespec tp;
	struct timespec tp1;

    memset(&tp,0,sizeof(struct timespec));
 	memset(&tp1,0,sizeof(struct timespec));
    
	if(clock_gettime(CLOCK_REALTIME,&tp)<0)
        printf("get time false\n");
    else 
        printf("gettime0 %ds.%dns\n",tp.tv_sec,tp.tv_nsec);


    //memset(&tp,0,sizeof(struct timespec));


        usleep(1000000);

	memset(&tp1,0,sizeof(struct timespec));


    if(clock_gettime(CLOCK_REALTIME,&tp1)<0)
        printf("get time false\n");
    else 
        printf("gettime1 %ds.%dns\n",tp1.tv_sec,tp1.tv_nsec);

	subTime(&tp1,&tp1,&tp);
	printf("offset %ds.%dns\n",tp1.tv_sec,tp1.tv_nsec);
	

    printf("\n");
    }

  printf("Hello, World!!\n");
  return 0;
}
