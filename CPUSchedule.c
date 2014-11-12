#include<stdlib.h>

struct process{
    int process_no;
    int arrival_time;
    int cpu_burst;
};

typedef struct process process;

void FCFS(process process_list[], int no_of_processes){
    int i = 0;
    int process_no = 0, start_time = 0, end_time = 0, wait_time = 0, turn_time = 0, curr_time = 0;
    int processes_completed = 0;
    int total_wait_time = 0, total_turn_time = 0;

    printf("\n\n-------------------------First Come First Serve Scheduling-----------------------------------\n\n");
    printf("proc\tt_start\tt_end\twait_time\tturnaround_time\n");

    for(i=0;i<no_of_processes;i++){
        if(processes_completed == 0)
            start_time = process_list[i].arrival_time;
        wait_time = start_time - process_list[i].arrival_time;
        if(wait_time < 0)
            wait_time = 0;
        process_no = i+1;
        end_time = start_time + process_list[i].cpu_burst;
        turn_time = end_time - process_list[i].arrival_time;
        printf("%d\t%d\t%d\t%d\t\t%d\n", process_no, start_time, end_time, wait_time, turn_time);
        start_time = end_time;
        processes_completed++;
        total_wait_time += wait_time;
        total_turn_time += turn_time;
    }
    printf("\nAverage waiting time = %f\n", (total_wait_time/(no_of_processes * 1.0)));
    printf("Average turnaround time = %f\n\n", (total_turn_time/(no_of_processes * 1.0)));
    return;
}

void SJF(process process_list[], int no_of_processes){
    int i = 0;
    int process_no = 0, start_time = 0, end_time = 0, wait_time = 0, turn_time = 0, curr_time = 0;
    int total_wait_time = 0, total_turn_time = 0;
    int processes_completed = 0;

    printf("\n\n-----------------------------Shortest Job First Scheduling-----------------------------------\n\n");
    printf("proc\tt_start\tt_end\twait_time\tturnaround_time\n\n");

    int process_status[100];
    for(i=0;i<100;i++){
        process_status[i] = 0;
    }

    curr_time = 0;
    while(processes_completed < no_of_processes){
        int min_val = 999999;
        int index = 0;
        for(i=0;i<no_of_processes;i++){
            if(process_status[i] == 0 && process_list[i].arrival_time <= curr_time && process_list[i].cpu_burst < min_val){
                min_val = process_list[i].cpu_burst;
                index = i;
            }
        }
        process_status[index] = 1;
        process_no = index + 1;
        if(processes_completed == 0)
            start_time = process_list[index].arrival_time;
        else
            start_time = curr_time;
        end_time = start_time + process_list[index].cpu_burst;
        wait_time = start_time - process_list[index].arrival_time;
        turn_time = end_time - process_list[index].arrival_time;
        printf("%d\t%d\t%d\t%d\t\t%d\n", process_no, start_time, end_time, wait_time, turn_time);
        processes_completed++;
        curr_time = curr_time + process_list[index].cpu_burst;
        total_wait_time += wait_time;
        total_turn_time += turn_time;
    }
    printf("\nAverage waiting time = %f\n", (total_wait_time/(no_of_processes * 1.0)));
    printf("Average turnaround time = %f\n\n", (total_turn_time/(no_of_processes * 1.0)));
    return;
}

void SRJF(process process_list[], int no_of_processes){
    printf("\n\n-----------------------------------Shortest Remaining Job First Scheduling-----------------------------------\n\n");
    printf("Process\t|Turnaround Time| Waiting Time\n");

    int at[100],bt[100],rt[100],endTime,i,smallest;
    int remain=0,n,time,sum_wait=0,sum_turnaround=0;

    n = no_of_processes;
    for(i=0;i<n;i++){
        at[i] = process_list[i].arrival_time;
        bt[i] = process_list[i].cpu_burst;
        rt[i] = bt[i];
    }

    int start_time = 0, end_time = 0;
    rt[99] = 999999;

    int a[1000];
    for(i=0;i<1000;i++){
        a[i]=0;
    }

    int x = 0;
    for(time=0;remain!=n;time++){
        smallest=99;
        for(i=0;i<n;i++){
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
            {
                smallest=i;
            }
        }
        a[x] = smallest+1;
        x++;
        rt[smallest]--;
        if(rt[smallest]==0)
        {
            remain++;
            endTime=time+1;
            printf("\nP[%d]\t|\t%d\t|\t%d",smallest+1,endTime-at[smallest],endTime-bt[smallest]-at[smallest]);
            sum_wait+=endTime-bt[smallest]-at[smallest];
            sum_turnaround+=endTime-at[smallest];
        }
    }
    printf("\n\nAverage waiting time = %f\n",sum_wait*1.0/n);
    printf("Average Turnaround time = %f",sum_turnaround*1.0/5);

    i=0;
    start_time = 0;
    end_time = 0;

    printf("\n\nproc\tt_start\tt_end\n");
    time = 0;
    while(a[i]!=0){
        time++;
        if(a[i]!=a[i+1]){
            printf("%d\t%d\t%d\n", a[i], start_time, time);
            start_time = time;
        }
        i++;
    }

    return;
}

int RR(process process_list[], int no_of_processes){
    printf("\n\n-----------------------------------Round Robin Scheduling-----------------------------------\n\n");
    int i,j,n,time,remain,flag=0,ts;
    int sum_wait=0,sum_turnaround=0,at[100],bt[100],rt[100];
    n = no_of_processes;
    remain = n;

    for(i=0;i<n;i++){
        at[i] = process_list[i].arrival_time;
        bt[i] = process_list[i].cpu_burst;
        rt[i] = bt[i];
    }

    printf("Enter time slice:\n");
    scanf("%d",&ts);
    printf("Process\t|Turnaround time|waiting time\n");

    int a[1000];
    int b[1000];
    int c[1000];
    for(i=0;i<1000;i++){
        a[i] = b[i] = c[i] = 0;
    }

    int x = 0;
    for(time=0,i=0;remain!=0;){
        if(rt[i]<=ts && rt[i]>0){
            a[x] = i+1;
            b[x] = time;
            time+=rt[i];
            c[x] = time;
            x++;
            rt[i]=0;
            flag=1;
        }
        else if(rt[i]>0){
            a[x] = i+1;
            b[x] = time;
            rt[i]-=ts;
            time+=ts;
            c[x] = time;
            x++;
        }
        if(rt[i]==0 && flag==1)
        {
            remain--;
            printf("P[%d]\t|\t%d\t|\t%d\n",i+1,time-at[i],time-at[i]-bt[i]);
            sum_wait+=time-at[i]-bt[i];
            sum_turnaround+=time-at[i];
            flag=0;
        }
        if(i==n-1)
            i=0;
        else if(at[i+1]<=time)
            i++;
        else
            i=0;
        }
    printf("\nAvg sum_wait = %f\n",sum_wait*1.0/n);
    printf("Avg sum_turnaround = %f",sum_turnaround*1.0/n);

    printf("\n\nproc\tt_start\tt_end\n");
    i = 0;
    while(a[i]!=0){
        printf("%d\t%d\t%d\n", a[i], b[i], c[i]);
        i++;
    }

    return;
}

int main(){
    int i = 0;
    int no_of_processes = 0;
    process new_process_list[100];
    printf("Enter no of processes:\n");
    scanf("%d", &no_of_processes);
    while(i < no_of_processes){
        i++;
        int arrival = 0;
        int burst = 0;
        printf("Enter arrival_time for process %d:\n" , i);
        scanf("%d", &arrival);
        printf("Enter cpu_burst for process %d:\n" , i);
        scanf("%d", &burst);
        process new_process;
        new_process.process_no = i;
        new_process.arrival_time = arrival;
        new_process.cpu_burst = burst;
        new_process_list[i-1] = new_process;
    }

    FCFS(new_process_list, no_of_processes);
    SJF(new_process_list, no_of_processes);
    SRJF(new_process_list, no_of_processes);
    RR(new_process_list, no_of_processes);
    return 0;
}
