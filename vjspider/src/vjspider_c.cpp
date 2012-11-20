#include <vjspider_c.h>
#include <vjspider.h>
#include <vjspider_helper.h>

map<int, VJSpider*>     __vjspiders;
map<int, string>        __cookies;
map<int, get_data>      __tmpgetdata;
map<int, post_data>     __tmppostdata;
map<int, string>        __getstring;
map<int, string>        __poststring;

bool vj_init_global_envi()
{
    return VJSpider::init_global_envi();
}

void vj_release_global_envi()
{
    return VJSpider::release_global_envi();
}

int vj_create_spider()
{
    int idx = VJRand();
    while(__vjspiders.find(idx) != __vjspiders.end()) idx = VJRand();

    __cookies[idx] = "";
    __poststring[idx] = "";
    __getstring[idx] = "";
    __vjspiders[idx] = new VJSpider();
    __tmpgetdata[idx].clear();
    __tmppostdata[idx].clear();

    return idx;
}

void vj_release_spider(int idx)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it != __vjspiders.end())
    {
        delete it->second;
        __vjspiders.erase(it);
    }

    map<int, get_data>::iterator getit = __tmpgetdata.find(idx);
    if(getit != __tmpgetdata.end())
    {
        getit->second.clear();
        __tmpgetdata.erase(getit);
    }

    map<int, post_data>::iterator postit = __tmppostdata.find(idx);
    if(postit != __tmppostdata.end())
    {
        postit->second.clear();
        __tmppostdata.erase(postit);
    }

    __cookies[idx] = "";
    __getstring[idx] = "";
    __poststring[idx] = "";

    return;
}

bool vj_init_context(int idx, bool auto_del_cookie, const char* cookie_file, bool use_cookie)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end()) return false;

    return __vjspiders[idx]->init_context(auto_del_cookie, cookie_file, use_cookie);
}

const char* vj_get_cookie_filename(int idx)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end())
    {
        __cookies[idx] = "";
        return __cookies[idx].c_str();
    }

    __cookies[idx] = it->second->get_cookie_filename();
    return __cookies[idx].c_str();
}

void vj_del_cookie_file(int idx)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end()) return;

    return it->second->del_cookie_file();
}

bool vj_push_get_data(int idx, const char* name, const char* value)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end()) return false;

    __tmpgetdata[idx].push_back(get_data_item(name, value));
    return true;
}

bool vj_push_post_data(int idx, const char* name, const char* value)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end()) return false;

    __tmppostdata[idx].push_back(post_data_item(name, value));
    return true;
}

void vj_clear_get_data(int idx)
{
    map<int, get_data>::iterator it = __tmpgetdata.find(idx);
    if(it == __tmpgetdata.end()) return;

    it->second.clear();
}

void vj_clear_post_data(int idx)
{
    map<int, post_data>::iterator it = __tmppostdata.find(idx);
    if(it == __tmppostdata.end()) return;

    it->second.clear();
}

const char* vj_get(int idx, const char* url, unsigned int code, int cookie)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end())
    {
        __getstring[idx] = "";
        return __getstring[idx].c_str();
    }

    __getstring[idx] = it->second->get(url, __tmpgetdata[idx], code, (VJ_USE_COOKIE_TYPE)cookie);
    return __getstring[idx].c_str();
}

const char* vj_post(int idx, const char* url, unsigned int code, int cookie)
{
    map<int, VJSpider*>::iterator it = __vjspiders.find(idx);
    if(it == __vjspiders.end())
    {
        __poststring[idx] = "";
        return __poststring[idx].c_str();
    }

    __poststring[idx] = it->second->post(url, __tmppostdata[idx], code, (VJ_USE_COOKIE_TYPE)cookie);
    return __poststring[idx].c_str();
}
