#!/env/bin/usr python3

def lista(n):
    lst = []
    for i in range(n):
        lst.append(i+1)
    return lst

def permutar (arr, inicio, fim):
    if inicio == fim:
        print arr
        return

    permutar (arr, inicio+1, fim)

    for i in range(inicio, n):
        if (arr[inicio] == arr[i]): continue
        trocar(arr, inicio, i)
        permutar(arr, inicio+1, fim)
        trocar(arr, inicio, i)

def trocar (n, i, j):
    temp = arr[i]
    arr[i] = arr[j]
    arr[j] = temp

n = input("Defina um N: ")

    arr = lista(n)

permutar(arr, 0, n-1) 
