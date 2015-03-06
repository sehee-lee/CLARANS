/***************************************************************************
 *   Copyright (C) 2007 by Alok Watve   *
 *   alokkw@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H
#define SIZE 256

/**
	@author Alok Watve <alokkw@gmail.com>
*/
#include <string>

using namespace std;

class StringTokenizer
{
    private:
        string *tokens;
        int current, token_count;
    public:
        StringTokenizer();

        ~StringTokenizer();

        int tokenize(string s, string delim);

        string get_next_token();

        void reset_tokens();

        int get_token_count();
};

#endif
