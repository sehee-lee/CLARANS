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
#include "record.h"

using namespace std;

Record::Record()
{
    index = -1;
    id = "TMP_ID";
    cluster_id = -1;
    for(int i=0;i<NUM_DIM;i++)
    {
        dim_array[i] = '-';
    }
}

Record::~Record()
{
}

Record::Record(const Record &r)
{
    this->index = r.index;
    this->id = r.id;
    this->cluster_id = r.cluster_id;
    for(int i=0;i<NUM_DIM;i++)
    {
        this->dim_array[i] = r.dim_array[i];
    }
}

void Record::makecopy(Record *r)
{
    this->index = r->index;
    this->id = r->id;
    this->cluster_id = r->cluster_id;
    for(int i=0;i<NUM_DIM;i++)
    {
        this->dim_array[i] = r->dim_array[i];
    }
}

Record::Record(string v_id, long v_index, string dim)
{
    id = v_id;
    index = v_index;
    cluster_id = -1;
    StringTokenizer st;
    long count = st.tokenize(dim, ",");
    if(count != NUM_DIM)
    {
        cerr<<"Unexpected number of dimesions :"<<count<<" Expected : "<<NUM_DIM<<endl;
    }
    else
    {
        for(int i=0;i<count;i++)
        {
            stringstream ss(st.get_next_token());
            ss >> dim_array[i];
        }
    }
}

string Record::get_record()
{
    stringstream record("");
    for(int i=0;i < NUM_DIM;i++)
    {
        record<<dim_array[i]<<",";
    }
    return record.str();
}

string Record::get_id()
{
    return id;
}

void Record::set_id(string s)
{
    id = s;
}

long Record::get_index()
{
    return index;
}

void Record::set_index(long s)
{
    index = s;
}

char Record::get_dimension(long index)
{
    if(index < NUM_DIM)
    {
        return dim_array[index];
    }
    else
    {
        cerr<<"Dimension index out of range"<<endl;
        return '-';
    }
}

double Record::get_distance(Record *r)
{
    double distance = 0.;
    for(int i=0;i<NUM_DIM;i++)
    {
        if(r->dim_array[i] != this->dim_array[i])
        {
            distance += 1.;
        }
    }
    return distance;
}

void Record::set_dimension(long dim_cnt, char value)
{
    if(dim_cnt < NUM_DIM)
    {
        dim_array[dim_cnt] = value;
    }
}
