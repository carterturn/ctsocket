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
#include <iostream>

using namespace std;

int main(){

	ctserversecure server("passwordpassword");

	server.create(5553);
	server.getconn();

	cout << server.c_read() << "\n";
	server.c_write("server.create(5553); server.getconn(); cout << server.c_read() << 'n';");

	cout << server.s_read() << "\n";
	server.s_write("Testing testing testing testing testing testing testing testing testing    Copyright 2016 Carter Turnbaugh  This file is part of Terca C++ Sockets.  Terca C++ Sockets is free software: you can redistribute it and/or modify  it under the terms of the GNU General Public License as published by  the Free Software Foundation, either version 3 of the License, or  (at your option) any later version.  Terca C++ Sockets is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  GNU General Public License for more details.  You should have received a copy of the GNU General Public License  along with Terca C++ Sockets.  If not, see <http://www.gnu.org/licenses/>.");

	server.c_close();

	return 0;
}
