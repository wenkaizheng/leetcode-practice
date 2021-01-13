import collections
class LFUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity                                        
        self.di = {}                                                    
        self.lfu = defaultdict(OrderedDict)                            
        self.least = 0                                                  
        
    def get(self, key: int) -> int:
        return self.update(key) if key in self.di else -1      
    def update(self, key: int , value = None) -> int:
        poz = self.di[key] + 1                                         
        v = self.lfu[poz - 1].pop(key)                                   
        if value is not None:                                           
            v = value                                                    
        self.lfu[poz][key], self.di[key] = v, poz                        
        if not self.lfu[poz - 1] and self.least == poz - 1:              
            self.least += 1
        return self.lfu[poz][key]        

    def put(self, key: int, value: int) -> None:
         
        if not self.capacity: return                                     
        if key in self.di: self.update(key, value)                       
        else:                                                           
            if len(self.di) == self.capacity:                            
                del self.di[self.lfu[self.least].popitem(last=False)[0]] 
            self.lfu[1][key] = value                                     
            self.di[key] = 1
            self.least = 1 
