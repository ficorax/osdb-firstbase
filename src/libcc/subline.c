/*
 * Copyright (C) 2001 FirstBase Software, Inc. All rights reserved.
 *
 * $Id: subline.c,v 9.0 2001/01/09 02:56:21 john Exp $
 *
 * See the file LICENSE for conditions of use and distribution.
 *
 */

#ifndef LINT
static char Subline_sid[] = "@(#) $Id: subline.c,v 9.0 2001/01/09 02:56:21 john Exp $";
#endif

#include <fb.h>

#if !FB_PROTOTYPES
static int fb_rearline();
#else
static int fb_rearline(char *line, char *s, int snum, int attr);
#endif /* FB_PROTOTYPES */

#define FB_MAXLINE 	250		/* general mac line length */
int fb_subline_maxline = FB_MAXLINE;

/*
 * subline - get attr separated field snum from s into line.
 */

   fb_subline(line, s, snum, attr)
      char *line, *s;
      int snum, attr;
 
      {
         char *p, *q, savec;
	 int ret = 1, cc = 0;

         if (fb_subline_maxline < FB_MAXLINE)
            fb_subline_maxline = FB_MAXLINE;
         if (snum < 0)
            return(fb_rearline(line, s, snum, attr));
         for (p = s, q = s; *q && snum > 0; q++){
            if (*q == attr){
               if (--snum == 0)
                  break;
               p = q + 1;
               cc = 0;
               }
            if (++cc >= fb_subline_maxline)
               break;
            }
         snum--;
         if (snum > 0){          /* if past array, set to null */
            q = p;
	    ret = 0;
	    }
	 savec = *q;		/* save and restore the character */
         *q = '\0';
         strcpy(line, p);
	 *q = savec;
	 return(ret);
      }

   static fb_rearline(line, s, snum, attr)
      char *line, *s;
      int snum, attr;
 
      {
         char *p, *q, savec;
	 int ret = 1;

         if (*s == 0){
            line[0] = 0;
            return(0);
            }
         for (q = s; *q; q++)
            ;
         if (q != s)
            q--;
         if (*q == attr){
            if (q == s){		/* just a single NEWLINE in field */
               line[0] = 0;
               return(0);
               }
            p = q - 1;
            }
         else
            p = q;
         for (; snum < 0; p--){
            if (*p == attr || p == s){
               if (++snum == 0){
                  if (*p == attr)
                     p++;
                  break;
                  }
               q = p;
               }
            if (p == s)
               break;
            }
         if (snum != 0){          /* if past array, set to null */
            q = p;
	    ret = 0;
	    }
         if (*q != attr && snum == 0)
            q++;
	 savec = *q;		/* save and restore the character */
         *q = '\0';
         strcpy(line, p);
	 *q = savec;
	 return(ret);
      }
