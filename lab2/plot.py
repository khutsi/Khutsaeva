import datetime
import matplotlib.pyplot as plt
data = []
x = []
y = []
with open('forplot') as file:
    for i in file.readlines():
        splitted = i.split()
        datestr = splitted[0]+' '+splitted[1]
        date = datetime.datetime.strptime(datestr, '%Y-%m-%d %H:%M:%S.%f') # 2020-02-25 12:29:46.040
        data.append((date,int(splitted[2])))
data.sort(key=lambda x: x[0])
x = [i[0] for i in data]
a = 0
for i in data:
    a += i[1]
    y.append(a/128)
(fig, ax) = plt.subplots(1, 1)
ax.plot(x, y)
for n, label in enumerate(ax.xaxis.get_ticklabels()):
    if n % 2 != 0:
        label.set_visible(False)
ax.yaxis.set_major_formatter(plt.FormatStrFormatter('%d'))
plt.ylabel('Kbit')
plt.savefig('plot.png')
