import sys

months = ["January","February","March","April","May","June","July","August","September","October","November","December"]
daysInMon = [31,28,31,30,31,30,31,31,30,31,30,31]
week = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]

def isLeap(yr):
    if (yr%4 == 0 and yr%100 != 0) or yr%400 == 0:
        return 1
    else:
        return 0

ytd = [0]*3000
ytd[0] = (365 + isLeap(1980))%7
for i in range(1,3000):
    ytd[i] = (ytd[i-1] + 365 + isLeap(i+1980))%7

for lin in sys.stdin:
    d,m,y = lin.split()

    y = int(y)
    y -= 1981
    y = y%2800
    c = (int(d) + ytd[y])%7
    
    for i in range(12):
        if (m == months[i]):
            break
        else:
            c = (c + daysInMon[i])%7

    if isLeap(y + 1981) and m != "January" and m != "February":
        c = (c + 1)%7

    print(week[c])
