# Đảm bảo đường dẫn tới mã nguồn Nginx chính xác
NGINX_SRC=/usr/src/nginx-1.27.3

all:
	# Cấu hình Nginx với module động của bạn
	$(NGINX_SRC)/configure --add-dynamic-module=$(PWD)
	# Xây dựng các module
	make -C $(NGINX_SRC) modules

clean:
	# Xoá các file .so và các file tạm trong quá trình biên dịch
	rm -rf objs *.so
