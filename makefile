CPP=g++

BASE=ctsocket.cpp ctsocket.h
SECURE=ctsocketsecure.cpp ctsocketsecure.h
CLIENT=ctclient.cpp ctclient.h
CLIENTSECURE=ctclientsecure.h
SERVER=ctserver.cpp ctserver.h
SERVERSECURE=ctserversecure.h

build: $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -c -fPIC $(BASE)
	$(CPP) -c -fPIC $(SECURE)
	$(CPP) -c -fPIC $(CLIENT)
	$(CPP) -c -fPIC $(CLIENTSECURE)
	$(CPP) -c -fPIC $(SERVER)
	$(CPP) -c -fPIC $(SERVERSECURE)
	$(CPP) -shared -Wl,-soname,libctsocket.so -o libctsocket.so *.o
install:
	cp -f libctsocket.so /usr/lib/
	[ -d /usr/include/ctsocket ] || mkdir /usr/include/ctsocket
	cp -f *.h /usr/include/ctsocket/
uninstall:
	rm /usr/lib/libctsocket.so
	rm /usr/include/ctsocket/*.h
	rmdir /usr/include/ctsocket
test_server: tserver.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -o server tserver.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE) -ltomcrypt
test_client: tclient.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -o client tclient.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE) -ltomcrypt
test_secure: tsecure.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -o secure tsecure.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE) -ltomcrypt
test: test_server test_client test_secure
clean:
	for file in $(ls *.o); do rm $file; done
	for file in $(ls *.so); do rm $file; done
	for file in $(ls *.gch); do rm $file; done
	if [ -e server ]; then rm server; fi
	if [ -e client ]; then rm client; fi
	if [ -e secure ]; then rm secure; fi
