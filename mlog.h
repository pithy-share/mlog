/*
MIT License

Copyright (c) 2020 zhangyong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef __MLOG_H__
#define __MLOG_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MLOG_LEVEL_DEBUG,
	MLOG_LEVEL_INFO,
	MLOG_LEVEL_WARN,
	MLOG_LEVEL_ERROR,
	MLOG_LEVEL_FATAL,
	MLOG_LEVEL_MAX
} mlog_level_t;

typedef unsigned int file_len_t;


typedef enum {
	MLOG_OK,
	MLOG_OPEN_FILE_ERR,
	MLOG_PARA_ERR
} mlog_ret_t;
#define SIZE_K (1024)
#define SIZE_M (1024*SIZE_K)

#define MLOG_ENABLE
#define MLOG_FILE_ENABLE
#define MLOG_LEVEL_CUR MLOG_LEVEL_DEBUG

#define LOG_STR_LEN 1024

#define FILE_NAME_MAX_LEN 128
#define LOG_FILE_NAME "mylog"

#define MAX_FILE_CNTS 2
#define ONE_LOGFILE_MAX_LEN (2*SIZE_M)


#ifdef MLOG_ENABLE
mlog_ret_t mlog(mlog_level_t level, char * fmt, ...);
#define M_DEBUG(x...) mlog(MLOG_LEVEL_DEBUG, x)
#define M_INFO(x...)  mlog(MLOG_LEVEL_INFO, x)
#define M_WARN(x...)  mlog(MLOG_LEVEL_WARN, x)
#define M_ERROR(x...) mlog(MLOG_LEVEL_ERROR, x)
#define M_FATAL(x...) mlog(MLOG_LEVEL_FATAL, x)
#else 
#define M_DEBUG(x...)
#define M_INFO(x...)
#define M_WARN(x...)
#define M_ERROR(x...)
#define M_FATAL(x...)
#endif


//M_DEBUG("sdffsf %s", hello);

#ifdef __cplusplus
}
#endif
#endif
