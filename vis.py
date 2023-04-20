import matplotlib.pyplot as plt
x = []
y = []
f = open('input.txt', 'r')
f.readline()  # skip the first line (header
for row in f:
    row = row.split(' ')
    x.append(float(row[0]))
    y.append(float(row[1]))
x.append(float(x[0]))
y.append(float(y[0]))
 
fig, (ax1, ax2, ax3) = plt.subplots(1, 3)
fig.set_figheight(5)
fig.set_figwidth(15)
temp = list(range(1, len(x)))
# print(len(y))
t1 = len(y)
ax1.plot(x, y, "-o")
ox = x
oy = y
 
f.close()
f = open('output.txt', 'r')
n = int(f.readline())
t2 = n
for i in range(n):
    p = int(f.readline())
    x = []
    y = []
    for j in range(p):
        row = f.readline().split(' ')
        x.append(float(row[0]))
        y.append(float(row[1]))
    x.append(float(x[0]))
    y.append(float(y[0]))
    ax2.plot(x, y, "-o")
 
f.close()
f = open('outputAfterMerge.txt', 'r')
n = int(f.readline())
t3 = n
for i in range(n):
    p = int(f.readline())
    x = []
    y = []
    for j in range(p):
        row = f.readline().split(' ')
        x.append(float(row[0]))
        y.append(float(row[1]))
    x.append(float(x[0]))
    y.append(float(y[0]))
    ax3.plot(x, y, "-o")
 
for a, b, c in zip(ox, oy, temp):
    ax1.text(a, b, str(c), color="black", fontsize=12)
    ax2.text(a, b, str(c), color="black", fontsize=12)
    ax3.text(a, b, str(c), color="black", fontsize=12)
 
 
ax1.set_title('Original Polygon: vertices- ' + str(t1 - 1))
ax2.set_title('Polygon Decomposition: faces- ' + str(t2))
ax3.set_title('After Merging: faces- ' + str(t3))
plt.savefig("combined.png")
plt.show()