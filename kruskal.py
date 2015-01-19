import sys

def find(component, u):
    if not u in component:
        return u
    if component[u] != u:
        component[u] = find(component, component[u])
    return component[u]

def combine(component, rank, u, v):
    u, v = find(component, u), find(component, v)
    if rank[u] > rank[v]:
        component[v] = u
    else:
        component[u] = v
    if rank[u] == rank[v]:
        rank[v] += 1

def kruskal(edges, component, rank):
    tree = set()
    for _, u, v in sorted(edges):
        if find(component, u) != find(component, v):
            tree.add((u, v))
            combine(component, rank, u, v)
    return tree

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.stderr.write("Usage : python %s inputfile\n" % sys.argv[0])
        raise SystemExit(1)
    inputfile = sys.argv[1]
    with open(inputfile, 'r') as f:
        (num_edges, num_vertices) = [int(item) for item in f.readline().split(' ')]
        next(f)
        component = {}
        edges = []
        for line in f:
            (u, v, weight) = [int(item) for item in line.split(' ')]
            component[u] = u
            component[v] = v
            edges.append((weight, u, v))
        rank = {u: 0 for u in range(0, num_edges)}
        print kruskal(edges, component, rank)

