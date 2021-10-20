import math
import matplotlib.pyplot as plt

N=2500
F0=0
B=0
O=0.8
h=0.02
V0=0
w=1
x0=1

b = [0 for i in range(N)] 
d0 = [0 for i in range(N)] 
d1 = [0 for i in range(N)]
d2 = [0 for i in range(N)]

xs = [0 for i in range(N)] 
xn = [0 for i in range(N)]

a1 = 1
a2 = w*w * h*h -2 - B*h
a3 = 1 + B*h

b[0]=1
b[1]=0

d0[0]=1
d0[1]=1

d1[0]=0
d1[1]=-1

d2[0]=0
d2[1]=0

xs[0] = 1
xs[1] = 0

xn[0] = x0
xn[1] = 0



for i in range(2,N):
	b[i] = F0 * math.sin(O * (h * i)) * h*h
	d0[i] = a3
	d1[i] = a2
	d2[i] = a1

for q in range(N):
	qs = 0
	qn = 0
	xn[0] = 1/d0[i] *b[0]
	xn[1] = (1 / d0[i])* (b[1] - d1[1]*xn[0])
	
	for i in range(2,N):
		xn[i] = (1 / d0[i]) * (b[i] - d1[i] * xn[i-1] - d2[i] * xn[i-2])
		
	for i in range(0,N):
		qs += xs[i]*xs[i]
		qn += xn[i]*xn[i]

	for i in range(0,N):
		 xs[i]=xn[i]

t = [0 for i in range(N)] 
for i in range(N):
	t[i]=i*h

plt.plot(t,xn)
plt.title("Podpunkt 3")
plt.xlabel("t")
plt.ylabel("xn")
plt.show()