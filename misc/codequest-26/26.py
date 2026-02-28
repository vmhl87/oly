done = False

def test():
    global done

    n = int(input())

    edges = []
    m = 1

    for i in range(n):
        v = [int(x) for x in input().split()]
        m = max(m, v[0])
        for j in range(1, len(v)):
            edges.append((v[0], v[j]))
            m = max(m, v[j])

    adj = [[] for i in range(m+1)]

    for e in edges:
        adj[e[0]].append(e[1])

    count = [0 for i in range(m+1)]

    faults = [int(x) for x in input().split()]

    for f in faults: count[f] += 1

    done = False

    def dfs(i):
        global done

        for j in adj[i]:
            dfs(j)
            count[i] += count[j]

        if count[i] == len(faults):
            if not done:
                print(i)
                done = True
    
    dfs(1)

t = int(input())
for i in range(t): test()
