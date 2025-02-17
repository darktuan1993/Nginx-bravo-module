#include "ngx_http_bravo_module.h"

// Hàm xử lý request
static ngx_int_t ngx_http_bravo_handler(ngx_http_request_t *r) {
    ngx_buf_t *b;
    ngx_chain_t out;
    struct sysinfo s_info;
    char buffer[512];

    if (sysinfo(&s_info) != 0) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    char hostname[128];
    gethostname(hostname, sizeof(hostname));

    int len = snprintf(buffer, sizeof(buffer),
        "<html><head><title>Bravo System LB Status</title></head>"
        "<body><h1>Bravo System Load Balancer Status</h1>"
        "<p><strong>Hostname:</strong> %s</p>"
        "<p><strong>Nginx Version:</strong> %s</p>"
        "<p><strong>Uptime:</strong> %ld seconds</p>"
        "</body></html>",
        hostname, NGINX_VER, s_info.uptime
    );

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = len;
    ngx_str_set(&r->headers_out.content_type, "text/html");

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    out.buf = b;
    out.next = NULL;
    b->pos = (u_char *) buffer;
    b->last = (u_char *) buffer + len;
    b->memory = 1;
    b->last_buf = 1;

    ngx_http_send_header(r);
    return ngx_http_output_filter(r, &out);
}

// Cấu hình module
static ngx_command_t ngx_http_bravo_commands[] = {
    { ngx_string("bravo_system_lb_status"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_bravo_loc_conf_t, enable),
      NULL },
    ngx_null_command
};

// Tạo config cho location
static void *ngx_http_bravo_create_loc_conf(ngx_conf_t *cf) {
    ngx_http_bravo_loc_conf_t *conf;
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_bravo_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }
    conf->enable = NGX_CONF_UNSET;
    return conf;
}

static char *ngx_http_bravo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child) {
    ngx_http_bravo_loc_conf_t *prev = parent;
    ngx_http_bravo_loc_conf_t *conf = child;
    ngx_conf_merge_value(conf->enable, prev->enable, 0);
    return NGX_CONF_OK;
}

// Khai báo module
static ngx_http_module_t ngx_http_bravo_module_ctx = {
    NULL, NULL,
    NULL, NULL, NULL, NULL,
    ngx_http_bravo_create_loc_conf,
    ngx_http_bravo_merge_loc_conf
};

ngx_module_t ngx_http_bravo_module = {
    NGX_MODULE_V1,
    &ngx_http_bravo_module_ctx,
    ngx_http_bravo_commands,
    NGX_HTTP_MODULE,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NGX_MODULE_V1_PADDING
};
