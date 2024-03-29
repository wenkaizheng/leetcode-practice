class Solution:
    def addOperators(self, num: 'str', target: 'int') -> 'List[str]':

        N = len(num)
        answers = []
        def recurse(index, prev_operand, current_operand, value, string):

            # Done processing all the digits in num
            #print(current_operand)
            if index == N:

                # If the final value == target expected AND
                # no operand is left unprocessed
                if value == target and current_operand == 0:
                    answers.append("".join(string[1:]))
                return

            # Extending the current operand by one digit
            current_operand = current_operand*10 + int(num[index])
            str_op = str(current_operand)

            # To avoid cases where we have 1 + 05 or 1 * 05 since 05 won't be a
            # valid operand. Hence this check
            if current_operand > 0:

                # NO OP recursion
               # print("no op",prev_operand,current_operand,value,string)
                recurse(index + 1, prev_operand, current_operand, value, string)

            # ADDITION
            string.append('+'); string.append(str_op)
           # print("add",prev_operand,current_operand,value,string)
            recurse(index + 1, current_operand, 0, value + current_operand, string)
            string.pop();string.pop()

            # Can subtract or multiply only if there are some previous operands
            if string:

                # SUBTRACTION
                string.append('-'); string.append(str_op)
               # print("sub",prev_operand,current_operand,value,string)
                recurse(index + 1, -current_operand, 0, value - current_operand, string)
                string.pop();string.pop()

                # MULTIPLICATION
                string.append('*'); string.append(str_op)
               # print(value,prev_operand)
                #print("mul",prev_operand,current_operand,value,string)
                recurse(index + 1, current_operand * prev_operand, 0, value - prev_operand + (current_operand * prev_operand), string)
                string.pop();string.pop()

                #DIVISION
                if current_operand == 0:
                    return 
                string.append('/'); string.append(str_op)
               # print(value,prev_operand)
               # print("div",prev_operand,current_operand,value,string)
                recurse(index + 1, prev_operand / current_operand, 0, value - prev_operand + (prev_operand / current_operand), string)
                string.pop();string.pop()
        recurse(0, 0, 0, 0, [])    
        return answers

class Solution1:
    def addOperators(self, num: 'str', target: 'int') -> 'List[str]':

        N = len(num)
        answers = []
        def recurse(index, prev_operand, value, string):

            # Done processing all the digits in num
            
            if index == N:

                # If the final value == target expected AND
                # no operand is left unprocessed
                if value == target:
                    answers.append("".join(string[1:]))
                return

            # Extending the current operand by one digit
            current_operand = int(num[index])
            str_op = str(current_operand)

        

            # ADDITION
            string.append('+'); string.append(str_op)
            #print("add",prev_operand,current_operand,value,string)
            recurse(index + 1, current_operand, value + current_operand, string)
            string.pop();string.pop()

            # Can subtract or multiply only if there are some previous operands
            if string:

                # SUBTRACTION
                string.append('-'); string.append(str_op)
                #print("sub",prev_operand,current_operand,value,string)
                recurse(index + 1, -current_operand, value - current_operand, string)
                string.pop();string.pop()

                # MULTIPLICATION
                string.append('*'); string.append(str_op)
               # print(value,prev_operand)
                #print("mul",prev_operand,current_operand,value,string)
                recurse(index + 1, current_operand * prev_operand, value - prev_operand + (current_operand * prev_operand), string)
                string.pop();string.pop()

                if current_operand == 0:
                    return 
                string.append('/'); string.append(str_op)
               # print(value,prev_operand)
                #print("div",prev_operand,current_operand,value,string)
                #print(value - prev_operand + (prev_operand / current_operand))
                recurse(index + 1, prev_operand / current_operand, value - prev_operand + (prev_operand / current_operand), string)
                string.pop();string.pop()
        recurse(0, 0, 0, [])    
        return answers
s = Solution()
print(s.addOperators("1234",46))
print(s.addOperators("1234",12-3/4))
s = Solution1()
print(s.addOperators("1234",46))
print(s.addOperators("155",1))
