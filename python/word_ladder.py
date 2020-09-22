from typing import List
from collections import defaultdict 
from collections import deque
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList or not endWord or not beginWord or not wordList:
            return 0
        size = len(beginWord)
        lookup = defaultdict(list)                                  
        for word in wordList:                                       
            for i in range(size):
                lookup[word[:i] + "*" + word[i+1:]].append(word)    
        print(lookup)                                       
        queue =  deque([(beginWord, 1)])                
        visited = {beginWord: True}
        
        while(queue):
            currWord, pathLength = queue.popleft()
            print(currWord)
            for i in range(size):
                possibleWordPattern = currWord[:i] + "*" + currWord[i+1:]
                
                for word in lookup[possibleWordPattern]:
                    
                    if(currWord == word):
                        continue
                    
                    if(word == endWord):
                        return pathLength + 1
                    
                    if(word not in visited):
                        visited[word] = True
                        queue.append((word, pathLength + 1))
        return 0
s = Solution()
print(s.ladderLength("hit","cog",["hot","dot","dog","lot","log","cog"]))
