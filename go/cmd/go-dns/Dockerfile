FROM golang:latest
COPY  ./* /go-dns/
RUN  ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
     echo 'Asia/Shanghai' >/etc/timezone && \
     go env -w GO111MODULE=on && \
     go env -w GOPROXY=https://goproxy.cn,direct && \
     cd /go-dns && \
     go build -o /bin/app
EXPOSE 53 5353
ENTRYPOINT [ "app" ]