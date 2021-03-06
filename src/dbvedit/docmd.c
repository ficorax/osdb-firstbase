/*
 * Copyright (C) 2001 FirstBase Software, Inc. All rights reserved.
 *
 * $Id: docmd.c,v 9.1 2001/02/16 19:42:57 john Exp $
 *
 * See the file LICENSE for conditions of use and distribution.
 *
 */

#ifndef LINT
static char Docmd_sid[] = "@(#) $Id: docmd.c,v 9.1 2001/02/16 19:42:57 john Exp $";
#endif

#include <dbve_ext.h>

static int ext_command = 0;
static char *NOADD = ".noadd";
extern short int cdb_noaddrec;
extern int globaledit;
extern char *globalpat;
static char *HLP_V_EDCOM = 	"v_edcom.hlp";

/* 
 *  docmd - execute one dbedit command 
 */

   docmd()
      {
         int eflag, disp_st, j;
         long fb_scanfor(), atol();
	 char *fb_trim(), tfile[FB_MAXNAME];

	 disp_st = REDRAW;
         eflag = 0;
         if (st == FB_END || st == FB_ABORT){
	    if (st == FB_ABORT){
	       if (ext_command == 1){
		  ext_command = 0;
		  fb_xcommand();
		  return(NOREDRAW);
		  }
	       else
		  ext_command = 1;
	       }
            rec = oldrec = 0L;
            if (pindx == 0 && st == FB_END && mode == NULL)
               return(FB_END);
            irec[pindx] = ibase[pindx];
            mode = NULL;
            return(NOREDRAW);
            }
	 ext_command = 0;
	 if (st == FB_QHELP){
	    fb_move(3,1); fb_clrtoeol();
	    if (phead->p_help == NULL)
	       fb_fhelp(HLP_V_EDCOM);
	    else
	       fb_fhelp(pcur->p_help);
	    return(ZAP_REDRAW);
	    }
         else if (st == FB_QSIGNAL){
            rec = oldrec = 0L;
            return(NOREDRAW);
            }
	 fb_trim(com);
         switch (com[0]){
            case FB_FADD:
               eflag = 1;
               rec = -1L;
               break;
            case '?':				/* FB_HELP */
	       fb_move(3, 1); fb_clrtoeol();
               fb_help(com, hp);
	       return(ZAP_REDRAW);
               break;
	    case '!':				/* FB_BANG */
	       fb_cshell(com);
	       fb_serror(FB_MESSAGE, NIL, NIL);
	       fb_scrhdr(hp, NIL);
	       fb_scrlbl(hp->sdict);
	       return(ZAP_REDRAW);
	       break;
            case '>':				/* FB_INTO */
               if (hp->b_tree)
	          fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL], NIL);
	       else if (hp->ifd > 0){	/* index exists */
		  if (pindx + 1 < cdb_db->ifields - 1){ /* iptr is there */
		     ibase[pindx + 1]  = irec[pindx];
		     irec[pindx + 1] = irec[pindx];
		     pindx++;
		     }
		  else
		     fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL], NIL);
		  }
	       else{			/* no index exists */
	          if (com[1] == NULL){	/* simple > command */
		     if (++simple_pindx >= phead->p_maxedit)
			simple_pindx = 0;
		     }
		  else {		/* >N command */
		     j = atoi(com + 1) - 1;	/* convert to 0 based */
		     if (j >= 0 && j < phead->p_maxedit)
		        simple_pindx = j;
		     }
		  hp->ip[0] = phead->p_nedit[simple_pindx]->n_fp;
	          }
               return(REDRAW);
            case '<':				/* FB_OUTOF */
               if (hp->b_tree)
	          fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL], NIL);
	       else if (hp->ifd > 0){	/* index exists */
		  if (pindx - 1 >= 0)
		     --pindx;
		  else
		     fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL], NIL);
		  }
	       else{			/* no index exists */
	          if (--simple_pindx < 0)
		     simple_pindx = phead->p_maxedit - 1;
		  hp->ip[0] = phead->p_nedit[simple_pindx]->n_fp;
	          }
               return(REDRAW);
            case '.':				/* FB_DOT */
               eflag = 1;
	       fb_allsync(hp);
               rec = fb_scanfor(NIL, 2);
               break;
            case '@':				/* FB_DEREF */
               if ((com[1] == NULL || com[1] == CHAR_a || com[1] == CHAR_A) &&
	             scanner == 0){
	          fb_rootname(tfile, hp->dbase);
		  strcat(tfile, NOADD);
		  if (cdb_noaddrec || access(tfile, 0) == 0){
		     if (globaladd)
                        fb_xerror(FB_MESSAGE, SYSMSG[S_ILLEGAL],
                           SYSMSG[S_LOCKED]);
		     /* else */
                     fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL],SYSMSG[S_LOCKED]);
                     return(NOREDRAW);
		     }
                  mode = FB_FADD;	/* so next time, com will be FB_FADD */
		  }
               else{		/* must be a simple deref */
                  eflag = 1;
                  rec = atol(com+1);
                  if (hp->irec != NULL)
		     hp->irec[0] = NULL;
	          fb_allsync(hp);
                  }
               break;
            default:
               if (st == FB_END || st == FB_ABORT)
                  def = 2;
               else if (st == FB_DEFAULT || st == FB_ESIGNAL ||
                     st == FB_FSIGNAL)
                  def = 1; /* bump index ptr */
               else if (st == FB_YSIGNAL || st == FB_BSIGNAL)
                  def = 3; /* decr index ptr */
               else if (st == FB_SSIGNAL){
                  com[0] = CHAR_SLASH;
                  com[1] = NULL;
                  def = 0;
                  }
               else
                  def = 0;
               if (def >= 0){
	          fb_allsync(hp);
                  rec = fb_scanfor(com, def);
		  }
               eflag = 1;
               break;
            }
         if (eflag == 1){
            fb_lock_head(hp);
	    st = fb_gethead(hp);
            fb_unlock_head(hp);
	    if (st == FB_ERROR)
	       fb_xerror(FB_READ_ERROR, SYSMSG[S_BAD_HEADER], hp->dbase);
            if ((rec > 0L && rec <= (hp->reccnt)) || rec == -1L){
               oldrec = rec;
               if ((disp_st = edit(dot)) == FB_END)  /* from autoadd mode */
	          disp_st = REDRAW;
               }
            else{
	       fb_fmessage(NIL);
	       if (rec == 0L)
                  fb_serror(FB_MESSAGE, SYSMSG[S_SEARCHING],
                     SYSMSG[S_NOT_FOUND]);
               if (rec == -2L)		/* signal from scandb */
	          disp_st = REDRAW;
               else
	          disp_st = NOREDRAW;
	       rec = oldrec;		/* reset rec from error cond */
	       if (mode == NULL && (globaledit > 0 || globalpat != NULL)){
                  if (globaledit > 0)
		     fb_serror(FB_MESSAGE, SYSMSG[S_ILLEGAL], NIL);
	          return(FB_END);
		  }
	       return(disp_st);
	       }
            }
	 if (mode == NULL && 
	       (globaladd || globaledit > 0 || globalpat != NULL))
	    return(FB_END);
         return(disp_st);
      }
