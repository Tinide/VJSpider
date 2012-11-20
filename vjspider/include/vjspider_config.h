#ifndef VJSPIDER_CONFIG_H
#define VJSPIDER_CONFIG_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

#ifdef VJSPIDER_EXPORTS
#define VJSPIDER_API __declspec(dllexport)
#else
#define VJSPIDER_API __declspec(dllimport)
#endif

typedef pair<string, string> post_data_item;
typedef pair<string, string> get_data_item;
typedef vector<post_data_item> post_data;
typedef vector<get_data_item> get_data;

/**
 * The code names
 */
#define VJCD_GB2312             CP_ACP
#define VJCD_UTF8               CP_UTF8

#define VERBOSE_FILENAME        "CURL_VERBOSE.log"

#endif
