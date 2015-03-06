//
// C++ Interface: Clarans
//
// Description: 
//
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

#ifndef KMEDOID_H
#define KMEDOID_H

#include <string>
#include <ctime>
#include <sys/times.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>

#include "record.h"
/**
    @author Alok <watvealo@cse.msu.edu>
*/

class Clarans
{
    private:
        long num_clusters;
        long max_iterations;
        long maxneighbor;
        vector<Record*> records;
        string datafilename;

        vector<long> select_random_medoids();

        /** Replaces a medoid with a non-medoid object such that total cost is reduced.
        Returns true if a successful swap is made. False otherwise.
        */
        bool swap_medoids(vector<long> *);
        void assign_points_to_clusters(vector<long> current);
        double get_cost();
    public:
        Clarans();

        Clarans(string filename, long n_clusters, long iterations, long mxn);

        ~Clarans();

        long read_file();

        void make_clusters();

        void display_clusters();

        long get_num_points();

        double get_avg_intracluster_distance();
};

#endif
