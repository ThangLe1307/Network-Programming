
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

    // make a socket:

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // bind it to the port we passed in to getaddrinfo():

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    //TODO: error handler
    //TODO: free freeaddrinfo (neu khong khi chay lau ngay se tran RAM
}