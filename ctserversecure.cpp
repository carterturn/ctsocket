/*
  Copyright 2016 Carter Turnbaugh

  This file is part of Terca C++ Sockets.

  Terca C++ Sockets is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca C++ Sockets is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca C++ Sockets.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ctserversecure.h"

using namespace std;

ctserversecure::ctserversecure(string key){
	register_cipher(&aes_desc);
	
	xts_start(find_cipher("aes"), (const unsigned char *) key.c_str(), (const unsigned char *) key.c_str(), 16, 0, &aes);
}

string ctserversecure::s_read(){
	
	string emessage = "";

	bool done = false;
	while(!done){

		string tmpmsg = c_read();
		if(tmpmsg.substr(tmpmsg.length() - 6) == "#@#end"){
			done = true;
		}
		else{
			emessage += (char) atoi(tmpmsg.c_str());
		}
		cout << ":" << hex << tmpmsg.substr(tmpmsg.length() - 6) << ": " << done << "\n";
	}
	
	unsigned char msg[emessage.length()];
	bzero(msg, emessage.length());
	
	// I will admit less than perfect knowledge of cryptography, so I am leaving the tweak as 0 for now (until I can come up with a client-server sync trick)
	unsigned char tweak[256];
	memset(tweak, '\0', 256);
	snprintf((char*)tweak, 256, "%d", 0);
	cout << "secureread\n";
	
	xts_decrypt((unsigned char *) emessage.c_str(), emessage.length(), msg, tweak, &aes);

	return string((const char*) msg).substr(0, emessage.length());
}

int ctserversecure::s_write(string message){
	return c_write(message);
}
