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
#pragma once

#include <iostream>
#include <gnutls/gnutls.h>
#include <gnutls/crypto.h>

class ctsocketsecure {

public:
	ctsocketsecure(std::string key);
	
	std::string encrypt(std::string data);
	std::string decrypt(std::string data);
protected:
	gnutls_cipher_hd_t cipher_handle;
	gnutls_datum_t key;
};
