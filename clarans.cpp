//
// C++ Implementation: Clarans
//
// Description: 
//
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

#include "clarans.h"

Clarans::Clarans()
{
}


Clarans::~Clarans()
{
}

Clarans::Clarans(string filename, long n_clusters, long iterations, long mxn)
{
    datafilename = filename;
    num_clusters = n_clusters;
    max_iterations = iterations;
    maxneighbor = mxn;
}

long Clarans::get_num_points()
{
    return records.size();
}

long Clarans::read_file()
{
    ifstream in_file;
    in_file.open(datafilename.c_str(), ios::in);
    if(!in_file)
    {
        cerr<<"Could not open file :"<<datafilename<<endl;
        return 1;
    }

    // Read all the records from the file into a vector.
    in_file.clear();
    in_file.seekg(0, ios::beg);
    long cluster_index = 0;
    while(!in_file.eof())
    {
        string line;
        getline(in_file, line);
        if(line.length() > 3  && line[0] != '#')
        {
            StringTokenizer st1;
            st1.tokenize(line, ":");
            string id = st1.get_next_token();
            string v = st1.get_next_token();
            try
            {
                Record *r = new Record(id, cluster_index, v);
                records.push_back(r);
            }
            catch (std::bad_alloc ex)
            {
                cout<<"Caught bad_alloc in "<<__FILE__<<":"<<__LINE__<<endl;
                exit(2);
            }
        }
        cluster_index++;
    }
    in_file.close();
    return cluster_index;
}

void Clarans::assign_points_to_clusters(vector<long> current)
{
    long num_records = records.size();
    for(long i=0;i<num_records;i++)
    {
        double distance = 9999999.;
        long cl_id = -1;
        for(long j=0;j<current.size();j++)
        {
            long index = current[j];
            double d = records[i]->get_distance(records[index]);
            if(d < distance)
            {
                distance = d;
                cl_id = index;
            }
        }
        records[i]->set_cluster_id(cl_id);
    }
}

double Clarans::get_cost()
{
    long num_records = records.size();
    double cost = 0.;
    for(long i=0;i<num_records;i++)
    {
        long medoid = records[i]->get_cluster_id();
        cost += records[i]->get_distance(records[medoid]);
    }
    return cost;
}

void Clarans::make_clusters()
{
    long num_records = records.size();
    double min_cost = 9999999.;
    vector <long> best_medoids;
    long itr = 0;
    srand(time(NULL));
    for(long i=0;i<max_iterations;i++)
    {
        // Randomly select a set of medoids
        vector<long> current = select_random_medoids();
        // Vector representing indexes of cluster centers corresponding to
        // current solution
        assign_points_to_clusters(current);
        swap_medoids(&current);
        double cost = get_cost();
        if(cost < min_cost)
        {
            min_cost = cost;
            best_medoids = current;
        }
    }
    assign_points_to_clusters(best_medoids);
}

void Clarans::display_clusters()
{
    long num_records = records.size();
    bool * displayed = new bool[num_records];
    for(long i=0;i<num_records;i++)
    {
        displayed[i] = false;
    }
    for(long i=0;i<num_records;i++)
    {
        if(displayed[i] == false)
        {
            displayed[i] = true;
            long cl_id = records[i]->get_cluster_id();
//             cout<<records[i]->get_id()<<","<<records[i]->get_record()<<endl;
            // Display all the records in this cluster
            for(long j = i;j<num_records;j++)
            {
                long id = records[j]->get_cluster_id();
                if(id == cl_id)
                {
                    displayed[j] = true;
                    cout<<records[j]->get_id()<<","<<records[j]->get_record()<<endl;
                }
            }
            cout<<"*************************"<<endl;
        }
    }
}

double Clarans::get_avg_intracluster_distance()
{
    long num_records = records.size();
    bool * done = new bool[num_records];
    for(long i=0;i<num_records;i++)
    {
        done[i] = false;
    }
    double avg_icd = 0.;
    long verification = 0;
    for(long i=0;i<num_records;i++)
    {
        if(done[i] == false)
        {
            long cl_id = records[i]->get_cluster_id();
            vector <long> records_in_this_cluster;
            for(long j = i;j<num_records;j++)
            {
                long id = records[j]->get_cluster_id();
                if(id == cl_id)
                {
                    done[j] = true;
                    records_in_this_cluster.push_back(j);
                }
            }
            long size_of_cluster = records_in_this_cluster.size();
            verification += size_of_cluster;
            double dist = 0.;
            for(long j=0;j< size_of_cluster;j++)
            {
                for(long k=j+1;k< size_of_cluster;k++)
                {
                    dist += records[records_in_this_cluster[j]]->get_distance(records[records_in_this_cluster[k]]);
                }
            }
            dist /= (size_of_cluster*(size_of_cluster - 1)/2);
            avg_icd += dist;
        }
    }
    assert(verification == num_records);
    avg_icd /= num_clusters;
    return avg_icd;
}

bool Clarans::swap_medoids(vector <long> * crrnt)
{
    // I am following algorithm described by Han & Ng (CLARANS 1994)
    long num_records = records.size();
    long m = 0;
    assert(num_clusters == crrnt->size());
    while(m<maxneighbor)
    {
        bool * is_medoid = new bool[num_records];
        for(long i=0;i<num_records;i++)
        {
            is_medoid[i] = false;
        }
        for(long i=0;i<num_clusters;i++)
        {
            is_medoid[(*crrnt)[i]] = true;
        }

        long index_oi = rand()%num_clusters;
        long o_i = (*crrnt)[index_oi];
        long o_h = rand()%num_records;
        // Make sure that o_h is a non-medoid
        while(is_medoid[o_h])
        {
            o_h = rand()%num_records;
        }
        double cost = 0.;
        // Find the cost of swapping o_i and o_h
        for(long o_j=0;o_j<num_records;o_j++)
        {
            if(!is_medoid[o_j])
            {
                // Distance of o_j from its current medoid.
                long cur_med = records[o_j]->get_cluster_id();
                double d1 = records[o_j]->get_distance(records[cur_med]);
                // Distance of o_j from new medoid
                double d2 = records[o_j]->get_distance(records[o_h]);
                // Distance of o_j from any other medoid
                double d3 = 9999999.;
                for(long j=0;j< num_clusters;j++)
                {
                    if(j != index_oi && (*crrnt)[j] != cur_med && records[o_j]->get_distance(records[(*crrnt)[j]]) < d3)
                        d3 = records[o_j]->get_distance(records[(*crrnt)[j]]);
                }

                if(cur_med == o_i)
                {
                    if(d3 < d2)
                    {
                        // Case I: o_j currently belongs to o_i and switches cluster to some other existing medoid after swap
                        assert(d3 >= d1);
                        cost += (d3 - d1);
                    }
                    else
                    {
                        // Case II: o_j currently belongs to o_i and switches cluster to new medoid o_h
                        cost += (d2 - d1);
                    }
                }
                else
                {
                    // Case IV: o_j does not belong to o_i but switches cluster to new medoid o_h
                    if(d2 < d1)
                    {
                        cost += (d2 - d1);
                    }
                    // Case III: o_j does not belong to o_i, neither does it switch cluster after the swap. Cost is not chaged hence nothing needs to be done here.
                }
            }
        }
        if(cost < 0)
        {
            (*crrnt)[index_oi] = o_h;
            assign_points_to_clusters(*crrnt);
            m = 0;
        }
        else
        {
            m++;
        }
        delete[] is_medoid;
    }
}

vector<long> Clarans::select_random_medoids()
{
    long num_records = records.size();
    vector <long> current;
    for(long i=0;i<num_clusters;i++)
    {
        bool flag = true;
        long m;
        while(flag)
        {
            flag = false;
            m = rand() % num_records;
            // Check if this medoid is selected already
            for(long j=0;j<current.size();j++)
            {
                if(current[j] == m)
                {
                    flag = true;
                }
            }
        }
        current.push_back(m);
    }
    return current;
}

int main(int argc, char ** argv)
{
    string filename = "data.txt";
    long num_clusters = 2;
    long iterations = 10;
    long maxneighbor = 10;
    if(argc > 1)
    {
        filename = argv[1];
    }
    if(argc > 2)
    {
        sscanf(argv[2], "%d", &num_clusters);
    }
    if(argc > 3)
    {
        sscanf(argv[3], "%d", &iterations);
    }
    if(argc > 4)
    {
        sscanf(argv[4], "%d", &maxneighbor);
    }
    Clarans problem_instance(filename, num_clusters, iterations, maxneighbor);
    problem_instance.read_file();

    tms start_buffer, finish_buffer;
    long start = times(&start_buffer);
    problem_instance.make_clusters();
    long finish = times(&finish_buffer);
    long total_time = (finish_buffer.tms_utime - start_buffer.tms_utime) + (finish_buffer.tms_stime - start_buffer.tms_stime);
    cout<<"#Data_points="<<problem_instance.get_num_points()<<";Clusters="<<num_clusters<<";Time="<<total_time<<";Avg intra-cluster Distance="<<problem_instance.get_avg_intracluster_distance()<<endl;
    problem_instance.display_clusters();
}
