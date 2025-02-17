#ifndef _NGX_HTTP_BRAVO_MODULE_H_
#define _NGX_HTTP_BRAVO_MODULE_H_

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <sys/sysinfo.h>
#include <unistd.h>

// Hàm xử lý request
static ngx_int_t ngx_http_bravo_handler(ngx_http_request_t *r);

// Cấu trúc config module
typedef struct {
    ngx_flag_t enable;
} ngx_http_bravo_loc_conf_t;

// Hàm tạo config location
static void *ngx_http_bravo_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_bravo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

#endif // _NGX_HTTP_BRAVO_MODULE_H_
