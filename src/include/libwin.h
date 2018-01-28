/*
* Copyright (C) 2001 FirstBase Software, Inc. All rights reserved.
*
* $Id: libwin.h,v 9.0 2001/01/09 02:56:15 john Exp $
*
* See the file LICENSE for conditions of use and distribution.
*
*/

#if !FB_PROTOTYPES

extern fb_cx_add_buttons();
extern fb_cx_boot();
extern fb_cx_close();
extern fb_cx_delete_exchoices();
extern fb_cx_deposit_exchoices();
extern fb_cx_fb_xerror();
extern fb_cx_get_buttons();
extern fb_cx_get_dict();
extern fb_cx_get_menu();
extern fb_cx_get_message();
extern fb_cx_get_seekfile();
extern fb_cx_get_status();
extern fb_cx_get_toolname();
extern fb_cx_get_viewpage();
extern fb_cx_get_workdir();
extern fb_cx_init();
extern fb_cx_pop_buttons();
extern fb_cx_pop_env();
extern fb_cx_pop_message();
extern fb_cx_pop_status();
extern fb_cx_push_buttons();
extern fb_cx_push_env();
extern fb_cx_push_message();
extern fb_cx_push_status();
extern fb_cx_read();
extern fb_cx_set_buttons();
extern fb_cx_set_dict();
extern fb_cx_set_menu();
extern fb_cx_set_message();
extern fb_cx_set_seekfile();
extern fb_cx_set_seekpoint();
extern fb_cx_set_status();
extern fb_cx_set_toolname();
extern fb_cx_set_viewpage();
extern fb_cx_set_workdir();
extern fb_cx_signal_1();
extern fb_cx_signal_2();
extern fb_cx_sub_buttons();
extern fb_cx_testcontrol();
extern fb_cx_werror();
extern fb_cx_write();
extern long fb_cx_get_seekpoint();

#else  /* FB_PROTOTYPES */

extern fb_cx_add_buttons(char *s);
extern fb_cx_boot(void);
extern fb_cx_close(void);
extern fb_cx_delete_exchoices(void);
extern fb_cx_deposit_exchoices(fb_exchoice *e);
extern fb_cx_fb_xerror(int e, char *p, char *q);
extern fb_cx_get_buttons(char *s);
extern fb_cx_get_dict(char *ddict, char *vdict);
extern fb_cx_get_menu(char *fname);
extern fb_cx_get_message(char *s);
extern fb_cx_get_seekfile(char *s);
extern fb_cx_get_status(char *s);
extern fb_cx_get_toolname(char *s);
extern fb_cx_get_viewpage(void);
extern fb_cx_get_workdir(char *s);
extern fb_cx_init(void);
extern fb_cx_pop_buttons(void);
extern fb_cx_pop_env(void);
extern fb_cx_pop_message(void);
extern fb_cx_pop_status(void);
extern fb_cx_push_buttons(char *s);
extern fb_cx_push_env(char *buttons, char *status, char *msg);
extern fb_cx_push_message(char *s);
extern fb_cx_push_status(char *s);
extern fb_cx_read(void);
extern fb_cx_set_buttons(char *s);
extern fb_cx_set_dict(char *ddict, char *vdict);
extern fb_cx_set_menu(char *fname);
extern fb_cx_set_message(char *s);
extern fb_cx_set_seekfile(char *s);
extern fb_cx_set_seekpoint(long p);
extern fb_cx_set_status(char *s);
extern fb_cx_set_toolname(char *s);
extern fb_cx_set_viewpage(int p);
extern fb_cx_set_workdir(char *s);
extern fb_cx_signal_1(void);
extern fb_cx_signal_2(void);
extern fb_cx_sub_buttons(char *s);
extern fb_cx_testcontrol(void);
extern fb_cx_werror(int m, char *a, char *b);
extern fb_cx_write(int sigflag);
extern long fb_cx_get_seekpoint(void);

#endif /* FB_PROTOTYPES */
