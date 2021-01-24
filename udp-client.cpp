#include "server.hpp"



void client(SOCKET s, struct sockaddr_in *peerp);


int main(int argc, char **argv){
    struct sockaddr_in peer;
    SOCKET s;
    
    INIT();
    
    set_address(argv[1], argv[2], &peer, "udp");
    
    s = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(!isvalidsock(s))
        error(1, errno, "error call of socket");
    
    client(s, &peer);
    EXIT(0);
}


static void client(SOCKET s, struct sockaddr_in *peerp) {
    int rc;
    int peerlen
    char buf[120];
    
    int peerlen = sizeof(*peer);
    
    if(sendto(s, "", 1, 0, (struct sockaddr * ) peerp, peerlen) < 0)
        error(1, errno, "error call of sendto");
    
    rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr * ) peerp, &peerlen);
    
    if (rc >= 0)
        write(1, buf, rc);
    else
        error(1, errno, "error call of recvfrom");
}
