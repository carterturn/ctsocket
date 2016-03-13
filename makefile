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
	cp libctsocket.so /usr/lib/
	mkdir /usr/include/ctsocket
	cp *.h /usr/include/ctsocket/
uninstall:
	rm /usr/lib/libctsocket.so
	rm /usr/include/ctsocket/*.h
	rmdir /usr/include/ctsocket
test_server: tserver.cpp $(BASE) $(CLIENT) $(SERVER)
	$(CPP) -o server tserver.cpp $(BASE) $(CLIENT) $(SERVER)
test_client: tclient.cpp $(BASE) $(SECURE) $(CLIENT) $(CLIENTSECURE) $(SERVER)
	$(CPP) -o client tclient.cpp $(BASE) $(CLIENT) $(SERVER)
test: test_server test_client
clean:
	rm *.o *.so *.gch
	rm server client
