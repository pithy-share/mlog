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

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "mlog.h"
#include "mlog_port.h"

//#define MLOG_DEBUG_ENABLE
#ifdef MLOG_DEBUG_ENABLE
#define MLOG_DEBUG printf
#define MLOG_INFO printf
#define MLOG_ERROR printf
#else
#define MLOG_DEBUG(...)
#define MLOG_INFO(...)
#define MLOG_ERROR(...)
#endif
#ifdef MLOG_ENABLE
char string[LOG_STR_LEN];
char tmp_buf[LOG_STR_LEN/2];
#define TMP_LEN 10
char * level_str[] = {
	"debug",
	"info",
	"warn",
	"error",
	"fatal"
	
};


#ifdef MLOG_FILE_ENABLE
typedef enum {
	FILE_EXSIT,
	FILE_NOT_EXSIT
} exsit_t;
#define FILE_IDX_FILE "file_idx"
#define OLD_IDX(last_idx) (((last_idx) + 1) % MAX_FILE_CNTS)
typedef struct {
	int last_idx;
	file_len_t files_len[MAX_FILE_CNTS];
} file_mgr_t;

char filename[FILE_NAME_MAX_LEN];

file_mgr_t file_mgr = {
	0,
};

static int read_last_idx(void)
{
	FILE * file = NULL;
	char tmp[TMP_LEN];
	int idx= 0;
	file = fopen(FILE_IDX_FILE, "r");
	if(!file) {
		return 0;
	}
	if(fread(tmp, 1, sizeof(tmp), file)) {
		idx = atoi(tmp);
		MLOG_DEBUG("r idx:%u \n", idx);
	}

	fclose(file);
	return idx;
}

static int write_last_idx(int idx)
{
	FILE * file = NULL;
	char tmp[TMP_LEN];
	memset(tmp, 0, sizeof(tmp));
	file = fopen(FILE_IDX_FILE, "w+");
	if(!file) {
		return FILE_NOT_EXSIT;
	}
	sprintf(tmp, "%u\n", idx);
	fwrite(tmp, 1, strlen(tmp), file);
	fclose(file);
}

static exsit_t is_file_exsit(char * file_name, file_len_t* p_len)
{
	FILE * file = NULL;
	
	file = fopen(file_name, "r");
	if(!file) {
		return FILE_NOT_EXSIT;
	}
	fseek(file, 0, SEEK_END);
	if(p_len) {
		*p_len = ftell(file);
	}
	fclose(file);
	return FILE_EXSIT;
}
static void get_file_name(char* filename, int idx)
{
	char tmp[TMP_LEN];
	
	filename[0] = '\0';
	strcat(filename, LOG_FILE_NAME);
	sprintf(tmp, "_%u.log", idx);
	strcat(filename, tmp);
	MLOG_DEBUG("file name:%s \n", filename);
	

}
static FILE * get_log_file()
{
	int i;
	file_len_t f_len;
	
	for(i = 0; i < MAX_FILE_CNTS; i ++) {
		get_file_name(filename, i);
		if(is_file_exsit(filename , &f_len) == FILE_NOT_EXSIT) {
			write_last_idx(i);
			return fopen(filename, "w+");
		} else {
			if(f_len < ONE_LOGFILE_MAX_LEN) {
				return fopen(filename, "a+");
			}
		}
		file_mgr.files_len[i] = f_len;
	}
	
	file_mgr.last_idx = read_last_idx();
	file_mgr.last_idx = OLD_IDX(file_mgr.last_idx);
	
	get_file_name(filename, file_mgr.last_idx);
	write_last_idx(file_mgr.last_idx);
	return fopen(filename, "w+");
	
}
#endif
mlog_ret_t mlog(mlog_level_t level, char * fmt, ...)
{	
	va_list ap;
	file_len_t len = 0;
	FILE * log_file = NULL;
	
	if(level < MLOG_LEVEL_CUR) {
		MLOG_DEBUG("level small %d %d\n", level, MLOG_LEVEL_CUR);
		return MLOG_OK;
	}
	
	if(level >= MLOG_LEVEL_MAX) {
		MLOG_ERROR("para err\n");
		return MLOG_PARA_ERR;
	}
	
	va_start(ap,fmt);

	tmp_buf[0] = '\0';
	get_time_str(tmp_buf);

	len += sprintf(string + len, "%s ", tmp_buf);
	len += sprintf(string + len, "%s: ", level_str[level]);
	len += vsprintf(string + len, fmt, ap);
	
	print_by_user(string);
	
	va_end(ap);

#ifdef MLOG_FILE_ENABLE

	log_file = get_log_file();
	
	if(log_file == NULL) {
		MLOG_ERROR("mlog file open err\n");
		return MLOG_OPEN_FILE_ERR;
	}

	fprintf(log_file, string);
	
	fclose(log_file);

#endif

	return MLOG_OK;
}

#endif
