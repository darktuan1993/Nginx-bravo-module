# Đảm bảo đường dẫn tới mã nguồn Nginx đúng
NGINX_SRC=/usr/src/nginx-1.27.3

# Các bước build module động của bạn
all:
	# Cấu hình Nginx với module động của bạn
	$(NGINX_SRC)/configure --add-dynamic-module=$(PWD)
	# Xây dựng các module
	make -C $(NGINX_SRC) modules

clean:
	# Xoá các file .so và các file tạm trong quá trình biên dịch
	rm -rf objs *.so
