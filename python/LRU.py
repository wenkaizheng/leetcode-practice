import collections 
class LRUCache:

    def __init__(self, capacity: int):
        self.map = {}
        self.deque = collections.deque([])
        self.cap = capacity

    def get(self, key: int) -> int:
         if key in self.map:
            self.deque.remove(key)
            self.deque.append(key)
            return self.map[key]
         return -1

    def put(self, key: int, value: int) -> None:
        
        if key in self.map:
           
            self.map[key] = value
            self.deque.remove(key)
            self.deque.append(key)
        else:
            if len(self.deque) >= self.cap:
                k = self.deque.popleft()
                del self.map[k]
            self.map[key] = value
            self.deque.append(key)
            


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
