from typing import List
import collections
class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        def dfs(i):
            component.append(i)
            for j in adj_lst[i]:
                if not visited[j]:
                    visited[j] = True
                    dfs(j)
            
        n = len(s)
        adj_lst = [[] for _ in range(n)]
        for i, j in pairs:
            adj_lst[i].append(j)
            adj_lst[j].append(i)
       
        visited = [False for _ in range(n)]
        lst = list(s)
        for i in range(n):
            if not visited[i]:
                visited[i] = True
                component = []
                dfs(i)
                component.sort()
                chars = [lst[k] for k in component]
                chars.sort()
                for i in range(len(component)):
                    lst[component[i]] = chars[i]
            
        return ''.join(lst)
class Solution1(object):
    def calcEquation(self, equations, values, queries):
        """
        :type equations: List[List[str]]
        :type values: List[float]
        :type queries: List[List[str]]
        :rtype: List[float]
        """
        # Step 1. Build the Graph
        graph = collections.defaultdict(dict)
        for (x, y), val in zip(equations,values):
            graph[x][y] = val
            graph[y][x] = 1.0 / val
        print(graph)
        
        # Step 2. DFS function
        def dfs(x, y, visited ):
            # neither x not y exists
            if (x,y) in visited:
                return visited[(x,y)]
           # visited.add((x,y))
            
            # x points to y
            if y in graph[x]:
                visited[(x,y)] = graph[x][y]
                return graph[x][y]
            
            # x maybe connected to y through other nodes
            # use dfs to see if there is a path from x to y
            visited[(x,y)] = -1
            for i in graph[x]:
               # if (i,y) not in visited:
                    p = dfs(i, y, visited)
                    if  p  == -1:
                        continue
                    else:
                        visited[(x,y)] = graph[x][i] * visited[(i,y)]
                        #return graph[x][i] * temp
               
            return visited[(x,y)]
            
        # go through each of the queries and find the value
        res = []
        for query in queries:
           
            if query[0] not in graph or query[1] not in graph:
                    res.append (-1.0)
                    continue
            res.append(dfs(query[0], query[1], {}))
        return res
s = Solution()
print(s.smallestStringWithSwaps("dcab",[[0,3],[1,2],[0,2]]))

s1 = Solution1() 
print(s1.calcEquation([["a","b"],["b","c"]],[2.0,3.0],[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]))

