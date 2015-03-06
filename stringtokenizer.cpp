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

#include "stringtokenizer.h"

using namespace std;

StringTokenizer::StringTokenizer()
{
    token_count = 0;
    tokens = new string[SIZE];
}


StringTokenizer::~StringTokenizer()
{
   delete[] tokens;
}


int StringTokenizer::tokenize(string s, string delim)
{
    int i = s.find_first_not_of(delim);
    int len = s.length();
    for(; i<len; i++)
    {
        int j = s.find_first_of(delim, i);
        if (j != s.npos)
        {
            tokens[token_count++] = s.substr(i, j-i);
            i = j;
        }
        else
        {
            tokens[token_count++] = s.substr(i);
            break;
        }
    }
    current = 0;
    return token_count;
}

string StringTokenizer::get_next_token()
{
    if(current >= token_count)
    {
        current = 0;
    }
    return tokens[current++];
}

void StringTokenizer::reset_tokens()
{
    current = 0;
}

int StringTokenizer::get_token_count()
{
    return token_count;
}
