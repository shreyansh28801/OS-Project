#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int arrival_time;
    int temp; //for temporary data storage
    int burst_time;
    int exit_time;
    int spendInIo;
    int io;
    int cpu;
    bool responseFlag;
    int firsrt_time_cpu_got;
};

bool isEqual(Node a, Node b)
{
    if (a.arrival_time != b.arrival_time)
        return false;
    if (a.burst_time != b.burst_time)
        return false;
    if (a.exit_time != b.exit_time)
        return false;
    if (a.io != b.io || a.cpu != b.cpu)
        return false;
    return true;
}

bool isAnyOfBtGreaterThanZero(vector<Node> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].burst_time > 0)
        {
            return true;
        }
    }

    return false;
}

void print_arr(vector<Node> arr)
{
    cout << "Array of Processes\n";
    int i = 0;
    cout << setw(4) << "pro. name" << setw(8) << "  A.T." << setw(9) << "    B.T." << setw(7) << "C .T ." << setw(15) << "TurnArornd Time" << setw(15) << "WatingTime " << setw(20) << "Response Time \n";
    ;
    for (auto x : arr)
    {
        
        cout << setw(4) << "P" << i << setw(8) << x.temp << setw(9) << x.burst_time << setw(7) << x.exit_time << setw(15) << x.exit_time - x.temp << setw(15) << x.exit_time - x.temp - x.burst_time << setw(15) << x.firsrt_time_cpu_got - x.temp << setw(15) << endl;
        i++;
    }
}

void print_arr_beforeSove(vector<Node> arr)
{
    cout << "Array of Processes\n";
    int i = 0;
    cout << setw(25) << "pro. name" << setw(8) << "  A.T." << setw(9) << "    B.T." << setw(12) << "C .T ." << setw(24) << "time spent in I/o"<<setw(30) << "  I/o condition given\n";
    for (auto x : arr)
    {
       
        cout << setw(20) << "P" << i << setw(10) << x.arrival_time << setw(10) << x.burst_time << setw(10) << x.exit_time << setw(20) << x.spendInIo<<setw(20) << x.io << setw(10) << x.cpu << setw(10) << endl;
        i++;
    }
}

void print_node(Node x)
{
    cout << "Node: \n";
    cout << x.arrival_time << " " << x.burst_time << " " << x.exit_time << " " << x.io << " " << x.cpu << " " << endl;
}

int main()
{
    int n, i;
    cin >> n;
    vector<Node> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].arrival_time >> arr[i].burst_time;
        arr[i].exit_time = -1;
        if (i % 2 == 0)
        {
            arr[i].io = 2;
            arr[i].cpu = 5;
        }
        else
        {
            arr[i].io = 3;
            arr[i].cpu = 6;
        }
    }
    for (int i = 0; i < n; i++)
    {
        arr[i].temp = arr[i].arrival_time;
        arr[i].responseFlag = true;
    }

    cout << "\nExplaining each and every intermediate step of solution of q2 using Shortest Job First  :-\n";
    print_arr_beforeSove(arr);

    int current_Time = 0;
    int not_to_select_after_1_iteration;
    int curr_index = 0;
    
    while (isAnyOfBtGreaterThanZero(arr))
    {
        int flag = 1;
       
        cout << "\ncurrent time is " << current_Time << "\n";
        vector<Node> tmp;
        auto it = arr[0];
        int mn_burst_time;

        for (int i = 0; i < n; i++)
        {
            if (arr[i].arrival_time <= current_Time && arr[i].burst_time != 0)
            {
                if (i != not_to_select_after_1_iteration)
                {
                    /* code */
                    tmp.push_back(arr[i]);
                }
            }
        }

        if (0 == tmp.size())
        {

            flag = 0;
            mn_burst_time = INT_MAX;
            int prev_mn = mn_burst_time;
            for (int i = 1; i < arr.size(); i++)
            {
                if (arr[i].burst_time != 0)
                {
                    // it
                    mn_burst_time = min(mn_burst_time, arr[i].burst_time);
                    it = mn_burst_time != prev_mn ? arr[i] : it;
                }
            }
        }

        if (1 == flag)
        {
            it = tmp[0];
            mn_burst_time = it.burst_time;
            for (int i = 1; i < tmp.size(); i++)
            {
                if (tmp[i].burst_time > 0 && mn_burst_time > tmp[i].burst_time)
                {
                    // it
                    it = tmp[i];
                    mn_burst_time = tmp[i].burst_time;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (isEqual(arr[i], it))
            {
                if (arr[i].responseFlag == true)
                {
                    /* code */
                    arr[i].firsrt_time_cpu_got = current_Time;
                    arr[i].responseFlag = false;
                }
                arr[i].arrival_time = current_Time + arr[i].cpu + arr[i].io;

                arr[i].burst_time -= arr[i].cpu;
                arr[i].burst_time = max(arr[i].burst_time, 0);
                current_Time += it.cpu;
                arr[i].spendInIo += arr[i].io;
                not_to_select_after_1_iteration = i;

                break;
            }
        }
        cout << "\n\n";
        print_arr_beforeSove(arr);
        cout << "\n\n";
    }
    cout << "\n Now Final Answer\n";

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i].exit_time = arr[i].arrival_time;
    }

    print_arr(arr);

    return 0;
}