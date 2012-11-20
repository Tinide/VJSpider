# VJ Spider

## What's VJ Spider?

***VJ Spider*** is the spider module on ***NBUT Virtual Judge***. Also, you can use it in your own projects.

The ***VJ Spider*** is based on ***[libcurl](http://curl.haxx.se/libcurl/)***. I wrote it via C++ and exported the C version.

## Compile

The ***VJ Spider*** is wrote on Visual Studio 2010. So you have to open it on Visual Studio 2010, or add the whole files to your own project.

Then you need the ***'libcurl.dll'*** and ***'libcurld.dll'***.

## How to use it

***VJ Spider*** supports for ***POST*** and ***GET***.

The header file ***'vjspider.h'*** is needed.

### Initizlize

At first, you should initialize the enviroment by calling the function:

    VJSpider::init_global_envi();

Then the Spider pointer should be created:

    VJSpider* spider = new VJSpider();

After you created the spider object, you should initialize it:

    spider->init_context();

### POST

To post the data to a website, you need a `post_data` object to store the data.

    post_data data;

Next you should make some ***'data pairs (key and value)'*** and push them into the `post_data` object:

    post_data_item item("key", "value");
    data.push_back(item);

After you did all of the steps above, you can post the data to a website via the spider and get the result:

    string html = spider->post("http://yourwebsite", data);

### GET

To execute the GET operation, the steps are almost the same as the POST operation.

you can reference to the code below:

    get_data data;
    data.push_back(get_data_item("key1", "value1"));
    data.push_back(get_data_item("key2", "value2"));
    string html = spider->get("http://yourwebsite", data);

### Use cookie

You can use the cookie when connect to one website.

#### Initialize

When you initialize a spider object, there are some parameters:

    bool init_context(bool auto_del_cookie = true, string cookie_file = "$", bool use_cookie = true);

+ auto_del_cookie

  It's in the TODO list.

+ cookie_file

  The filename of cookie file. If it's ***"$"***, the spider will generate a random filename.

+ use_cookie

  If it's true, the spider will use the cookie during its lifetime.

#### POST & GET

You can reference the functions below:

    string get(string url, get_data data, unsigend int code = VJCD_UTF8, VJ_USE_COOKIE_TYPE cookie = VJUCT_USE_COOKIE);
    string post(string url, post_data data, unsigned int code = VJCD_UTF8, VJ_USE_COOKIE_TYPE cookie = VJUCT_USE_COOKIE);

+ url
  
  The url of website.

+ data
  
  The data (POST or GET) you would like to upload to the website.

+ code

  Page code. You can choose one of those values below:

  - ***VJCD_GB2312*** : GB2312 (ACP)
  - ***VJCD_UTF8*** : UTF-8

+ cookie

  The cookie mode. You can choose one of those values below:

  - ***VJUCT_NO_COOKIE*** : No cookie used
  - ***VJUCT_USE_COOKIE*** : Use cookie that saved before but do not save it this time.
  - ***VJUCT_SAVE_COOKIE*** : Save the cookie this time.

## Contribute

Want to contribute? Great! You can get touch with [XadillaX](mailto:admin@xcoder.in).

Author: XadillaX

Contributors: Waiting for you...
