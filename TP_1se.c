#include <stdio.h>
#include <limits.h>
#define MAX_PROCESSES 20
/*Functions prototypes*/
void FIFO(int n, int pro[], int art[], int bt[]);
void SJF(int n, int pro[], int art[], int bt[]);
void SRT(int n, int pro[], int art[], int bt[]);
void RR(int n, int pro[], int art[], int bt[], float qt);

int main(){
	int n, i, j;
	float qt;
	int pro[MAX_PROCESSES], bt[MAX_PROCESSES], art[MAX_PROCESSES];

	printf("Enter number of processes :");
	scanf("%d", &n);
	printf("Enter processes indicators:\n");
	for(i=0;i<n;i++){
		scanf("%d", &pro[i]);
	}
	printf("Enter arraving time :\n");
	for(i=0;i<n;i++){
		printf("P%d = ", i+1);
		scanf("%d", &art[i]);
	}
	printf("Enter burst time :\n");
	for(i=0;i<n;i++){
		printf("P%d = ", i+1);
		scanf("%d", &bt[i]);
	}
	printf("Enter the quantum = ");
	scanf("%f", &qt);

	printf("\nBy FIFO:\n");
	FIFO(n, pro, art, bt);

	printf("\nBy SJF:\n");
	SJF(n, pro, art, bt);

	printf("\nBy SRT:\n");
	SRT(n, pro, art, bt);

	printf("\nBy RR:\n");
	RR(n, pro, art, bt, qt);

	return 0;
}
/*===============================*/
/*===============================*/
void FIFO(int n, int pro[], int art[], int bt[]){
	int i, j, buf, min_index;
	int  out[MAX_PROCESSES];
	float num1, num2, num3;
	float wt[MAX_PROCESSES+1], rot[MAX_PROCESSES+1], r[MAX_PROCESSES+1];

	//Sorting based on arrival time
	for(i=0;i<n-1;i++){
		min_index = i;
		for(j=i+1;j<n;j++){
			if(art[j] < art[min_index]){
				min_index = j;
			}
		}
		buf = art[i];
		art[i] = art[min_index];
		art[min_index] = buf;

		buf = bt[i];
		bt[i] = bt[min_index];
		bt[min_index] = buf;

		buf = pro[i];
		pro[i] = pro[min_index];
		pro[min_index] = buf;
	}
	//Calculate time of get out
	out[0] = art[0] + bt[0];
	for(i=1;i<n;i++){
		out[i] = out[i-1] + bt[i];
	}
	//Calculate rotation time
	for(i=0;i<n;i++){
		rot[i] = out[i] - art[i];
	}
	//Calculate waiting time
	for(i=0;i<n;i++){
		wt[i] = rot[i] - bt[i];
	}
	//Calculate effective time
	for(i=0;i<n;i++){
		r[i] = (float)bt[i] / rot[i];
	}
	/*Calculate average*/
	num1 = 0;
	num2 = 0;
	num3 = 0;
	for(i=0;i<n;i++){
		num1 = num1 + wt[i];
		num2 = num2 + rot[i];
		num3 = num3 + r[i];
	}
	wt[n] = num1/n;
	rot[n] = num2/n;
 	r[n] = num3/n;
	//Printi results
	printf("Processes\tarrival time\tTime of get out\tBurst time\tRotation\tWaiting time\tEffeciency\n");
	printf("---------\t-------------\t--------------\t----------\t--------\t------------\t--------\n");
	for(i=0;i<n;i++){
		printf("P%d\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.0f\t\t%.2f\n", pro[i], art[i], out[i], bt[i], rot[i], wt[i], r[i]);
	}
	printf("Average\t\t\t\t\t\t\t\t%.2f\t\t%.2f\t\t%.2f\n", rot[n], wt[n], r[n]);
}
/*===============================*/
/*===============================*/
void SJF(int n, int pro[], int art[], int bt[]){
	int i, j, z, k, buf, min_index, currentTime;
	int out[MAX_PROCESSES];
	float num1, num2, num3;
	float wt[MAX_PROCESSES+1], rot[MAX_PROCESSES+1], r[MAX_PROCESSES+1];

	//Sorting based on arrival time
	for(i=0;i<n-1;i++){
		min_index = i;
		for(j=i+1;j<n;j++){
			if(art[j] < art[min_index]){
				min_index = j;
			}
		}
		buf = art[i];
		art[i] = art[min_index];
		art[min_index] = buf;

		buf = bt[i];
		bt[i] = bt[min_index];
		bt[min_index] = buf;

		buf = pro[i];
		pro[i] = pro[min_index];
		pro[min_index] = buf;
	}

	currentTime = art[0];
	for(i=0;i<n;i++){
		//Select the processes they are in the queue
		j=i;
		for(k=i+1;k<n;k++){
			if(art[k] <= currentTime){
				j = k;
			}else{
				break;
			}
		}
		//Sorting the processes based on burst time
		for(k=i;k<j;k++){
			min_index = k;
			for(z=k+1;z<=j;z++){
				if(bt[z] < bt[min_index]){
					min_index = z;
				}
			}
			buf = bt[k];
			bt[k] = bt[min_index];
			bt[min_index] = buf;

			buf = art[k];
			art[k] = art[min_index];
			art[min_index] = buf;

			buf = pro[k];
			pro[k] = pro[min_index];
			pro[min_index] = buf;
		}
		//Execute the process
		/*update the current time*/ currentTime = currentTime + bt[i];
		/*Calculate time of get out*/ out[i] = currentTime;
		/*Calculate rotation time*/ rot[i] = out[i] - art[i];
	}
	//Calculate waiting time
	wt[0] = 0;
	for(i=1;i<n;i++){
		wt[i] = rot[i] - bt[i];
	}
	//Calculate effective time
	for(i=0;i<n;i++){
		r[i] = (float)bt[i] / rot[i];
	}
	//Calculate average
	num1 = 0;
	num2 = 0;
	num3 = 0;
	for(i=0;i<n;i++){
		num1 = num1 + wt[i];
		num2 = num2 + rot[i];
		num3 = num3 + r[i];
	}
	wt[n] = num1/n;
	rot[n] = num2/n;
 	r[n] = num3/n;
	//Print results
	printf("Processes\tarrival time\tTime of get out\tBurst time\tRotation\tWaiting time\tEffeciency\n");
	printf("---------\t-------------\t--------------\t----------\t--------\t------------\t--------\n");
	for(i=0;i<n;i++){
		printf("P%d\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.0f\t\t%.2f\n", pro[i], art[i], out[i], bt[i], rot[i], wt[i], r[i]);
	}
	printf("Average\t\t\t\t\t\t\t\t%.2f\t\t%.2f\t\t%.2f\n", rot[n], wt[n], r[n]);
}
/*===============================*/
/*===============================*/
void SRT(int n, int pro[], int art[], int bt[]){
	int i, j, z, k, s, b, buf, min_index, currentTime;
	int out[MAX_PROCESSES], remaining[MAX_PROCESSES], finish[MAX_PROCESSES];
	float num1, num2, num3;
	float wt[MAX_PROCESSES+1], rot[MAX_PROCESSES+1], r[MAX_PROCESSES+1];

	//Sorting based on arrival time
	for(i=0;i<n-1;i++){
		min_index = i;
		for(j=i+1;j<n;j++){
			if(art[j] < art[min_index]){
				min_index = j;
			}
		}
		buf = art[i];
		art[i] = art[min_index];
		art[min_index] = buf;

		buf = bt[i];
		bt[i] = bt[min_index];
		bt[min_index] = buf;

		buf = pro[i];
		pro[i] = pro[min_index];
		pro[min_index] = buf;
	}

	s = 0;
	for(i=0;i<n;i++){
		finish[i] = 0;
		wt[i] = 0;
		remaining[i] = bt[i];
		s = s + bt[i];
	}

	currentTime = art[0];
	for(b=1;b<=s;b++){
        int min_time = INT_MAX;
		//Finding the process that has the shortest remaining time
		for(i=0;i<n;i++){
			if(art[i] <= currentTime && finish[i] == 0 && remaining[i] < min_time){
				min_index = i;
				min_time = remaining[i];
			}
		}
		//Execute that process for one time
		remaining[min_index] = remaining[min_index] - 1;
		currentTime = currentTime + 1;
		//Check if that process has finished
		if(remaining[min_index] == 0){
			finish[min_index] = 1;
			out[min_index] = currentTime;
			rot[min_index] = out[min_index] - art[min_index];
		}
	}
	//Calculate the waiting time
	for(i=0;i<n;i++){
        wt[i] = rot[i] - bt[i];
	}
	//Calculate effective time
	for(i=0;i<n;i++){
		r[i] = (float)bt[i] / rot[i];
	}
	//Calculate average
	num1 = 0;
	num2 = 0;
	num3 = 0;
	for(i=0;i<n;i++){
		num1 = num1 + wt[i];
		num2 = num2 + rot[i];
		num3 = num3 + r[i];
	}
	wt[n] = num1/n;
	rot[n] = num2/n;
 	r[n] = num3/n;
	//Printing results
	printf("Processes\tarrival time\tTime of get out\tBurst time\tRotation\tWaiting time\tEfficiency\n");
	printf("---------\t-------------\t--------------\t----------\t--------\t------------\t--------\n");
	for(i=0;i<n;i++){
		printf("P%d\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.0f\t\t%.2f\n", pro[i], art[i], out[i], bt[i], rot[i], wt[i], r[i]);
	}
	printf("Average\t\t\t\t\t\t\t\t%.2f\t\t%.2f\t\t%.2f\n", rot[n], wt[n], r[n]);
}
/*===============================*/
/*===============================*/
void RR(int n, int pro[], int art[], int bt[], float qt){
	int i, j, k;
	float num1, num2, num3, currentTime;
	float wt[MAX_PROCESSES+1], rot[MAX_PROCESSES+1], r[MAX_PROCESSES+1], remaining[MAX_PROCESSES], out[MAX_PROCESSES];

	for(i=0;i<n;i++){
        remaining[i] = bt[i];
	}
	currentTime = 0;
	while(1){
        int end = 1;
        for(i=0;i<n;i++){
            if(art[i] > currentTime){
                continue;
            }
            if(remaining[i] > 0){
                end = 0;
                if(remaining[i] <= qt){
                    currentTime = currentTime + remaining[i];
                    remaining[i] = 0;
                    out[i] = currentTime;
                }else{
                    currentTime = currentTime + qt;
                    remaining[i] = remaining[i] - qt;
                }
            }
        }
        if(end == 1){
            break;
        }
	}
	/*Calculate rotation time*/
   for(i=0;i<n;i++){
        rot[i] = out[i] -art[i];
   }
   /*Calculate waiting time*/
   for(i=0;i<n;i++){
        wt[i] = rot[i] - bt[i];
   }
   /*Calculate efficiency and average*/
   for(i=0;i<n;i++){
        r[i] = bt[i] / rot[i];
   }
    num1 = 0;
    num2 = 0;
    num3 = 0;
    for(i=0;i<n;i++){
        num1 += wt[i];
        num2 += rot[i];
        num3 += r[i];
    }
    wt[n] = num1 / (float)n;
    rot[n] = num2 / (float)n;
    r[n] = num3 / (float)n;
    //Printing results
	printf("Processes\tArrival time\tTime of get out\tBurst time\tRotation\tWaiting time\tEfficiency\n");
	printf("---------\t-------------\t--------------\t----------\t--------\t------------\t--------\n");
	for(i=0;i<n;i++){
		printf("P%d\t\t%d\t\t%.2f\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n", pro[i], art[i], out[i], bt[i], rot[i], wt[i], r[i]);
	}
	printf("Average\t\t\t\t\t\t\t\t%.2f\t\t%.2f\t\t%.2f\n", rot[n], wt[n], r[n]);
}
