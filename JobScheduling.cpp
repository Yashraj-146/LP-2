#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Job {
    int processing_time;
    int profit;
    int deadline;
};

bool compareJobs(const Job& job1, const Job& job2)
{
    return job1.deadline < job2.deadline;
}

pair<int, vector<Job>> greedyJobScheduling(vector<Job>& jobs) {
    int current_time = 0;
    vector<Job> scheduled_jobs;

    int total_profit = 0;

    for(Job& job : jobs) {
        if(job.processing_time + current_time <= job.deadline)
        {
            current_time += job.processing_time;
            scheduled_jobs.push_back(job);
            total_profit += job.profit;
        }
    }
    return make_pair(total_profit, scheduled_jobs);
}

int main() {
    vector<Job> jobs = {
        {1, 10, 3},
        {2, 20, 6},
        {3, 30, 8}
    };
    pair<int, vector<Job>> result = greedyJobScheduling(jobs);

    cout<<"Scheduled Jobs: \n";
    for(Job& job : result.second) {
        cout<<"Processing time: "<<job.processing_time<<", Profit: "<<job.profit<<", Deadline: "<<job.deadline<<endl;
    }
    cout<<"Total Profit: "<<result.first<<endl;

    return 0;
}