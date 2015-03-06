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

/**
    @author Alok Watve <watvealo@cse.msu.edu>
 */


#ifndef RECORD_H
#define RECORD_H

#include "stringtokenizer.h"
#include <iostream>
#include <string>
#include <sstream>

#define NUM_DIM 25

using namespace std;

/**
 * This class defined a vector which is our basic unit for data.
 */

class Record
{
    private :
        long index;
        string id;
        /** Id of the cluster this record belongs to */
        long cluster_id;
        char dim_array[NUM_DIM];
    public :
        Record();
        ~Record();

        /** Copy constructor*/
        Record(const Record &r);

        /** Generates a vector using the given dimensions.*/
        Record(string v_id, long v_index, string dim);

        /** Generates a vector using a string. The string should have each dimensions separated by comma*/
        Record(long id, string dim);

        /** Copy contents of r into this record*/
        void makecopy(Record *r);

        /** Returns hamming distance between two records.*/
        double get_distance(Record *r);

        /** Returns the given dimension of this vector.*/
        char get_dimension(long index);

        /** Returns a string represetation of record. Each dimension is separated by ','*/
        string get_record();

        /** Returns id of this record*/
        string get_id();

        /** Sets id of this record */
        void set_id(string s);

        /** Sets a particular dimension in the record*/
        void set_dimension(long dim_cnt, char value);

        /** Get cluster id */
        long get_cluster_id()
        {
            return cluster_id;
        }

        /** Set cluster id */
        void set_cluster_id(long c_id)
        {
            cluster_id = c_id;
        }

        /** Sets index of this record */
        void set_index(long s);

        /** Returns index of this record*/
        long get_index();
};

#endif
