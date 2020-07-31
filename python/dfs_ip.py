from typing import List
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        def dfs(s, sub, ips, ip):
            if sub == 4:                                        # should be 4 parts
                if s == '':
                    ips.append(ip[1:])                          # remove first '.'
                return
            for i in range(1, 4):                               # the three ifs' order cannot be changed!
                if i <= len(s):                                 # if i > len(s), s[:i] will make false!!!!
                    if int(s[:i]) <= 255:
                        dfs(s[i:], sub+1, ips, ip+'.'+s[:i])
                    if s[0] == '0': break                       # make sure that res just can be '0.0.0.0' and remove like '00'
        ips = []
        dfs(s, 0, ips, '')
        return ips
s = Solution()
rc = s.restoreIpAddresses("25525511135")
for ip in rc:
    print(ip)
