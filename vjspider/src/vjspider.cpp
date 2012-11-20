#include <vjspider.h>
#include <vjspider_helper.h>
#include <curl/curl.h>

bool sranded = false;

VJSpider::VJSpider() :
    m_szCookieFilename(""),
    m_bAutoDelCookie(true)
{
}

VJSpider::~VJSpider()
{
    if(m_bAutoDelCookie) del_cookie_file();
}

bool VJSpider::init_global_envi()
{
    CURLcode code;
    code = curl_global_init(CURL_GLOBAL_WIN32);
    if(CURLE_OK != code)
    {
        cerr << "Failed to initiate libcurl..." << endl;
        return false;
    }

    srand(time(NULL));
    VJSrand(time(NULL));

    return true;
}

void VJSpider::release_global_envi()
{
    curl_global_cleanup();
}

bool VJSpider::init_context(bool auto_del_cookie, string cookie_file, bool use_cookie)
{
    char guid[32];
    sprintf(guid, "%d.cookie", time(NULL));
    if(use_cookie)
    {
        m_szCookieFilename = (cookie_file == "$") ? guid : cookie_file;
        m_bAutoDelCookie = auto_del_cookie;
        return true;
    }
    else
    {
        m_szCookieFilename = "";
        m_bAutoDelCookie = true;
        return true;
    }

    return true;
}

string VJSpider::get_cookie_filename()
{
    return m_szCookieFilename;
}

void VJSpider::del_cookie_file()
{
    if(get_cookie_filename() != "") DeleteFile(get_cookie_filename().c_str());
}

string VJSpider::get(string url, get_data data, unsigned int code, VJ_USE_COOKIE_TYPE cookie)
{
    /**
     * Get the temp filename to receive the content.
     */
    string write_filename = generate_temp_filename(".rcv");
    FILE* fp = fopen(write_filename.c_str(), "w+");
    if(NULL == fp)
    {
        cerr << "Can't create the recieve file..." << endl;
        return "";
    }

    /**
     * Initiate the CURL handle.
     */
    CURL* curl;
    curl = curl_easy_init();
    if(NULL == curl)
    {
        cerr << "Can't create the CURL handle..." << endl;
        return "";
    }

    /**
     * It will output some information
     * when some error occured.
     */
//#ifdef _DEBUG
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//#endif

    if(data.size() != 0)
    {
        /**
         * If we have data in GET_DATA and it has no '?' in url,
         * then we have to add a '?' at the end of url.
         *
         * EG. HTTP://WWW.EXAMPLE.COM/INDEX.HTML -> HTTP://WWW.EXAMPLE.COM/INDEX.HTML?
         */
        if(url.find("?") == string::npos) url += "?";

        /**
         * We add the GET_DATA at the end of url
         *
         * EG. HTTP://WWW.EXAMPLE.COM/INDEX.HTML? -> HTTP://WWW.EXAMPLE.COM/INDEX.HTML?&USERNAME=EG
         */
        for(int i = 0; i < data.size(); i++)
        {
            url += "&";
            if(code == 936 || code == 0) url += VJURLHelper::escapeURL(data[i].first);
            url += "=";
			if(code == 936 || code == 0) url += VJURLHelper::escapeURL(data[i].second);
			else
			{
				VJCodeConvert convert(data[i].second.c_str(), VJCD_GB2312, code);
				url += VJURLHelper::escapeURL(convert.ToString());
			}
        }
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    /**
     * Parse the cookie using type.
     * Something like CURLOPT_COOKIEFILE and CURLOPT_COOKIEJAR.
     */
    switch(cookie)
    {
    case VJUCT_NO_COOKIE: break;
    case VJUCT_USE_COOKIE:
        {
            if(get_cookie_filename() != "")
            {
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, get_cookie_filename().c_str());
            }
            break;
        }
    case VJUCT_SAVE_COOKIE:
        {
            if(get_cookie_filename() != "")
            {
                curl_easy_setopt(curl, CURLOPT_COOKIEJAR, get_cookie_filename().c_str());
            }
            break;
        }

    default:
        {
            break;
        }
    }

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /** Excute 'GET' */
    curl_easy_perform(curl);

    /**
     * Free handles
     */
    fclose(fp);
    curl_easy_cleanup(curl);

    /**
     * Read the content
     */
    fp = fopen(write_filename.c_str(), "r");
    if(NULL == fp)
    {
        cerr << "Can't open the recieve file..." << endl;
        return "";
    }
    char ch;
    string html = "";
    while(!feof(fp)) ch = fgetc(fp), html += ch; 
    fclose(fp);

    DeleteFile(write_filename.c_str());

    /**
     * If it's UTF-8, then change it to GB2312
     */
    if(code == VJCD_UTF8)
    {
        VJCodeConvert convert(html.c_str(), VJCD_UTF8, VJCD_GB2312);
        html = convert.ToString();
    }

    return html;
}

string VJSpider::post(string url, post_data data, unsigned int code, VJ_USE_COOKIE_TYPE cookie)
{
    /**
     * Get the temp filename to receive the content.
     */
    string write_filename = generate_temp_filename(".rcv");
    FILE* fp = fopen(write_filename.c_str(), "w+");
    if(NULL == fp)
    {
        cerr << "Can't create the recieve file..." << endl;
        return "";
    }

    /**
     * Initiate the CURL handle.
     */
    CURL* curl;
    curl = curl_easy_init();
    if(NULL == curl)
    {
        cerr << "Can't create the CURL handle..." << endl;
        return "";
    }

    /**
     * It will output some information
     * when some error occured.
     */
//#ifdef _DEBUG
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//#endif

    string datastr = "";
    if(data.size() != 0)
    {
        /**
         * We add the GET_DATA at the end of url
         *
         * EG. '&USERNAME=EG'
         */
        for(int i = 0; i < data.size(); i++)
        {
            datastr += "&";
            if(code == 936 || code == 0) datastr += VJURLHelper::escapeURL(data[i].first);
			else
			{
				VJCodeConvert convert(data[i].first.c_str(), VJCD_GB2312, code);
				datastr += VJURLHelper::escapeURL(convert.ToString());
			}
            datastr += "=";
			if(code == 936 || code == 0) datastr += VJURLHelper::escapeURL(data[i].second);
			else
			{
				VJCodeConvert convert(data[i].second.c_str(), VJCD_GB2312, code);
				datastr += VJURLHelper::escapeURL(convert.ToString());
			}
        }
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, datastr.c_str());

    /**
     * Append the headlist
     */
    curl_slist* headerlist = NULL;
    static const char buf[] = "Expect:";
    headerlist = curl_slist_append(headerlist, buf);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

    /**
     * Parse the cookie using type.
     * Something like CURLOPT_COOKIEFILE and CURLOPT_COOKIEJAR.
     */
    switch(cookie)
    {
    case VJUCT_NO_COOKIE: break;
    case VJUCT_USE_COOKIE:
        {
            if(get_cookie_filename() != "")
            {
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, get_cookie_filename().c_str());
            }
            break;
        }
    case VJUCT_SAVE_COOKIE:
        {
            if(get_cookie_filename() != "")
            {
                curl_easy_setopt(curl, CURLOPT_COOKIEJAR, get_cookie_filename().c_str());
            }
            break;
        }

    default:
        {
            break;
        }
    }

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /** Excute 'POST' */
    curl_easy_perform(curl);

    /**
     * Free handles
     */
    fclose(fp);
    curl_easy_cleanup(curl);

    /**
     * Read the content
     */
    fp = fopen(write_filename.c_str(), "r");
    if(NULL == fp)
    {
        cerr << "Can't open the recieve file..." << endl;
        return "";
    }
    char ch;
    string html = "";
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch != 1) html += ch;
    }
    fclose(fp);

    DeleteFile(write_filename.c_str());

    /**
     * If it's UTF-8, then change it to GB2312
     */
    if(code == VJCD_UTF8)
    {
        VJCodeConvert convert(html.c_str(), VJCD_UTF8, VJCD_GB2312);
        html = convert.ToString();
    }

    return html;
}

string VJSpider::generate_temp_filename(string suffix)
{
    char filename[25];
    sprintf(filename, "%d", time(NULL));

    string ans = filename;
    for(int i = 0; i < 5; i++)
    {
        ans += ('A' + (rand() % 26));
    }
    ans += suffix;

    return ans;
}
