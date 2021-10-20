# "Numerical Recipes" ludcmp() C code on page 46 translated into Python
# I make it as simple as possible, disregard efficiency.
# Here a is a list of list, n is integer (size of the matrix)
# index is a list, and d is also a list of size 1
# Python list index starts from 0.  So matrix index is from 0 to n-1.
#
import math
from numpy.linalg import norm

def ludcmp(a, n, indx, d):
    d[0] = 1.0
    
    vv=indx.copy()
    for i in range(0,n):
        big = 0.0
        for j in range(0,n):
            temp = math.fabs(a[i][j])
            if (temp > big):
                big = temp
        vv[i]=1.0/big
   
    for j in range(0,n):
        
        big = 0.0
        for i in range(0,n):           
            if(i<j):
                l = i
            else:
                l = j
            sum = a[i][j]    
            for k in range(0,l):
                sum -= a[i][k]*a[k][j]
            
            a[i][j] = sum
           
            if(i>=j):
                dum = vv[i]*math.fabs(sum)
                if (dum >= big):
                    big = dum
                    imax = i
            
        if (j != imax):
            dum = a[imax]
            a[imax] = a[j]
            a[j] = dum
            d[0] = - d[0]
            vv[imax] = vv[j]
        
        indx[j] = imax
        dum = 1.0/a[j][j]
        for i in range(j+1,n):
            a[i][j] *= dum

def lubksb(a, n, indx, b):
    ii = -1
    
    for i in range(0,n):
        ip = indx[i]
        sum = b[ip]
        b[ip] = b[i]
        if(ii != -1):
            for j in range(ii,i):
                sum -= a[i][j]*b[j]
        elif(sum != 0):
            ii = i
        b[i] = sum
    

    for i in range(n-1,-1,-1):
        sum = b[i]
        for j in range(i+1,n):
            sum -= a[i][j]*b[j]
        b[i] = sum/a[i][i]





def normal(M,N):
	q = abs(M[0][0])
	for i in range (N):
		for j in range(N):
			if (abs(M[i][j])>=q):
				q=abs(M[i][j])
	return q


N = 4
f = open("Wyniki.txt",'w')
A = [[0 for i in range(N)] for m in range(N)]
A_copy = [[0 for i in range(N)] for m in range(N)]
A_od = [[0 for i in range(N)] for m in range(N)]
A_copy2 = [[0 for i in range(N)] for m in range(N)]
o=0

for i in range (N):
	for j in range (N):
		A[i][j]=1/(i+j+o+2)
		A_copy[i][j]=1/(i+j+o+2)
		A_copy2[i][j]=1/(i+j+o+2)
print('Macierz A')
f.write('Macierz A')
f.write('\n')
for i in A:
	print(i)
	f.write(str(i))
	f.write('\n')

indx = [0 for m in range(0, N)]
d = [0 for m in range(0, N)]
print()

# zad1
f.write('\n')
f.write('zad1:')
f.write('\n')
print('zad1:')
ludcmp(A,N,indx,d)
f.write('Macierz LU')
f.write('\n')
print('Macierz LU')
for i in A:
	print(i)
	f.write(str(i))
	f.write('\n')
f.write('\n')
f.write('Macierz U: \n')
for i in range(N):
	for j in range(N):
		if i<=j:
			f.write(str(A[i][j]))
			f.write(" ")
		else:
			f.write('0 ')
	f.write('\n')
f.write('Macierz L: \n')
for i in range(N):
	for j in range(N):
		
		if i>j:
			f.write(str(A[i][j]))
			f.write(" ")
		else:
			if i==j:
				f.write('1 ')
			else:
				f.write('0 ')
	f.write('\n')
print()

# zad2
f.write('zad2:')
f.write('\n')
print('zad2:')
dat_A=1.0
for i in range(N):
	dat_A = dat_A * A[i][i]
f.write('wyznacznik A=')
print('wyznacznik A')
print(dat_A)
f.write(str(dat_A))
f.write('\n')
print()

# zad3
print('zad3:')
f.write('zad3:')
f.write('\n')
b = [0 for m in range(0, N)]
for i in range(N):
	# zerowanie wektora b i wstawianie 1 naodpowiednie miejsce
	for j in range(N):
		b[j]= 0.0

	b[i]=1.0 
	lubksb(A,N,indx,b)
	for q in range(N):
		A_od[q][i]=b[q]
f.write('Macierz odwrota\n')
for i in A_od:
	print(i)
	f.write(str(i))
	f.write('\n')
# zad 4
print("zad4:")
f.write('zad4:')
f.write('\n')
f.write('A * A_odwrotna\n')
w_i = [[0 for i in range(N)] for m in range(N)]
for i in range(N):
	for j in range(N):
		for q in range(N):
			w_i[i][j]+=A_copy[i][q]*A_od[q][j]
for i in  w_i:
	print(i)
	f.write(str(i))
	f.write('\n')
# zad 5
print("zad5")
f.write("zad5")
f.write('\n')
nor_A = normal(A_copy2,N)
print(nor_A)
f.write('norma_A = ')
f.write(str(nor_A))
f.write('\n')

nor_A_od =normal(A_od,N)
print(nor_A_od)
f.write('norma_A_odwrotna = ')
f.write(str(nor_A_od))
f.write('\n')

wsk= nor_A *  nor_A_od
f.write('wsk_A_i_A_odwr = ')
print(wsk)
f.write(str(wsk))
f.close()