/**************************************
 * @file    : vjspider.h
 * @author  : admin@xcoder.in
 * @date    : 2012-5-30
 */
#ifndef VJSPIDER_H
#define VJSPIDER_H

#include "vjspider_config.h"

enum VJ_USE_COOKIE_TYPE
{
    VJUCT_NO_COOKIE,
    VJUCT_USE_COOKIE,
    VJUCT_SAVE_COOKIE
};

/**
 * Class VJSpider
 * The secondary encapsulation for 'libcurl'
 * Make it more fit for C++
 */
class VJSPIDER_API VJSpider
{
public:
    VJSpider();
    virtual ~VJSpider();

    /**
     * Initiate the context of libcurl.
     * Including the cookie file.
     */
    bool                    init_context(bool auto_del_cookie = true, string cookie_file = "$", bool use_cookie = true);

    /**
     * Get the cookie filename.
     */
    string                  get_cookie_filename();

    /**
     * Delete the cookie file.
     */
    void                    del_cookie_file();

    /**
     * Do something to initiate or clear the enviroment of libcurl.
     */
    static bool             init_global_envi();
    static void             release_global_envi();

    /**
     * Generate a temp file
     */
    static string           generate_temp_filename(string suffix = "");

    /** CURL functions */
public:
    /**
     * Get the HTML content use GET method.
     */
    string                  get(string url, get_data data, unsigned int code = VJCD_UTF8, VJ_USE_COOKIE_TYPE cookie = VJUCT_USE_COOKIE);

    /**
     * Get the HTML content use POST method.
     */
    string                  post(string url, post_data data, unsigned int code = VJCD_UTF8, VJ_USE_COOKIE_TYPE cookie = VJUCT_SAVE_COOKIE);

private:
    string                  m_szCookieFilename;
    bool                    m_bAutoDelCookie;
};

#endif
