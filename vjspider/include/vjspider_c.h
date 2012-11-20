#ifndef VJSPIDER_C_H
#define VJSPIDER_C_H

#include "vjspider_config.h"

extern "C" bool         VJSPIDER_API vj_init_global_envi();
extern "C" void         VJSPIDER_API vj_release_global_envi();

extern "C" int          VJSPIDER_API vj_create_spider();
extern "C" void         VJSPIDER_API vj_release_spider(int idx);

extern "C" bool         VJSPIDER_API vj_init_context(int idx, bool auto_del_cookie = true, const char* cookie_file = "$", bool use_cookie = true);

extern "C" const char   VJSPIDER_API *vj_get_cookie_filename(int idx);
extern "C" void         VJSPIDER_API vj_del_cookie_file(int idx);

extern "C" bool         VJSPIDER_API vj_push_get_data(int idx, const char* name, const char* value);
extern "C" bool         VJSPIDER_API vj_push_post_data(int idx, const char* name, const char* value);
extern "C" void         VJSPIDER_API vj_clear_get_data(int idx);
extern "C" void         VJSPIDER_API vj_clear_post_data(int idx);

extern "C" const char   VJSPIDER_API *vj_get(int idx, const char* url, unsigned int code = VJCD_UTF8, int cookie = 1);
extern "C" const char   VJSPIDER_API *vj_post(int idx, const char* url, unsigned int code = VJCD_UTF8, int cookie = 2);

#endif
