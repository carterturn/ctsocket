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
#include "ctsocketsecure.h"

using namespace std;

ctsocketsecure::ctsocketsecure(string key){
		register_cipher(&aes_desc);
	
		xts_start(find_cipher("aes"), (const unsigned char *) key.c_str(), (const unsigned char *) key.c_str(), 16, 0, &aes);
}

string ctsocketsecure::decrypt(string data){
		if(data.length() > 31){
				string forward = decrypt(data.substr(0, 31));
				string backward = decrypt(data.substr(31));
				return forward + backward;
		}

		unsigned char msg[data.length()];
		bzero(msg, data.length());
	
		// I will admit less than perfect knowledge of cryptography, so I am leaving the tweak as 0 for now (until I can come up with a client-server sync trick)
		unsigned char tweak[256];
		memset(tweak, '\0', 256);
		snprintf((char*)tweak, 256, "%d", 0);
	
		xts_decrypt((unsigned char *) data.c_str(), data.length(), msg, tweak, &aes);

		string result = string((const char*) msg).substr(0, data.length());
		
		return result.substr(0, result.find('\4'));
}

string ctsocketsecure::encrypt(string data){
		if(data.length() > 31){
				string forward = encrypt(data.substr(0, 31));
				string backward = encrypt(data.substr(31));
				return forward + backward;
		}
		
		// I will admit less than perfect knowledge of cryptography, so I am leaving the tweak as 0 for now (until I can come up with a client-server sync trick)
		unsigned char tweak[256];
		memset(tweak, '\0', 256);
		snprintf((char*)tweak, 256, "%d", 0);

		int padlength = 31 - data.length();

		for(int i = 0; i < padlength; i++) data += '\4';

		unsigned char emsg[data.length()];

		xts_encrypt((const unsigned char *) data.c_str(), data.length(), emsg, tweak, &aes);

		string result = "";
		for(int i = 0; i < data.length(); i++){
				result += emsg[i];
		}

		return result;
}
