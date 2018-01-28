/*
 * Copyright (C) 2001 FirstBase Software, Inc. All rights reserved.
 *
 * $Id: plib.c,v 9.0 2001/01/09 02:56:03 john Exp $
 *
 * See the file LICENSE for conditions of use and distribution.
 *
 */

#ifndef LINT
static char sccsid[] = "@(#)plib.c	8.2 11/26/93 FB";
#endif

#include <dbvf_ext.h>
#include <varargs.h>

   F_fb_initscreen()		/* initialize the vscreen variables */
      {
	 vfscr.s_ccount[F_PROW] = 0;
         F_nullscr(&vfscr);
      }

   F_fb_move(x, y)
      int x, y;

      {
         vfscr.s_x = x - 1;
	 vfscr.s_y = y - 1;
      }

/*
 * nullscr - null out the given screen
 */
   F_nullscr(s)
      fscreen *s;

      {
         register int i, j;

         for (i = 0; i < p_lines; i++){
	    for (j = 0; j < p_cols; j++)
	       s->line[i][j] = NULL;
	    s->s_ccount[i] = 0;
	    }
      }

   F_fb_printw(va_alist)
      va_dcl

      {
         va_list ap;
         char sbuf[200];

	 va_start(ap);
         fb_sprintf(sbuf, &ap);
	 va_end(ap);
         F_fb_prints(sbuf);
      }

   F_fb_prints(buf)
      char *buf;
      
      {
	 register char *p;
	 
	 for (p = buf; *p; p++)
	    F_fb_s_putw(*p);
      }

   F_fb_s_putw(c)
      char c;
      
      {
	 register int x, y;

	 if (c == FB_NEWLINE){
	    ++vfscr.s_x;
	    vfscr.s_y = 0;
	    }
	 else if (c == '\t'){
	    for (;;){
	       F_fb_s_putw(CHAR_BLANK);
	       if (vfscr.s_y % 8 == 0 || vfscr.s_y >= p_cols - 1)
	          break;
	       }
	    }
	 else if (vfscr.s_y < p_cols){
	    x = vfscr.s_x;
	    y = vfscr.s_y;
	    vfscr.line[x][y] = c;
	    vfscr.s_ccount[x]++;
	    if (++y < p_cols)
	       vfscr.s_y = y;
	    else
	       vfscr.s_y = p_cols - 1;
	    }
      }

/*
 * screendump - spit out complete vfscr.
 */

   screendump()

      {
         register int i, j;
         fscreen *s;
	 char c;
	 int lastrow, lastcol, nlines = 0;

         s = &vfscr;
         for (lastrow = p_lines - 1; lastrow >= 0; lastrow--)
	    if (s->s_ccount[lastrow] > 0)
	       break;
         for (i = 0; i <= lastrow; i++){
	    if (s->s_ccount[i] > 0){
	       for (lastcol = p_cols - 1; lastcol >= 0; lastcol--)
		  if (s->line[i][lastcol] != NULL)
		     break;
	       for (j = 0; j <= lastcol; j++){
		  c = s->line[i][j];
		  if (c == NULL)
		     c = FB_BLANK;
		  putc(c, stdout);
		  }
	       }
	    putc(FB_NEWLINE, stdout);
	    nlines++;
	    }
	 if (formfeed_flag && nlines < p_lines)
	    putc('\014', stdout);
	 else{
	    /* simulate a formfeed with blank lines */
	    for (; nlines < p_lines; nlines++)
	       putc(FB_NEWLINE, stdout);
	    }
	 F_nullscr(s);
      }
