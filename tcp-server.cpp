#include "server.hpp"



void set_address(char* hname, char* sname, struct sockaddr_in *sap, char *protocol);
void error(int status, int err, char *format, ...);

static void server(SOCKET s, struct sockaddr_in **peerp){
    send(s, "hello", 5, 0);
}


int main(int argc, char ** argv) {
    struct sockaddr_in local;
    struct sockaddr_in peer;
    char *hname; // host name
    char *sname; // server name
    int peerlen; // ?
    
    SOCKET s1; // for set socket numbers
    SOCKET s;
    
    const int on = 1; // root id
    
    INIT();
    
    if(argc == 2){
        hname = NULL;
        sname = argv[1];
    } else {
        hname = argv[1];
        sname = argv[2];
    }
    
    // setup numder and address of port in variable a local
    set_address(hname, sname, &local, "tcp");
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(!isvalidsock(s))
        error(1, errno, "error of call socket");
   
    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        error(1, errno, "error of call setsockopt");
    
    // binding to variable local the param define struct
    if(bind(s, (struct sockaddr * ) &local, sizeof(local)))
        error(1, errno, "error of call bind");
    
    // we is ready take connects of our clients
    if(listen(s, NLISTEN))
        error(1, errno, "error of call listen")
    
    do {
        /* for each client we begin proccessing */
        // size of payload
        peerlen = sizeof(peer);
        
        // enble accept an take payload only define sizes and self payload for our struct socket address
        s1 = accept(s, (struct sockaddr *) &peer, &peerlen);
        
        
        if(!isvalidsock(s1))
            error(1, errno, "error of call accept");
        
        server(s1, &peer);
        
        CLOSE(s1);
        
    } while(1); // for one client - obviously - while(0)
    
    EXIT(0);
}


static void set_address(char* hname, char* sname, struct sockaddr_in *sap, char *protocol){
    struct servent *sp;
    struct hostent *hp;
    char *endptr;
    short port;
    
    bzero(sap, sizeof(*sap));
    // AF_INET - pointer on Internet interface
    sap->sin_family = AF_INET;
    
    //for host
    if(hname != NULL){
        // this numberly address
        if(!inet_aton(hname, &sap->sin_addr)){
            // this strings address
            hp = gethostbyname(hname);
            if(hp == NULL)
                error(1, 0, "undefined host: %s\n", hname);
            sap->sin_addr = *(struct in_addr * )hp->h_addr;
        }
    } else
        // default value
        sap->sin_addr.s_addr = htonl(INADDR_ANY);
    
    // always for server
    port = strtol(sname, &endptr, 0);
    
    if(*endptr == '\0')
        sap->sin_port = htons(port);
    else{
        sp = getservbyname(sname, protocol);
    }
}

void error(int status, int err, char *format, ...){
    va_list ap;
    va_start(ap, fmt);
    
    fprintf(stderr, "%s: ", program_name);
    vfprintf(stderr, fmt, ap);
    
    va_end(ap);
    
    if(err)
        printf(stderr, ": %s (%d)\n", stderror(err), err);
    if (status)
        EXIT(status);
}
