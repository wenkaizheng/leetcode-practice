class Solution:
    def decodeString(self, s: str) -> str:
        stack, curNum, curString = [], 0, ''
        for c in s:
            if c == '[':
                stack.append((curString, curNum))
                curString, curNum = '', 0
            elif c == ']':
                prevString, num = stack.pop()
                curString = prevString + num*curString
            elif c.isdigit():
                curNum = curNum*10 + int(c)
            else:
                curString += c
        return curString
class Solution1:
    def numDecodings(self, s: str) -> int:
        if len(s) == 1:
            return 1 if  0 < int(s[0]) else 0
        rc = [0]* (len(s)+1)
        rc[0] = 1
        rc[1] = rc[0] if s[0]!='0' else 0
        print(rc)
        for i in range(2,len(s)+1):
           
            if 0< int(s[i-1:i]) <= 9:
                rc[i] += rc[i-1]
            if 10<=int(s[i-2:i])<=26:
                rc[i] += rc[i-2] 
       
        return rc[-1]
        
        
class Solution2:
    def decodeAtIndex(self, s: str, k: int) -> str:
	    size = 0
	    l = len(s)
	    for i in range(l):
		    if s[i]>='a' and s[i]<='z':
			    size+=1
		    else:
			    size*=(ord(s[i])-48)

	    for i in range(l-1, -1, -1):
		    k%=size
		    if not k and s[i]>='a' and s[i]<='z':
			    return s[i]
		    if s[i]>='0' and s[i]<='9':
			    size//=(ord(s[i])-48)
		    else:
			    size-=1
s = Solution()   
s1 = Solution1()
s2 = Solution2()   
print(s.decodeString("2[abc]3[cd]ef"))
print(s1.numDecodings("226"))
print(s2.decodeAtIndex("leet2code3",10))                            