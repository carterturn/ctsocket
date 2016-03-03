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
	cp libctsocket.so /usr/lib/
	mkdir /usr/include/ctsocket
	cp *.h /usr/include/ctsocket/
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
	rm *.o *.so *.gch
	rm server client secure
