
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


int main() {

    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints, 0, sizeof hints); // xoa bo nho rac
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE;     // dung dia chi ip cua may hien tai

    /*
     * Điểm "ăn tiền" ở đây là cờ AI_PASSIVE.
     * Khi bạn bật cờ này, bạn đang bảo hệ điều hành: "Tôi sắp làm một Server.
     * Hãy tự động lấy địa chỉ IP của chính cái máy tính này
     * (tương đương INADDR_ANY hoặc 0.0.0.0) để điền vào cấu trúc cho tôi".
     * Nhờ vậy, bạn không cần quan tâm máy mình đang có IP là gì.
    */

    getaddrinfo(NULL, "3490", &hints, &res);

    /*
     * Vì đã dùng AI_PASSIVE ở trên, bạn được phép truyền tham số đầu tiên (node) là NULL.
     * Hàm này sẽ phân giải Port "3490", đóng gói nó cùng với IP máy của bạn, và trả về một cấu trúc res hoàn chỉnh.
    */

    // tao socket va tra ve FD:
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    //TODO: error handler
    //TODO: free freeaddrinfo (neu khong khi chay lau ngay se tran RAM)

}


// chi chap nhan connect o may local
int local_connection() {

    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // Tự động hỗ trợ cả IPv4 (127.0.0.1) và IPv6 (::1)
    hints.ai_socktype = SOCK_STREAM; // Dùng TCP

    // BƯỚC 1: Bỏ dòng hints.ai_flags = AI_PASSIVE;
    // Vì AI_PASSIVE chỉ dùng khi bạn muốn lắng nghe trên mọi giao diện (0.0.0.0)

    // BƯỚC 2: Truyền "localhost" (hoặc "127.0.0.1") thay vì truyền NULL
    int status = getaddrinfo("localhost", "3490", &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // Tạo socket và bind như cũ
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);

    // ĐỪNG QUÊN giải phóng bộ nhớ sau khi dùng xong res
    freeaddrinfo(res);

    return 0;
}