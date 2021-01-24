#include "server.hpp"



void client(SOCKET s, struct sockaddr_in *peerp);


int main(int argc, char **argv){
    struct sockaddr_in peer;
    SOCKET s;
    
    INIT();
    
    set_address(argv[1], argv[2], &peer, "tcp");
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(!isvalidsock(s))
        error(1, errno, "error call of socket");
    
    if(connect(s, (struct socketaddr * ) &peer, sizeof(peer)))
        error(1, errno, "error call of connect");
    
    client(s, &peer);
    EXIT(0);
}


static void client(SOCKET s, struct sockaddr_in *peerp) {
    int rc;
    char buf[120];
    
    for(;;){
        rc = recv(s, buf, sizeof(buf), 0);
        
        if(rc <= 0)
            break;
        
        write(1, buf, rc);
    }
}
