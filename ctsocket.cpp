/*
  Copyright 2017 Carter Turnbaugh

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
#include "ctsocket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

using namespace std;

string ctsocket::c_read(){

	string data = "";
	bool reading = true;
	while(reading){
		char reccstr[ctsocket_datasize + 1];
		bzero(reccstr, ctsocket_datasize + 1);
		read(socketid, reccstr, ctsocket_datasize + 1);
		for(int i = 1; i < (unsigned char) reccstr[0] + 1; i++){
			data += reccstr[i];
		}
		if(((unsigned char) reccstr[0]) < ctsocket_datasize) reading = false;
	}

	return data;
}

int ctsocket::c_write(string data){

	if(data.length() >= ctsocket_datasize){
		while(data.length() > 0){
			string temp = data.substr(0, ctsocket_datasize);
			data.erase(0, ctsocket_datasize);
			char msg[temp.length() + 1];
			bzero(msg, temp.length() + 1);
			msg[0] = temp.length();
			for(int i = 0; i < temp.length(); i++){
				msg[i+1] = temp[i];
			}
			send(socketid, msg, sizeof(msg), 0);
			if(data.length() == 0 && temp.length() == ctsocket_datasize) data += '\0';
		}
	}
	else{
		char msg[data.length() + 1];
		bzero(msg, data.length() + 1);
		msg[0] = data.length();
		for(int i = 0; i < data.length(); i++){
			msg[i+1] = data[i];
		}
		send(socketid, msg, sizeof(msg), 0);
	}
	
	return 0;
}
