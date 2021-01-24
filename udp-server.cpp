#include "server.hpp"



void server(SOCKET s, struct sockaddr_in *localp);


int main(int argc, char **argv){
    struct sockaddr_in local;
    char *hname;
    char *sname;
    SOCKET s;
    
    INIT();
    
    if(argc == 2){
        hname = NULL;
        sname = argv[1];
    } else {
        hname = argv[1];
        sname = argv[2];
    }
    
    set_address(hname, sname, &local, "udp");
    
    s = socket(AF_INET, SOCK_DREAM, 0);
    
    if(!isvalidsock(s))
        error(1, errno, "error call of socket");
    
    if(bind(s, (struct sockaddr * ) &local, sizeof(local)))
        error(1, errno, "error call of bind");
    
    server(s, &local);
    EXIT(0);
}


static void server(SOCKET s, struct sockaddr_in *localp){
    struct sockaddr_in peer;
    int peerlen;
    char buf[1];
    
    for(;;){
        peerlen = sizeof(peer);
        
        if(recvfrom(s, buf, sixeof(buf), 0, struct sockaddr * ) &peer, &peerlen) < 0)
            error(1, errno, "error call of recvfrom");
        
        if(sendto(s, "hello\n", 6, 0 (struct sockaddr * ) &peer, peerlen) < 0)
            error(1, errno, "error call of sendto");
    }
}
