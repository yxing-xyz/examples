#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>
const char *req = "CONNECT 255.255.245.243:8443 HTTP/1.1\r\n"
"Host: 255.255.245.243:8443\r\n"
"User-Agent: curl/8.8.0\r\n"
"Proxy-Connection: Keep-Alive\r\n\r\n";
int main() {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    BIO *bio = BIO_new_ssl_connect(ctx);
    if (bio == NULL) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    SSL *ssl;
    BIO_get_ssl(bio, &ssl); // 获取SSL指针
    if (ssl == NULL) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    // 设置连接信息
    BIO_set_conn_hostname(bio, "127.0.0.1:8080");

    // 建立连接
    if (BIO_do_connect(bio) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    // 验证服务器证书
    // if (SSL_get_verify_result(ssl) != X509_V_OK) {
    //     fprintf(stderr, "Certificate verification error.\n");
    //     exit(1);
    // }

    // 发送数据
    if (BIO_write(bio, req, strlen(req)) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        printf("Data sent to server.\n");
    }

    // 读取服务器响应（可选）
/*     char buffer[1024];
    int len = BIO_read(bio, buffer, sizeof(buffer) - 1);
    if (len > 0) {
        buffer[len] = '\0';
        printf("Server response: %s\n", buffer);
    } else {
        ERR_print_errors_fp(stderr);
    } */
    SSL_set_shutdown(ssl, SSL_RECEIVED_SHUTDOWN | SSL_SENT_SHUTDOWN);
    // 关闭连接
    if (SSL_shutdown(ssl) != 1) {
        // 第一次调用失败，可能需要等待对方关闭通知
        if (SSL_shutdown(ssl) != 1) {
            ERR_print_errors_fp(stderr);
        }
    }

    // 清理工作
    BIO_free_all(bio);
    SSL_CTX_free(ctx);

    return 0;
}