# Makefile - make the final program.
# Copyright (C) 2023 Water Horizontal Branch

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
bfi: bfi.c
	$(CC) bfi.c -o bfi -std=c11
bf2c: bf2c.c
	$(CC) bf2c.c -o bf2c -std=c11
.PHONY clean: 
	rm bfi bf2c
.PHONY install: bfi bf2c
	rm /usr/bin/bfi /usr/bin/bf2c
	cp bfi /usr/bin/bfi
	cp bf2c /usr/bin/bf2c