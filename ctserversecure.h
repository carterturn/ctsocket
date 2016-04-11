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
#pragma once

#include "ctserver.h"
#include "ctsocketsecure.h"

class ctserversecure : public ctserver, public ctsocketsecure {
public:
ctserversecure(std::string key) : ctsocketsecure(key){}
	int s_write(std::string data){
		encryptstart();
		int result = c_write(encrypt(data));
		encryptend();
		return result;
	}
	std::string s_read(){
		encryptstart();
		std::string result = decrypt(c_read());
		encryptend();
		return result;
	}

};
