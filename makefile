CPP=g++

BASE=ctsocket.cpp ctsocket.h
CLIENT=ctclient.cpp ctclient.h
SERVER=ctserver.cpp ctserver.h

build: $(BASE) $(SECURE) $(CLIENT)
	$(CPP) -c -fPIC $(BASE)
	$(CPP) -c -fPIC $(CLIENT)
	$(CPP) -c -fPIC $(SERVER)
	$(CPP) -shared -Wl,-soname,libctsocket.so -o libctsocket.so *.o
install:
	cp -f libctsocket.so /usr/lib/
	[ -d /usr/include/ctsocket ] || mkdir /usr/include/ctsocket
	cp -f *.h /usr/include/ctsocket/
uninstall:
	rm -f /usr/lib/libctsocket.so
	rm -f /usr/include/ctsocket/*.h
	[ -d /usr/include/ctsocket ] && rmdir /usr/include/ctsocket
test_server: tserver.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -o server tserver.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE) -ltomcrypt
test_client: tclient.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE)
	$(CPP) -o client tclient.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER) $(SERVERSECURE) -ltomcrypt
test: test_server test_client
clean:
	for file in $$(ls *.o); do rm $$file; done
	for file in $$(ls *.so); do rm $$file; done
	for file in $$(ls *.gch); do rm $$file; done
	if [ -e server ]; then rm server; fi
	if [ -e client ]; then rm client; fi
