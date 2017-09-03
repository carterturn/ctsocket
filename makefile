CPP=g++

BASE=ctsocket
CLIENT=ctclient
SERVER=ctserver

build: $(BASE).o $(CLIENT).o $(SERVER).o
	$(CPP) -shared -Wl,-soname,libctsocket.so -lgnutls -o libctsocket.so *.o
$(BASE).o : $(BASE).cpp
	$(CPP) -c -fPIC $(BASE).cpp
$(CLIENT).o : $(CLIENT).cpp
	$(CPP) -c -fPIC $(CLIENT).cpp
$(SERVER).o : $(SERVER).cpp
	$(CPP) -c -fPIC $(SERVER).cpp
install:
	cp -f libctsocket.so /usr/lib/
	chmod a+r /usr/lib/libctsocket.so
	[ -d /usr/include/ctsocket ] || mkdir /usr/include/ctsocket
	cp -f *.h /usr/include/ctsocket/
	chmod a+r /usr/include/ctsocket
	chmod a+r /usr/include/ctsocket/*
uninstall:
	rm -f /usr/lib/libctsocket.so
	rm -f /usr/include/ctsocket/*.h
	[ -d /usr/include/ctsocket ] && rmdir /usr/include/ctsocket
test_server: tserver.cpp $(BASE) $(CLIENT) $(SERVER)
	$(CPP) -o server tserver.cpp $(BASE) $(CLIENT) $(SERVER)
test_client: tclient.cpp $(BASE) $(CLIENT) $(SERVER)
	$(CPP) -o client tclient.cpp $(BASE) $(CLIENT) $(SERVER)
test: test_server test_client
clean:
	for file in $$(ls *.o); do rm $$file; done
	for file in $$(ls *.so); do rm $$file; done
	for file in $$(ls *.gch); do rm $$file; done
	if [ -e server ]; then rm server; fi
	if [ -e client ]; then rm client; fi
