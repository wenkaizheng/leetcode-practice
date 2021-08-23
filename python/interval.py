from typing import List
import bisect
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        if intervals == []:
           return []
        rc = []
        intervals = sorted(intervals)
       # print(intervals)
        rc.append(intervals[0])
        for i in range(1,len(intervals)):
            tmp = rc.pop()
            if tmp[1] >= intervals[i][0]:
                tmp[1] = max(intervals[i][1],tmp[1])
                rc.append(tmp)
            else:
                rc.append(tmp)
                rc.append(intervals[i])
        return rc
        

class Solution1:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        result = []
        
        for interval in intervals:
			# the new interval is after the range of other interval, so we can leave the current interval baecause the new one does not overlap with it
            if interval[1] < newInterval[0]:
                result.append(interval)
            # the new interval's range is before the other, so we can add the new interval and update it to the current one
            elif interval[0] > newInterval[1]:
                result.append(newInterval)
                newInterval = interval
            # the new interval is in the range of the other interval, we have an overlap, so we must choose the min for start and max for end of interval 
            #elif interval[1] >= newInterval[0] or interval[0] <= newInterval[1]:
            else:
                newInterval[0] = min(interval[0], newInterval[0])
                newInterval[1] = max(newInterval[1], interval[1])

        
        result.append(newInterval); 
        return result


class Solution2:
  def findRightInterval(self, intervals):
    l = sorted((e[0], i) for i, e in enumerate(intervals))
    res = []
    for e in intervals:
        r = bisect.bisect_left(l, (e[1],))
        res.append(l[r][1] if r < len(l) else -1)
    return res
                
class Solution3:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        if not intervals: return 0
        intervals.sort(key=lambda x: x[0])  # sort on start time
        prevEnd, cnt = intervals[0][1], 0
        for x in intervals[1:]:
            if x[0] < prevEnd:  # find overlapping interval
                cnt += 1
                prevEnd = min(prevEnd, x[1])  # erase the one with larger end time
            else:
                prevEnd = x[1]   # update end time
        return cnt

s = Solution()
print(s.merge([[1,3],[2,6],[8,10],[15,18]]))

s1 = Solution1()
print(s1.insert([[1,2],[3,5],[6,7],[8,10],[12,16]],[4,8]))

s2 = Solution2()
print(s2.findRightInterval([[1,4],[2,3],[3,4]]))

s3 = Solution3()
print(s3.eraseOverlapIntervals([[1,2],[2,3],[3,4],[1,3]]))