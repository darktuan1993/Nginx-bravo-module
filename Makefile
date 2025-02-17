NGINX_SRC=/usr/local/nginx

all:
	./configure --add-dynamic-module=$(PWD)
	make modules

clean:
	rm -rf objs *.so
